#pragma once
#include <string>

typedef unsigned int uint;

class Besedilo
{
private:
	char** str;
	size_t lineCount;
	size_t length;
	size_t* lineLengths;

public:

	Besedilo();
	~Besedilo();

	size_t GetLineCount();
	size_t GetLength();

	int prestejSamoglasnike() const;
	int prestejSteviloBesed() const;
	bool jePodniz(size_t lineIndex, const char* substr) const;
	std::string toString() const;

	static int NizVStevilo(const char* str);
	static bool VeljavniEmail(const char* str);
	static float NizVFloat(const char* str);
	static size_t GetLength(const char* str);
};