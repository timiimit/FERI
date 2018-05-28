#include "Frame.h"
#include <algorithm>

Frame::Frame(std::string name) : name(name)
{
}

Frame::~Frame()
{
	for (auto component : components)
	{
		delete component;
	}
}

void Frame::push(Component* c)
{
	components.push_back(c);
}

Component* Frame::pop()
{
	Component* c = components.back();
	components.pop_back();
	return c;
}

bool Frame::brisiX(uint index)
{
	if (index >= components.size())
		return false;

	auto iter = components.begin();
	std::advance(iter, index);
	components.erase(iter);
	return true;
}

Component* Frame::getX(uint index) const
{
	auto iter = components.begin();
	std::advance(iter, index);
	return *iter;
}

bool Frame::contains(Component * c) const
{
	return find(components.begin(), components.end(), c) != components.end();
}

size_t Frame::size() const
{
	return components.size();
}

std::ostream& operator<<(std::ostream & stream, Frame & frame)
{
	stream << "frame '" << frame.name << "' has size: " << frame.size();
	return stream;
}

std::istream & operator>>(std::istream & stream, Frame & frame)
{
	std::string s;
	stream >> s;
	frame = Frame(s);
	return stream;
}