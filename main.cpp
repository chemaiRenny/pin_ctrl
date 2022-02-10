#include "main.h"

enum state{
    ON = 1,
    OFF = 0,
    IDLE = 0
}typedef state;

DigitalOut myLed(LED1);
BufferedSerial sp(USBTX,USBRX);

int main()
{
    char buf;
    const char* dispense = "\r\n[+]Powering ON ...\r\n";
    const char* cancel = "\r\n[-]Powering OFF...\r\n";
    const char* deflt = "\r\n[!]Nothing TODO...\r\n";

    state led_state = IDLE;

    sp.set_baud(BAUDRATE);
    while(1)
    {
        sp.read(&buf,sizeof(buf)); //read buffer serial
        switch(buf)
        {
            case ON_CHR:
                sp.write(dispense,strlen(dispense));
                led_state = ON;
                myLed.write(led_state);
                ThisThread::sleep_for(1s);
                break;

            case OFF_CHR:
                sp.write(cancel,strlen(cancel));
                led_state = OFF;
                myLed.write(led_state);
                ThisThread::sleep_for(1s);
                break;
                
            default:
                sp.write(deflt,strlen(deflt));
                led_state = IDLE;
                myLed.write(led_state);
                break;
        }
        
    }
}