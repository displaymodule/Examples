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
import epd7c
import Image
import ImageFont
import ImageDraw
COLORED = 1
UNCOLORED = 0

def main():
	print("Init epd ...")
	epd = epd7c.EPD()
	epd.init()
	
	print("clear the frame buffer")
	frame_black = [0xFF] * (epd.width * epd.height / 8)
	frame_red = [0xFF] * (epd.width * epd.height / 8)
	print("load pictures to the buffer")
	frame_black = epd.get_frame_buffer(Image.open('horse.bmp'))
	frame_red = epd.get_frame_buffer(Image.open('DMLOGO.bmp'))
	print("write strings to the buffer")
	font1 = ImageFont.truetype('/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf', 20)
	font2 = ImageFont.truetype('/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf', 32)
	epd.set_rotate(epd7c.ROTATE_0)
	epd.draw_string_at(frame_red, 490, 260, "It's time", font1, COLORED)
        epd.draw_string_at(frame_red, 450, 300, "to display your IDEA", font1, COLORED)
        epd.draw_string_at(frame_red, 500, 340, "IDEA", font2, COLORED)
	print("display...")
	epd.draw_frame(frame_black, frame_red)
	print("OK! Let's goto sleep mode")
	epd.sleep()


if __name__ == '__main__':
    main()

