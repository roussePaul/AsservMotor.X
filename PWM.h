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

    extern void init_PWM(void);
    extern void disable_PWM(void);
    extern void enable_PWM(void);
    extern void ch1Break(void);
    extern void ch1Run(void);
    extern void ch1SetSpeed(int);
    extern void ch2Break(void);
    extern void ch2Run(void);
    extern void ch2SetSpeed(int);


#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

