#ifndef TMATERIEL_H
#define TMATERIEL_H

#include "FoxG20_gpio.h"
#include <stdio.h>

class tmateriel
{
private:

    FoxG20_gpio* Porte = NULL; //NULL est non nullptr problème au niveau de la compilation
    FoxG20_gpio* Lampe = NULL;
    FoxG20_gpio* Diode = NULL;

public:
    tmateriel(char*,char*,char*);

    void AllumerLampe();
    void EteindreLampe();
    void AllumerDiode();
    void EteindreDiode();

    void DeploquerPorte();

    void OuvrirPorte();
    void FermerPorte();
};

#endif // TMATERIEL_H
