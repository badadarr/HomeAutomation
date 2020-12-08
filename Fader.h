template<class T>
class Fader
{
  public:
  bool active = false;
  long startTime = 0;
  long duration = 0;
  T &from;
  T &to;
  
  Fader(T &fromState, T &toState)
    :from(fromState)
    ,to(toState)
  {
  }

  bool start(int duration)
  {
    if(active)
      return false;
    active = true;
    startTime = millis();
    this->duration = duration;
  }
  
  bool fade()
  {
    if(!active) 
      return false;
    long t = millis() - startTime;
    if(t >= duration || t < 0 || duration == 0)
    {
      from.setValues(to);
      active = false;
      return false;
    }
    float f1 = (float)t / duration;
    float f0 = 1 - f1;
    from.fade(to, long(f0 * 0x10000), long(f1 * 0x10000));
    return true;
  }
};

