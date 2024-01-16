#include "PinNames.h"
#include "ThisThread.h"
#include "mbed.h"
#include "USS.h"
#include <chrono>
#include <cstdio>

USS uss(D4, D5, chrono::microseconds(10), chrono::milliseconds(60));
int main() {
    uss.setTemperature(10);
    while (true) {
        double echoTime = uss.getEchoTime();
        double distance = uss.getDistance();
        printf("echo : %lf | ", echoTime);
        printf("distance : %lf\r\n", distance);
    }
}
