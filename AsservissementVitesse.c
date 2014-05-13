float vc, wc;

void runAsservVitesse()
{
    float v1,v2;
    getVRoues(vc,wc,&v1,&v2);
    setConsignePIDs(v1,v2);
}

void setConsigneVitesse(float v, float w)
{
    vc = v;
    wc = w;
    
}
