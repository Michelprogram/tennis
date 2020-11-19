#include "tlecteur.h"

tLecteur::tLecteur()
{

}

void tLecteur :: LireNumero(char *Num)
/*
 * Lit un numéro de carte
 */
{
   char Trame[100];
   printf("Passer votre carte : \n");
   PortSerie.Recevoir('\r', Trame, SANS_FINAL);

   strncpy(Num,Trame+1,strlen(Trame)-2);
   Num[strlen(Trame)-2]='\0';
   printf("Carte Scanner");

}

