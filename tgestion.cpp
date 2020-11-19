#include <ctime>

#include "tgestion.h"
#include "tlecteur.h"
#include "tclavier.h"
#include "thistorique.h"
#include "tmateriel.h"
#include "tcomptemembre.h"

tGestion::tGestion()
{
    monLecteur = new tLecteur();
    monClavier = new tclavier();
    monHistorique = new thistorique("data_historique.txt");
    monMateriel = new tmateriel("A30","A27","B30");
    monCompteMembre = new tcompteMembre("data_membre.bin");
}

void tGestion::run()
{
    char numeroCarteClient[100],numeroCarteAdmin[100];
    int codeCarteClient = 0,codeCarteAdmin = 0;
    short compteur = 0;

    bool flagAdmin = false;

    monLecteur->LireNumero(numeroCarteClient);
    codeCarteClient = monClavier->LireCode();

    if (monCompteMembre->Verifie(numeroCarteClient,codeCarteClient))
    {
        compteur = 0;
        monMateriel->DeploquerPorte();
        tempo();
        monMateriel->EteindreLampe();

        monHistorique->Ajouter(numeroCarteClient);
    }

    else if (!monCompteMembre->Verifie(numeroCarteClient,codeCarteClient))
    {
        compteur++;
    }

    else if (compteur == 3)
    {
        monMateriel->AllumerDiode();
        while (strcmp(numeroCarteAdmin,"22227777") != 0 && flagAdmin)
        {
            printf("Porte bloquer passer la carte Admin \n");
            monLecteur->LireNumero(numeroCarteAdmin);
            codeCarteAdmin = monClavier->LireCode();

            flagAdmin = monCompteMembre->Verifie(numeroCarteAdmin,codeCarteAdmin);

        }
        monMateriel->EteindreDiode();
    }
}

void tGestion::tempo()
{
    sleep(5);
}
