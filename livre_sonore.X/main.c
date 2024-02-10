// CONFIG2
#pragma config POSCMOD = NONE          // Primary Oscillator Select (Primary oscillator disabled)
#pragma config I2C1SEL = PRI            // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = ON             // IOLOCK Protection (Once IOLOCK is set, cannot be changed)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRC           // Oscillator Select (Fast RC Oscillator (FRC) with Postscaler)
#pragma config SOSCSEL = LPSOSC           // Sec Oscillator Select (Default Secondary Oscillator (SOSC))
#pragma config WUTSEL = LEG             // Wake-up timer Select (Legacy Wake-up Timer)
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)

// CONFIG1
#pragma config WDTPS = PS32768         // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = OFF              // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF              // Watchdog Timer Enable (Watchdog Timer is enabled)
#pragma config ICS = PGx1               // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF              // JTAG Port Enable (JTAG port is enabled)
// #pragma config statements should precede project file includes.
//---------
#include "xc.h"
#include <stdint.h>
#include "DFPlayer.h"
//#include "adcVolume.h"
//#include "uartCom.h"

void ledOn() {
    LATBbits.LATB5 = 1;
}

void ledOff() {
    LATBbits.LATB5 = 0;
}

int main(void) {

    //uint8_t _sending[] = {0x7E, 0xFF, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xEF};
    // Configure pins
    AD1PCFGbits.PCFG0 = 1; // Configure AN0 as digital input
    AD1PCFGbits.PCFG1 = 1; // defi,ir par defaut comme input

    AD1PCFGbits.PCFG2 = 1;
    AD1PCFGbits.PCFG3 = 1;

    AD1PCFGbits.PCFG4 = 1;
    AD1PCFGbits.PCFG5 = 1;


    //Input config
    TRISAbits.TRISA0 = 1; // Set RA0 as input
    TRISAbits.TRISA1 = 1; // Set RA1 as input
    TRISBbits.TRISB0 = 1; // Set RB0 as input
    TRISBbits.TRISB1 = 1; // Set RB1 as input
    //Output config
    TRISBbits.TRISB5 = 0; // Set RB5 as output
    LATBbits.LATB5 = 0;

    // UART initialization
    //uart1_init();
    initDFPLayer();
    // UART pin selection
    RPINR18bits.U1RXR = 18; // Assign U1RXR to RP9
    RPOR4bits.RP8R = 3; // Assign U1TX to RP8
    TRISBbits.TRISB8 = 0; // RP8 as output (TX)
    //TRISBbits.TRISB9 = 1; // RP9 as input (RX)

   

    while (1) {

       // volumeChange();

        if (PORTAbits.RA0 == 0) {
            ledOn();
            play(1);
        }
        if (PORTAbits.RA1 == 0) {
            ledOn();
            play(2);

        }
        if (PORTBbits.RB0 == 0) {
            ledOn();
            play(3);
        }
        if (PORTBbits.RB1 == 0) {
            ledOn();
            play(4);
        }

        ledOff();

    }

    return 0;
}
