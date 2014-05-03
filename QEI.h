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

    #define EnableIntQEI1                   _QEI1IE = 1
    #define DisableIntQEI1                  _QEI1IE = 0
    #define SetPriorityIntQEI1(priority)    _QEI1IP = priority

    #define EnableIntQEI2                   _QEI2IE = 1
    #define DisableIntQEI2                  _QEI2IE = 0
    #define SetPriorityIntQEI2(priority)    _QEI2IP = priority

    extern int AngPos1[2] = {0,0}; // Two variables are used for Speed Calculation
    extern int AngPos2[2] = {0,0}; // Two variables are used for Speed Calculation

    extern void openQEI(void);
    extern void closeQEI(void);


#ifdef	__cplusplus
}
#endif

#endif	/* QEI_H */

