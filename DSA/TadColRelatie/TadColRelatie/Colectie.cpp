#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>
#include <exception>

using namespace std;

// BC=WC=Theta(1)
bool rel(TElem e1, TElem e2) {
    return e1 <= e2;
}

// BC=WC=Theta(n)
Colectie::Colectie() {
    capacitate = CAPACITATE_INITIALA;
    tablou = new Nod[capacitate];
    radacina = NIL;
    dimensiune = 0;
    primuLiber = 0;

    for (int i = 0; i < capacitate - 1; i++) {
        tablou[i].dreapta = i + 1;
    }
    tablou[capacitate - 1].dreapta = NIL;
}

// BC=WC=Theta(n)
void Colectie::redimensioneaza() {
    int capacitateNoua = capacitate * 2;
    Nod* tablouNou = new Nod[capacitateNoua];

    // copiaza nodurile existente
    for (int i = 0; i < capacitate; i++) {
        tablouNou[i] = tablou[i];
    }

    // initializeaza noile pozitii libere
    for (int i = capacitate; i < capacitateNoua - 1; i++) {
        tablouNou[i].dreapta = i + 1;
    }
    tablouNou[capacitateNoua - 1].dreapta = NIL;

    // conecteaza spatiul liber existent cu cel nou
    if (primuLiber == NIL) {
        primuLiber = capacitate;
    }
    else {
        // gaseste ultimul nod liber din lista actuala
        int ultim = primuLiber;
        while (tablouNou[ultim].dreapta != NIL && tablouNou[ultim].dreapta < capacitate) {
            ultim = tablouNou[ultim].dreapta;
        }
        tablouNou[ultim].dreapta = capacitate;
    }

    delete[] tablou;
    tablou = tablouNou;
    capacitate = capacitateNoua;
}
// BC=Theta(1)
// WC=Theta(n)
// Overall = Theta(1) 
// aloca un nod liber din array
int Colectie::alocareNod() {
    if (primuLiber == NIL) {
        redimensioneaza();
    }

    int index = primuLiber;
    primuLiber = tablou[primuLiber].dreapta;

    tablou[index] = Nod();

    return index;
}

// WC=BC=Theta(1)
void Colectie::eliberareNod(int index) {
    tablou[index].dreapta = primuLiber;
    primuLiber = index;
}

// BC=Theta(1)
// WC=Theta(n)
// Overall O(n)
void Colectie::adauga(TElem e) {
    if (radacina == NIL) { // daca nu exista radacina , creez una
        radacina = alocareNod();
        tablou[radacina] = Nod(e);
        dimensiune++;
        return;
    }

    int curent = radacina;

    while (true) {
        if (e == tablou[curent].elem) { // daca elementul exista deja, cresc fr
            tablou[curent].frecventa++;
            dimensiune++;
            return;
        }
        else if (rel(e, tablou[curent].elem) && e != tablou[curent].elem) { 
            if (tablou[curent].stanga == NIL) {
                tablou[curent].stanga = alocareNod();
                tablou[tablou[curent].stanga] = Nod(e);
                dimensiune++;
                return;
            }
            curent = tablou[curent].stanga;
        }
        else {
            if (tablou[curent].dreapta == NIL) {
                tablou[curent].dreapta = alocareNod();
                tablou[tablou[curent].dreapta] = Nod(e);
                dimensiune++;
                return;
            }
            curent = tablou[curent].dreapta;
        }
    }
}

// BC = Theta(1)
// WC = Theta(n)
// Overall = O(n)
int Colectie::gasesteMinin(int nod) {
    while (tablou[nod].stanga != NIL) {
        nod = tablou[nod].stanga;
    }
    return nod;
}

