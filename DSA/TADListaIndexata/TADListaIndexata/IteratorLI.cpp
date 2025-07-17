#include "IteratorLI.h"
#include "LI.h"
#include <exception>

// BC=WC=Theta(1)
IteratorLI::IteratorLI(LI& li): lista(li) {
    current = lista.head;
}

// BC=WC=Theta(1)
void IteratorLI::prim(){
	current = lista.head;
}

// BC=WC=Theta(1)
void IteratorLI::urmator(){
    if (!valid()) {
        throw std::exception();
    }
    current = lista.urm[current];
}

// BC=WC=Theta(1)
bool IteratorLI::valid() const{
    return current != -1;
}

// BC=WC=Theta(1)
TElem IteratorLI::element() const{
    if (!valid()) {
        throw std::exception();
    }
	return lista.val[current];
}

// BC=WC=Theta(1)
TElem IteratorLI::elimina()
{
	if (!valid())
		throw std::exception();
	int poz = current;
	TElem e = element();
	int anterior = lista.prec[poz];
	int urmator = lista.urm[poz];
	if (anterior != -1) { // refac legaturile in lista
		lista.urm[anterior] = urmator;
	}
	else {
		lista.head = urmator;
	}
	if (urmator != -1) {
		lista.prec[urmator] = anterior;
	}
	else {
		lista.tail = anterior;
	}

	lista.urm[poz] = lista.primLiber; // marchez elementul eliberat in lista de locuri libere
	lista.primLiber = poz;
	lista.len--;
	current = urmator; // mut iteratorul pe urmatorul element
	return e;
}
/*
	pre : lista : Lista , it : Iterator
	post: elimina(it) = elementul eliminat
	@ : arunca exceptie daca it nu este valid
	SubAlgoritm elimina(it)
		Daca it.valid = false atunci
			@arunca exceptie
		SfDaca
		poz <- current
		e <- it.element
		anterior <- lista.prec[poz]
		urmator <- lista.urm[poz]
		Daca anterior != -1 atunci
			lista.urm[anterior] <- urmator
		Altfel
			lista.head <- urmator
		SfDaca
		Daca urmator != -1 atunci
			lista.prec[urmator] <- anterior
		Altfel
			lista.tail <- anterior
		SfDaca
		lista.urm[poz] <- lista.primLiber
		lista.primLiber <- poz
		lista.len <- lista.len - 1
		current <- urmator
		elimina(it) <- e
	SfSubAlgoritm
*/