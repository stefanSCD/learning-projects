#include <assert.h>
#include <exception>

#include "TestExtins.h"
#include "LI.h"
#include "IteratorLI.h"

using namespace std;

void testCreare() {
    LI lista = LI();
    assert(lista.vida());
    IteratorLI it = lista.iterator();
    assert(!it.valid());
    try {
        it.urmator();
        assert(false);
    } catch (exception &) {
        assert(true);
    }
    assert(lista.dim() == 0);
}

void testAdauga() {
    LI lista = LI();
    lista.adaugaSfarsit(1);
    assert(!lista.vida());
    assert(lista.dim() == 1);
    assert(lista.element(0) == 1);
    try {
        lista.element(2);
        assert(false);
    } catch (exception&){
        assert(true);
    }

    for (int i = 0; i <= 100; i ++){
        lista.adaugaSfarsit(i);
        lista.adauga(lista.dim() - 1,i);
        try {
            lista.adauga((i+2)*2,i);
            assert(false);
        } catch (exception&){
            assert(true);
        }

        assert(lista.dim() == 2*(i+1) + 1);
    }
    IteratorLI it = lista.iterator();
    assert(it.element() == 1);
    it.urmator();
    int i = 0;
    while (it.valid()){
        assert(it.element() == i);
        it.urmator();
        assert(it.element() == i);
        it.urmator();
        i++;
    }
    assert(!it.valid());
    try {
        it.element();
        assert(false);
    } catch (exception&){
        assert(true);
    }
    it.prim();
    assert(it.valid());
    assert(it.element() == 1);

    i = 1;
    int v = 0;
    while (i < lista.dim()){
        assert(lista.element(i) == v);
        i++;
        i++;
        v++;
    }
}

void testModificaStergeCauta() {
    LI lista = LI();
    for (int i = 0; i <= 100; i ++){
        lista.adaugaSfarsit(i);
    }
    assert(lista.dim() == 101);
    assert(lista.cauta(50) == 50);
    assert(lista.cauta(100) == 100);
    assert(lista.sterge(100) == 100);
    try {
        lista.sterge(100);
        assert(false);
    } catch (exception&){
        assert(true);
    }
    assert(lista.dim() == 100);
    assert(lista.cauta(100) == -1);
    assert(lista.cauta(99) == 99);
    int v = 99;
    for (int i = 0; i < 100; i++){
        lista.modifica(i,v);
        v--;
    }
    assert(lista.element(99) == 0);
    assert(lista.cauta(99) == 0);
    assert(lista.cauta(0) == 99);
    assert(lista.cauta(50) == 49);
    try {
        lista.modifica(v,v);
        assert(false);
    } catch (exception&){
        assert(true);
    }
    IteratorLI it = lista.iterator();
    for (int i = 99; i > -1; i--){
        assert(it.element() == i);
        it.urmator();
    }
    assert(!it.valid());
    for (int i = 99; i > -1; i--){
        lista.sterge(i);
        assert(lista.dim() == i);
    }
    assert(lista.vida());
    assert(lista.dim() == 0);
    it.prim();
    assert(!it.valid());
}


void testElimina() {
    LI lista;
    lista.adaugaSfarsit(10);
    lista.adaugaSfarsit(20);
    lista.adaugaSfarsit(30);
    lista.adaugaSfarsit(40);

    // eliminare de la inceput
    {
        IteratorLI it = lista.iterator();
        assert(it.valid());
        assert(it.element() == 10);
        TElem sters = it.elimina();
        assert(sters == 10);
        assert(it.valid());
        assert(it.element() == 20);
        assert(lista.dim() == 3);
    }

    // eliminare din interiorul listei
    {
        IteratorLI it = lista.iterator();
        it.urmator();
        assert(it.element() == 30);
        TElem sters = it.elimina();
        assert(sters == 30);
        assert(it.valid());
        assert(it.element() == 40);
        assert(lista.dim() == 2);
    }

    // elimnare de la final
    {
        IteratorLI it = lista.iterator();
        it.urmator();
        assert(it.element() == 40);
        TElem sters = it.elimina();
        assert(sters == 40);
        assert(!it.valid()); // iterator devine invalid
        assert(lista.dim() == 1);
    }

    // eliminare cand lista are 1 element
    {
        IteratorLI it = lista.iterator();
        assert(lista.dim() == 1);
        TElem sters = it.elimina();
        assert(sters == 20);
        assert(!it.valid());
        assert(lista.dim() == 0);
        assert(lista.vida());
    }

    // iterator invalid
    {
        LI l2;
        IteratorLI it = l2.iterator();
        assert(!it.valid());
        try {
            it.elimina();
            assert(false);
        }
        catch (exception) {
            assert(true);
        }
    }
}


void testAllExtins() {
    testCreare();
    testAdauga();
    testModificaStergeCauta();
	testElimina();
}
