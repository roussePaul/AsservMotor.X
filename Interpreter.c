/*
 * File:   Interpreter.c
 * Author: Paul Rousse
 *
 * Created on 12 mai 2014, 18:33
 */
#include <stdlib.h>
#include <stdio.h>

#include "Asservissement.h"
#include "AsservissementPosition.h"
#include "AsservissementVitesse.h"
#include "Interpreter.h"
#include "QEI.h"


int interpreter(char *commande)
{
    float x,y,t;
    float v,w;

    if(commande == 0)
        return;

    // Asservissement en position
    if(commande[0] == 'X')
    {
        sscanf(commande,"X%fY%fT%f",&x,&y,&t);
        setConsignePosition(x,y,t);
        setAsservType(ASSERV_POSITION);
    }
    // Asservissement en vitesse
    else if(commande[0] == 'V')
    {
        sscanf(commande,"V%fW%f",&v,&w);
        setConsigneVitesse(v,w);
        setAsservType(ASSERV_VITESSE);
    }
    // Reset de l'odométrie
    else if(commande[0] == 'R')
    {
        resetOdometrie();
    }
    // Allumer les moteurs
    else if(commande[0] == 'E')
    {
       // enableMotors();
    }
    // Eteindre les moteurs
    else if(commande[0] == 'D')
    {
       // disableMotors()
    }
    // Arret d'urgence
    else if(commande[0] == 'B')
    {
       // arretUrgence();
    }

    return 0;
}
