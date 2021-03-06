/*
 * File:   PWM.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 18:33
 */

#include "../dsPIC33F/h/p33FJ128MC802.h"
#include "../peripheral_30F_24H_33F/pwm.h"
#include "PWM.h"
#include "math.h"

void openPWM(void)
{
    disablePWM;                     /* Disable the PWM Module */

    P1TPER = PER;                            /* P1TPER = 40MHz / (F_PWM * 1) - 1 = 1023, where F_PWM
                                             is the desired switching frequency and 40MHz is cycle frequency.
                                             here F_PWM = 39,062.5Hz */
    P1TCONbits.PTMOD = 0b00;                 /* PWM time base operates in Free Running mode */

    P1DC1 = 0;                               /* Initial Duty cycle */
    P1DC2 = 0;                               /* Maxiaml Duty cycle is 2047 ( = 2 * P1TPER +1 ) */

    /*~~~~~~~~~~~~~~~~~~~~~~~ PWM1 Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    PWM1CON1bits.PEN1H = 0;                  /* PWM1H is controlled by GPIO module */
    PWM1CON1bits.PEN1L = 1;                  /* PWM1L is controlled by PWM module */
    PWM1CON1bits.PMOD1 = 1;                  /* Select Independent Output PWM mode */
    
    PWM1CON1bits.PEN2H = 0;                  /* PWM2H is controlled by GPIO module */
    PWM1CON1bits.PEN2L = 1;                  /* PWM2L is controlled by PWM module */
    PWM1CON1bits.PMOD2 = 1;                  /* Select Independent Output PWM mode */

    PWM1CON1bits.PEN3H = 0;                  /* PWM3H is controlled by GPIO module */
    PWM1CON1bits.PEN3L = 0;                  /* PWM3L is controlled by GPIO module */
    /* others are controlled by GPIO module */
    _TRISB14 = 0;
    _TRISB12 = 0;

    ch1Break;
    ch2Break;
}

void setSpeed1(int s)
{
    _LATB14 = (s & 0x8000)>>15 ;
    if(s<0)
    {
        s = -s;
    }
    P1DC1 = MAX(s,MAXDC);
    return;
}

void setSpeed2(int s)
{
    _LATB12 = (s & 0x8000)>>15 ;
    if(s<0)
    {
        s = -s;
    }
    P1DC2 = MAX(s,MAXDC);
    return;
}