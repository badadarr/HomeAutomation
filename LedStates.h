#include <ESP8266WebServer.h>
#include "LedFunction.h"

const int MAX_LED_COUNT = 300;

class LedStates
{
  public:
  uint8_t values[MAX_LED_COUNT][3] = {{0}};
  int count = 0;
  bool dirty = false;
  Adafruit_NeoPixel &pixels;
  LedFunction *function = 0;
  
  LedStates(Adafruit_NeoPixel &ledPixels)
  :pixels(ledPixels)
  {
    count = pixels.numPixels();
  }

  void setFunction(LedFunction *newFunction)
  {
    if(function)
      delete function;
    function = newFunction;
    if(!function)
      return;
    function->state = this;
  }

  void setRgb(int i, uint8_t r, uint8_t g, uint8_t b)
  {
    values[i][0] = r;
    values[i][1] = g;
    values[i][2] = b;
    dirty = true;
  }

  virtual void render()
  {
    if(function)
      function->render();
  }

  void setValues(LedStates &to)
  {
    for(int i = 0; i < count; i++)
      for(int j = 0; j < 3; j++)
        values[i][j] = to.values[i][j];
    setFunction(to.function);
    to.function = 0;
    dirty = true;
  }

  void commit()
  {
    if(!dirty)
      return;
    for(int i = 0; i < count; i++)
      pixels.setPixelColor(i, pixels.Color(values[i][0], values[i][1], values[i][2]));
    pixels.show();
    dirty = false;
  }

  void fade(LedStates &to, long f0, long f1)
  {
    for(int i = 0; i < count; i++)
      pixels.setPixelColor(i, pixels.Color((values[i][0] * f0 + to.values[i][0] * f1) >> 16, (values[i][1] * f0 + to.values[i][1] * f1) >> 16, (values[i][2] * f0 + to.values[i][2] * f1) >> 16));
    pixels.show();
    dirty = true;
  }
};

