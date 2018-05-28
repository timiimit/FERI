#include "Button.h"
#include "Frame.h"

Button::Button() : Button(0, 0)
{
}

Button::Button(uint width, uint height) : Button(width, height, "")
{
}

Button::Button(uint width, uint height, std::string text) :
	text(text),
	width(width),
	height(height),
	pressed(false)
{
}

Button::Button(const Button & c) : Button(c.width, c.height, c.text)
{
}

std::string Button::getText()
{
	return text;
}

void Button::setText(std::string text)
{
	this->text = text;
}

uint Button::getWidth()
{
	return width;
}

void Button::setWidth(uint width)
{
	this->width = width;
}

uint Button::getHeight()
{
	return height;
}

void Button::setHeight(uint height)
{
	this->height = height;
}

void Button::addToFrame(Frame * f)
{
	f->push(this);
}

void Button::visible(bool b)
{
	visibility = b;
}

