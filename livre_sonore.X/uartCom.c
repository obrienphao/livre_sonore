

#include "uartCom.h"
#include "xc.h"
#include <stdint.h>

// Configuration de l'UART1
#define UART1_BAUD_RATE 9600
#define UART1_TX_PIN RP8
#define UART1_RX_PIN RP9

// Définir la fréquence du système en Hz (ici 8 MHz)
#define FCY 8000000UL

void uart1_init(void) {

    
    U1BRG = 25; // 9600 @ 8MHZ
    U1MODEbits.UARTEN = 1; // UART2 is Enabled
    U1MODEbits.USIDL = 0; // Continue operation at Idlestate
    U1MODEbits.IREN = 0; // IrDA En/Decoder is disabled
    U1MODEbits.RTSMD = 0; // flow control mode
    U1MODEbits.UEN1 = 0b00; // UTX, RTX, are enabled U1CTS, U1RTS are disabled
    U1MODEbits.UEN0 = 0b00; // UTX, RTX, are enabled U1CTS, U1RTS are disabled
    U1MODEbits.WAKE = 1; // Wake-up on start bit is enabled
    U1MODEbits.LPBACK = 0; // Loop-back is disabled
    U1MODEbits.ABAUD = 0; // auto baud is disabled
    U1MODEbits.RXINV = 0; // No RX inversion
    U1MODEbits.BRGH = 0; // low boud rate
    U1MODEbits.PDSEL = 0b00; // 8bit no parity
    U1MODEbits.STSEL = 0; // one stop bit 


    U1STAbits.UTXISEL1 = 0b00;
    U1STA &= 0xDFFF; // clear TXINV by bit masking
    U1STAbits.UTXBRK = 0; // sync break tx is disabled
    U1STAbits.UTXEN = 1; //transmit  is enabled
    U1STAbits.URXISEL = 0b00; // interrupt flag bit is set when RXBUF is filled whith 1 character
    U1STAbits.ADDEN = 0; // address detect mode is disabled
    U1STAbits.RIDLE = 0;

    IPC2bits.U1RXIP = 0; // sET uart1 Priority to 7
    IFS0bits.U1RXIF = 0; // clear interrupt flag of rx
    IFS0bits.U1TXIF = 0; // clear interrupt flag of rx
    IEC0bits.U1RXIE = 0; // enable rx recieved data interrupt
    IEC0bits.U1TXIE = 0;





}

void write(uint8_t *buffer, uint8_t length) {
    for (uint8_t index = 0; index < length; index++) {
        U1TXREG = buffer[index];
        while (!U1STAbits.TRMT); // Wait for the transmit buffer to be empty
    }
}

uint8_t read(void) {
    while (!U1STAbits.URXDA); // Wait until data is available in U1RXREG
    return U1RXREG;
}

void uart_write_char(char data) {
    while (!U1STAbits.TRMT); // Attendre que le registre U1TXREG soit vide
    U1TXREG = data; // Écrire le caractère dans le registre de transmission
}
