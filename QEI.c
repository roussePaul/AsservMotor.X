/*
 * File:   QEI.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 18:33
 */

#include "../dsPIC33F/h/p33FJ128MC802.h"
#include "../peripheral_30F_24H_33F/Generic.h"
#include "../peripheral_30F_24H_33F/qei.h"
#include "QEI.h"
#include "UART.h"

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


int ofPOS1CNT = 0;
int ofPOS2CNT = 0;
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



unsigned int AngPos1[2] = {0,0}; // Two variables are used for Speed Calculation
unsigned int AngPos2[2] = {0,0}; // Two variables are used for Speed Calculation
int Speed1,Speed2;
unsigned int POS1CNTcopy = 0;
unsigned int POS2CNTcopy = 0;
void PositionCalculation(void)
{
    POS1CNTcopy = (int)POS1CNT;
    POS2CNTcopy = (int)POS2CNT;
    
    if (POS1CNTcopy < 0)
        POS1CNTcopy = -POS1CNTcopy;
    AngPos1[1] = AngPos1[0];
    AngPos1[0] = (unsigned int)(((unsigned long)POS1CNTcopy * 2048)/125);
    WriteUART('1');
    WriteUART('p');
    WriteUART(AngPos1[0]);
    WriteUART('\n');

    if (POS2CNTcopy < 0)
        POS2CNTcopy = -POS2CNTcopy;
    AngPos2[1] = AngPos2[0];
    AngPos2[0] = (unsigned int)(((unsigned long)POS2CNTcopy * 2048)/125);
    WriteUART('2');
    WriteUART('p');
    WriteUART(AngPos2[0]);
    WriteUART('\n');

    // 0 <= POSCNT <= 1999 to 0 <= AngPos <= 32752
    return;
}
void InitTMR1(void)
{
    TMR1 = 0; // Reset timer counter
    T1CONbits.TON = 0; // Turn off timer 1
    T1CONbits.TSIDL = 0; // Continue operation during sleep
    T1CONbits.TGATE = 0; // Gated timer accumulation disabled
    T1CONbits.TCS = 0; // use Tcy as source clock
    T1CONbits.TCKPS = 2; // Tcy / 64 as input clock
    PR1 = 1728; // Interrupt period = 0.0075 sec with a 64 prescaler
    IFS0bits.T1IF = 0; // Clear timer 1 interrupt flag
    IEC0bits.T1IE = 1; // Enable timer 1 interrupts
    T1CONbits.TON = 1; // Turn on timer 1
    return;
}
#define MAX_CNT_PER_REV (500 * 4 - 1)
#define MAXSPEED (unsigned int)(((unsigned long)MAX_CNT_PER_REV*2048)/125)
#define HALFMAXSPEED (MAXSPEED>>1)

void __attribute__((interrupt,auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0; // Clear timer 1 interrupt flag
    PositionCalculation();

    Speed1 = AngPos1[0] - AngPos1[1];
    if (Speed1 >= 0)
    {
        if (Speed1 >= (HALFMAXSPEED))
            Speed1 = Speed1 - MAXSPEED;
    }
    else
    {
        if (Speed1 < -(HALFMAXSPEED))
            Speed1 = Speed1 + MAXSPEED;
    }
    Speed1 *= 2;
    WriteUART('1');
    WriteUART('s');
    WriteUART(Speed1);
    WriteUART('\n');

    Speed2 = AngPos2[0] - AngPos2[1];
    if (Speed2 >= 0)
    {
        if (Speed2 >= (HALFMAXSPEED))
            Speed2 = Speed1 - MAXSPEED;
    }
    else
    {
        if (Speed2 < -(HALFMAXSPEED))
            Speed2 = Speed2 + MAXSPEED;
    }
    Speed2 *= 2;
    WriteUART('2');
    WriteUART('s');
    WriteUART(Speed2);
    WriteUART('\n');

    return;
}