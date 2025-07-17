#pragma once
#include "Vector.h"
#include "Iterator.h"

typedef int TElem;

#define NULL_TELEMENT 0

class MatrixIterator;

class Matrice {

private:
	/* aici e reprezentarea */
	int rows; // nr linii
	int cols; // nr coloane
	Vector linii;
	Vector1 elemente;
	
public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);


	//destructor
	~Matrice(){};

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	TElem element(int i, int j) const;


	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem);

	MatrixIterator iterator() const;
};
