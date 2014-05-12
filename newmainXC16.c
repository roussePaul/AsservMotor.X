/*
 * File:   newmainXC16.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 18:33
 */

//#define __dsPIC33FJ128MC802__

#define FCY 40000000UL

#include <stdio.h>
#include <stdlib.h>

#include "Clock.h"  //done
#include "PWM.h"    //done

#include "xc.h"
#include "../peripheral_30F_24H_33F/Generic.h"

#include "QEI.h"
#include "UART.h"
#include "ADC.h"
#include "Timers.h"
#include "PID.h"
#include "Asservissement.h"


/* Configuration Bit Settings */
_FOSCSEL(FNOSC_FRC)
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT)
_FWDT(FWDTEN_OFF)                               //disable the watchdog timer   
_FPOR(FPWRT_PWR32)
_FICD(ICS_PGD1 & JTAGEN_OFF)                    //disable JTAG, enable debugging on PGx1 pins

int main(void) {
    char c;

    INTCON1bits.NSTDIS = 1;
    openQEI();
    OpenUART();
//    openPWM();
//    InitTMR2();

    Clock_Init();
//    enablePWM;
//    ch1Run;
//    ch2Run;

    initInterpreter();
    initOdometrie();
    initAsservissement();

    while(1)
    {
        c = (char)ReadUART1();

        if(buildCommande())
        {
            interpreteCommande();
            clearCommande();
        }
    }

    return 0;
}
