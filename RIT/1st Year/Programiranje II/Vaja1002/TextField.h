#pragma once
#include <string>

#include "definitions.h"
#include "Component.h"

class TextField : public Component
{
protected:
	std::string text;
	uint width;
	uint height;

public:
	TextField();
	TextField(uint width, uint height);
	TextField(uint width, uint height, std::string text);
	TextField(const TextField& c);

	std::string getText();
	void setText(std::string text);

	uint getWidth();
	void setWidth(uint width);

	uint getHeight();
	void setHeight(uint height);

	virtual void addToFrame(Frame* f) override;
	virtual void visible(bool b) override;

};