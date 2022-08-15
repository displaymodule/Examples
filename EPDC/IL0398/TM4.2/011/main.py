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
import epd4_2
import Image
import ImageFont
import ImageDraw
COLORED = 1
UNCOLORED = 0

def main():
	print("Init epd ...")
	epd = epd4_2.EPD()
	epd.init()
	frame_black = [0xFF] * (epd.width * epd.height / 8)
	frame_red = [0xFF] * (epd.width * epd.height / 8)
	print("load pictures to the buffer")
	frame_red = epd.get_frame_buffer(Image.open('gray.bmp'))
	print("write strings to the buffer")
	epd.draw_frame(frame_black, frame_red)
	print("display...")
	print("OK! Let's goto sleep mode")
	epd.sleep()


if __name__ == '__main__':
    main()

