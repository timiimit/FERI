#include "Horse.h"
#include <string>



Horse::Horse() :
	canRun(true),
	speed(20.0f),
	name(nullptr)
{
}


Horse::~Horse()
{
	if (name)
		delete[] name;
}

bool Horse::GetCanRun() const
{
	return canRun;
}

void Horse::SetCanRun(bool canRun)
{
	this->canRun = canRun;
}

float Horse::GetSpeed() const
{
	return speed;
}

void Horse::SetSpeed(float speed)
{
	this->speed = speed;
}

const char* Horse::GetName() const
{
	return name;
}

void Horse::SetName(const char* name)
{
	if (this->name)
		delete[] this->name;

	int len = strlen(name) + 1;
	this->name = new char[len];
	memcpy(this->name, name, len * sizeof(*name));
}

