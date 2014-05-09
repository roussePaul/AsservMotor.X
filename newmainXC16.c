/*
 * File:   newmainXC16.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 18:33
 */

//#define __dsPIC33FJ128MC802__

#include "xc.h"
#include "dsp.h"
#include "../peripheral_30F_24H_33F/Generic.h"

#include "Clock.h"  //done
#include "PWM.h"    //done
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
    Clock_Init();
    OpenUART();
    openQEI();
    openPWM();
    InitTMR1();
    mSET_CPU_IP(0);

    enablePWM;
    ch1Run;
    ch2Run;
    setSpeed1(-0x03FF);
    setSpeed2(0x03FF);
    PORTBbits.RB14 = 1;
    while(1);

    closeQEI();
    CloseUART();
    return 0;
}
