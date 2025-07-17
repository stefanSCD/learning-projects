#pragma once;

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorColectie;

class Colectie {

	friend class IteratorColectie;

private:
	static const int CAPACITATE_INITIALA = 100;
	static const int NIL = -1;
	struct Nod {
		TElem elem;
		int frecventa;
		int stanga;
		int dreapta;

		Nod() : elem(0), frecventa(0), stanga(NIL), dreapta(NIL) {}
		Nod(TElem e) : elem(e), frecventa(1), stanga(NIL), dreapta(NIL) {}
	};
	Nod* tablou;
	int radacina;
	int dimensiune;
	int capacitate;
	int primuLiber;
	void redimensioneaza();
	int alocareNod();
	void eliberareNod(int index);

	int gasesteMinin(int nod);

	/* aici e reprezentarea */
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

	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();

	// returneaza diferenta dintre valoarea maixma si cea minima(presupunem val intregi)
	// daca colectia este vida, se returneaza -1
	int diferenta() const;

};

