// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cassert>

template<typename T>
class MyVector {
public:

	MyVector(int size) :
			_size(size) {
		_elem = new T[size];
	}

	virtual ~MyVector() {
		/*
		// el código está en comentario porque puede causar errores sin
		// la implemntación correcta de los constructores/operatores de 
		// copia/movimiento correctos
		//
		delete[] _elem;
		_elem = nullptr;
		_size = 0;
		*/
	}

	std::size_t size() {
		return _size;
	}

	T& operator[](std::size_t i) {
		assert(i < _size);
		return _elem[i];
	}

	const T& operator[](std::size_t i) const {
		assert(i < _size);
		return _elem[i];
	}

public:

	T *_elem;
	std::size_t _size;
};

