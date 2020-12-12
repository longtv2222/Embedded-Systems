/*
 * File:   newmainXC16.c
 * Author: blaob
 *
 * Created on December 2, 2020, 5:48 PM
 */

#include <xc.h>
#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "ADC.h"
#include "UART2.h"
#include "ChangeClk.h"
#include "Ios.h"

#pragma config IESO = OFF // 2 Speed Startup disabled
#pragma config FNOSC = FRC // Start up CLK = 8 MHz
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor off
#pragma config SOSCSEL = SOSCLP // Secondary oscillator for Low Power Operation
#pragma config POSCFREQ = MS //Primary Oscillator/External clk freq betwn
#pragma config OSCIOFNC = ON //CLKO output disabled on pin 8, use as IO.
#pragma config POSCMOD = NONE // Primary oscillator mode is disabled 

#define Nop() {__asm__ volatile ("nop");}
#define ClrWdt() {__asm__ volatile ("clrwdt");}
#define Sleep() {__asm__ volatile ("pwrsav #0");}   //Sleep() - put MCU in sleep mode - CPU and some peripherals off
#define Idle() {__asm__ volatile ("pwrsav #1");}    //Idle() - put MCU in idle mode - only CPU off
#define dsen() {__asm__ volatile ("BSET DSCON, #15");} //


unsigned int clock_val;
int main(void) {
    NewClk(32);     //Use system clock 32kHz
    IOinit();   //Initialize IO ports
    CNinit();   //Initialize change notification
    InitUART2();   //Initialize UART2
    
    // Change Clock
    clock_val = 32;
    NewClk(clock_val); // 8 for 8 MHz; 500 for 500 kHz; 32 for 32 kHz
     ///////////////PULSE TEST SETTING 1 
//    Change Clock
    NewClk(8); // 8 for 8 MHz; 500 for 500 kHz; 32 for 32 kHz

    //Clock output on REFO/RB15 ? PULSE GEN Testing purposes only
    TRISBbits.TRISB15 = 0; // Set RB15 as output for REFO
    REFOCONbits.ROSSLP = 1; // Ref oscillator is disabled in sleep
    REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
    REFOCONbits.RODIV = 0b0011;
    REFOCONbits.ROEN = 1; // Ref oscillator is enabled 
    
    
    ///////////////PULSE TEST SETTING 2
    // Change Clock
//    NewClk(8); // 8 for 8 MHz; 500 for 500 kHz; 32 for 32 kHz
//
//    //Clock output on REFO/RB15 ? PULSE GEN Testing purposes only
//    TRISBbits.TRISB15 = 0; // Set RB15 as output for REFO
//    REFOCONbits.ROSSLP = 1; // Ref oscillator is disabled in sleep
//    REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
//    REFOCONbits.RODIV = 0b1111;
//    REFOCONbits.ROEN = 1; // Ref oscillator is enabled
    
    ///////////////PULSE TEST SETTING 3
    // Change Clock
//    NewClk(500); // 8 for 8 MHz; 500 for 500 kHz; 32 for 32 kHz
//
//    //Clock output on REFO/RB15 ? PULSE GEN Testing purposes only
//    TRISBbits.TRISB15 = 0; // Set RB15 as output for REFO
//    REFOCONbits.ROSSLP = 1; // Ref oscillator is disabled in sleep
//    REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
//    REFOCONbits.RODIV = 0b1001;
//    REFOCONbits.ROEN = 1; // Ref oscillator is enabled
    
   ///////////////PULSE TEST SETTING 4
    // Change Clock
//    NewClk(500); // 8 for 8 MHz; 500 for 500 kHz; 32 for 32 kHz
//
//    //Clock output on REFO/RB15 ? PULSE GEN Testing purposes only
//    TRISBbits.TRISB15 = 0; // Set RB15 as output for REFO
//    REFOCONbits.ROSSLP = 1; // Ref oscillator is disabled in sleep
//    REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
//    REFOCONbits.RODIV = 0b0111;
//    REFOCONbits.ROEN = 1; // Ref oscillator is enabled 

    while(1) {}
    
    return 0;
}


