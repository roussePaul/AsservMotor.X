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

#define MAX_POSCNT 65535
    
    typedef union
    {
        struct {
              unsigned int poscnt:16;
              int overflow:16;
        };
        long cnt;
    } enc_cnt;


    float DAngle1,DAngle2;


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

/*
 * Odométrie
*/

// Paramètres géométriques du robot
#define R_ROUE 0.05
#define ENTRAXE 0.20

// Interval de temps d'execution de l'odométrie
#define DT 0.005

    // Vitesse des roues codeuses
    float v1,v2;

    struct Position {
        float x,y,t;
    } position;
    struct Vitesse {
        float v,w;
    } vitesse;

    void initOdometrie();
    void resetOdometrie();

    void computeQEIsDeltaAngle();
    float computeDeltaAngle(enc_cnt *lastPosition, enc_cnt *currentPosition);
    void updateCnt(enc_cnt *last, enc_cnt *current);

    void computeOdometrie(float dThetaGauche, float dThetaDroite);      // Calcul de la position et des vitesses
    void sendOdometrie();       // Envoie la position et la vitesse du robot sur le port série

    void getVRoues(float v, float w, float *vg, float *vd);     // Renvoie la vitesse des roues

#ifdef	__cplusplus
}
#endif

#endif	/* QEI_H */

