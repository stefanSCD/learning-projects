#include "TestScurt.h"
#include <assert.h>
#include "Multime.h"
#include "IteratorMultime.h"

void testAll() { //apelam fiecare functie sa vedem daca exista
	Multime m;
	assert(m.vida() == true);
	assert(m.dim() == 0); //adaug niste elemente
	assert(m.adauga(5) == true);
	assert(m.adauga(1) == true);
	assert(m.adauga(10) == true);
	assert(m.adauga(7) == true);
	assert(m.adauga(1) == false);
	assert(m.adauga(10) == false);
	assert(m.adauga(-3) == true);
	assert(m.dim() == 5);
	assert(m.cauta(10) == true);
	assert(m.cauta(16) == false);
	assert(m.sterge(1) == true);
	assert(m.sterge(6) == false);
	assert(m.dim() == 4);


	IteratorMultime im = m.iterator();
	im.prim();
	int s = 0;
	while (im.valid()) {
		TElem e = im.element();
		s += e;
		im.urmator();
	}
	assert(s == 19);

	Multime M;
	assert(M.diferentaMaxMin() == -1);

	Multime m1;
	m1.adauga(42);
	assert(m1.diferentaMaxMin() == 0);

	Multime m2;
	m2.adauga(10);
	bool adaugat = m2.adauga(10);
	assert(!adaugat);
	assert(m2.dim() == 1);
	assert(m2.diferentaMaxMin() == 0);

	Multime m3;
	m3.adauga(5);
	m3.adauga(15);
	assert(m3.diferentaMaxMin() == 10);
}
