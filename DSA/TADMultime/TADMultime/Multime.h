#pragma once
#define NULL_TELEM -1
typedef int TElem;

class IteratorMultime;

class Multime {
    friend class IteratorMultime;
private:
    TElem* ch;          
    int* urm; 
    int m;
    int primLiber;
    int dimensiune;
    bool* ocupat;

    // Functia de dispersie
    int d(TElem elem) const;

    // Actualizeaza primLiber dupa ocuparea unei pozitii
    void actPrimLiber();

    // Redimensionare si rehashing
    void redimensionare();

    // Functie auxiliara pentru stergere recursiva
    void stergeRec(int i, int anterior, int pozDisp);

    // Trece la urmatorul numar prim
    int nextPrime(int n) const;
public:
    //constructorul implicit
    Multime();

    //adauga un element in multime
    //returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
    bool adauga(TElem e);

    //sterge un element din multime
    //returneaza adevarat daca elementul a existat si a fost sters
    bool sterge(TElem e);

    //verifica daca un element se afla in multime
    bool cauta(TElem elem) const;

    //intoarce numarul de elemente din multime;
    int dim() const;

    //verifica daca multimea e vida;
    bool vida() const;

    //returneaza un iterator pe multime
    IteratorMultime iterator() const;

    // destructorul multimii
    ~Multime();

    // retunreaza diferenta dintre maxim si minim sau -1 daca nu sunt elemente
    int diferentaMaxMin() const;
};