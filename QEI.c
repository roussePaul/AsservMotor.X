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

    _QEA1R = 9; //Module QEI 1 phase A sur RP9, RB9
    _QEB1R = 22; //Module QEI 1 phase B sur RP22, RC6
    _QEA2R = 23; //Module QEI 2 phase A sur RP23, RC7
    _QEB2R = 24; //Module QEI 2 phase B sur RP24, RC8


    POS1CNT = 0;
    POS2CNT = 0;
    /* CONFIG1:  */
    /* CONFIG2: QEI_QE_CLK_DIVIDE_1_1 & QEI_QE_OUT_ENABLE & POS_CNT_ERR_INT_DISABLE & MATCH_INDEX_PHASEA_HIGH & MATCH_INDEX_PHASEB_HIGH */

}


int POS1CNTcopy = 0;
int POS2CNTcopy = 0;
void PositionCalculation(void)
{
    POS1CNTcopy = (int)POS1CNT;
    POS2CNTcopy = (int)POS2CNT;
    
    if (POS1CNTcopy < 0)
        POS1CNTcopy = -POS1CNTcopy;
    AngPos1[1] = AngPos1[0];
    AngPos1[0] = (unsigned int)(((unsigned long)POS1CNTcopy * 2048)/125);

    if (POS2CNTcopy < 0)
        POS2CNTcopy = -POS2CNTcopy;
    AngPos2[1] = AngPos2[0];
    AngPos2[0] = (unsigned int)(((unsigned long)POS2CNTcopy * 2048)/125);

    // 0 <= POSCNT <= 1999 to 0 <= AngPos <= 32752
    return;
}

void CloseQEI(void)
{
    CloseQEI1();
    CloseQEI2();
}