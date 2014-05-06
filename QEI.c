/*
 * File:   QEI.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 18:33
 */

#include "../dsPIC33F/h/p33FJ128MC802.h"
#include "../peripheral_30F_24H_33F/Generic.h"
#include "../peripheral_30F_24H_33F/qei.h"
#include "../peripheral_30F_24H_33F/timer.h"
#include "QEI.h"
#include "UART.h"
#include "PWM.h"

int ofPOS1CNT;
int ofPOS2CNT;
unsigned int POS1CNTcopy;
unsigned int POS2CNTcopy;
long AngPos1[2]; // Two variables are used for Speed Calculation
long AngPos2[2]; // Two variables are used for Speed Calculation
int Speed1;
int Speed2;

void openQEI(void)
{
    /* CONFIG1: QEI_MODE_x4_MATCH & QEI_NORMAL_IO & QEI_INPUTS_NOSWAP & QEI_IDLE_CON */
    /* CONFIG2: QEI_QE_CLK_DIVIDE_1_256 & QEI_QE_OUT_ENABLE & POS_CNT_ERR_INT_DISABLE & MATCH_INDEX_PHASEA_LOW & MATCH_INDEX_PHASEB_LOW */
    OpenQEI1(QEI_MODE_x4_MATCH & QEI_NORMAL_IO & QEI_INPUTS_NOSWAP & QEI_IDLE_CON,
            QEI_QE_CLK_DIVIDE_1_256 & QEI_QE_OUT_ENABLE & POS_CNT_ERR_INT_DISABLE & MATCH_INDEX_PHASEA_LOW & MATCH_INDEX_PHASEB_LOW);
    OpenQEI2(QEI_MODE_x4_MATCH & QEI_NORMAL_IO & QEI_INPUTS_NOSWAP & QEI_IDLE_CON,
            QEI_QE_CLK_DIVIDE_1_256 & QEI_QE_OUT_ENABLE & POS_CNT_ERR_INT_DISABLE & MATCH_INDEX_PHASEA_LOW & MATCH_INDEX_PHASEB_LOW);

    MAX1CNT = MAXCNT_VALUE;
    MAX2CNT = MAXCNT_VALUE;

    POS1CNT = 0x00;
    POS2CNT = 0x00;

    ofPOS1CNT = 0;
    ofPOS2CNT = 0;
    POS1CNTcopy = 0;
    POS2CNTcopy = 0;
    AngPos1[0] = 0;
    AngPos1[1] = 0;
    AngPos2[0] = 0;
    AngPos2[1] = 0;
    Speed1 = 0;
    Speed2 = 0;
    
    _QEA1R = 7; //Module QEI 1 phase A sur RP7, RB7
    _QEB1R = 8; //Module QEI 1 phase B sur RP8, RB8
    _INDX1R = 6 ; //Module QEI 1 index sur RP6, RB6
    _QEA2R = 10; //Module QEI 2 phase A sur RP10, RB10
    _QEB2R = 9; //Module QEI 2 phase B sur RP9, RB9
    _INDX2R = 11; //Module QEI 2 index sur RP11, RB11

    ConfigIntQEI1(QEI_INT_PRI_5 & QEI_INT_DISABLE);
    ConfigIntQEI2(QEI_INT_PRI_5 & QEI_INT_DISABLE);

    return;
}
void closeQEI(void)
{
    CloseQEI1();
    CloseQEI2();
    return;
}


/* Interruptions de gestion des over/underflow de POSCNT */
void __attribute__((interrupt,auto_psv)) _QEI1Interrupt(void)
{
    DisableIntQEI1;
    _QEI1IF = 0;
    WriteUART('1');
    switch(QEI1CONbits.UPDN)
    {
        case 0 :
            ofPOS1CNT--;
            WriteUART('d');
            break;
        case 1 :
            ofPOS1CNT++;
            WriteUART('u');
            break;
    }
    WriteUART(ofPOS1CNT);
    WriteUART('\n');

    EnableIntQEI1;
    return;
}
void __attribute__((interrupt,auto_psv)) _QEI2Interrupt(void)
{
    DisableIntQEI2;
    _QEI2IF = 0;

    WriteUART('2');
    switch(QEI2CONbits.UPDN)
    {
        case 0 :
            ofPOS2CNT--;
            WriteUART('d');
            break;
        case 1 :
            ofPOS2CNT++;
            WriteUART('u');
            break;
    }
    WriteUART(ofPOS2CNT);
    WriteUART('\n');

    EnableIntQEI2;
    return;
}


void __attribute__((interrupt,auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0; // Clear timer 1 interrupt flag

    /* Calcul de la position des roues */
    POS1CNTcopy = (unsigned int)POS1CNT;
    POS2CNTcopy = (unsigned int)POS2CNT;

    AngPos1[1] = AngPos1[0];
    AngPos1[0] = (long)((long)POS1CNTcopy + ofPOS1CNT);
    WriteUART('1');
    WriteUART('p');
    WriteUART(POS1CNTcopy);
    WriteUART('\n');
    //SetSpeed1(POS1CNTcopy);

    AngPos2[1] = AngPos2[0];
    AngPos2[0] = (long)((long)POS2CNTcopy + ofPOS2CNT);
    WriteUART('2');
    WriteUART('p');
    WriteUART(POS2CNTcopy);
    WriteUART('\n');
    SetSpeed2(POS2CNTcopy);


    Speed1 = (int)(AngPos1[0] - AngPos1[1]);
//    if (Speed1 >= 0)
//    {
//        if (Speed1 >= (HALFMAXSPEED))
//            Speed1 = Speed1 - MAXSPEED;
//    }
//    else
//    {
//        if (Speed1 < -(HALFMAXSPEED))
//            Speed1 = Speed1 + MAXSPEED;
//    }
//    Speed1 *= 2;
    WriteUART('1');
    WriteUART('s');
    WriteUART(Speed1);
    WriteUART('\n');

    Speed2 = (int)(AngPos2[0] - AngPos2[1]);
    WriteUART('2');
    WriteUART('s');
    WriteUART(Speed2);
    WriteUART('\n');

    return;
}