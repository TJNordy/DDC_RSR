/*
  DDCANJOMOUSE.cpp

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "DDCANJOMOUSE.h"

#if defined(_USING_DYNAMIC_HID)

static const uint8_t _hidReportDescriptor[] PROGMEM = {

  //  JoyMouse
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)  // 54
    0x09, 0x02,                    // USAGE (Mouse)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x85, 0x01,                    //     REPORT_ID (1)
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
    0x29, 0x03,                    //     USAGE_MAXIMUM (Button 3)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x75, 0x05,                    //     REPORT_SIZE (5)
    0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //     USAGE (X)
    0x09, 0x31,                    //     USAGE (Y)
    0x09, 0x38,                    //     USAGE (Wheel)
    0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x81, 0x06,                    //     INPUT (Data,Var,Rel)
    0xc0,                          //   END_COLLECTION
    0xc0,                          // END_COLLECTION
};

//================================================================================
//================================================================================
//	JoyMouse

/* This function is for limiting the input value for x and y
 * axis to -127 <= x/y <= 127 since this is the allowed value
 * range for a USB HID device.
 */
int JoyMouse_::limit_xy(int const xy)
{
	if     (xy < -127) return -127;
	else if(xy >  127) return 127;
	else               return xy;
}

JoyMouse_::JoyMouse_() : _buttons(0)
{
    DynamicHIDSubDescriptor *node = new DynamicHIDSubDescriptor(_hidReportDescriptor, sizeof(_hidReportDescriptor), true); // data, length, inProgMem
    DynamicHID().AppendDescriptor(node);
}

void JoyMouse_::begin(void)
{
}

void JoyMouse_::end(void)
{
}

void JoyMouse_::click(uint8_t b)
{
	_buttons = b;
	move(0,0,0);
	_buttons = 0;
	move(0,0,0);
}

void JoyMouse_::move(int x, int y, signed char wheel)
{
	uint8_t m[4];
	m[0] = _buttons;
	m[1] = limit_xy(x);
	m[2] = limit_xy(y);
	m[3] = wheel;
	DynamicHID().SendReport(1,m,4);
}

void JoyMouse_::buttons(uint8_t b)
{
	if (b != _buttons)
	{
		_buttons = b;
		move(0,0,0);
	}
}

void JoyMouse_::press(uint8_t b)
{
	buttons(_buttons | b);
}

void JoyMouse_::release(uint8_t b)
{
	buttons(_buttons & ~b);
}

bool JoyMouse_::isPressed(uint8_t b)
{
	if ((b & _buttons) > 0)
	{
		return true;
	}
	return false;
}

#endif
