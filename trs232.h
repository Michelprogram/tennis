#ifndef	RS232_H
#define	RS232_H
//----------------------------------------------------------------------------
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <time.h>
//----------------------------------------------------------------------------
#define COM1 (char *)	"/dev/ttyUSB0"
#define COM2	"/dev/ttyS1"
//----------------------------------------------------------------------------
#define BPS9600  0
#define BPS4800  1
#define BPS2400  2
#define BPS19200 3
//----------------------------------------------------------------------------
#define BIT8	0
#define BIT7	1
#define BIT6	2
#define BIT5	3
//----------------------------------------------------------------------------
#define STOP1	0
#define STOP2	1
//----------------------------------------------------------------------------
#define PAS_DE_PARITE  0
#define PARITE_PAIRE	  1
#define PARITE_IMPAIRE 2
//----------------------------------------------------------------------------
#define AVEC_FINAL	0
#define SANS_FINAL	1
//----------------------------------------------------------------------------
#define OK		0
#define ERREUR 	-1
#define TIMEOUT	-2
#define RIEN_RECU	1

//----------------------------------------------------------------------------
class tRs232
    {
    private:
        termios Config;
        char MessageConfigurer[30];
        int fd;	//Descripteur de fichier
        int Configurer(char* pPort,int Vitesse,int NbBits,int Parite,int NbStop);

   //------------------------------
    public:
        tRs232(void);
        tRs232(char* pPort,int Vitesse,int NbBits,int Parite,int NbStop);
        ~tRs232();
        void AfficherMessageConfigurer();

        // Envoyer une chaine de caract�re
        int Envoyer(char* pChaine);

        // Recevoir Nb caract�res
        int Recevoir(int Nb,char* pChaine);

        // Recevoir une cha�ne se terminant par un caract�re donn�
        // (\r, \n ou autre)
        // avec ou sans time out
        int Recevoir(char Fin, char* pChaine, int Mode);
        int Recevoir(char Fin, char* pChaine, int Mode, int Attente);

        // Recevoir une s�rie de caract�res avec time out
        int RecevoirCaractere(char* Caractere, int Attente);

           } ;

#endif
