#include "tclavier.h"
#include <iostream>
#include <cstdio>

using namespace std;

tclavier::tclavier()
{

}

int tclavier::LireCode()
/*
 * Méthode qui lit un code compris entre 1000 et 9999
*/
{
    int pin = 0;

    while (pin < 1000 || pin > 9999 )
    {
        printf("Code Pin : ");

        if(scanf("%d",&pin) != 1)
        {
             cin.ignore();
             cin.clear();
             printf("Renseigner un code sans caractère \n");
        }

    }
    printf("Code PIN renseigner \n");

    return pin;

}
