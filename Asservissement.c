
AsservType asservType;


void runAsservissement()
{
    if(asservType == ASSERV_POSITION)
        runAsservPosition();
    else if(asservType = ASSERV_VITESSE)
        runAsservVitesse();
}

void setAsservType(AsservType asserv)
{
    asservType = asserv;
}