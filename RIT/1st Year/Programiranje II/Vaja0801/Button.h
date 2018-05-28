#pragma once
#include <string>

#include "definitions.h"
#include "Component.h"

class Button : public Component
{
protected:

	std::string text;
	uint width;
	uint height;
	bool pressed;

public:

	Button();
	Button(uint width, uint height);
	Button(uint width, uint height, std::string text);
	Button(const Button& c);

	std::string getText();
	void setText(std::string text);

	uint getWidth();
	void setWidth(uint width);

	uint getHeight();
	void setHeight(uint height);

	
	virtual void addToFrame(Frame* f) override;
	virtual void visible(bool b) override;
};