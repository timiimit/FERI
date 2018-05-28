#pragma once
#include <string>

class Frame;

class Component
{
protected:
	std::string name;
	int position_x;
	int position_y;
	bool visibility;

public:
	Component();
	Component(std::string name, int xPos, int yPos);
	Component(std::string name, int xPos, int yPos, bool visible);
	Component(const Component& c);

	std::string getName();
	void setName(std::string name);

	int getPositionX();
	void setPositionX(int xPos);

	int getPositionY();
	void setPositionY(int yPos);

	bool getVisible();
	void setVisible(bool visibility);

	virtual void addToFrame(Frame* z) = 0;
	virtual void visible(bool b) = 0;
};