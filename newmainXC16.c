/*
 * File:   newmainXC16.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 18:33
 */

//#define __dsPIC33FJ128MC802__

#define FCY 40000000UL

#include "Clock.h"  //done
#include "PWM.h"    //done

#include "xc.h"
#include "../peripheral_30F_24H_33F/Generic.h"

#include "QEI.h"
#include "UART.h"
#include "ADC.h"
#include "Timers.h"
#include "PID.h"

/* Configuration Bit Settings */
_FOSCSEL(FNOSC_FRC)
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT)
_FWDT(FWDTEN_OFF)                               //disable the watchdog timer   
_FPOR(FPWRT_PWR32)
_FICD(ICS_PGD1 & JTAGEN_OFF)                    //disable JTAG, enable debugging on PGx1 pins

int main(void) {
    INTCON1bits.NSTDIS = 1;
    openQEI();
    OpenUART();
//    openPWM();
//    InitTMR2();

    Clock_Init();
//    enablePWM;
//    ch1Run;
//    ch2Run;

    while(1);

    return 0;
}
