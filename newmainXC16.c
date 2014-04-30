/*
 * File:   newmainXC16.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 18:33
 */

//#define __dsPIC33FJ128MC802__

#include "xc.h"
#include "dsp.h"
#include "../peripheral_30F_24H_33F/pps.h"
#include "../peripheral_30F_24H_33F/timer.h"
#include "../peripheral_30F_24H_33F/uart.h"

#include "Clock.h"  //done
#include "PWM.h"    //done
#include "QEI.h"
#include "UART.h"
#include "ADC.h"

/* Configuration Bit Settings */
_FOSCSEL(FNOSC_FRC)
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT)
_FWDT(FWDTEN_OFF)                               //disable the watchdog timer   
_FPOR(FPWRT_PWR32)
_FICD(ICS_PGD1 & JTAGEN_OFF)                    //disable JTAG, enable debugging on PGx1 pins

int main(void) {
    Clock_Init();
    init_PWM();

    while(1);

    CloseQEI();
    return 0;
}
