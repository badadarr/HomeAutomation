#include <ESP8266WebServer.h>
#ifndef LED_FUNCTION_H
#define LED_FUNCTION_H

const char *rgbNames[] = {"r", "g", "b"};

class LedStates;
class LedFunction
{
  public:
  LedStates *state;
  LedFunction()
  {
  }

  virtual bool init(ESP8266WebServer &server)
  {
  }

  bool loadRGBValues(ESP8266WebServer &server, uint8_t *rgb)
  {
    bool valid = false;
    for(int i = 0; i < 3; i++)
      if(server.hasArg(rgbNames[i]))
      {
        int value = server.arg(rgbNames[i]).toInt();
        if(value < 0 || value > 255)
        {
          String message = "Illegal value:\n\n";
          message += rgbNames[i];
          message += "=";
          message += server.arg(rgbNames[i]);
          message += "\nOnly values 0 to 255 are allowed. 0 is off and 255 is 100% lit.";
          server.send(200, "text/plain", message);
          return false;
        }
        rgb[i] = value;
      }
    return true;
  }
  
  virtual void render() = 0;
};

#endif
