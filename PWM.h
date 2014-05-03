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

//    extern void disable_PWM(void);
//    extern void enable_PWM(void);

    #define ch1Break                        P1OVDCONbits.POVD2L = 0
    #define ch1Run                          P1OVDCONbits.POVD2L = 1
//    extern void ch1Break(void);
//    extern void ch1Run(void);
    extern void ch1SetSpeed(unsigned int);

    #define ch2Break                        P1OVDCONbits.POVD2L = 0
    #define ch2Run                          P1OVDCONbits.POVD2L = 1
//    extern void ch2Break(void);
//    extern void ch2Run(void);
    extern void ch2SetSpeed(unsigned int);


#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

