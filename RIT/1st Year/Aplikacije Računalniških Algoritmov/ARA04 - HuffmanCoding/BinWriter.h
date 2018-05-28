#pragma once
#include <fstream>
#include <string>

class BinWriter
{
private:
	size_t bufSize;
	char* buf;
	size_t bufBitIndex;
	std::ofstream file;

public:
	BinWriter(std::string path);
	~BinWriter();

	void writeBit(bool bit);
	void writeByte(char c);
	void writeInt(int num);
	void writeFloat(float single);
};