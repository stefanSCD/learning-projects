#include "TestScurt.h"
#include "Colectie.h"
#include "IteratorColectie.h"
#include <assert.h>

void testAll() {
	Colectie c;
	c.adauga(5);
	c.adauga(6);
	c.adauga(0);
	c.adauga(5);
	c.adauga(10);
	c.adauga(8);

	assert(c.dim() == 6);
	assert(c.nrAparitii(5) == 2);

	assert(c.sterge(5) == true);
	assert(c.dim() == 5);

	assert(c.cauta(6) == true);
	assert(c.vida() == false);

	IteratorColectie ic = c.iterator();
	assert(ic.valid() == true);
	while (ic.valid()) {
		ic.element();
		ic.urmator();
	}
	assert(ic.valid() == false);
	ic.prim();
	assert(ic.valid() == true);

	Colectie col;
	assert(col.diferenta() == -1);

	col.adauga(5);
	assert(col.diferenta() == 0);

	col.adauga(10);
	col.adauga(2);
	col.adauga(7);
	assert(col.diferenta() == 10 - 2);

	Colectie c3;
	c3.adauga(9);
	c3.adauga(7);
	c3.adauga(5);
	c3.adauga(3);
	c3.adauga(1);
	assert(c3.diferenta() == 9 - 1);

	col.adauga(-2);
	assert(col.diferenta() == 12);
}
