// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <ctime>
#include <random>

class Resource {
	std::random_device _rd;
	std::mt19937 _gen;
	std::uniform_int_distribution<unsigned int> _dist;
public:

	Resource() :
			_rd(), _gen(_rd()) {
		_count++;
	}

	virtual ~Resource() {
		_count--;
	}

	unsigned int action() {
		return _dist(_gen);
	}

	static int _count;
};





