/* 
 * File:   PID.h
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 7 mai 2014, 10:14
 */

#ifndef PID_H
#define	PID_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    int initPIDs(void);
    void setConsignePIDs(float vg, float vd);
    void runPIDs();

#ifdef	__cplusplus
}
#endif

#endif	/* PID_H */

