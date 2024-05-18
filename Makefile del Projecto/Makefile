OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

program.exe: program.o Cuenca.o Barco.o Cjt_Productos.o Ciudad.o Error_Module.o
	g++ -o program.exe *.o

Cjt_Productos.o: Cjt_Productos.cc Error_Module.hh
	g++ -c Cjt_Productos.cc $(OPCIONS) 

Ciudad.o: Ciudad.cc Cjt_Productos.hh
	g++ -c Ciudad.cc $(OPCIONS) 

Barco.o: Barco.cc Cjt_Productos.hh
	g++ -c Barco.cc $(OPCIONS) 

Error_Module.o: Error_Module.cc 
	g++ -c Error_Module.cc $(OPCIONS) 

Cuenca.o: Cuenca.cc Ciudad.hh Barco.hh BinTree.hh
	g++ -c Cuenca.cc $(OPCIONS) 

program.o: program.cc Cuenca.hh Cjt_Productos.hh
	g++ -c program.cc $(OPCIONS)

clean:
	rm -f *.o
	rm -f *.exe
