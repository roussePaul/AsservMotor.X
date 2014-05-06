/*
 * File:   Timers.h
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 30 avril 2014, 14:10
 */

#include "../dsPIC33F/h/p33FJ128MC802.h"
#include "../peripheral_30F_24H_33F/Generic.h"
#include "../peripheral_30F_24H_33F/timer.h"

void InitTMR1(void)
{
    /* config: T1_OFF & T1_IDLE_CON & T1_SOURCE_INT & T1_PS_1_64 */
    // Interrupt period = 0.005 sec with a 64 prescaler
    OpenTimer1(T1_OFF & T2_GATE_OFF & T1_IDLE_CON & T1_PS_1_64 & T1_SOURCE_INT,3124);
    ConfigIntTimer1(T1_INT_PRIOR_6 & T1_INT_ON);
    T1CONbits.TON = 1; // Turn on timer 1
    return;
}

void InitTMR2(void)
{
    //On ouvre le Timer2 qui gère l'asservissement toutes les 10ms
    OpenTimer2(T2_OFF & T2_GATE_OFF & T2_IDLE_CON & T2_SOURCE_INT & T2_PS_1_64 & T2_32BIT_MODE_OFF, 6249);
    ConfigIntTimer2(T2_INT_PRIOR_4 & T2_INT_ON); //Interruption ON et priorité 3
    T2CONbits.TON = 1; // Turn on timer 2
    return;
}

void InitTMR3(void)
{
    //On ouvre le Timer2 qui gère l'asservissement toutes les 10ms
    OpenTimer2(T3_OFF & T3_GATE_OFF & T3_IDLE_CON & T3_SOURCE_INT & T3_PS_1_64, 6249);
    ConfigIntTimer3(T3_INT_PRIOR_4 & T3_INT_ON); //Interruption ON et priorité 3
    T3CONbits.TON = 1; // Turn on timer 3
    return;
}