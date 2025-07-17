#include <exception>
#include <iostream>
#include "LI.h"
#include "IteratorLI.h"

// BC = WC = Theta(n)
void LI::redimensioneaza() {
	int nouaCapacitate = capacitate * 2;

	TElem* valNou = new TElem[nouaCapacitate];
	int* urmNou = new int[nouaCapacitate];
	int* precNou = new int[nouaCapacitate];

	// copiez valorile si legaturile
	for (int i = 0; i < capacitate; ++i) {
		valNou[i] = val[i];
		urmNou[i] = urm[i];
		precNou[i] = prec[i];
	}

	// actualizez lista de spatii libere
	for (int i = capacitate; i < nouaCapacitate - 1; ++i) {
		urmNou[i] = i + 1;
	}
	urmNou[nouaCapacitate - 1] = -1; // ultimul element nu are urmator liber
	primLiber = capacitate; // spatiile libere încep de la capacitate

	delete[] val;
	delete[] urm;
	delete[] prec;

	val = valNou;
	urm = urmNou;
	prec = precNou;

	capacitate = nouaCapacitate;
}

// BC=WC=Theta(1)
LI::LI() {
	capacitate = 10;
	val = new TElem[capacitate];
	urm = new int[capacitate];
	prec = new int[capacitate];

	for (int i = 0; i < capacitate - 1; ++i) {
		urm[i] = i + 1;
	}
	urm[capacitate - 1] = -1;
	primLiber = 0;

	head = -1;
	tail = -1;
	len = 0;
}

// BC=WC=Theta(1)
int LI::dim() const {
	return len;
}

// BC=WC=Theta(1)
bool LI::vida() const {
	if (len == 0) {
		return true;
	}
	return false;
}

// BC = Theta(1)
// WC = Theta(n)
// Overall = O(n)
TElem LI::element(int i) const {
	if (i < 0 || i >= len) {
		throw std::exception();
	}
	int current = head;
	for (int j = 0; j < i; ++j) {
		current = urm[current];
	}
	return val[current];
}

// BC = Theta(1)
// WC = Theta(n)
// Overall = O(n)
TElem LI::modifica(int i, TElem e) {
	if (i < 0 || i >= len) {
		throw std::exception();
	}
	int current = head;
	for (int poz = 0; poz < i; ++poz) {
		current = urm[current];
	}
	TElem oldValue = val[current];
	val[current] = e;
	return oldValue;
}

// BC = Theta(1)
// WC = Theta(n)
// Overall = Theta(1)
void LI::adaugaSfarsit(TElem e) {
	if (primLiber == -1) {
		redimensioneaza();
	}

	int pos = primLiber;          // prima pozitie libera
	primLiber = urm[primLiber];   // actualizez urmatoarea pozitie libera

	val[pos] = e;
	urm[pos] = -1;                // nu are urmator pentru ca e ultimul element
	prec[pos] = tail;             // precedentul devine ultimul element anterior

	if (tail != -1) {
		urm[tail] = pos;	// ultimul element anterior pointeaza la noul element
	}
	else { // cazul in care lista e goala
		head = pos;
	}

	tail = pos;
	len++;
}

// BC = Theta(1)
// WC = Theta(n)
// Overall = O(n)
void LI::adauga(int i, TElem e) {
	if (i < 0 || i > len) {
		throw std::exception();
	}
	if (primLiber == -1) {
		redimensioneaza();
	}

	int pos = primLiber;
	primLiber = urm[primLiber];
	val[pos] = e;

	if (i == 0) {
		// adaugare la inceput
		urm[pos] = head;
		prec[pos] = -1;
		if (head != -1) {
			prec[head] = pos;
		}
		else { // cazul in care lista era goala
			tail = pos; 
		}
		head = pos;
	}
	else if (i == len) {
		// adaugare la sfarsit
		urm[pos] = -1;
		prec[pos] = tail;
		if (tail != -1) {
			urm[tail] = pos;
		}
		else {
			head = pos;
		}
		tail = pos;
	}
	else {
		// adaugare in interior
		int current = head;
		for (int k = 0; k < i; ++k) {
			current = urm[current];
		}
		int precedent = prec[current];

		urm[precedent] = pos;
		prec[pos] = precedent;

		urm[pos] = current;
		prec[current] = pos;
	}

	len++;
}

// BC = Theta(1)
// WC = Theta(n)
// Overall = O(n)
TElem LI::sterge(int i) {
	if (i < 0 || i >= len)
		throw std::exception();

	int poz = head;
	int index = 0;

	while (index < i) {
		poz = urm[poz];
		index++;
	}

	TElem e = val[poz];

	int anterior = prec[poz];
	int urmator = urm[poz];

	if (anterior != -1)
		urm[anterior] = urmator;
	else
		head = urmator;

	if (urmator != -1)
		prec[urmator] = anterior;
	else
		tail = anterior;

	urm[poz] = primLiber;
	primLiber = poz;

	len--;

	return e;
}

// BC = Theta(1)
// WC = Theta(n)
// Overall = O(n)
int LI::cauta(TElem e) const{
	int poz = head;
	int index = 0;

	while (poz != -1) {
		if (val[poz] == e) {
			return index;
		}
		poz = urm[poz];
		index++;
	}

	return -1;
}

// BC=WC=Theta(1)
IteratorLI LI::iterator() {
	return  IteratorLI(*this);
}

// BC=WC=Theta(1)
LI::~LI() {
	delete[] val;
	delete[] urm;
	delete[] prec;
}
