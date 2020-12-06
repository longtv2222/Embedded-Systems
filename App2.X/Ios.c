/*
 * File:   IOS.c
 * Author: Garth Slaney, Long Ta, Weitao Wu
 *
 * Created on October 13, 2020, 11:13 PM
 */

#include "Ios.h"
#include <xc.h>
#include <stdio.h>
#include "UART2.h"
#include "ADC.h"

int CN30Flag = 0;   //RA2 push button flag
int CN0Flag = 0;    //RA4 push button flag
int CN1Flag = 0;    //RB4 push button flag

//This function initializes IO ports.
void IOinit() {
    AD1PCFG = 0xFFFF; // Turn all analog pins as digital
    CNPU1bits.CN0PUE = 1; //Enables pull up resistor on RA4/CN0
    CNPU2bits.CN30PUE = 1; //Enables pull up resistor on RA2/CN3
    CNPU1bits.CN1PUE = 1; //Enables pull up resistor on RB4/CN1
    TRISAbits.TRISA2 = 1; //RA2 is input, PB1 is connected to this port.
    TRISAbits.TRISA4 = 1; //RA4 is input, PB2 is connected to this port.
    TRISBbits.TRISB4 = 1; //RB4 is input, PB3 is connected to this port
    CNinit();
}


void CNinit() {
    CNEN1bits.CN1IE = 1;    //Configure change of notification input of RB4
    CNEN1bits.CN0IE = 1;    //Configure change of notification input of RA4
    CNEN2bits.CN30IE = 1;   //Configure change of notification input of RA2
    IEC1bits.CNIE = 1;      //Set interrupt request to occur
    IPC4bits.CNIP0 = 0;         
    IPC4bits.CNIP1 = 1;
    IPC4bits.CNIP2 = 1;     //Change in IO Notifcation priority 6.
}

//This function implements the IO checks and LED blinking functions
void IOcheck() {
    if(PORTAbits.RA2 == 0 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 1) {  //If PB1 is pressed 
        uint16_t value;
        value=do_ADC();
        displayVoltage(value);
    }else if(PORTAbits.RA4 == 0 && PORTBbits.RB4 == 1 && PORTAbits.RA2 == 1) { //IF PB2 is pressed 
        uint16_t value;
        value=do_ADC();
        displayResistance(value);
    }else if(PORTBbits.RB4 == 0 && PORTAbits.RA4 == 1 && PORTAbits.RA2 == 1) {  //IF PB3 is pressed 
        Idle();//set MCU to idle mode
    }
}

void displayVoltage(value) {
    float vol=0;
    vol=value*(3/(pow(2,10)-1));//Vin = Vref * ADCBUF/(2^10 - 1) 
    char str[20];
    sprintf(str,"%1.3f",vol);
     //display voltage
    Disp2String(" \r VOLTMETER Voltage=");
    Disp2String(str);
    XmitUART2('V',1);
}

void displayResistance(value) {
    //Vin = Vref * (R-DUT/(1000 + R-DUT))
    //Vin/Vref = ADCBUF/1023 
    //R-DUT = 1000*(ADCBUF/1023)/(1-ADCBUF/1023)
    float R= 1000*(value/1023)/(1-value/1023);
    char str[20];
    sprintf(str,"%1.3f",R);
    //display resistance
    Disp2String(" \r OHMMETER Resistance="); 
    Disp2String(str);
    XmitUART2('Ω',1);
}

//Interrupt routine for _CNInterrupt
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void) {
    Nop();
}



