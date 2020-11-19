#ifndef TFOXG20_H
#define TFOXG20_H
class FoxG20_gpio
{
  public :
	   FoxG20_gpio(const char* pNumBroche);
	   ~FoxG20_gpio() ;
     void Ecrire(int Valeur);
     int Lire();
  private :
	  char* NumBroche;
	  int IdKernel ;
    void Preparer_gpio_Ligne();
    void Definir_Direction(char* Direction);
}; 
#endif
