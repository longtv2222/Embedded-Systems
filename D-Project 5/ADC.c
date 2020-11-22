/*
 * File:   ADC.c
 * Author: blaob
 *
 * Created on November 21, 2020, 12:29 PM
 */


#include "xc.h"
#include "ADC.h"

uint16_t do_ADC(void) {
    AD1CON1bits.ADON = 1; //Enable ADC module
    
    AD1CON1bits.FORM0 = 0;
    AD1CON1bits.FORM1 = 0; //Save data output as unsigned integer type.
    
    AD1CON1bits.SSRC0 = 1;
    AD1CON1bits.SSRC1 = 1;
    AD1CON1bits.SSRC2 = 1; //Internal counter ends sampling and starts conversion
   
    AD1CON2bits.VCFG = 0b000;
    AD1CON2bits.CSCNA = 0;
    
//    AD1CON2bits.SMPI = 0b0000; //Only if you want to use interrupt
    AD1CON2bits.BUFM = 0;   //Enable 16-word buffer
    AD1CON2bits.ALTS = 0;   //Always uses MUX A input multiplexer settings
    
    AD1CON3bits.ADRC = 0;   //Use system clock
    AD1CON3bits.SAMC = 0b11111;     //Sampling time 31 * 2 /fclk
    
    AD1CHSbits.CH0NA = 0;   //Set negative input to VR-
    AD1CHSbits.CH0SA = 0b0101;  //Enable AN5 or pin number 18 to ADC input/
    
    AD1PCFGbits.PCFG5 = 0;   //Disable digital IO on pin 18.
    
    AD1CSSLbits.CSSL0 = 0;
    AD1CSSLbits.CSSL1 = 0;
    AD1CSSLbits.CSSL2 = 0;
    AD1CSSLbits.CSSL3 = 0;
    AD1CSSLbits.CSSL4 = 0;
    AD1CSSLbits.CSSL5 = 0;
    AD1CSSLbits.CSSL10 = 0;
    AD1CSSLbits.CSSL11 = 0;
    AD1CSSLbits.CSSL12 = 0; //Analog channel omitted from input scan
    
    
    AD1CON1bits.SAMP = 1;
    while(!AD1CON1bits.DONE) {}
    
    uint16_t value = ADC1BUF0;  //SAVE ADC1BUF0 output to value
    AD1CON1bits.SAMP = 0;       //Stop sampling
    AD1CON1bits.ADON = 0;       //Turn off ADC
    
    return value;
}

