##/**********************************************************************************************
## Copyright (c) 2018 DisplayModule. All rights reserved.
##
## Redistribution and use of this source code, part of this source code or any compiled binary
## based on this source code is permitted as long as the above copyright notice and following
## disclaimer is retained.
##
## DISCLAIMER:
## THIS SOFTWARE IS SUPPLIED "AS IS" WITHOUT ANY WARRANTIES AND SUPPORT. DISPLAYMODULE ASSUMES
## NO RESPONSIBILITY OR LIABILITY FOR THE USE OF THE SOFTWARE.
## ********************************************************************************************/
import epdPi
import Image
import ImageDraw
import ImageFont
import RPi.GPIO as GPIO

# resolution
EPD_WIDTH       = 640
EPD_HEIGHT      = 384

# commands
PANEL_SETTING                               = 0x00
POWER_SETTING                               = 0x01
POWER_OFF                                   = 0x02
POWER_OFF_SEQUENCE_SETTING                  = 0x03
POWER_ON                                    = 0x04
POWER_ON_MEASURE                            = 0x05
BOOSTER_SOFT_START                          = 0x06
DEEP_SLEEP                                  = 0x07
DATA_START_TRANSMISSION_1                   = 0x10
DATA_STOP                                   = 0x11
DISPLAY_REFRESH                             = 0x12
IMAGE_PROCESS                               = 0x13
LUT_FOR_VCOM                                = 0x20
LUT_BLUE                                    = 0x21
LUT_WHITE                                   = 0x22
LUT_GRAY_1                                  = 0x23
LUT_GRAY_2                                  = 0x24
LUT_RED_0                                   = 0x25
LUT_RED_1                                   = 0x26
LUT_RED_2                                   = 0x27
LUT_RED_3                                   = 0x28
LUT_XON                                     = 0x29
PLL_CONTROL                                 = 0x30
TEMPERATURE_SENSOR_COMMAND                  = 0x40
TEMPERATURE_CALIBRATION                     = 0x41
TEMPERATURE_SENSOR_WRITE                    = 0x42
TEMPERATURE_SENSOR_READ                     = 0x43
VCOM_AND_DATA_INTERVAL_SETTING              = 0x50
LOW_POWER_DETECTION                         = 0x51
TCON_SETTING                                = 0x60
TCON_RESOLUTION                             = 0x61
SPI_FLASH_CONTROL                           = 0x65
REVISION                                    = 0x70
GET_STATUS                                  = 0x71
AUTO_MEASUREMENT_VCOM                       = 0x80
READ_VCOM_VALUE                             = 0x81
VCM_DC_SETTING                              = 0x82

# orientation
ROTATE_0                                    = 0
ROTATE_90                                   = 1
ROTATE_180                                  = 2
ROTATE_270                                  = 3

