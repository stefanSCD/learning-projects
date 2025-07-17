#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>

// BC=WC=Theta(1)
IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	/* de adaugat */
	current = col.head;
	head = col.head;
	currentIndex = 1;
}

// BC=WC=Theta(1)
TElem IteratorColectie::element() const{
	/* de adaugat */
	return current->info.first;
}

// BC=WC=Theta(1)
bool IteratorColectie::valid() const {
	/* de adaugat */
	if (current == nullptr) {
		return false;
	}
	return true;
}

// BC=WC=Theta(1)
void IteratorColectie::urmator() {
	/* de adaugat */
	if (!valid()) {
		throw std::exception();
	}
	if (currentIndex < current->info.second) {
		currentIndex++;
	}
	else {
		current = current->next;
		currentIndex = 1;
	}
}

// BC=WC=Theta(1)
void IteratorColectie::prim() {
	/* de adaugat */
	current = head;
	currentIndex = 1;
}
