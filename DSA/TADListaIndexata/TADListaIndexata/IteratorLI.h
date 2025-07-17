#pragma once
#include "LI.h"

class LI;


class IteratorLI{
    friend class LI;
private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container

   	IteratorLI(LI& lista); 
  
	//contine o referinta catre containerul pe care il itereaza
	LI& lista; 
   	
	/* aici e reprezentarea  specifica a iteratorului */
	int current;
	

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element() const;

		TElem elimina();
};

