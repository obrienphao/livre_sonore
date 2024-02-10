/*
 * File:   adcVolume.c
 * Author: dimbu
 *
 * Created on 10 f�vrier 2024, 18:29
 */


#include "xc.h"
#include "adcVolume.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Configuration de l'ADC

void adc_init() {
  //  AD1PCFG = 0xFFFF; // Configurer toutes les broches comme entr�es num�riques par d�faut
    AD1PCFGbits.PCFG9 = 0; // Configurer AN9 comme entr�e analogique
    AD1CON1 = 0x00E0; // Configuration de l'ADC : Mode automatique, D�clench� manuellement, Conversion 12 bits
    AD1CSSL = 0; // Aucune num�risation de balayage des entr�es analogiques
    AD1CON3 = 0x1F02; // Fr�quence de conversion : Tcy * 32 (approximativement 1.6 us)
    AD1CON2 = 0; // Pas de multiplexage pour le mode manuel
}

// Lecture de la valeur du potentiom�tre

uint16_t read_potentiometer() {
    AD1CHSbits.CH0SA = 9; // S�lectionner l'entr�e AN9 pour la conversion
    AD1CON1bits.SAMP = 1; // Commencer l'�chantillonnage
    AD1CON1bits.SAMP = 0; // Arr�ter l'�chantillonnage et commencer la conversion
    while (!AD1CON1bits.DONE); // Attendre la fin de la conversion
    return ADC1BUF0; // Lire la valeur convertie
}

// Fonction pour ajuster la valeur du potentiom�tre sur l'intervalle de 0 � 30
uint8_t map_to_range(uint16_t value, uint16_t in_min, uint16_t in_max, uint8_t out_min, uint8_t out_max) {
    // Assurer que la valeur est dans la plage d'entr�e
    if (value < in_min) {
        value = in_min;
    } else if (value > in_max) {
        value = in_max;
    }

    // Effectuer la conversion proportionnelle
    return (uint8_t)(((value - in_min) * (out_max - out_min)) / (in_max - in_min) + out_min);
}