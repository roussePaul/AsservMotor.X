/*
 * File:   Clock.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 18:33
 */

#include "../dsPIC33F/h/p33FJ128MC802.h"

void Clock_Init()
{
   /* Configure Oscillator to operate the device at 40MIPS
 * Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
 * Fosc= 10*(32)/(2*2)=80Mhz for Fosc, Fcy = 40MHz */

    /* Configure PLL prescaler, PLL postscaler, PLL divisor */
    PLLFBD=30;                 /* M = PLLFBD + 2 */
    CLKDIVbits.PLLPOST=0;   /* N1 = 2 */
    CLKDIVbits.PLLPRE=0;    /* N2 = 2 */

    __builtin_write_OSCCONH(0x03);            /* New Oscillator FRC w/ PLL */
    __builtin_write_OSCCONL(0x01);          /* Enable Switch */

    while(OSCCONbits.COSC != 0b011);        /* Wait for new Oscillator to become FRC w/ PLL */
    while(OSCCONbits.LOCK != 1);            /* Wait for Pll to Lock */
}