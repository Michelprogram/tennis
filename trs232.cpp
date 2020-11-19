#include "trs232.h"

//-----------------------------------------------------------------------------
int tRs232::Configurer(char* pPort,int Vitesse,int NbBits,int Parite,int NbStop)
{
    int Res;
    //Ouverture de la com.
    fd = open(pPort,O_RDWR | O_NONBLOCK);
    if (fd == -1)
    {
        fprintf(stderr,"Erreur lors de l'ouverture de %s\n",pPort);
        strcpy(MessageConfigurer, "Erreur lors de l'ouverture du port !");
        exit (-1);
    }
    else
    {
        strcpy(MessageConfigurer, "Ouverture du port reussie.");
        tcgetattr(fd,&Config);
        // Suppression de l'echo
        //Config.c_lflag &= ~(ECHO) ;
        Config.c_lflag = 0;
        Config.c_iflag = IGNBRK | IGNPAR;
        Config.c_oflag = 0;

        Config.c_cflag = CREAD | CLOCAL;

        // Vitesse
        switch (Vitesse)
        {
            case BPS9600: 	Config.c_cflag |= B9600;break;
            case BPS4800: 	Config.c_cflag |= B4800;break;
            case BPS2400: 	Config.c_cflag |= B2400;break;
            case BPS19200: 	Config.c_cflag |= B19200;break;
            default: 		//fprintf(stderr,"Vitesse non utilisable\n");
                            strcpy(MessageConfigurer, "Vitesse non utilisable !\n");
                            exit (-1);
        }

        // Taille data
        switch (NbBits)
        {
            case BIT8: Config.c_cflag |= CS8;break;
               case BIT7: Config.c_cflag |= CS7;break;
            case BIT6: Config.c_cflag |= CS6;break;
               case BIT5: Config.c_cflag |= CS5;break;
            default: 	//fprintf(stderr,"Taille de donnee non conforme\n");
                        strcpy(MessageConfigurer, "Taille de donnee non conforme !\n");
                        exit (-1);
        }

        // Parite
        switch (Parite)
        {
            case PARITE_PAIRE : Config.c_cflag |=  PARENB; break;
               case PARITE_IMPAIRE : Config.c_cflag |= (PARODD | PARENB);break;
            default : break;
        }

        // Nombre de bits de stop
        switch(NbStop)
        {
            case STOP2 : Config.c_cflag |= CSTOPB;break;
        }

        // Application de la configuration

        Res = tcsetattr(fd, TCSANOW, &Config);
        if (Res == -1)
        {
            fprintf(stderr, "Erreur lors de l'application de la configuration\n");
               exit (-1);
        }
        tcflush(fd, TCIFLUSH);
        tcflush(fd, TCOFLUSH);
    }
    return 0;
}

//----------------------------------------------------------------------------
void tRs232::AfficherMessageConfigurer()
{
    printf("%s\n\n", MessageConfigurer);
}

//----------------------------------------------------------------------------
tRs232::tRs232(char* pPort, int Vitesse, int NbBits, int Parite, int NbStop)
{
   Configurer(pPort,Vitesse,NbBits,Parite,NbStop);
}

//----------------------------------------------------------------------------
tRs232::tRs232(void)
{
   Configurer(COM1,BPS9600,BIT8,PAS_DE_PARITE,STOP1);
}

//----------------------------------------------------------------------------
tRs232::~tRs232()
{
   close(fd);
}

//----------------------------------------------------------------------------
int tRs232::Envoyer(char* pChaine)
{
   int Res = write (fd, pChaine, strlen(pChaine));
   return (Res);
}

//----------------------------------------------------------------------------
int tRs232::Recevoir(int Nb, char* pChaine)
{
    int i = 0;
    char Car;
    int Res;

    do
    {
        Res = read (fd, &Car, 1);
        if (Res > 0)
        {
            pChaine[i] = Car;
            i++;
        }
    }
    while (i < Nb);

    pChaine[i] = '\0';
    return i;
}

//----------------------------------------------------------------------------
int tRs232::Recevoir(char Fin, char* pChaine, int Mode)
{
    int i = 0;
    char Car = 0x00;
    int Res;

    do
    {
        Res = read(fd, &Car, 1);
        if (Res > 0)
        {
            pChaine[i] = Car;
            i++;
        }
    }
    while (Car != Fin);

    if (Mode == SANS_FINAL)
       i--;

    pChaine[i] = '\0';
    tcflush(fd, TCIFLUSH);
    return i;
}

//----------------------------------------------------------------------------
int tRs232::Recevoir(char Fin, char* pChaine, int Mode, int Attente)
{
    int i = 0;
    char Car = 0x00;
    int Res;
    time_t TimeRef;
    time_t Time;

    TimeRef = time(&TimeRef);

    do
    {
        Res = read(fd, &Car, 1);
        if (Res > 0)
        {
            TimeRef = time(&TimeRef);
            pChaine[i] = Car;
            i++;
        }

        Time = time(&Time);
        if ((Time - TimeRef) >= Attente)
        {
            pChaine[i] = '\0';
            return TIMEOUT;
        }
    }
    while (Car != Fin);

    if (Mode == SANS_FINAL)
       i--;

    pChaine[i] = '\0';
    tcflush(fd, TCIFLUSH);
    return i;
}

//----------------------------------------------------------------------------
int tRs232::RecevoirCaractere(char* Caractere, int Attente)
{
    int Res;
    char Car;
    time_t TimeRef;
    time_t Time;

    TimeRef = time(&TimeRef);
    do
    {
        Time = time(&Time);
        Res = read (fd, &Car, 1);
    }
    while((Res != 1) && ((Time - TimeRef) < Attente));

    if (Res > 0)
    {
        *Caractere = Car;
        return OK;
    }
    else
        return TIMEOUT;
}

//----------------------------------------------------------------------------

