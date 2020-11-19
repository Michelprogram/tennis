#include <iostream>
#include "FoxG20_gpio.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

FoxG20_gpio::FoxG20_gpio(const char* pNumBroche)
{
	int NbCases = strlen(pNumBroche)+1;
	NumBroche = new char[NbCases];
	strcpy(NumBroche,pNumBroche);
	printf("Valeur de NumBroche : %s\n",NumBroche);
	int Numero=atoi(NumBroche+1) ;
	if (*NumBroche>='A' && *NumBroche<='E')
		IdKernel=(*NumBroche - 'A') * 32 + Numero ;
	else
		exit (1) ;
	printf ("IdKernel=%d\n", IdKernel) ;
}

FoxG20_gpio::~FoxG20_gpio()
{
   FILE * pFic ;
   char gpio_value[35];

   sprintf(gpio_value, "/sys/class/gpio/pio%s/.", NumBroche);

   if ((pFic=fopen(gpio_value,"r"))!=NULL)
   {
      fclose (pFic) ;
      if ((pFic = fopen("/sys/class/gpio/unexport","w")) == NULL)
      {
         printf("Cannot open export file : %s\n",NumBroche);
         exit(1);
      }
      rewind(pFic);
      fprintf(pFic,"%d",IdKernel);
      fclose(pFic);
   }
}

void FoxG20_gpio::Ecrire(int Valeur)
{
	  FILE *Fich;
	  char gpio_value[35];

	  Preparer_gpio_Ligne();
	  Definir_Direction((char*) "out");

	// ECRIRE LA VALEUR
	  sprintf(gpio_value, "/sys/class/gpio/pio%s/value", NumBroche);
	  if ((Fich = fopen(gpio_value, "rb+")) == NULL)
		{
			printf("Cannot open value file.\n");
			exit(1);
		}
	  rewind(Fich);
	  fprintf(Fich,"%d", Valeur);
	  fclose(Fich);
}




int FoxG20_gpio:: Lire()
{
	 FILE *Fich;
	 char gpio_value[35];
	 char ValeurLue;

	 Preparer_gpio_Ligne();
	 Definir_Direction((char*) "in");

	// RECUPERER Valeur
	 sprintf(gpio_value, "/sys/class/gpio/pio%s/value", NumBroche);
	 if ((Fich = fopen(gpio_value, "rb")) == NULL)
			{
				printf("Cannot open value file.\n");
				exit(1);
			}
	 fread(&ValeurLue, sizeof(char), 1, Fich);
	 fclose(Fich);
	 return ValeurLue-0x30; // pour oter code ascii
}


void FoxG20_gpio::Preparer_gpio_Ligne()
{
	FILE *Fich;

	  // Préparer la broche utilisée
	   if ((Fich = fopen("/sys/class/gpio/export","w")) == NULL)
		{
			printf("Cannot open export file : %s\n",NumBroche);
			exit(1);
		}
	   rewind(Fich);
	   fprintf(Fich,"%d",IdKernel);
	   fclose(Fich);
}

void FoxG20_gpio::Definir_Direction(char* Direction) // IN ou OUT
{
   FILE * Fich;
	char gpio_direction[35];
	sprintf(gpio_direction, "/sys/class/gpio/pio%s/direction", NumBroche);
	if ((Fich = fopen(gpio_direction, "rb+")) == NULL)
	{
		printf("Cannot open direction file.\n");
		exit(1);
	}
	rewind(Fich);
	fprintf(Fich, Direction);
	fclose(Fich);
}
