#include "Iterator.h"
#include "Matrice.h"
#include <exception>

//BC:Theta(1)
//O(m)
MatrixIterator::MatrixIterator(const Matrice& m) : matrix(m) {
	prim();
}

//BC:Theta(1)
//O(m)
void MatrixIterator::prim()
{
	row = 0;
	col = 0;
	while (row < matrix.nrLinii() && matrix.element(row, col) == NULL_TELEMENT) {
		row++;
	}
}

//BC:Theta(1)
// O(n)
void MatrixIterator::urmator()
{
	do {
		col++;
		if (col == matrix.nrColoane())
		{
			col = 0;
			row++;
		}
	} while (row < matrix.nrLinii() && matrix.element(row, col) == NULL_TELEMENT);
}

// Theta(1)
bool MatrixIterator::valid() const
{
	return row < matrix.nrLinii();
}

//Theta(1)
// O(n)
TElem MatrixIterator::element() const
{
	if (!valid())
		throw std::exception();
	return matrix.element(row, col);
}

