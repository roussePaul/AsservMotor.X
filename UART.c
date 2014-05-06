/*
 * File:   ADC.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 18:33
 */

#include "../dsPIC33F/h/p33FJ128MC802.h"
#include "../peripheral_30F_24H_33F/generic.h"
#include "../peripheral_30F_24H_33F/uart.h"

void OpenUART(void)
{
    //*************************************************************
    // Unlock Registers
    //*************************************************************
    __builtin_write_OSCCONL(OSCCON & ~(1<<6));
    //************************************************************
    // Configure Input Functions
    // (See Table 30-1)
    //*************************************************************
    //*******************************
    // Assign U1Rx To Pin RP3
    //***************************
    _U1RXR = 3; //RPINR18bits.U1RXR
    //*************************************************************
    // Configure Output Functions
    // (See Table 30-2)
    //*************************************************************
    //***************************
    // Assign U1Tx To Pin RP2
    //***************************
    _RP2R = 3; //RPOR1bits.RP2R

    //*************************************************************
    // Lock Registers
    //*************************************************************
    __builtin_write_OSCCONL(OSCCON | (1<<6));

    OpenUART1(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_UEN_00
            & UART_EN_WAKE & UART_DIS_LOOPBACK & UART_DIS_ABAUD & UART_UXRX_IDLE_ONE
            & UART_BRGH_SIXTEEN & UART_ODD_PAR_8BIT & UART_1STOPBIT,
            UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO & UART_SYNC_BREAK_DISABLED
            & UART_TX_ENABLE & UART_INT_RX_CHAR & UART_ADR_DETECT_DIS,
            86); // Baud Rate = 114942

}

void CloseUART(void)
{
    CloseUART1();
    return;
}

void WriteUART(unsigned int data)
{
    WriteUART1(data);
    return;
}
void putsUART(unsigned int *buffer)
{
    putsUART1(buffer);
    return;
}