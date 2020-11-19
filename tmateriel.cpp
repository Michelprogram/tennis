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

void tmateriel::AllumerLampe()
/*
 * Allume la lampe
 */
{
    Lampe->Ecrire(1);
}

void tmateriel::EteindreLampe()
/*
 * Eteint la lampe
 */
{
    Lampe->Ecrire(0);
}

void tmateriel::AllumerDiode()
/*
 * Allume la diode
 */
{
    Diode->Ecrire(1);
}

void tmateriel::EteindreDiode()
/*
 * Eteint la diode
 */
{
    Diode->Ecrire(0);
}

void tmateriel::OuvrirPorte()
{
    Porte->Ecrire(1);
}

void tmateriel::FermerPorte()
{
    Porte->Ecrire(0);
}
