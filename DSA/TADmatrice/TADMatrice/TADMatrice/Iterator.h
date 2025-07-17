#pragma once
#include "Matrice.h"

class MatrixIterator {
	friend class Matrice;

private:
	const Matrice& matrix;
	int row;
	int col;
public:
	// constructorul primeste o referinta catre matrice
	MatrixIterator(const Matrice& m);
	// reseteaza pozitia iteratorului la inceputul matricei
	void prim();
	// muta iteratorul pe urmatorul element din matrice
	void urmator();
	// verifica daca iteratorul e valid
	bool valid() const;
	// returneaza valoarea elementului din matrice referinta la care se afla iteratorul
	TElem element() const;

};