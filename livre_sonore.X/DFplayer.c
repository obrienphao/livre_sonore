/*
 * File:   DFPlayer.c
 * Author: dimbu
 *
 * Created on February 2, 2024, 3:20 PM
 */


#include "DFplayer.h"
#include "uartCom.h"
#include "xc.h"
#include "adcVolume.h"


uint8_t _sending[DFPLAYER_SEND_LENGTH] = {0x7E, 0xFF, 06, 00, 01, 00, 00, 00, 00, 0xEF};

uint16_t pot_value =0;
uint8_t mapped_value =0;

void initDFPLayer() {

    uart1_init();
    //Configurer l'ADC
    //adc_init();
}

void volumUp() {
    //  Serial.println("vol++");
    singleCmd(0x04);
}

void volumDown() {
    // Serial.println("vol--");
    singleCmd(0x05);
}

void volume(uint8_t volume) {
    sendStack(0x06, volume);

}

void volumeChange() {
    // Configurer l'ADC
    pot_value = read_potentiometer();
    mapped_value = map_to_range(pot_value, 0, 1023, 0, 30);
    volume(mapped_value);
}

void pause() {
    singleCmd(0x0E);
}

void start() {
    singleCmd(0x0D);
}

void singleCmd(uint8_t command) {
    sendStack(command, 0);
}

void play(int fileNumber) {
    sendStack(0x03, fileNumber);
}

// Send the data in _sending[] to DFPlayer Mini module

void sendStack(uint8_t command, uint16_t argument) {
    _sending[Stack_Command] = command;
    uint16ToArray(argument, _sending + Stack_Parameter);
    uint16ToArray(calculateCheckSum(_sending), _sending + Stack_CheckSum);
    // Write to serial
    uart_write();
}

void uint16ToArray(uint16_t value, uint8_t *array) {
    *array = (uint8_t) (value >> 8);
    *(array + 1) = (uint8_t) (value);
}

uint16_t calculateCheckSum(uint8_t *buffer) {
    uint16_t sum = 0;
    for (int i = Stack_Version; i < Stack_CheckSum; i++) {
        sum += buffer[i];
    }
    return -sum;
}

void uart_write() {

    write(_sending, DFPLAYER_SEND_LENGTH);
}

void enableACK() {
    _sending[Stack_ACK] = 0x01;
}

void disableACK() {
    _sending[Stack_ACK] = 0x00;
}

