#pragma once
#include <utility>

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorColectie;
template <class TElem>
struct Node {
	std::pair<TElem,int> info;
	Node<TElem>* next;
};

class Colectie {

	friend class IteratorColectie;

private:
	/* aici e reprezentarea */
	Node<TElem>* head;
	Node<TElem>* tail;
	int size;
public:
		//constructorul implicit
		Colectie();

		//adauga un element in colectie
		void adauga(TElem e);

		//sterge o aparitie a unui element din colectie
		//returneaza adevarat daca s-a putut sterge
		bool sterge(TElem e);

		//verifica daca un element se afla in colectie
		bool cauta(TElem elem) const;

		//returneaza numar de aparitii ale unui element in colectie
		int nrAparitii(TElem elem) const;


		//intoarce numarul de elemente din colectie;
		int dim() const;

		//verifica daca colectia e vida;
		bool vida() const;

		//adauga nr aparitii ale elementului elem in colectie
		//arunca exceptie in cazul in care nr este negativ
		void adaugaAparitiiMultiple(int nr, TElem elem);

		//returneaza un iterator pe colectie
		IteratorColectie iterator() const;

		// destructorul colectiei
		~Colectie();


};

