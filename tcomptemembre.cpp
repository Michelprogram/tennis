#include "tcomptemembre.h"
#include "string.h"
#include <stdio.h>
#include <iostream>

using namespace std;

tcompteMembre::tcompteMembre(char* apNomFichier)
/*
 * Constructeur, affectation de name_file
 */
{
    name_file = new char[strlen(apNomFichier)+1];
    strcpy(name_file,apNomFichier);
}


int tcompteMembre::Ajouter(sMembre* unMembre)
/*
 * Méthode qui prend une structure Membre en paramètre
 * Retourne -1 si le fichier ne c'est pas bien fermé
 * Retourne 0 si le fichier ne c'est pas ouvert
 * Retourne 1 si le membre a été ajouter
 */
{
    int flag = 0;

    if ((fichier=fopen(name_file,"a")) == NULL)
    {
        printf("impossible ouvrir fichier");
    }

    else
    {
        if (fwrite(unMembre,sizeof(sMembre),1,fichier) != 0)
        {
            fclose(fichier);
            flag = 1;
        }

        else
        {
            flag = -1;
        }
    }

    return flag;

}

int tcompteMembre::LireMembre(int NumEnreg, sMembre* unMembre)
/*
 * Méthode qui prend en paramètre un numéro pour se positionner dans le dossier .bin
 * Et aussi une structure membre dans laquelle stocker la réponse
 * Méthode qui retourne -1 si le numéro n'est pas dans le bonne intervalle
 * Retourne 0 si mauvaise ouverture du fichier
 * Retourne 1 si tout c'est bien passé
*/
{
    int flag = 0;

    if ((fichier=fopen(name_file,"r")) == NULL)
    {
        printf("impossible ouvrir fichier");
    }

    else
    {
        set_nb_membre(fichier);

        if (NumEnreg+1 > nb_membre)
        {
            flag = -1;
        }

        else
        {
            fseek(fichier,NumEnreg*sizeof (sMembre),SEEK_SET);
            fread(unMembre,sizeof(sMembre),1,fichier);
            fclose(fichier);
            flag = 1;

        }
    }

    return flag;
}

int tcompteMembre::Rechercher(sMembre* psMembre)
/*
 * Méthode Rechercher un membre dans le dossier data.bin par le biais du parametre psMembre
 * Retourne -1 si la méthode n'a pas réussi à écrire dans le fichier
 * Retourne 0 si la méthode n'a pas réussi à ouvrir le fichier
 * Retourne 1 si tout c'est bien passé
*/
{
    struct sMembre tempo;
    int flag = 0;

    if ((fichier=fopen(name_file,"r")) == NULL)
    {
        printf("impossible ouvrir fichier");
    }

    else
    {
        set_nb_membre(fichier);

        for (short i = 0;i<nb_membre;i++)
        {
            if (fread(&tempo,sizeof (sMembre),1,fichier) != 0)
            {
                if (strcmp(tempo.numero,psMembre->numero) == 0)
                {
                    strcpy(psMembre->nom,tempo.nom);
                    psMembre->code = tempo.code;
                    flag = 1;
                }
            }

            else
            {
                flag = -1;
            }

        }

        fclose(fichier);
    }

    return flag;
}


int tcompteMembre::Verifie(char* numero,int code)
/*
 * Méthode qui vérifie si le numéro correspond au code passer en paramètre
 * En utilisant la méthode rechercher
 * Si elle trouve le bon numéro avec le bon code renvoie 1 sinon 0
 */
{
    struct sMembre tempo;
    strcpy(tempo.numero,numero);

    int flag = 0;

    if (Rechercher(&tempo) == 1)
        {

        if (tempo.code == code)
            {
                flag = 1;
            }

        }

    return flag;

}


void tcompteMembre::set_nb_membre(FILE* file)
/*
 * Méthode ajouter personellement pour connaître le nombre de membre
 * Et l'affecter à l'attribut nb_membre
 */
{
    fseek(file,0,SEEK_END);
    nb_membre = ftell(file)/sizeof (sMembre);
    fseek(file,0,SEEK_SET);
}
