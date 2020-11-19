#include "tmateriel.h"
#include "FoxG20_gpio.h"
#include <string.h>
#include <unistd.h>

//Porte L2 PA30 30
//Lampe L5 PA27 27
//Diode L8 PB30 62

tmateriel::tmateriel(char* porte,char* lampe,char* diode)
/*
 * Constructeur qui affecte les variables
 */
{

    Porte = new FoxG20_gpio(porte);
    Lampe = new FoxG20_gpio(lampe);
    Diode = new FoxG20_gpio(diode);

}

void tmateriel::DeploquerPorte()
/*
 * Debloque la porte et allume la lampe
 */
{
    if (AllumerLampe())
    {
        sleep(5);
        EteindreLampe();
    }

}

bool tmateriel::AllumerLampe()
/*
 * Allume la lampe
 */
{
    Lampe->Ecrire(1);

    if (Lampe->Lire() == 1)
        return true;

    return false;
}

bool tmateriel::EteindreLampe()
/*
 * Eteint la lampe
 */
{
    Lampe->Ecrire(0);

    if (Lampe->Lire() == 0)
        return true;

    return false;
}

bool tmateriel::AllumerDiode()
/*
 * Allume la diode
 */
{
    Diode->Ecrire(1);

    if (Diode->Lire() == 1)
        return true;

    return false;
}

bool tmateriel::EteindreDiode()
/*
 * Eteint la diode
 */
{
    Diode->Ecrire(0);

    if (Diode->Lire() == 0)
        return true;

    return false;

}
