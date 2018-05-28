#pragma once
#include <fstream>
#include <string>

class BinReader
{
private:
	size_t bufSize;
	char* buf;
	size_t bufBitIndex;
	std::ifstream file;

public:
	BinReader(std::string path);
	~BinReader();

	bool readBit();
	char readByte();
	int readInt();
	float readFloat();

	size_t size();
	bool isEOF();
};