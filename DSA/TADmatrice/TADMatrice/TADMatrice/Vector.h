#pragma once
#include <stdlib.h>
#include <utility>
typedef int TElem;
typedef std::pair <int, TElem> Pair;

class  Vector
{
public:
	int* v;
	Vector();
	~Vector();
	int getLen() const;
	void Add(int x);
	void Delete(int x);
private:
	int capacity;
	int len;
};

class Vector1
{
public:
	Pair *p;
	Vector1();
	~Vector1();
	int getLen1() const;
	void Add(int indice_col, TElem x);
	void Delete(int indice_col, TElem x);
	void insertAt(int pos, int indice_col, TElem x);
private:
	int capacity;
	int len;
};


