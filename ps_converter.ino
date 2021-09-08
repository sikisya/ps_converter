//
// NEGCON to USB GamePad
//         Seeduino XIAO
//

//#include <PsxControllerHwSpi.h>
#include <PsxControllerBitBang.h>
#include <Adafruit_TinyUSB.h> // v0.10.x
#include "tinyusb.h"

//#define USE_GAMEPAD_HAT_4_WAY
//#define USE_GAMEPAD_HAT_8_WAY
//#define _DEBUG

const byte PIN_PS2_DAT = 5;
const byte PIN_PS2_CMD = 6;
const byte PIN_PS2_CLK = 7;
const byte PIN_PS2_ATT = 8;
const byte PIN_PS2_ACK = 9;

PsxControllerBitBang<PIN_PS2_ATT, PIN_PS2_CMD, PIN_PS2_DAT, PIN_PS2_CLK> psx;
//PsxControllerHwSpi<PIN_PS2_ATT> psx;

uint8_t const desc_hid_report[] =
{
  TUD_HID_REPORT_DESC_GAMEPAD()
};

Adafruit_USBD_HID usb_hid;
hid_gamepad_report_t gp;

bool haveController = false;

#ifdef _DEBUG
void printInput(PsxController *psx)
{
  String str;

  auto protocol = psx->getProtocol();
  switch (protocol)
  {
    //case PSPROTO_DIGITAL:
    //case PSPROTO_DUALSHOCK:
    //case PSPROTO_DUALSHOCK2:
    //case PSPROTO_FLIGHTSTICK:
    case PSPROTO_NEGCON:
      str = "NEGCON: ";
      str += (psx->buttonPressed(PSB_PAD_LEFT))  ? "←" : "　";
      str += (psx->buttonPressed(PSB_PAD_DOWN))  ? "↓" : "　";
      str += (psx->buttonPressed(PSB_PAD_UP))    ? "↑" : "　";
      str += (psx->buttonPressed(PSB_PAD_RIGHT)) ? "→" : "　";

      str += (psx->buttonPressed(PSB_TRIANGLE))  ? "△" : "　";
      str += (psx->buttonPressed(PSB_CIRCLE))    ? "○" : "　";

      str += (psx->buttonPressed(PSB_R1))        ? "R1" : "  ";
      str += (psx->buttonPressed(PSB_START))     ? "ST" : "  ";

      str += " L1:";
      str += psx->getAnalogButton(PSAB_L1);
      str += " ×:";
      str += psx->getAnalogButton(PSAB_CROSS);
      str += " □:";
      str += psx->getAnalogButton(PSAB_SQUARE);

      byte lx, ly;
      psx->getLeftAnalog(lx, ly);
      str += " LX:";
      str += lx;
      str += " LY:";
      str += ly;

      break;
    //case PSPROTO_JOGCON:

    default:
      break;
  }
  Serial.println(str);
}
#endif

