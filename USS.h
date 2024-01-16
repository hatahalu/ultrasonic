#ifndef USS_H
#define USS_H

#include "InterruptIn.h"
#include "mbed.h"
#include <chrono>

class USS {
public:
    USS(PinName trigger, PinName echo, chrono::microseconds triggerPulse, chrono::milliseconds interval);
    
    void setTemperature(double degrees);
    double getEchoTime();
    double getDistance();

private:
    void _riseTrigger();
    void _riseEcho();
    void _fallEcho();

    DigitalOut _trigger;
    InterruptIn _echo;
    Timer _timer;
    Ticker _ticker;

    chrono::microseconds _triggerPulse;
    double _echoTime = 0.0;
    double _sonicSpeed = 340.0;
};

#endif
