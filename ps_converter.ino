#include "PsxNewLib/src/PsxControllerBitBang.h"

const byte PIN_PS2_DAT = 5;
const byte PIN_PS2_CMD = 4;
const byte PIN_PS2_ATT = 3;
const byte PIN_PS2_CLK = 2;

PsxControllerBitBang<PIN_PS2_ATT, PIN_PS2_CMD, PIN_PS2_DAT, PIN_PS2_CLK> psx;

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

void setup()
{
  Serial.begin(9600);
  Serial.println("setup");
}

void loop()
{
  if (!haveController)
  {
    if (psx.begin ())
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
