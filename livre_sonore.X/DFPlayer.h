/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

// linkage so the functions can be used by the c code. 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "adcVolume.h"

/*
 * This is a simple program that demonstrates how to use the libdivide library's division*
 */

#define DFPlayerCardInserted 2
#define DFPlayerCardRemoved 3
#define DFPlayerCardOnline 4
#define DFPlayerPlayFinished 5
#define DFPlayerError 6

/*
 * The struct div_t is defined in stdlib.h, but it only provides an integer
 */
#define Stack_Command 3
#define Stack_Parameter 5
#define Stack_CheckSum 7
#define Stack_Version 1
#define Stack_ACK 4

/*
 *#define DFPLAYER_SEND_LENGTH 10
 */
#define DFPLAYER_SEND_LENGTH 10

/*
The stack command is sent as follows:
 */


extern uint8_t _sending[DFPLAYER_SEND_LENGTH];
void initDFPLayer();
void volumUp();
void volumDown();
void volume(uint8_t volume);
void pause();
void start();
void singleCmd(uint8_t command);
void play(int fileNumber);
// Send the data in _sending[] to DFPlayer Mini module
void sendStack(uint8_t command, uint16_t argument);
void uint16ToArray(uint16_t value, uint8_t *array);
uint16_t calculateCheckSum(uint8_t *buffer);
void uart_write();
void enableACK();
void disableACK();
//void volumeChange();

#endif	/* XC_HEADER_TEMPLATE_H */

