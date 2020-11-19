#include "thistorique.h"
#include <ctime>
#include <string.h>
#include <string>


thistorique::thistorique(char* nameFile)
/*
 * Constructeur qui prend en paramètre un nom de fichier
 * Allocation dynamiquement à la variable name_file
 */
{
    name_file = new char[strlen(nameFile+1)];
    strcpy(name_file,nameFile);
}

int thistorique::Ajouter(char * NumeroMembre)
/*
 * Méthode qui prend en paramètre un Numero à enregistrer dans le fichier
 * Ajoute le numéro avec l'heure et retourne 0
 * Retourne 1 si le fichier n'a pas pu s'ouvrir
 */
{
    struct tm *Date;
    time_t temps;
    ofstream File;

    time(&temps);
    Date = localtime(&temps);

    File.open(name_file,ios::app);

    if ( !File )
    {
        return 1;
    }

    else
    {

    File << Date->tm_hour << ":"
         << Date->tm_min << ":"
         << Date->tm_sec << " "

         << Date->tm_mday << "/"
         << Date->tm_mon << "/"
         << Date->tm_year+1900 << " "

         << NumeroMembre << endl;

    File.close();

    return 0;

    }
}


bool thistorique::AfficherHistorique()
/*
 * Affiche le contenu du fichier .bin
 * Retourne false si le fichier ne s'ouvre pas
 * Retourne true si le fichier s'ouvre
 */
{

    char temps[80],date[80],Nbmembre[80];
    ifstream File;

    File.open(name_file);

    if (!File)
    {
        return false;
    }

    while ( File >> temps >> date >> Nbmembre )
    {
        cout << temps << " " <<  date << " " << Nbmembre << endl;
    }


    File.close();

    return true;

}


