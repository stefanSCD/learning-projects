#include "Vector.h"
#include "utility"


//Theta(1) BC=WC
Vector::Vector()
{
	this->len = 0;
	this->capacity = 4;
	this->v = (int*)malloc(this->capacity * sizeof(int));
}

//Theta(1) BC=WC
Vector::~Vector()
{
	free(this->v);
}

//Theta(1) BC=WC
int Vector::getLen() const
{
	return this->len;
}

//BC:Theta(1)
//WC:Theta(n)
//O(n)
void Vector::Add(int x) {
	if (this->len == this->capacity) {
		int new_capacity = this->capacity * 2;
		int* new_v = (int*)malloc(new_capacity * sizeof(int));
		for (int i = 0; i < this->len; i++) {
			new_v[i] = this->v[i];
		}
		free(this->v);
		this->v = new_v;
		this->capacity = new_capacity;
	}
	v[this->len++] = x;
}

//Theta(n) BC=WC
void Vector::Delete(int x)
{
	int i = 0;
	while (i < this->len && this->v[i] != x) {
		i++;
	}
	if (i == this->len) {
		return;
	}
	for (int j = i; j < this->len - 1; j++) {
		this->v[j] = this->v[j + 1];
	}
	this->len--;
}

//Theta(1) BC=WC
Vector1::Vector1()
{
	this->len = 0;
	this->capacity = 4;
	this->p = (Pair*)malloc(sizeof(Pair) * this->capacity);
}


//Theta(1) BC=WC
Vector1::~Vector1()
{
	free(this->p);
	this->p = nullptr;
}


//Theta(1) BC=WC
int Vector1::getLen1() const
{
	return this->len;
}

//BC:Theta(1)
//WC:Theta(n)
//O(n)
void Vector1::Add(int indice_col, TElem x)
{
	std::pair<int, TElem> pereche = { indice_col, x };
	if (this->len == this->capacity) {
		int new_capacity = this->capacity * 2;
		Pair* new_p = (Pair*)malloc(sizeof(Pair) * new_capacity);
		for (int i = 0; i < this->len; i++) {
			new_p[i] = this->p[i];
		}
		free(this->p);
		this->p = new_p;
		this->capacity = new_capacity;
	}
	p[this->len++] = pereche;
}


//Theta(n) BC=WC
void Vector1::Delete(int indice_col, TElem x)
{
	int i = 0;
	while (i < this->len && this->p[i].first != indice_col && this->p[i].second != x) {
		i++;
	}
	if (i == this->len) {
		return;
	}
	for (int j = i; j < this->len - 1; j++) {
		this->p[j] = this->p[j + 1];
	}
	this->len--;
}

//BC: Theta(1)
//WC: Theta(n)
//O(n)
void Vector1::insertAt(int pos, int indice_col, TElem x) {
	if (this->len == this->capacity) {
		int new_capacity = this->capacity * 2;
		Pair* new_p = (Pair*)malloc(sizeof(Pair) * new_capacity);
		for (int i = 0; i < this->len; i++) {
			new_p[i] = this->p[i];
		}
		free(this->p);
		this->p = new_p;
		this->capacity = new_capacity;
	}
	for (int i = this->len; i > pos; i--) {
		this->p[i] = this->p[i - 1];
	}
	this->p[pos] = { indice_col, x };
	this->len++;
}
