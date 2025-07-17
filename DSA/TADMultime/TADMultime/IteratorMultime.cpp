#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>

// BC=Theta(1)
// WC=Theta(m)
// Overall = O(m)
IteratorMultime::IteratorMultime(const Multime& m) : multime(m) {
    pozitie = 0;
    while (pozitie < multime.m && !multime.ocupat[pozitie]) {
        pozitie++;
    }
}

// BC=Theta(1)
// WC=Theta(m)
// Overall = O(m)
void IteratorMultime::prim() {
    pozitie = 0;
    while (pozitie < multime.m && !multime.ocupat[pozitie]) {
        pozitie++;
    }
}

// BC=Theta(1)
// WC=Theta(m)
// Overall = O(m)
void IteratorMultime::urmator() {
    if (!valid()) {
        throw std::exception();
    }
    pozitie++;
    while (pozitie < multime.m && !multime.ocupat[pozitie]) {
        pozitie++;
    }
}

// BC=WC=Theta(1)
TElem IteratorMultime::element() const {
    if (!valid()) {
        throw std::exception();
    }
    return multime.ch[pozitie];
}

// BC=WC=Theta(1)
bool IteratorMultime::valid() const {
    return pozitie < multime.m && multime.ocupat[pozitie];
}