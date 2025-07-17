#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;
// BC=WC=Theta(1)
bool rel(TElem e1, TElem e2) {
	/* de adaugat */
	return e1 <= e2;
}
// BC=WC=Theta(1)
Colectie::Colectie() {
	/* de adaugat */
	head = nullptr;
	tail = nullptr;
	size = 0;
}
// BC=Theta(1), WC=Theta(n), Overall = O(n)
void Colectie::adauga(TElem e) {
	Node<TElem>* current = head;
	Node<TElem>* prev = nullptr;

	while (current != nullptr && rel(current->info.first, e)) {
		if (current->info.first == e) {
			current->info.second++;
			return;
		}
		prev = current;
		current = current->next;
	}

	Node<TElem>* newNode = new Node<TElem>;
	newNode->info = std::make_pair(e, 1);
	newNode->next = current;

	if (prev == nullptr) {
		head = newNode;
	}
	else {
		prev->next = newNode;
	}

	size++;
}

// BC=Theta(1), WC=Theta(n), Overall = O(n)
bool Colectie::sterge(TElem e) {
	Node<TElem>* current = head;
	Node<TElem>* prev = nullptr;

	while (current != nullptr) {
		if (current->info.first == e) {
			if (current->info.second > 1) {
				current->info.second--;
			}
			else {
				if (prev == nullptr) {
					head = current->next;
				}
				else {
					prev->next = current->next;
				}
				delete current;
				size--;
			}
			return true;
		}
		prev = current;
		current = current->next;
	}
	return false;
}


// BC=Theta(1)
// WC=Theta(n)
// Overall = O(n)
bool Colectie::cauta(TElem elem) const {
	/* de adaugat */
	if (nrAparitii(elem) > 0) {
		return true;
	}
	return false;
}

// BC=Theta(1)
// WC=Theta(n)
// Overall = O(n)
int Colectie::nrAparitii(TElem elem) const {
	/* de adaugat */
	Node<TElem>* current = head;
	while (current != nullptr) {
		if (current->info.first == elem) {
			return current->info.second;
		}
		current = current->next;
	}
	return 0;
}

// BC=WC=Theta(n)
int Colectie::dim() const {
	/* de adaugat */
	Node<TElem>* current = head;
	int count = 0;
	while (current != nullptr) {
		count += current->info.second;
		current = current->next;
	}
	return count;
}

// BC=WC=Theta(1)
bool Colectie::vida() const {
	/* de adaugat */
	return this->size == 0;
}

// BC=WC=Theta(1)
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

// BC=WC=Theta(n)
Colectie::~Colectie() {
	Node<TElem>* current = head;
	while (current != nullptr) {
		Node<TElem>* next = current->next;
		delete current;
		current = next;
	}
}

// BC=Theta(1) , WC=Theta(n), Overall = O(n)
void Colectie::adaugaAparitiiMultiple(int nr, TElem elem)
{
	if (nr < 0) {
		throw std::exception();
	}
	Node<TElem>* current = head;
	Node<TElem>* prev = nullptr;
	while (current != nullptr && rel(current->info.first, elem)) {
		if (current->info.first == elem) {
			current->info.second += nr;
			return;
		}
		prev = current;
		current = current->next;
	}
	Node<TElem>* newNode = new Node<TElem>;
	newNode->info = std::make_pair(elem, nr);
	newNode->next = current;
	if (prev == nullptr) {
		head = newNode;
	}
	else {
		prev->next = newNode;
	}

	size++;
}
/*
	pre :   elem: TElem
			nr: int 
			C : Colectie
	post :  elem ? C 
			frecv(elem) = nr
	@: arunca exceptie daca nr < 0
	SubAlgoritm adaugaAparitiiMultiple(nr: intreg, TElem : TElement, C: Colectie)
		Daca nr < 0 atunci
			arunca exceptie
		SfDaca

		current: ?head
		prev: ?NIL
		
		CatTimp current != NIL si C.rel(current->info.first, elem) executa
			Daca current->info.first == elem atunci
				[current].info.second <- nr + current->info.second
				Intoarce
			SfDaca
			prev <- current
			current <- current->next
		SfCatTimp
		newNode: ?Node<TElem> // aloca(newNode)
		newNode->info <- std::make_pair(elem,nr)
		newNode->next <- current
		
		Daca prev == NIL atunci
			head <- newNode
		altfel
			prev->next <- newNode
		SfDaca

		size <- size + 1
	SfSubAlgoritm
*/
