/* 
 * File:   UART.h
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 20:55
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

    extern void OpenUART(void);
    extern void CloseUART(void);
    extern void WriteUART(unsigned int);
    extern void putsUART1(unsigned int *buffer);
    extern int ReadUART();

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

