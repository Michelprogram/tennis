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
    monMateriel = new tmateriel("A30","A27","A28"); //Porte lampe diode
    monCompteMembre = new tcompteMembre("data_membre.bin");
}

void tGestion::run()
{
    char numeroCarteClient[100],numeroCarteAdmin[100];
    int codeCarteClient = 0,codeCarteAdmin = 0;
    short compteur = 0;

    bool flagAdmin = false;
    bool flagClient = false;

    while (true)
    {

        monLecteur->LireNumero(numeroCarteClient);//L'utilisateur passe sa carte

        while (compteur != 3 && !flagClient)
        {
            codeCarteClient = monClavier->LireCode();//Tappe le code pin

            if(monCompteMembre->Verifie(numeroCarteClient,codeCarteClient) == 1)
            {
                printf("Le code Pin est correcte ! \n");
                flagClient = true;
            }
            else if (monCompteMembre->Verifie(numeroCarteClient,codeCarteClient) == 0)
            {
                 printf("Le code Pin est incorrecte ! \n");
                 monMateriel->AllumerLampe();
                 tempo(2);
                 monMateriel->EteindreLampe();
            }

            compteur++;
            printf("Nombres de tentative(s) : %d\n",compteur);

        }

        if(compteur == 3)
        {
            printf("3 tentatives :( \n");
            monMateriel->AllumerDiode();

            while (strcmp(numeroCarteAdmin,"22227777") != 0 && !flagAdmin)
            {
                printf("Porte bloquer passer la carte Admin \n");
                monLecteur->LireNumero(numeroCarteAdmin);
                codeCarteAdmin = monClavier->LireCode();

                flagAdmin = monCompteMembre->Verifie(numeroCarteAdmin,codeCarteAdmin);

            }

            flagAdmin = false;
            monMateriel->EteindreDiode();
        }

        else if (flagClient)
        {
            printf("L'utilisateur rentre sur le terrain :) \n");
            flagClient = false;

            monMateriel->AllumerLampe();//Allume la lampe
            monMateriel->OuvrirPorte(); //Débloque la porte
            tempo(5);

            monMateriel->EteindreLampe();//Eteint la lampe

            tempo(5);

            monMateriel->FermerPorte();

            monHistorique->Ajouter(numeroCarteClient);//Ajoute à l'historique
        }

        compteur = 0;
    }

}

void tGestion::tempo(short seconds)
{
    sleep(seconds);
}
