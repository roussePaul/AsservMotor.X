/*
 * File:   QEI.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 18:33
 */

#include "../dsPIC33F/h/p33FJ128MC802.h"
#include "../peripheral_30F_24H_33F/pps.h"
#include "../peripheral_30F_24H_33F/qei.h"
#include "QEI.h"

void openQEI(void)
{
    /* QEI enabled (x4 mode) with position counter reset by match (MAXxCNT) */
    //QEI1CONbits.QEIM = 0b111;
    //QEI2CONbits.QEIM = 0b111;
    //QEI1CONbits.SWPAB = 0;
    //QEI2CONbits.SWPAB = 0;

    /* Digital filter outputs are enabled on QEAx/QEBx/INDXx pins */
    /* with Digital Filter Clock Divide 1:1 */
    //DFLT1CONbits.QEOUT = 1;
    //DFLT2CONbits.QEOUT = 1;
    //DFLT1CONbits.QECK = 0b000;
    //DFLT2CONbits.QECK = 0b000;

    /* CONFIG1: QEI_MODE_x4_MATCH & QEI_NORMAL_IO & QEI_INPUTS_NOSWAP & QEI_IDLE_CON */
    /* CONFIG2: QEI_QE_CLK_DIVIDE_1_1 & QEI_QE_OUT_ENABLE & POS_CNT_ERR_INT_DISABLE & MATCH_INDEX_PHASEA_LOW & MATCH_INDEX_PHASEB_LOW */
    OpenQEI1(QEI_MODE_x4_MATCH & QEI_NORMAL_IO & QEI_INPUTS_NOSWAP & QEI_IDLE_CON,
            QEI_QE_CLK_DIVIDE_1_1 & QEI_QE_OUT_ENABLE & POS_CNT_ERR_INT_DISABLE & MATCH_INDEX_PHASEA_LOW & MATCH_INDEX_PHASEB_LOW);
    OpenQEI2(QEI_MODE_x4_MATCH & QEI_NORMAL_IO & QEI_INPUTS_NOSWAP & QEI_IDLE_CON,
            QEI_QE_CLK_DIVIDE_1_1 & QEI_QE_OUT_ENABLE & POS_CNT_ERR_INT_DISABLE & MATCH_INDEX_PHASEA_LOW & MATCH_INDEX_PHASEB_LOW);

    //ConfigIntQEI1(QEI_INT_PRI_6 & QEI_INT_DISABLE);
    //ConfigIntQEI2(QEI_INT_PRI_6 & QEI_INT_DISABLE);
    SetPriorityIntQEI1(6);
    SetPriorityIntQEI2(6);

    MAX1CNT = MAXCNT_VALUE;
    MAX2CNT = MAXCNT_VALUE;

    POS1CNT = 0x00;
    POS2CNT = 0x00;
    
    _QEA1R = 7; //Module QEI 1 phase A sur RP7, RB7
    _QEB1R = 8; //Module QEI 1 phase B sur RP8, RB8
    _INDX1R = 6 ; //Module QEI 1 index sur RP6, RB6
    _QEA2R = 10; //Module QEI 2 phase A sur RP10, RB10
    _QEB2R = 9; //Module QEI 2 phase B sur RP9, RB9
    _INDX2R = 11; //Module QEI 2 index sur RP11, RB11


    return;
}

void closeQEI(void)
{
    CloseQEI1();
    CloseQEI2();
    return;
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