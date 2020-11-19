#ifndef TGESTION_H
#define TGESTION_H

#include "tlecteur.h"
#include "tclavier.h"
#include "thistorique.h"
#include "tmateriel.h"
#include "tcomptemembre.h"

class tGestion
{

private:

    tLecteur *monLecteur = NULL;
    tclavier *monClavier = NULL;
    thistorique *monHistorique = NULL;
    tmateriel *monMateriel = NULL;
    tcompteMembre *monCompteMembre = NULL;

public:
    tGestion();

    void run();
    void tempo();
};

#endif // TGESTION_H
