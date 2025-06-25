// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>

#include "MyVector.h"

int main(int, char**) {

	MyVector<int> a(10);

	// ejemplos de uso


	// copiar
	MyVector<int> b(a);

	// mover
	MyVector<int> c(std::move(a));

	MyVector<int> d(100);
	c = d; // copiar

	MyVector<int> e(10);
	e = std::move(c); // mover
	e = MyVector<int>(30); // mover

	// un caso "especial"
	MyVector<int> &f = e; // asignación por referencia
	f = e; // copiar
	f = std::move(e); // mover

	return 0;
}

