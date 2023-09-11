#include "mbed.h"
#include "stdio.h"
static BufferedSerial pc(USBTX, USBRX);
DigitalOut USSTriger (D4);       
Timer ActiveTime;
Ticker TrigerTiming;              
InterruptIn USSEcho (D5);        

void init(void);
void Output_Monitor(unsigned short Value);

unsigned short USSDistance;      

int main() {
    char val;                     
    init();
    while(1) {
        if(pc.readable() ){
            Output_Monitor( USSDistance );
            val = pc.get();
        }
    }
}

void Triger (){
    USSTriger = 1;
    wait_us(10);
    USSTriger = 0;
}

void RiseEcho(){
    ActiveTime.start();
}

void FallEcho(){
    unsigned long ActiveWidth;
    ActiveTime.stop();
    ActiveWidth = ActiveTime.read_us();
    USSDistance = ActiveWidth * 0.0170;
    ActiveTime.reset();
}

void init(void){   
    TrigerTiming.attach( Triger , 0.060 );     
    USSEcho.rise( RiseEcho );                  
    USSEcho.fall( FallEcho );                  
}

void Output_Monitor(unsigned short Value){
    pc.printf("%d[cm]\r\n",Value);
}