class EPD:
    def __init__(self):
        self.reset_pin = epdPi.RST_PIN
        self.dc_pin = epdPi.DC_PIN
        self.busy_pin = epdPi.BUSY_PIN
        self.width = EPD_WIDTH
        self.height = EPD_HEIGHT
        self.rotate = ROTATE_0

    def digital_write(self, pin, value):
        epdPi.epd_digital_write(pin, value)

    def digital_read(self, pin):
        return epdPi.epd_digital_read(pin)

    def delay_ms(self, delaytime):
        epdPi.epd_delay_ms(delaytime)

    def send_command(self, command):
        self.digital_write(self.dc_pin, GPIO.LOW)

        epdPi.spi_transfer([command])

    def send_data(self, data):
        self.digital_write(self.dc_pin, GPIO.HIGH)
        # the parameter type is list but not int
        # so use [data] instead of data
        epdPi.spi_transfer([data])

    def init(self):
        if (epdPi.epd_init() != 0):
            return -1
        self.reset()
        self.send_command(POWER_SETTING)
        self.send_data(0x37)
        self.send_data(0x00)
        self.send_command(PANEL_SETTING)
        self.send_data(0xCF)
        self.send_data(0x08)
        self.send_command(BOOSTER_SOFT_START)
        self.send_data(0xc7)
        self.send_data(0xcc)
        self.send_data(0x28)
        self.send_command(POWER_ON)
        self.wait_until_idle()
        self.send_command(PLL_CONTROL)
        self.send_data(0x3c)
        self.send_command(TEMPERATURE_CALIBRATION)
        self.send_data(0x00)
        self.send_command(VCOM_AND_DATA_INTERVAL_SETTING)
        self.send_data(0x77)
        self.send_command(TCON_SETTING)
        self.send_data(0x22)
        self.send_command(TCON_RESOLUTION)
        self.send_data(0x02)     #source 640
        self.send_data(0x80)
        self.send_data(0x01)     #gate 384
        self.send_data(0x80)
        self.send_command(VCM_DC_SETTING)
        self.send_data(0x1E)      #decide by LUT file
        self.send_command(0xe5)           #FLASH MODE
        self.send_data(0x03)

    def wait_until_idle(self):
        while(self.digital_read(self.busy_pin) == 0):      # 0: busy, 1: idle
            self.delay_ms(100)

    def reset(self):
        self.digital_write(self.reset_pin, GPIO.LOW)         # reset
        self.delay_ms(200)
        self.digital_write(self.reset_pin, GPIO.HIGH)
        self.delay_ms(200)

    def get_frame_buffer(self, image):
        buf = [0xFF] * (self.width * self.height / 8)

        image_monocolor = image.convert('1')
        imwidth, imheight = image_monocolor.size
        if imwidth != self.width or imheight != self.height:
            raise ValueError('Image must be same dimensions as display \
                ({0}x{1}).' .format(self.width, self.height))

        pixels = image_monocolor.load()
        for y in range(self.height):
            for x in range(self.width):
                if pixels[x, y] == 0:
                    buf[(x + y * self.width) / 8] &= ~(0x80 >> (x % 8))
        return buf

    def draw_frame(self, frame_buffer_black, frame_buffer_red):
        self.send_command(DATA_START_TRANSMISSION_1)
        for i in range(0, self.width / 8 * self.height):
            temp1 = frame_buffer_black[i]
            temp2 = frame_buffer_red[i]
            j = 0
            while (j < 8):
                if ((temp2 & 0x80) == 0x00):
                    temp3 = 0x04                #red
                elif ((temp1 & 0x80) == 0x00):
                    temp3 = 0x00                #black
                else:
                    temp3 = 0x03                #white
					
                temp3 = (temp3 << 4) & 0xFF
                temp1 = (temp1 << 1) & 0xFF
                temp2 = (temp2 << 1) & 0xFF
                j += 1
                if((temp2 & 0x80) == 0x00):
                    temp3 |= 0x04              #red
                elif ((temp1 & 0x80) == 0x00):
                    temp3 |= 0x00              #black
                else:
                    temp3 |= 0x03              #white
                temp1 = (temp1 << 1) & 0xFF
                temp2 = (temp2 << 1) & 0xFF
                self.send_data(temp3)
                j += 1
        self.send_command(DISPLAY_REFRESH)
        self.delay_ms(100)
        self.wait_until_idle()

    def sleep(self):
        self.send_command(POWER_OFF) 
        self.send_data(0x37)
        self.send_command(DEEP_SLEEP)        
        self.send_data(0xA5)        
 

    def set_rotate(self, rotate):
        if (rotate == ROTATE_0):
            self.rotate = ROTATE_0
            self.width = EPD_WIDTH
            self.height = EPD_HEIGHT
        elif (rotate == ROTATE_90): 
            self.rotate = ROTATE_90
            self.width = EPD_HEIGHT
            self.height = EPD_WIDTH
        elif (rotate == ROTATE_180): 
            self.rotate = ROTATE_180
            self.width = EPD_WIDTH
            self.height = EPD_HEIGHT
        elif (rotate == ROTATE_270): 
            self.rotate = ROTATE_270
            self.width = EPD_HEIGHT
            self.height = EPD_WIDTH

    def set_pixel(self, frame_buffer, x, y, colored):
        if (x < 0 or x >= self.width or y < 0 or y >= self.height):
            return
        if (self.rotate == ROTATE_0):
            self.set_absolute_pixel(frame_buffer, x, y, colored)
        elif (self.rotate == ROTATE_90):
            point_temp = x
            x = EPD_WIDTH - y
            y = point_temp
            self.set_absolute_pixel(frame_buffer, x, y, colored)
        elif (self.rotate == ROTATE_180):
            x = EPD_WIDTH - x
            y = EPD_HEIGHT- y
            self.set_absolute_pixel(frame_buffer, x, y, colored)
        elif (self.rotate == ROTATE_270):
            point_temp = x
            x = y
            y = EPD_HEIGHT - point_temp
            self.set_absolute_pixel(frame_buffer, x, y, colored)
    
    def set_absolute_pixel(self, frame_buffer, x, y, colored):

        if (x < 0 or x >= EPD_WIDTH or y < 0 or y >= EPD_HEIGHT):
            return
        if (colored):
            frame_buffer[(x + y * EPD_WIDTH) / 8] &= ~(0x80 >> (x % 8))
        else:
            frame_buffer[(x + y * EPD_WIDTH) / 8] |= 0x80 >> (x % 8)

    def draw_string_at(self, frame_buffer, x, y, text, font, colored):
        image = Image.new('1', (self.width, self.height))
        draw = ImageDraw.Draw(image)
        draw.text((x, y), text, font = font, fill = 255)

        pixels = image.load()
        for y in range(self.height):
            for x in range(self.width):

                if pixels[x, y] != 0:
                    self.set_pixel(frame_buffer, x, y, colored)

    def draw_line(self, frame_buffer, x0, y0, x1, y1, colored):
        # Bresenham algorithm
        dx = abs(x1 - x0)
        sx = 1 if x0 < x1 else -1
        dy = -abs(y1 - y0)
        sy = 1 if y0 < y1 else -1
        err = dx + dy
        while((x0 != x1) and (y0 != y1)):
            self.set_pixel(frame_buffer, x0, y0 , colored)
            if (2 * err >= dy):
                err += dy
                x0 += sx
            if (2 * err <= dx):
                err += dx
                y0 += sy

    def draw_horizontal_line(self, frame_buffer, x, y, width, colored):
        for i in range(x, x + width):
            self.set_pixel(frame_buffer, i, y, colored)

    def draw_vertical_line(self, frame_buffer, x, y, height, colored):
        for i in range(y, y + height):
            self.set_pixel(frame_buffer, x, i, colored)

    def draw_rectangle(self, frame_buffer, x0, y0, x1, y1, colored):
        min_x = x0 if x1 > x0 else x1
        max_x = x1 if x1 > x0 else x0
        min_y = y0 if y1 > y0 else y1
        max_y = y1 if y1 > y0 else y0
        self.draw_horizontal_line(frame_buffer, min_x, min_y, max_x - min_x + 1, colored)
        self.draw_horizontal_line(frame_buffer, min_x, max_y, max_x - min_x + 1, colored)
        self.draw_vertical_line(frame_buffer, min_x, min_y, max_y - min_y + 1, colored)
        self.draw_vertical_line(frame_buffer, max_x, min_y, max_y - min_y + 1, colored)

    def draw_filled_rectangle(self, frame_buffer, x0, y0, x1, y1, colored):
        min_x = x0 if x1 > x0 else x1
        max_x = x1 if x1 > x0 else x0
        min_y = y0 if y1 > y0 else y1
        max_y = y1 if y1 > y0 else y0
        for i in range(min_x, max_x + 1):
            self.draw_vertical_line(frame_buffer, i, min_y, max_y - min_y + 1, colored)

    def draw_circle(self, frame_buffer, x, y, radius, colored):
        # Bresenham algorithm
        x_pos = -radius
        y_pos = 0
        err = 2 - 2 * radius
        if (x >= self.width or y >= self.height):
            return
        while True:
            self.set_pixel(frame_buffer, x - x_pos, y + y_pos, colored)
            self.set_pixel(frame_buffer, x + x_pos, y + y_pos, colored)
            self.set_pixel(frame_buffer, x + x_pos, y - y_pos, colored)
            self.set_pixel(frame_buffer, x - x_pos, y - y_pos, colored)
            e2 = err
            if (e2 <= y_pos):
                y_pos += 1
                err += y_pos * 2 + 1
                if(-x_pos == y_pos and e2 <= x_pos):
                    e2 = 0
            if (e2 > x_pos):
                x_pos += 1
                err += x_pos * 2 + 1
            if x_pos > 0:
                break

    def draw_filled_circle(self, frame_buffer, x, y, radius, colored):
        # Bresenham algorithm
        x_pos = -radius
        y_pos = 0
        err = 2 - 2 * radius
        if (x >= self.width or y >= self.height):
            return
        while True:
            self.set_pixel(frame_buffer, x - x_pos, y + y_pos, colored)
            self.set_pixel(frame_buffer, x + x_pos, y + y_pos, colored)
            self.set_pixel(frame_buffer, x + x_pos, y - y_pos, colored)
            self.set_pixel(frame_buffer, x - x_pos, y - y_pos, colored)
            self.draw_horizontal_line(frame_buffer, x + x_pos, y + y_pos, 2 * (-x_pos) + 1, colored)
            self.draw_horizontal_line(frame_buffer, x + x_pos, y - y_pos, 2 * (-x_pos) + 1, colored)
            e2 = err
            if (e2 <= y_pos):
                y_pos += 1
                err += y_pos * 2 + 1
                if(-x_pos == y_pos and e2 <= x_pos):
                    e2 = 0
            if (e2 > x_pos):
                x_pos  += 1
                err += x_pos * 2 + 1
            if x_pos > 0:
                break

### END OF FILE ###
