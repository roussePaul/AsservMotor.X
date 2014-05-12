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
#include "../peripheral_30F_24H_33F/pps.h"
#include "QEI.h"
#include "UART.h"
#include "PWM.h"
#include "Timers.h"
#include <math.h>
#include "math.h"

enc_cnt enc_Cnt1;
enc_cnt enc_Cnt2;
enc_cnt AngPos1[2]; // Two variables are used for Speed Calculation
enc_cnt AngPos2[2]; // Two variables are used for Speed Calculation
int Speed1;
int Speed2;

void openQEI(void)
{
    MAX1CNT = 0xFFFF;
    MAX2CNT = 0xFFFF;

//    POS1CNT = 0xF000;
//    POS2CNT = 0x0033;

    enc_Cnt1.cnt = 0;
    enc_Cnt2.cnt = 0;
    AngPos1[0].cnt = 0;
    AngPos1[1].cnt = 0;
    AngPos2[0].cnt = 0;
    AngPos2[1].cnt = 0;
    Speed1 = 0;
    Speed2 = 0;

    PPSInput(IN_FN_PPS_QEA1,IN_PIN_PPS_RP6);
    PPSInput(IN_FN_PPS_QEB1,IN_PIN_PPS_RP7);
    PPSInput(IN_FN_PPS_QEB2,IN_PIN_PPS_RP8);
    PPSInput(IN_FN_PPS_QEA2,IN_PIN_PPS_RP9);

    unsigned int config1 = QEI_MODE_x4_MATCH & QEI_NORMAL_IO & QEI_IDLE_CON & QEI_INDEX_RESET_DISABLE;
    //& (QEI_DIR_SEL_CNTRL & QEI_INT_CLK & QEI_CLK_PRESCALE_1 & QEI_GATED_ACC_DISABLE & QEI_UP_COUNT);
    unsigned int config2 = QEI_QE_CLK_DIVIDE_1_256 & QEI_QE_OUT_ENABLE & POS_CNT_ERR_INT_DISABLE;

    OpenQEI1(config1 & QEI_INPUTS_NOSWAP,config2);
    OpenQEI2(config1 & QEI_INPUTS_SWAP,config2);
    ConfigIntQEI1(QEI_INT_PRI_5 & QEI_INT_ENABLE);
    ConfigIntQEI2(QEI_INT_PRI_5 & QEI_INT_ENABLE);
    InitTMR1();
}
void closeQEI(void)
{
    CloseQEI1();
    CloseQEI2();
}


/* Interruptions de gestion des over/underflow de POSCNT */
void __attribute__((interrupt,auto_psv)) _QEI1Interrupt(void)
{
//    WriteUART('1');
    if(QEI1CONbits.UPDN)
    {
        enc_Cnt1.overflow++;
//        WriteUART('u');
    }
    else
    {
        enc_Cnt1.overflow--;
//        WriteUART('d');
    }
//    WriteUART(enc_Cnt1.overflow);
//    WriteUART('\n');
    
    _QEI1IF = 0;
}
void __attribute__((interrupt,auto_psv)) _QEI2Interrupt(void)
{
//    WriteUART('2');
    if(QEI2CONbits.UPDN)
    {
        enc_Cnt2.overflow++;
//        WriteUART('u');
    }
    else
    {
        enc_Cnt2.overflow--;
//        WriteUART('d');
    }
//    WriteUART(enc_Cnt2.overflow);
//    WriteUART('\n');

    _QEI2IF = 0;
}


void __attribute__((interrupt,auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0; // Clear timer 1 interrupt flag



    computeQEIsDeltaAngle();

    computeOdometrie(DAngle1, DAngle2);


}

void computeQEIsDeltaAngle()
{

    /* Calcul de la position des roues */
    enc_Cnt1.poscnt = (unsigned int)POS1CNT;
    enc_Cnt2.poscnt = (unsigned int)POS2CNT;

    AngPos1[1] = AngPos1[0];
    AngPos1[0] = enc_Cnt1;
    updateCnt(&(AngPos1[1]),&(AngPos1[0]));
    DAngle1 = computeDeltaAngle(&(AngPos1[1]),&(AngPos1[0]));
//    WriteUART('1');
//    WriteUART('p');
//    WriteUART(enc_Cnt1.poscnt);
//    WriteUART('\n');

    AngPos2[1] = AngPos2[0];
    AngPos2[0] = enc_Cnt2;
    updateCnt(&(AngPos2[1]),&(AngPos2[0]));
    DAngle2 = computeDeltaAngle(&(AngPos2[1]),&(AngPos2[0]));
//    WriteUART('2');
//    WriteUART('p');
//    WriteUART(enc_Cnt2.poscnt);
//    WriteUART('\n');



}

float computeDeltaAngle(enc_cnt *lastPosition, enc_cnt *currentPosition)
{
    return (currentPosition->cnt - lastPosition->cnt)/MAX_CNT_PER_REV * 2.0 *M_PI;

}

void updateCnt(enc_cnt *last, enc_cnt *current)
{
    long diff;

    diff = current->poscnt - last->poscnt;

    if(current->overflow != last->overflow)
        diff += (current->overflow-last->overflow)* MAX_POSCNT;


    current->cnt = last->cnt + diff;
}


void initOdometrie()
{
    resetOdometrie();
}

void resetOdometrie()
{
    position.x = 0.0;
    position.y = 0.0;
    position.t = 0.0;

    vitesse.v = 0.0;
    vitesse.w = 0.0;
}

void computeOdometrie(float dThetaGauche, float dThetaDroite)
{
    float vdt = R_ROUE * (dThetaGauche + dThetaDroite)/( 2.0 );
    float wdt = R_ROUE * (dThetaDroite - dThetaGauche)/( ENTRAXE );

    // calcul de la position
    position.x += vdt * cos(position.t);
    position.y += vdt * sin(position.t);
    position.t += wdt;

    // calcul de la vitesse
    vitesse.v = vdt / DT;
    vitesse.w = wdt / DT;
}

void __attribute__((interrupt,auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0; // Clear timer 1 interrupt flag

    computeQEIsDeltaAngle();
    computeOdometrie(DAngle1, DAngle2);

}

void sendOdometrie()
{
    char transmit[200];
    sprintf(transmit, "X%fY%fT%fV%fW%f",position.x, position.y, position.t, vitesse.v, vitesse.w);

    putsUART(transmit);
}
