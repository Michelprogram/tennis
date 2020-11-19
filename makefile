Compilateur = arm-linux-gnueabi-g++
OptionsCompilateur = -c -std=c++03
Linkeur = arm-linux-gnueabi-g++
OptionsLinkeur = -D_GLIBCXX_USE_CXX11_ABI=0

Executable = Run


all: run

clean:
	rm -rf *.o
	rm -rf *~
	rm run

run: tlecteur.o trs232.o tmateriel.o thistorique.o tgestion.o tcomptemembre.o tclavier.o FoxG20_gpio.o main.o
	$(Linkeur) $(OptionsLinkeur) tlecteur.o trs232.o tmateriel.o thistorique.o tgestion.o tcomptemembre.o tclavier.o FoxG20_gpio.o main.o -o run

trs232.o: trs232.cpp
	$(Compilateur) $(OptionsCompilateur) trs232.cpp -o trs232.o

tlecteur.o: tlecteur.cpp 
	$(Compilateur) $(OptionsCompilateur) tlecteur.cpp -o tlecteur.o

thistorique.o: thistorique.cpp 
	$(Compilateur) $(OptionsCompilateur) thistorique.cpp -o thistorique.o

tgestion.o: tgestion.cpp 
	$(Compilateur) $(OptionsCompilateur) tgestion.cpp -o tgestion.o

tcomptemembre.o: tcomptemembre.cpp 
	$(Compilateur) $(OptionsCompilateur) tcomptemembre.cpp -o tcomptemembre.o

tmateriel.o: tmateriel.cpp
	$(Compilateur) $(OptionsCompilateur) tmateriel.cpp -o tmateriel.o

tclavier.o: tclavier.cpp
	$(Compilateur) $(OptionsCompilateur) tclavier.cpp -o tclavier.o

FoxG20_gpio.o: FoxG20_gpio.cpp 
	$(Compilateur) $(OptionsCompilateur) FoxG20_gpio.cpp -o FoxG20_gpio.o

main.o: main.cpp
	$(Compilateur) $(OptionsCompilateur) main.cpp -o main.o

