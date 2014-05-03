/*
 * File:   Timers.h
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 30 avril 2014, 14:10
 */

#include "../dsPIC33F/h/p33FJ128MC802.h"
#include "../peripheral_30F_24H_33F/Generic.h"
#include "../peripheral_30F_24H_33F/timer.h"

void initTMR1(void)
{
TMR1 = 0; // Reset timer counter
T1CONbits.TON = 0; // Turn off timer 1
T1CONbits.TSIDL = 0; // Continue operation during sleep
T1CONbits.TGATE = 0; // Gated timer accumulation disabled
T1CONbits.TCS = 0; // use Tcy as source clock
T1CONbits.TCKPS = 2; // Tcy / 64 as input clock
PR1 = 1728; // Interrupt period = 0.0075 sec with a 64 prescaler
IFS0bits.T1IF = 0; // Clear timer 1 interrupt flag
IEC0bits.T1IE = 1; // Enable timer 1 interrupts
T1CONbits.TON = 1; // Turn on timer 1
return;
}

void initTMR2(void)
{
    //On ouvre le Timer2 qui gère l'asservissement toutes les 10ms
    OpenTimer2(T2_ON & T2_GATE_OFF & T2_PS_1_256 & T2_32BIT_MODE_OFF & T2_SOURCE_INT, 0x600);
    ConfigIntTimer2(T2_INT_PRIOR_3 & T2_INT_ON); //Interruption ON et priorité 3
}