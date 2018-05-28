#include "Besedilo.h"

Besedilo::Besedilo() :
	str((char**)new const char*[10] { "this is line one", "this is line two", "this is a random string i came up with", "and there are five more to go", "one day i will finish this list", "this day may soon be upon us", "just 2 more lines if you dont include this one", "this line is going off the 1440p screen and its starting to scroll horizontally", "FINALLY this is the last line and this was the longest text ive written in any program i have ever made (in so short time). have a nice day and goodbye!", "" }),
	lineCount(0),
	length(0),
	lineLengths(nullptr)
{
	char** p = str;
	while (**p)
	{
		lineCount++;
		p++;
	}
	lineLengths = new size_t[lineCount];
	for (size_t i = 0; i < lineCount; i++)
	{
		lineLengths[i] = strlen(str[i]);
		length += lineLengths[i];
	}

}

Besedilo::~Besedilo()
{
	delete[] str;
	delete[] lineLengths;
	length = 0;
}

size_t Besedilo::GetLineCount()
{
	return lineCount;
}

size_t Besedilo::GetLength()
{
	return length;
}

int Besedilo::prestejSamoglasnike() const
{
	int count = 0;
	for (size_t i = 0; i < lineCount; i++)
	{
		for (size_t j = 0; j < lineLengths[i]; j++)
		{
			switch (str[i][j])
			{
				case 'a':
				case 'e':
				case 'i':
				case 'o':
				case 'u':
				case 'A':
				case 'E':
				case 'I':
				case 'O':
				case 'U':
					count++;
					break;
			}
		}
	}
	return count;
}

int Besedilo::prestejSteviloBesed() const
{
	int count = 0;
	for (size_t j = 0; j < lineCount; j++)
	{
		if (lineLengths[j] == 0)
			continue;

		count++;

		for (size_t i = 0; i < length; i++)
		{
			if (str[j][i] == ' ')
				count++;
		}
		return count;
	}
	return count;
}

bool Besedilo::jePodniz(size_t lineIndex, const char* substr) const
{
	size_t substrlen = strlen(substr);
	for (size_t i = 0; i < length; i++)
	{
		bool equal = true;
		for (int j = 0; j < substrlen; j++)
		{
			if (str[lineIndex][i + j] != substr[j])
			{
				equal = false;
				break;
			}
		}
		if (equal)
			return true;
	}
	return false;
}

std::string Besedilo::toString() const
{
	std::string s;
	for (size_t i = 0; i < lineCount; i++)
	{
		s += str[i];
		s += "\n";
	}
	return s;
}

int Besedilo::NizVStevilo(const char* str)
{
	size_t len = strlen(str);
	int result = 0;
	bool negate = str[0] == '-';
	for (size_t i = negate; i < len; i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			throw std::exception("parameter 'str' was not an integer number");
		}

		result *= 10;
		result += str[i] - '0';
	}
	return negate ? -result : result;
}

bool Besedilo::VeljavniEmail(const char* str)
{
	size_t len = strlen(str);
	int counter = 0;
	for (size_t i = 0; i < len; i++)
	{
		if (str[i] == '@')
		{
			counter++;
			if (counter > 1)
				return false;
		}
	}
	return counter == 1;
}

float Besedilo::NizVFloat(const char* str)
{
	size_t len = strlen(str);
	float result = 0;
	bool negate = str[0] == '-';
	int counterafterdot = 0;
	float help = 0.1f;
	for (size_t i = negate; i < len; i++)
	{
		if (!counterafterdot && str[i] == '.')
		{
			counterafterdot++;
			continue;
		}
		if (str[i] < '0' || str[i] > '9')
		{
			throw std::exception("parameter 'str' was not a floating-point number");
		}

		if (!counterafterdot)
		{
			result *= 10;
			result += str[i] - '0';
		}
		else
		{
			float help2 = help * (str[i] - '0');
			result += help2;
			help *= 0.1f;
		}
	}
	return negate ? -result : result;
}

size_t Besedilo::GetLength(const char* str)
{
	return strlen(str);
}
