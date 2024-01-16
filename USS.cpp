#include "USS.h"
#include "Callback.h"
#include <chrono>
#include <cstdio>
#include <ctime>
#include <ratio>


USS::USS(PinName trigger, PinName echo, chrono::microseconds triggerPulse, chrono::milliseconds interval):
    _trigger(trigger), _echo(echo)
{
    this->_triggerPulse = triggerPulse;
    this->_echo.rise(callback(this, &USS::_riseEcho));
    this->_echo.fall(callback(this, &USS::_fallEcho));

    this->_ticker.attach(callback(this, &USS::_riseTrigger), interval);
}

void USS::_riseTrigger() {
    this->_trigger.write(1);
    wait_us((int)this->_triggerPulse.count());
    this->_trigger.write(0);
}

void USS::_riseEcho() {
    this->_timer.start();
}

void USS::_fallEcho() {
    this->_timer.stop();
    this->_echoTime = this->_timer.elapsed_time().count();
    this->_timer.reset();
}

void USS::setTemperature(double degrees) {
    this->_sonicSpeed = 331.5 + 0.6 * degrees;
}

double USS::getEchoTime() {
    return this->_echoTime / 1000000;
}

double USS::getDistance() {
    return this->_sonicSpeed * this->_echoTime / 2 / 1000000;
}
