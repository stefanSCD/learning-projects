#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

// BC=WC=Theta(m)
Multime::Multime() {
    m = 127;
    ch = new TElem[m];
    urm = new int[m];
    ocupat = new bool[m];
    dimensiune = 0;
    primLiber = 0;

    for (int i = 0; i < m; i++) {
        ch[i] = NULL_TELEM;
        urm[i] = -1;
        ocupat[i] = false;
    }
}

// BC=WC=Theta(1)
int Multime::d(TElem elem) const {
    return abs(elem) % m;
}

// BC=Theta(1)
// WC=Theta(m)
// Overall = O(m)
void Multime::actPrimLiber() {
    primLiber++;
    while (primLiber < m && ocupat[primLiber]) {
        primLiber++;    
    }
}

// BC=WC=Theta(m)
void Multime::redimensionare() {
    TElem* ch_vechi = ch;
    int* urm_vechi = urm;
    bool* ocupat_vechi = ocupat;
    int m_vechi = m;

    m = nextPrime(m * 2);
    ch = new TElem[m];
    urm = new int[m];
    ocupat = new bool[m];
    dimensiune = 0;
    primLiber = 0;

    for (int i = 0; i < m; i++) {
        ch[i] = NULL_TELEM;
        urm[i] = -1;
        ocupat[i] = false;
    }

    for (int i = 0; i < m_vechi; i++) {
        if (ocupat_vechi[i]) {
            TElem elem = ch_vechi[i];
            int pozitie = d(elem);

            if (!ocupat[pozitie]) {
                ch[pozitie] = elem;
                ocupat[pozitie] = true;
                if (pozitie == primLiber) {
                    actPrimLiber();
                }
            }
            else {
                int j = pozitie;
                while (urm[j] != -1) {
                    j = urm[j];
                }

                ch[primLiber] = elem;
                ocupat[primLiber] = true;
                urm[j] = primLiber;
                actPrimLiber();
            }
            dimensiune++;
        }
    }
    delete[] ch_vechi;
    delete[] urm_vechi;
    delete[] ocupat_vechi;
}

// BC=Theta(1)
// WC=Theta(m)
// Overall = O(m)
bool Multime::adauga(TElem elem) {
    if (cauta(elem)) {
        return false;
    }

    int i = d(elem);

    if (!ocupat[i]) { // cazul in care locatia este libera
        ch[i] = elem;
        ocupat[i] = true;
        if (i == primLiber) {
            actPrimLiber();
        }
        dimensiune++;
        return true;
    }
    else { // cazul in care avem coliziune si adauga la sf listei
        if (primLiber >= m) {
            redimensionare();
            return adauga(elem);
        }
        int j = i; // gasesc sf lantului care incepe la pozitia i
        while (urm[j] != -1) {
            j = urm[j];
        }
        ch[primLiber] = elem;
        ocupat[primLiber] = true;
        urm[j] = primLiber;
        actPrimLiber();
        dimensiune++;
        return true;
    }
}

// BC=Theta(1)
// WC=Theta(n)
// Overall = O(n)
bool Multime::sterge(TElem elem) {
    int pozDisp = d(elem);

    int i = pozDisp;
    int anterior = -1;

    while (i != -1) {
        if (ocupat[i] && ch[i] == elem) {
            stergeRec(i, anterior, pozDisp);
            dimensiune--;
            return true;
        }
        anterior = i;
        i = urm[i];
    }

    return false;
}

// BC=Theta(1)
// WC=Theta(n)
// Overall = O(n)
void Multime::stergeRec(int i, int anterior, int pozDisp) {
    // cauta in lista care porneste de la i primul element care ar trebui sa fie la pozDisp
    int j = urm[i];
    int anteriorJ = i;

    while (j != -1) {
        if (ocupat[j] && d(ch[j]) == pozDisp) { // verific daca elementul este pe pozitia corecta
            ch[i] = ch[j]; // mut elementul in locul celui sters
            urm[i] = urm[j];

            stergeRec(j, anteriorJ, pozDisp);
            return;
        }
        anteriorJ = j;
        j = urm[j];
    }

    // nu am gasit niciun element care sa trebuiasca sa fie la pozDisp
    // putem sterge direct nodul de la pozitia i
    ch[i] = NULL_TELEM;
    ocupat[i] = false;

    // actualizez legaturile
    if (anterior != -1) {
        urm[anterior] = urm[i];
    }
    urm[i] = -1;

    // actualizez primLiber daca e necesar
    if (i < primLiber) {
        primLiber = i;
    }
}

// BC=Theta(1)
// WC=Theta(Sqrt(n))
// Overall = O(Sqrt(n))
int Multime::nextPrime(int n) const
{
    if (n <= 2) return 2;
    if (n <= 3) return 3;

    if (n % 2 == 0) {
        n++;
    }

    while (true) {
        bool isPrim = true;

        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) {
                isPrim = false;
                break;
            }
        }

        if (isPrim) {
            return n;
        }

        n += 2;
    }
}

// BC=Theta(1)
// WC=Theta(n)
// Overall = O(n)
bool Multime::cauta(TElem elem) const {
    int i = d(elem);

    while (i != -1) {
        if (ocupat[i] && ch[i] == elem) {
            return true;
        }
        i = urm[i];
    }
    return false;
}

// BC=WC=Theta(1)
int Multime::dim() const {
    return dimensiune;
}

// BC=WC=Theta(1)
bool Multime::vida() const {
    return dimensiune == 0;
}

// BC=WC=Theta(1)
Multime::~Multime() {
    delete[] ch;
    delete[] urm;
    delete[] ocupat;
}

// BC=Theta(1)
// WC=Theta(m)
// Overall = O(m)
int Multime::diferentaMaxMin() const
{
    if (dimensiune == 0) {
        return -1;
    }

    TElem minim, maxim;
    bool gasitPrimul = false;
    for (int i = 0; i < m; i++) {
        if (ocupat[i]) {
            TElem elem = ch[i];

            if (!gasitPrimul) {
                minim = maxim = elem;
                gasitPrimul = true;
            }
            else {
                if (elem < minim) {
                    minim = elem;
                }
                if (elem > maxim) {
                    maxim = elem;
                }
            }
        }
    }

    return maxim - minim;
}

/*
    pre: m :Multime
    post: diferentaMaxMin <- max(m) - min(m)
    subAlgoritm diferentaMaxMin(multime m)
        daca m.dimensiune() = 0 atunci
            diferentaMaxMin <- -1
        sfData
        gasitPrimul <- false
        pentru i<-0,m executa
            daca(m.ocupat(i)) atunci
                elem <- m.ch[i]
                daca gasitPrimul = false atunci
                    minim <- elem
                    maxim <- elem
                    gasitPrimul <- true
                altfel
                    daca elem < minim atunci
                        minim <- elem
                    sfDaca
                    daca elem > maxim atunci
                        maxim <- elem
                    sfDaca
                sfDaca
            sfDaca
        sfPentru
        diferentaMaxMin <- maxim - minim
    sfSubAlgoritm
*/


// BC=Theta(1)
// WC=Theta(m)
// Overall = O(m)
IteratorMultime Multime::iterator() const {
    return IteratorMultime(*this);
}