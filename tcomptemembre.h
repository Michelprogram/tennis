#ifndef TCOMPTEMEMBRE_H
#define TCOMPTEMEMBRE_H

#include <iostream>
#include "smembre.h"

class tcompteMembre
{

private:

    char* name_file = NULL;
    int nb_membre = 0;
    FILE* fichier = NULL;

    void set_nb_membre(FILE*);


public:
    tcompteMembre(char*);

    int Ajouter(sMembre*);
    int LireMembre(int,sMembre*);
    int Verifie(char*,int);
    int Rechercher(sMembre*);

};

#endif // TCOMPTEMEMBRE_H
