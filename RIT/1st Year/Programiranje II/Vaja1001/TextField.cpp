#include "TextField.h"
#include "Frame.h"

TextField::TextField() : TextField(0, 0, "")
{
}

TextField::TextField(uint width, uint height, std::string text) : 
	text(text),
	width(width),
	height(height)
{
}

TextField::TextField(uint width, uint height) : TextField(width, height, "")
{
}

TextField::TextField(const TextField & c) : TextField(c.width, c.height, c.text)
{
}

std::string TextField::getText()
{
	return text;
}

void TextField::setText(std::string text)
{
	this->text = text;
}

uint TextField::getWidth()
{
	return width;
}

void TextField::setWidth(uint width)
{
	this->width = width;
}

uint TextField::getHeight()
{
	return height;
}

void TextField::setHeight(uint height)
{
	this->height = height;
}

void TextField::addToFrame(Frame* f)
{
	f->push(this);
}

void TextField::visible(bool b)
{
	visibility = b;
}

