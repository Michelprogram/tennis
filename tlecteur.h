#ifndef TLECTEUR_H_
#define TLECTEUR_H_

#include "trs232.h"

class tLecteur
{

private :
    tRs232 PortSerie;

public:
    tLecteur();

    void LireNumero(char *Num);
};

#endif /* TLECTEUR_H_ */
