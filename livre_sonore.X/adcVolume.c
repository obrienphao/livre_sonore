/*
 * File:   adcVolume.c
 * Author: dimbu
 *
 * Created on 10 février 2024, 18:29
 */


#include "xc.h"
#include "adcVolume.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define NUM_SAMPLES 5
// Configuration de l'ADC

void adc_init() {
    AD1CON1bits.ADON = 1; // turn on the ADC
    AD1CON1bits.SAMP = 0;
    AD1CON1bits.ASAM = 0;
    AD1CON1bits.FORM = 0; //Decimal result, signed, right-justified
    AD1CON1bits.SSRC = 0b0111; //Clearing the SAMP bit in software ends sampling and begins conversion
    //------------------------
    AD1CON2 = 0; // utilisation de A comme INPUT analogique 

    //------------------------
    // AD1CON3=0;
    //------------------------
    AD1CON3bits.ADRC = 0; //use system clock
    AD1CON3bits.SAMC = 0b11111; //longest sample time possible 31Tcy
    AD1CON3bits.ADCS = 0b11111; //slowest cl 
    //-----------------

}

// Lecture de la valeur du potentiomètre

uint16_t read_potentiometer(int ch) {
    AD1CON1bits.SAMP = 1; // Commencer l'échantillonnage
    AD1CHSbits.CH0NB = 0; //Sample A Channel 0 Negative Input Select bits
    AD1CHSbits.CH0NA = 0; //Sample A Channel 0 Negative Input Select bits
    AD1CON1bits.ADON = 1; // turn on the ADC
    AD1PCFGbits.PCFG9 = 0;
    AD1CHSbits.CH0SA = ch;
    AD1CON1bits.SAMP = 1; // start sample

    while (!AD1CON1bits.DONE) {
    }; // loop untill finished
    //----------------------
    uint16_t sum = 0;

    for (int i = 0; i < NUM_SAMPLES; i++) {
        sum += ADC1BUF0;
        __builtin_nop(); // Ajouter un petit délai entre les échantillons
    }
    sum = sum / NUM_SAMPLES;
    //-----------------------
    AD1CON1bits.SAMP = 0;
    AD1CON1bits.ADON = 0; // turn on the ADC

    return sum;

}

// Fonction pour ajuster la valeur du potentiomètre sur l'intervalle de 0 à 30

uint8_t map_to_range(uint16_t value, uint16_t in_min, uint16_t in_max, uint8_t out_min, uint8_t out_max) {
    // Assurer que la valeur est dans la plage d'entrée
    if (value < in_min) {
        value = in_min;
    } else if (value > in_max) {
        value = in_max;
    }

    // Effectuer la conversion proportionnelle
    return (uint8_t) (((value - in_min) * (out_max - out_min)) / (in_max - in_min) + out_min);
}