void sendGamePadStatus(PsxController *psx)
{

  auto protocol = psx->getProtocol();
  switch (protocol)
  {
    //case PSPROTO_DIGITAL:
    //case PSPROTO_DUALSHOCK:
    //case PSPROTO_DUALSHOCK2:
    //case PSPROTO_FLIGHTSTICK:
    case PSPROTO_NEGCON:
      // set digital button
      if (psx->buttonPressed(PSB_CIRCLE))
      {
        gp.buttons += GAMEPAD_BUTTON_0;
      }
      if (psx->buttonPressed(PSB_TRIANGLE))
      {
        gp.buttons += GAMEPAD_BUTTON_1;
      }
      if (psx->buttonPressed(PSB_R1))
      {
        gp.buttons += GAMEPAD_BUTTON_2;
      }
      if (psx->buttonPressed(PSB_START))
      {
        gp.buttons += GAMEPAD_BUTTON_3;
      }

      // set hat
#ifdef USE_GAMEPAD_HAT_8_WAY
      {
        uint8_t d = 0;
        d += (psx->buttonPressed(PSB_PAD_UP)) ? 1 : 0;
        d += (psx->buttonPressed(PSB_PAD_RIGHT)) ? 2 : 0;
        d += (psx->buttonPressed(PSB_PAD_DOWN)) ? 4 : 0;
        d += (psx->buttonPressed(PSB_PAD_LEFT)) ? 8 : 0;

        if (d == 0 || d == 5 || d == 10 || d == 15)
        {
          gp.hat = GAMEPAD_HAT_CENTERED;
        }
        else if (d == 1 | d == 11)
        {
          gp.hat = GAMEPAD_HAT_UP;
        }
        else if (d == 3)
        {
          gp.hat = GAMEPAD_HAT_UP_RIGHT;
        }
        else if (d == 2 | d == 7)
        {
          gp.hat = GAMEPAD_HAT_RIGHT;
        }
        else if (d == 6)
        {
          gp.hat = GAMEPAD_HAT_DOWN_RIGHT;
        }
        else if (d == 4 | d == 14)
        {
          gp.hat = GAMEPAD_HAT_DOWN;
        }
        else if (d == 12)
        {
          gp.hat = GAMEPAD_HAT_DOWN_LEFT;
        }
        else if (d == 8 | d == 13)
        {
          gp.hat = GAMEPAD_HAT_LEFT;
        }
        else if (d == 9)
        {
          gp.hat = GAMEPAD_HAT_UP_LEFT;
        }
      }
#elif USE_GAMEPAD_HAT_4_WAY
      if (psx->buttonPressed(PSB_PAD_UP))
      {
        gp.hat = GAMEPAD_HAT_UP;
      }
      if (psx->buttonPressed(PSB_PAD_RIGHT))
      {
        gp.hat = GAMEPAD_HAT_RIGHT;
      }
      if (psx->buttonPressed(PSB_PAD_DOWN))
      {
        gp.hat = GAMEPAD_HAT_DOWN;
      }
      if (psx->buttonPressed(PSB_PAD_LEFT))
      {
        gp.hat = GAMEPAD_HAT_LEFT;
      }
#else
      if (psx->buttonPressed(PSB_PAD_UP))
      {
        gp.buttons += GAMEPAD_BUTTON_4;
      }
      if (psx->buttonPressed(PSB_PAD_RIGHT))
      {
        gp.buttons += GAMEPAD_BUTTON_5;
      }
      if (psx->buttonPressed(PSB_PAD_DOWN))
      {
        gp.buttons += GAMEPAD_BUTTON_6;
      }
      if (psx->buttonPressed(PSB_PAD_LEFT))
      {
        gp.buttons += GAMEPAD_BUTTON_7;
      }
#endif

      // set analog button
      byte lx, ly;
      psx->getLeftAnalog(lx, ly);
      gp.x = lx - 128;
      gp.y = ly - 128;
      gp.z = psx->getAnalogButton(PSAB_L1) - 128;
      gp.rx = psx->getAnalogButton(PSAB_CROSS) - 128;
      gp.ry = psx->getAnalogButton(PSAB_SQUARE) - 128;
  }
  usb_hid.sendReport(0, &gp, sizeof(gp));
}

void resetGamePad()
{
  gp.x = 0;
  gp.y = 0;
  gp.z = 0;
  gp.rx = 0;
  gp.ry = 0;
  gp.rz = 0;
  gp.hat = 0;
  gp.buttons = 0;
}

void setup()
{
#ifdef _DEBUG
  Serial.begin(9600);
  Serial.println("setup");
#endif

  usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));

  // How to change device name
  //   1. Open board.txt.
  //   2. Edit 'xxx.build.usb_product', 'xxx.build.vid' and 'xxx.build.pid'.
  //      e.g.)
  //         seeed_XIAO_m0.build.usb_product="PSX Controller"
  //         seeed_XIAO_m0.build.vid=0xF055
  //         seeed_XIAO_m0.build.pid=0xCAFE
  // usb_hid.setStringDescriptor("PSX Controller");

  usb_hid.begin();

  while ( !USBDevice.mounted() )
  {
    delay(1);
  }
}

void loop()
{
  if (!usb_hid.ready())
  {
    return;
  }

  resetGamePad();

  if (!haveController)
  {
    if (psx.begin())
    {
#ifdef _DEBUG
      Serial.println("Controller found!");
#endif
      if (!psx.enterConfigMode ())
      {
#ifdef _DEBUG
        Serial.println("Cannot enter config mode");
#endif
      }
      else
      {
        // Try to enable analog sticks
        if (!psx.enableAnalogSticks ()) {
#ifdef _DEBUG
          Serial.println("Cannot enable analog sticks");
#endif
        }

        if (!psx.exitConfigMode ()) {
#ifdef _DEBUG
          Serial.println("Cannot exit config mode");
#endif
        }
      }

      haveController = true;
    }
  }
  else
  {
    if (!psx.read())
    {
#ifdef _DEBUG
      Serial.println("controller lost.");
#endif
      haveController = false;
    }
    else
    {
#ifdef _DEBUG
      printInput(&psx);
#endif
      sendGamePadStatus(&psx);
    }
  }
}
