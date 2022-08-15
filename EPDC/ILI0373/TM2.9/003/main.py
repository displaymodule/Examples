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
import epd2_9c
import Image
import ImageFont
import ImageDraw
COLORED = 1
UNCOLORED = 0

def main():
	print("Init epd ...")
	epd = epd2_9c.EPD()
	epd.init()
	
	print("clear the frame buffer")
	frame_black = [0xFF] * (epd.width * epd.height / 8)
	frame_red = [0xFF] * (epd.width * epd.height / 8)
	print("load pictures to the buffer")
	frame_black = epd.get_frame_buffer(Image.open('dm_qrcode.bmp'))
	frame_red = epd.get_frame_buffer(Image.open('dm_logo.bmp'))
	print("write strings to the buffer")
	font = ImageFont.truetype('/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf', 10)
	epd.set_rotate(epd2_9c.ROTATE_90)
	epd.draw_string_at(frame_red, 150, 50, "www.displaymodule.com", font, COLORED)
	print("display...")
	epd.draw_frame(frame_black, frame_red)
	print("OK! Let's goto sleep mode")
	epd.sleep()


if __name__ == '__main__':
    main()

