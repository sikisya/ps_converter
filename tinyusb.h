/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */




// https://github.com/adafruit/Adafruit_TinyUSB_Arduino/blob/e02de0e0e9e1bd6d46a9ed032048d22deb032ea4/src/class/hid/hid.h

//--------------------------------------------------------------------+
// GAMEPAD
//--------------------------------------------------------------------+
/** \addtogroup ClassDriver_HID_Gamepad Gamepad
 *  @{ */

/* From https://www.kernel.org/doc/html/latest/input/gamepad.html
          ____________________________              __
         / [__ZL__]          [__ZR__] \               |
        / [__ TL __]        [__ TR __] \              | Front Triggers
     __/________________________________\__         __|
    /                                  _   \          |
   /      /\           __             (N)   \         |
  /       ||      __  |MO|  __     _       _ \        | Main Pad
 |    <===DP===> |SE|      |ST|   (W) -|- (E) |       |
  \       ||    ___          ___       _     /        |
  /\      \/   /   \        /   \     (S)   /\      __|
 /  \________ | LS  | ____ |  RS | ________/  \       |
|         /  \ \___/ /    \ \___/ /  \         |      | Control Sticks
|        /    \_____/      \_____/    \        |    __|
|       /                              \       |
 \_____/                                \_____/
     |________|______|    |______|___________|
       D-Pad    Left       Right   Action Pad
               Stick       Stick
                 |_____________|
                    Menu Pad
  Most gamepads have the following features:
  - Action-Pad 4 buttons in diamonds-shape (on the right side) NORTH, SOUTH, WEST and EAST.
  - D-Pad (Direction-pad) 4 buttons (on the left side) that point up, down, left and right.
  - Menu-Pad Different constellations, but most-times 2 buttons: SELECT - START.
  - Analog-Sticks provide freely moveable sticks to control directions, Analog-sticks may also
  provide a digital button if you press them.
  - Triggers are located on the upper-side of the pad in vertical direction. The upper buttons
  are normally named Left- and Right-Triggers, the lower buttons Z-Left and Z-Right.
  - Rumble Many devices provide force-feedback features. But are mostly just simple rumble motors.
 */

/// HID Gamepad Protocol Report.
typedef struct TU_ATTR_PACKED
{
  int8_t  x;         ///< Delta x  movement of left analog-stick
  int8_t  y;         ///< Delta y  movement of left analog-stick
  int8_t  z;         ///< Delta z  movement of right analog-joystick
  int8_t  rz;        ///< Delta Rz movement of right analog-joystick
  int8_t  rx;        ///< Delta Rx movement of analog left trigger
  int8_t  ry;        ///< Delta Ry movement of analog right trigger
  uint8_t hat;       ///< Buttons mask for currently pressed buttons in the DPad/hat
  uint32_t buttons;  ///< Buttons mask for currently pressed buttons
}hid_gamepad_report_t;

/// Standard Gamepad Buttons Bitmap
typedef enum
{
  GAMEPAD_BUTTON_0  = TU_BIT(0),
  GAMEPAD_BUTTON_1  = TU_BIT(1),
  GAMEPAD_BUTTON_2  = TU_BIT(2),
  GAMEPAD_BUTTON_3  = TU_BIT(3),
  GAMEPAD_BUTTON_4  = TU_BIT(4),
  GAMEPAD_BUTTON_5  = TU_BIT(5),
  GAMEPAD_BUTTON_6  = TU_BIT(6),
  GAMEPAD_BUTTON_7  = TU_BIT(7),
  GAMEPAD_BUTTON_8  = TU_BIT(8),
  GAMEPAD_BUTTON_9  = TU_BIT(9),
  GAMEPAD_BUTTON_10 = TU_BIT(10),
  GAMEPAD_BUTTON_11 = TU_BIT(11),
  GAMEPAD_BUTTON_12 = TU_BIT(12),
  GAMEPAD_BUTTON_13 = TU_BIT(13),
  GAMEPAD_BUTTON_14 = TU_BIT(14),
  GAMEPAD_BUTTON_15 = TU_BIT(15),
  GAMEPAD_BUTTON_16 = TU_BIT(16),
  GAMEPAD_BUTTON_17 = TU_BIT(17),
  GAMEPAD_BUTTON_18 = TU_BIT(18),
  GAMEPAD_BUTTON_19 = TU_BIT(19),
  GAMEPAD_BUTTON_20 = TU_BIT(20),
  GAMEPAD_BUTTON_21 = TU_BIT(21),
  GAMEPAD_BUTTON_22 = TU_BIT(22),
  GAMEPAD_BUTTON_23 = TU_BIT(23),
  GAMEPAD_BUTTON_24 = TU_BIT(24),
  GAMEPAD_BUTTON_25 = TU_BIT(25),
  GAMEPAD_BUTTON_26 = TU_BIT(26),
  GAMEPAD_BUTTON_27 = TU_BIT(27),
  GAMEPAD_BUTTON_28 = TU_BIT(28),
  GAMEPAD_BUTTON_29 = TU_BIT(29),
  GAMEPAD_BUTTON_30 = TU_BIT(30),
  GAMEPAD_BUTTON_31 = TU_BIT(31),
}hid_gamepad_button_bm_t;

/// Standard Gamepad Buttons Naming from Linux input event codes
/// https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
#define GAMEPAD_BUTTON_A       GAMEPAD_BUTTON_0
#define GAMEPAD_BUTTON_SOUTH   GAMEPAD_BUTTON_0

