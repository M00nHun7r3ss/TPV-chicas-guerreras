
#pragma once
#include "Component.h"

class Container;

class InputConverter : public Component {
public:
	InputConverter() {
	}
	virtual ~InputConverter()() {
	}
	auto handleInput(auto key);
};

