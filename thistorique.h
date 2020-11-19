#ifndef THISTORIQUE_H
#define THISTORIQUE_H

#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

class thistorique
{

private:

    char* name_file = NULL;

public:
    thistorique(char* );

    int Ajouter(char*);
    bool AfficherHistorique();

};

#endif // THISTORIQUE_H
