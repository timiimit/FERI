#include "Component.h"

Component::Component() : Component("", 0, 0)
{
}

Component::Component(std::string name, int xPos, int yPos) : Component(name, xPos, yPos, true)
{
}

Component::Component(std::string name, int xPos, int yPos, bool visible) :
	name(name),
	position_x(xPos),
	position_y(yPos),
	visibility(visible)
{
}

Component::Component(const Component& c) : Component(c.name, c.position_x, c.position_y, c.visibility)
{
}

std::string Component::getName()
{
	return name;
}

void Component::setName(std::string name)
{
	this->name = name;
}

int Component::getPositionX()
{
	return position_x;
}

void Component::setPositionX(int xPos)
{
	position_x = xPos;
}

int Component::getPositionY()
{
	return position_x;
}

void Component::setPositionY(int yPos)
{
	position_y = yPos;
}

bool Component::getVisible()
{
	return visibility;
}

void Component::setVisible(bool visibility)
{
	this->visibility = visibility;
}
