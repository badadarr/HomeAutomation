#include "LedFunction.h"

class SimpleRGBFunction: public LedFunction
{
  public:
    uint8_t rgb[3] = {0, 0, 0};
    bool set = false;

  SimpleRGBFunction()
  {    
  }

  virtual bool init(ESP8266WebServer &server)
  {
    if(!loadRGBValues(server, rgb))
      return false;
  }
  
  virtual void render()
  {
    if(set)
      return;
    for(int i = 0; i < state->count; i++)
      state->setRgb(i, rgb[0], rgb[1], rgb[2]);
    set = true;  
  }
};

