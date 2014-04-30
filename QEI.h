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

    extern int AngPos1[2] = {0,0}; // Two variables are used for Speed Calculation
    extern int AngPos2[2] = {0,0}; // Two variables are used for Speed Calculation

    extern void init_QEI(void);


#ifdef	__cplusplus
}
#endif

#endif	/* QEI_H */

