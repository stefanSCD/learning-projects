#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>

// BC=Theta(1)
// WC=Theta(n)
// Overall = O(n)
IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	/* de adaugat */
	stiva = new int[CAPACITATE_STIVA];
	varfStiva = -1;
	pozitieInNod = 0;
	plaseazaStanga(col.radacina);
}

// BC=WC=Theta(1)
TElem IteratorColectie::element() const {
	if (!valid()) {
		throw std::exception();
	}
	return col.tablou[stiva[varfStiva]].elem;
}

// BC=WC=Theta(1)
IteratorColectie::~IteratorColectie()
{
    delete[] stiva;
}

// BC=WC=Theta(1)
bool IteratorColectie::valid() const {
	return varfStiva >= 0;
}

// BC=Theta(1)
// WC=Theta(h)
// Overall = Theta(h)
void IteratorColectie::urmator() {
    if (!valid()) {
        throw std::exception();
    }

    pozitieInNod++;

    if (pozitieInNod < col.tablou[stiva[varfStiva]].frecventa) {
        // mai avem aparitii ale aceluiasi element
        return;
    }

    // trecem la urmatorul nod
    pozitieInNod = 0;
    int nod = stiva[varfStiva];
    varfStiva--;

    if (col.tablou[nod].dreapta != Colectie::NIL) {
        plaseazaStanga(col.tablou[nod].dreapta);
    }
}

// BC=Theta(1)
// WC=Theta(n)
// Overall = O(n)
// adauga in stiva toti descendentii stangi ai unui nod dat
void IteratorColectie::plaseazaStanga(int nod)
{
	while (nod != Colectie::NIL) {
		varfStiva++;
		stiva[varfStiva] = nod;
		nod = col.tablou[nod].stanga;
	}
}

// BC=WC=Theta(h)
void IteratorColectie::prim() {
    varfStiva = -1;
    pozitieInNod = 0;
    plaseazaStanga(col.radacina);
}
