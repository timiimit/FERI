#pragma once
#include <string>
#include <list>
#include <vector>
#include "definitions.h"
#include "Component.h"
#include <iostream>


class Frame
{
private:
	std::string name;
	std::list<Component*> components;

public:

	Frame(std::string name);
	~Frame();


	void push(Component* c);
	Component* pop();

	bool brisiX(uint index);
	Component* getX(uint index) const;
	bool contains(Component* c) const;

	size_t size() const;

	friend std::ostream& operator<<(std::ostream& stream, Frame& frame);
	friend std::istream& operator>>(std::istream& stream, Frame& frame);

	Component* operator[](uint index)
	{
		return getX(index);
	}
};