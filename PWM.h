/*
 * File:   PWM.h
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 18:33
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

    #define enable_PWM                      P1TCONbits.PTEN = 1
    #define disable_PWM                     P1TCONbits.PTEN = 0

    extern void openPWM(void);

    #define ch1Break                        P1OVDCONbits.POVD2L = 0
    #define ch1Run                          P1OVDCONbits.POVD2L = 1
    extern void SetSpeed1(int);

    #define ch2Break                        P1OVDCONbits.POVD2L = 0
    #define ch2Run                          P1OVDCONbits.POVD2L = 1
    extern void SetSpeed2(int);

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