#define GAMEPAD_BUTTON_B       GAMEPAD_BUTTON_1
#define GAMEPAD_BUTTON_EAST    GAMEPAD_BUTTON_1

#define GAMEPAD_BUTTON_C       GAMEPAD_BUTTON_2

#define GAMEPAD_BUTTON_X       GAMEPAD_BUTTON_3
#define GAMEPAD_BUTTON_NORTH   GAMEPAD_BUTTON_3

#define GAMEPAD_BUTTON_Y       GAMEPAD_BUTTON_4
#define GAMEPAD_BUTTON_WEST    GAMEPAD_BUTTON_4

#define GAMEPAD_BUTTON_Z       GAMEPAD_BUTTON_5
#define GAMEPAD_BUTTON_TL      GAMEPAD_BUTTON_6
#define GAMEPAD_BUTTON_TR      GAMEPAD_BUTTON_7
#define GAMEPAD_BUTTON_TL2     GAMEPAD_BUTTON_8
#define GAMEPAD_BUTTON_TR2     GAMEPAD_BUTTON_9
#define GAMEPAD_BUTTON_SELECT  GAMEPAD_BUTTON_10
#define GAMEPAD_BUTTON_START   GAMEPAD_BUTTON_11
#define GAMEPAD_BUTTON_MODE    GAMEPAD_BUTTON_12
#define GAMEPAD_BUTTON_THUMBL  GAMEPAD_BUTTON_13
#define GAMEPAD_BUTTON_THUMBR  GAMEPAD_BUTTON_14

/// Standard Gamepad HAT/DPAD Buttons (from Linux input event codes)
typedef enum
{
  GAMEPAD_HAT_CENTERED   = 0,  ///< DPAD_CENTERED
  GAMEPAD_HAT_UP         = 1,  ///< DPAD_UP
  GAMEPAD_HAT_UP_RIGHT   = 2,  ///< DPAD_UP_RIGHT
  GAMEPAD_HAT_RIGHT      = 3,  ///< DPAD_RIGHT
  GAMEPAD_HAT_DOWN_RIGHT = 4,  ///< DPAD_DOWN_RIGHT
  GAMEPAD_HAT_DOWN       = 5,  ///< DPAD_DOWN
  GAMEPAD_HAT_DOWN_LEFT  = 6,  ///< DPAD_DOWN_LEFT
  GAMEPAD_HAT_LEFT       = 7,  ///< DPAD_LEFT
  GAMEPAD_HAT_UP_LEFT    = 8,  ///< DPAD_UP_LEFT
}hid_gamepad_hat_t;

/// @}




// https://github.com/adafruit/Adafruit_TinyUSB_Arduino/blob/3b4d46b717f554c66fa95638abd4c28c0e6f22d2/src/class/hid/hid_device.h

// Gamepad Report Descriptor Template
// with 16 buttons, 2 joysticks and 1 hat/dpad with following layout
// | X | Y | Z | Rz | Rx | Ry (1 byte each) | hat/DPAD (1 byte) | Button Map (2 bytes) |
#define TUD_HID_REPORT_DESC_GAMEPAD(...) \
  HID_USAGE_PAGE ( HID_USAGE_PAGE_DESKTOP     )                 ,\
  HID_USAGE      ( HID_USAGE_DESKTOP_GAMEPAD  )                 ,\
  HID_COLLECTION ( HID_COLLECTION_APPLICATION )                 ,\
    /* Report ID if any */\
    __VA_ARGS__ \
    /* 8 bit X, Y, Z, Rz, Rx, Ry (min -127, max 127 ) */ \
    HID_USAGE_PAGE   ( HID_USAGE_PAGE_DESKTOP                 ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_X                    ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_Y                    ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_Z                    ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_RZ                   ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_RX                   ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_RY                   ) ,\
    HID_LOGICAL_MIN  ( 0x81                                   ) ,\
    HID_LOGICAL_MAX  ( 0x7f                                   ) ,\
    HID_REPORT_COUNT ( 6                                      ) ,\
    HID_REPORT_SIZE  ( 8                                      ) ,\
    HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ) ,\
    /* 8 bit DPad/Hat Button Map  */ \
    HID_USAGE_PAGE   ( HID_USAGE_PAGE_DESKTOP                 ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_HAT_SWITCH           ) ,\
    HID_LOGICAL_MIN  ( 1                                      ) ,\
    HID_LOGICAL_MAX  ( 8                                      ) ,\
    HID_PHYSICAL_MIN ( 0                                      ) ,\
    HID_PHYSICAL_MAX_N ( 315, 2                               ) ,\
    HID_REPORT_COUNT ( 1                                      ) ,\
    HID_REPORT_SIZE  ( 8                                      ) ,\
    HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ) ,\
    /* 16 bit Button Map */ \
    HID_USAGE_PAGE   ( HID_USAGE_PAGE_BUTTON                  ) ,\
    HID_USAGE_MIN    ( 1                                      ) ,\
    HID_USAGE_MAX    ( 32                                     ) ,\
    HID_LOGICAL_MIN  ( 0                                      ) ,\
    HID_LOGICAL_MAX  ( 1                                      ) ,\
    HID_REPORT_COUNT ( 32                                     ) ,\
    HID_REPORT_SIZE  ( 1                                      ) ,\
    HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ) ,\
  HID_COLLECTION_END \
