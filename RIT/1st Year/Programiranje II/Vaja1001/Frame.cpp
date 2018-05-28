#include "Frame.h"
#include <algorithm>

Frame::Frame(std::string name) : name(name)
{
}

Frame::~Frame()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		delete components[i];
	}
}

void Frame::push(Component* c)
{
	components.push_back(c);
}

Component* Frame::pop()
{
	Component* c = components[components.size() - 1];
	components.pop_back();
	return c;
}

bool Frame::brisiX(uint index)
{
	if (index >= components.size())
		return false;

	components.erase(components.begin() + index);
	return true;
}

Component* Frame::getX(uint index) const
{
	return components[index];
}

bool Frame::contains(Component * c) const
{
	return find(components.begin(), components.end(), c) != components.end();
}

size_t Frame::size() const
{
	return components.size();
}
