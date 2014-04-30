/*
 * File:   QEI.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 18:33
 */

#include "../dsPIC33F/h/p33FJ128MC802.h"
#include "../peripheral_30F_24H_33F/pps.h"
#include "../peripheral_30F_24H_33F/qei.h"

void init_QEI()
{
    /* QEI enabled (x4 mode) with position counter reset by match (MAXxCNT) */
    QEI1CONbits.QEIM = 0b111;
    QEI2CONbits.QEIM = 0b111;
    MAX1CNT = 0xFFFF;
    MAX2CNT = 0xFFFF;
    //QEI1CONbits.SWPAB = 0;
    //QEI2CONbits.SWPAB = 0;

    /* Digital filter outputs are enabled on QEAx/QEBx/INDXx pins */
    /* with Digital Filter Clock Divide 1:1 */
    DFLT1CONbits.QEOUT = 1;
    DFLT2CONbits.QEOUT = 1;
    DFLT1CONbits.QECK = 0b000;
    DFLT2CONbits.QECK = 0b000;
}

int AngPos[2] = {0,0}; // Two variables are used for Speed Calculation
int POSCNTcopy = 0;
void PositionCalculation(void)
{
    POSCNTcopy = (int)POSCNT;
    if (POSCNTcopy < 0)
        POSCNTcopy = -POSCNTcopy;
    AngPos[1] = AngPos[0];
    AngPos[0] = (unsigned int)(((unsigned long)POSCNTcopy * 2048)/125);
    // 0 <= POSCNT <= 1999 to 0 <= AngPos <= 32752
    return;
}