#pragma once
#include <string>
#include <vector>
#include "definitions.h"
#include "Component.h"

class Frame
{
private:
	std::string name;
	std::vector<Component*> components;

public:

	Frame(std::string name);
	~Frame();


	void push(Component* c);
	Component* pop();

	bool brisiX(uint index);
	Component* getX(uint index);

	size_t size();



};