// BC = Theta(1)
// WC = Theta(n)
// Overall = O(n)
bool Colectie::sterge(TElem e) {
    if (radacina == NIL) {
        return false;
    }

    int curent = radacina;
    int parinte = NIL;
    bool esteStanga = false;

    // gaseste nodul de sters
    while (curent != NIL && tablou[curent].elem != e) {
        parinte = curent;
        if (rel(e, tablou[curent].elem) && e != tablou[curent].elem) {
            curent = tablou[curent].stanga;
            esteStanga = true;
        }
        else {
            curent = tablou[curent].dreapta;
            esteStanga = false;
        }
    }

    if (curent == NIL) {
        return false; // elementul nu exista
    }

    // decrementeaza frecventa
    if (tablou[curent].frecventa > 1) {
        tablou[curent].frecventa--;
        dimensiune--;
        return true;
    }

    // sterge nodul (frecventa = 1)
    dimensiune--;
    int inlocuitor = NIL;

    if (tablou[curent].stanga == NIL) { // cazul in care nodul nu are fiu stang
        inlocuitor = tablou[curent].dreapta;
    }
    else if (tablou[curent].dreapta == NIL) { // cazul in care nodul nu are fiu drept
        inlocuitor = tablou[curent].stanga;
    }
    else {
        // nodul are doi copii - gaseste succesorul
        int succesor = gasesteMinin(tablou[curent].dreapta);

        // copiez datele succesorului in nodul curent
        tablou[curent].elem = tablou[succesor].elem;
        tablou[curent].frecventa = tablou[succesor].frecventa;

        // sterge succesorul (care sigur n-are fiu stang)
        int parinteSuccesor = curent;
        int nodSuccesor = tablou[curent].dreapta;

        // gasesc succesorul si parintele sau
        while (tablou[nodSuccesor].stanga != NIL) {
            parinteSuccesor = nodSuccesor;
            nodSuccesor = tablou[nodSuccesor].stanga;
        }

        if (parinteSuccesor == curent) {
            tablou[parinteSuccesor].dreapta = tablou[nodSuccesor].dreapta;
        }
        else {
            tablou[parinteSuccesor].stanga = tablou[nodSuccesor].dreapta;
        }

        eliberareNod(nodSuccesor);
        return true;
    }

    // actualizeaza legaturile
    if (parinte == NIL) {
        radacina = inlocuitor;
    }
    else if (esteStanga) {
        tablou[parinte].stanga = inlocuitor;
    }
    else {
        tablou[parinte].dreapta = inlocuitor;
    }

    eliberareNod(curent);
    return true;
}

// BC=Theta(1)
// WC=Theta(n)
// Overall = O(n)
bool Colectie::cauta(TElem elem) const {
    int curent = radacina;

    while (curent != NIL) {
        if (elem == tablou[curent].elem) {
            return true;
        }
        else if (rel(elem, tablou[curent].elem) && elem != tablou[curent].elem) {
            curent = tablou[curent].stanga;
        }
        else {
            curent = tablou[curent].dreapta;
        }
    }

    return false;
}

// BC=Theta(1)
// WC=Theta(n)
// Overall = O(n)
int Colectie::nrAparitii(TElem elem) const {
    int curent = radacina;

    while (curent != NIL) {
        if (elem == tablou[curent].elem) {
            return tablou[curent].frecventa;
        }
        else if (rel(elem, tablou[curent].elem) && elem != tablou[curent].elem) {
            curent = tablou[curent].stanga;
        }
        else {
            curent = tablou[curent].dreapta;
        }
    }

    return 0;
}

// BC=WC=Theta(1)
int Colectie::dim() const {
    return dimensiune;
}
// BC=WC=Theta(1)
bool Colectie::vida() const {
    return dimensiune == 0;
}

// BC=Theta(1)
// WC=Theta(n)
// Overall = O(n)
IteratorColectie Colectie::iterator() const {
    return IteratorColectie(*this);
}
// BC=WC=Theta(1)
Colectie::~Colectie() {
    delete[] tablou;
}

// BC=Theta(1)
// WC=Theta(n)
// Overall = O(n)
int Colectie::diferenta() const
{
    if (radacina == NIL) {
        return -1;
    }
    int curent = radacina;
    // gasesc minimul
    while (tablou[curent].stanga != NIL) {
        curent = tablou[curent].stanga;
    }
    int minim = tablou[curent].elem;

    curent = radacina;
    // gasesc maximul
    while (tablou[curent].dreapta != NIL) {
        curent = tablou[curent].dreapta;
    }
    int maxim = tablou[curent].elem;

    return maxim - minim;
}
/*
*   pre: c: Colectie
*   post: diferenta <- max(c) - min(c)
    subAlgoritm diferenta(Colectie c)
        daca c.radacina = NIL atunci
            diferenta <- -1
        sfDaca
        curent <- c.radacina
        catTimp c.tablou[curent].stanga != NIL repeta
            curent <- c.tablou[curent].stanga
        sfCatTimp
        minim <- c.tablou[curent].elem
        curent <- c.radacina
        catTimp c.tablou[curent].dreapta != NIL repeta
            curent <- c.tablou[curent].dreapta
        sfCatTimp
        maxim <- c.tablou[curent].elem

        diferenta <- maxim - minim

*/