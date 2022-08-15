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
import epd4_2c
import Image
import ImageFont
import ImageDraw
COLORED = 1
UNCOLORED = 0

def main():
	print("Init epd ...")
	epd = epd4_2c.EPD()
	epd.init()
	print("clear the frame buffer")
	frame_black = [0xFF] * (epd.width * epd.height / 8)
	frame_red = [0xFF] * (epd.width * epd.height / 8)
	print("load pictures to the buffer")
	frame_black = epd.get_frame_buffer(Image.open('black.bmp'))
	frame_red = epd.get_frame_buffer(Image.open('red.bmp'))
	print("write strings to the buffer")
	font = ImageFont.truetype('/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf', 48)
	font2 = ImageFont.truetype('/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf', 24)
	#epd.set_rotate(epd4_2c.ROTATE_0)
	epd.draw_string_at(frame_black, 20, 20, "Fresh", font, COLORED)
	epd.draw_string_at(frame_red, 350, 250, "/kg", font2, COLORED)
	epd.draw_string_at(frame_black, 20, 270, "www.displaymodule.com", font2, COLORED)
	print("display...")
	epd.draw_frame(frame_black, frame_red)
	print("OK! Let's goto sleep mode")
	epd.sleep()


if __name__ == '__main__':
    main()

