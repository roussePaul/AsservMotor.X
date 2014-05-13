#include "Asservissement.h"


AsservType asservType;


void __attribute__((interrupt,auto_psv)) _T2Interrupt(void)
{
    IFS0bits.T2IF = 0; // Clear timer 2 interrupt flag

    runAsservissement();

}

void initAsservissement()
{
    setConsigneVitesse(0.0,0.0);
    setAsservType(ASSERV_VITESSE);
}

void runAsservissement()
{
    if(asservType == ASSERV_POSITION)
        runAsservPosition();
    else if(asservType = ASSERV_VITESSE)
        runAsservVitesse();

    runPIDs();
}

void setAsservType(AsservType asserv)
{
    asservType = asserv;
}