/* 
 * File:   Asservissement.h
 * Author: Paulo
 *
 * Created on 12 mai 2014, 11:11
 */

#ifndef ASSERVISSEMENT_H
#define	ASSERVISSEMENT_H

#ifdef	__cplusplus
extern "C" {
#endif

    enum AsservType {ASSERV_POSITION, ASSERV_VITESSE};

    
    void runAsservissement();
    void setAsservType(AsservType asserv);

#ifdef	__cplusplus
}
#endif

#endif	/* ASSERVISSEMENT_H */

