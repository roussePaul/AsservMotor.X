/* 
 * File:   QEI.h
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 20:53
 */

#ifndef QEI_H
#define	QEI_H

#ifdef	__cplusplus
extern "C" {
#endif
    typedef union
    {
        struct {
              unsigned int poscnt:16;
              int overflow:16;
        };
        long cnt;
    } enc_cnt;

    #define EnableIntQEI1                   _QEI1IE = 1
    #define DisableIntQEI1                  _QEI1IE = 0
    #define SetPriorityIntQEI1(priority)    _QEI1IP = priority

    #define EnableIntQEI2                   _QEI2IE = 1
    #define DisableIntQEI2                  _QEI2IE = 0
    #define SetPriorityIntQEI2(priority)    _QEI2IP = priority

    extern void openQEI(void);
    extern void closeQEI(void);

    #define MAX_CNT_PER_REV (500 * 4 - 1)
    #define MAXSPEED (unsigned int)(((unsigned long)MAX_CNT_PER_REV*2048)/125)
    #define HALFMAXSPEED (MAXSPEED>>1)

#ifdef	__cplusplus
}
#endif

#endif	/* QEI_H */

