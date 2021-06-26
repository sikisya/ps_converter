//#include <PsxControllerHwSpi.h> // v0.3.0
#include <PsxControllerBitBang.h>
#include <Adafruit_TinyUSB.h>

const byte PIN_PS2_DAT = 10;
const byte PIN_PS2_CMD = 9;
const byte PIN_PS2_CLK = 8;
const byte PIN_PS2_ATT = 7;

PsxControllerBitBang<PIN_PS2_ATT, PIN_PS2_CMD, PIN_PS2_DAT, PIN_PS2_CLK> psx;
//PsxControllerHwSpi<PIN_PS2_ATT> psx;

uint8_t const desc_hid_report[] =
{
  TUD_HID_REPORT_DESC_GAMEPAD()
};

Adafruit_USBD_HID usb_hid;
hid_gamepad_report_t gp;

bool haveController = false;

void printInput(PsxController *psx)
{
  String str;
  
  auto protocol = psx->getProtocol();
  switch(protocol)
  {
    //case PSPROTO_DIGITAL:
    //case PSPROTO_DUALSHOCK:
    //case PSPROTO_DUALSHOCK2:
    //case PSPROTO_FLIGHTSTICK:
    case PSPROTO_NEGCON:
      str = "NEGCON: ";

      if (psx->buttonPressed(PSB_PAD_LEFT))
      {
        gp.hat = hid_gamepad_hat_t.GAMEPAD_HAT_LEFT;
      }
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
  gp.button = 0;
}

void setup()
{
  Serial.begin(9600);
  Serial.println("setup");

  usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.begin();

  while( !USBDevice.mounted() )
  {
    delay(1);
  }
}

void loop()
{
  resetGamePad();
  
  if (!haveController)
  {
    if (psx.begin())
    {
      Serial.println("Controller found!");
      if (!psx.enterConfigMode ())
      {
        Serial.println("Cannot enter config mode");
      }
      else
      {
        // Try to enable analog sticks
        if (!psx.enableAnalogSticks ()) {
          Serial.println("Cannot enable analog sticks");
        }
                
        if (!psx.exitConfigMode ()) {
          Serial.println("Cannot exit config mode");
        }
      }
      
      haveController = true;
    }
  }
  else
  {
    if (!psx.read())
    {
      Serial.println("controller lost.");
      haveController = false;
    }
    else
    {
      printInput(&psx);
    }
  }
}
