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

    bool AllumerLampe();
    bool EteindreLampe();
    bool AllumerDiode();
    bool EteindreDiode();

    void DeploquerPorte();
};

#endif // TMATERIEL_H
