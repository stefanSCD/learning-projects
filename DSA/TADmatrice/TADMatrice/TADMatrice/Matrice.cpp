#include "Matrice.h"
#include <iostream>
#include <exception>

using namespace std;

// Overall: Theta(m) WC=BC
Matrice::Matrice(int m, int n) {
	if (m <= 0 || n <= 0)
		throw exception();
	this->rows = m;
	this->cols = n;
	for (int i = 0; i <= m; i++) {
		linii.Add(0);
	}
}


// Overall: Theta(1) WC=BC
int Matrice::nrLinii() const{
	/* de adaugat */
	return this->rows;
}

//Overall: Theta(1) WC=BC
int Matrice::nrColoane() const{
	/* de adaugat */
	return this->cols;
}

//BC:Theta(1)
//WC:Theta(n)
//O(n)
TElem Matrice::element(int i, int j) const{
	/* de adaugat */
	if (i<0 || j < 0 || j>=this->cols || i>=this->rows) {
		throw exception();
		return NULL_TELEMENT;
	}
	int indStart = linii.v[i];
	int indStop = linii.v[i + 1];
	for (int k = indStart; k < indStop; k++) {
		if (elemente.p[k].first == j) {
			return elemente.p[k].second;
		}
	}
	return NULL_TELEMENT;
}

//BC:Theta(1)
//WC:Theta(n)
//O(n)
int cautaPozitie(const Vector1& elemente, int start, int stop, int j) {
	int pos = start;
	while (pos < stop && elemente.p[pos].first < j)
		pos++;
	return pos;
}

//BC:Theta(1)
//WC:Theta(max(n,m))
//O(max(n,m))
TElem Matrice::modifica(int i, int j, TElem e) {
	/* de adaugat */
	if (i < 0 || j < 0 || j >= this->cols || i >= this->rows) {
		throw exception();
		return NULL_TELEMENT;
	}
	TElem oldVal = element(i, j);
	int start = linii.v[i];
	int stop = linii.v[i + 1];
	int pos = cautaPozitie(elemente, start, stop, j);
	if (oldVal != NULL_TELEMENT) {
		if (e == NULL_TELEMENT) {
			elemente.Delete(j, e);
			for (int k = i + 1; k < rows + 1; k++) {
				linii.v[k]--;
			}
		}
		else {
			elemente.p[pos].second = e;
		}
	}
	else {
		if (e != NULL_TELEMENT) {
			elemente.insertAt(pos, j, e);
			for (int k = i + 1; k < rows + 1; k++) {
				linii.v[k]++;
			}
		}
	}
	return oldVal;
}


//Theta(1) BC=WC
MatrixIterator Matrice::iterator() const
{
	return MatrixIterator(*this);
}

