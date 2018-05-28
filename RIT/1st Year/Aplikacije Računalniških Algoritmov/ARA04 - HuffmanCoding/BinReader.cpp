#include "BinReader.h"

BinReader::BinReader(std::string path) : 
	bufSize(1024),
	buf(new char[bufSize]),
	bufBitIndex(bufSize * 8),
	file(path)
{
	//file.read(buf, bufSize);
}

BinReader::~BinReader()
{
	delete[] buf;
	if (file.is_open())
	{
		file.close();
	}
}

bool BinReader::readBit()
{
	if (bufBitIndex >= bufSize * 8)
	{
		memset(buf, 0, bufSize);
		file.read(buf, bufSize);
		bufBitIndex = 0;
	}

	bool b = (buf[bufBitIndex / 8] >> ((bufBitIndex % 8))) & 1;
	bufBitIndex++;
	return b;
}

char BinReader::readByte()
{
	char c = 0;
	for (size_t i = 0; i < 8; i++)
	{
		c |= readBit() << i;
	}
	return c;
}

int BinReader::readInt()
{
	int c = 0;
	for (size_t i = 0; i < 32; i++)
	{
		c |= readBit() << i;
	}
	return c;
}

float BinReader::readFloat()
{
	int c = 0;
	for (size_t i = 0; i < 32; i++)
	{
		c |= readBit() << i;
	}
	return *(float*)&c;
}

size_t BinReader::size()
{
	auto bak = file.tellg();
	file.seekg(0, file.end);
	size_t length = file.tellg();
	file.seekg(bak);
	return length;
}

bool BinReader::isEOF()
{
	bool eof = file.eof();
	int byteIndex = bufBitIndex / 8;
	int lastReadCount = file.gcount();
	return file.eof() && bufBitIndex/8 >= file.gcount();
}
