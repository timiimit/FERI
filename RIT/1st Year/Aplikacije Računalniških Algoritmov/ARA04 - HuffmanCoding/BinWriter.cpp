#include "BinWriter.h"

BinWriter::BinWriter(std::string path) :
	bufSize(1024),
	buf(new char[bufSize]),
	bufBitIndex(0),
	file(path)
{
	memset(buf, 0, bufSize);
}

BinWriter::~BinWriter()
{
	file.write(buf, bufBitIndex / 8);
	if (bufBitIndex & 0b111) // 1st two bits are not 0
	{
		file.write(buf + bufBitIndex / 8, 1); // write last byte
	}
	if (file.is_open())
		file.close();
	delete[] buf;
}

void BinWriter::writeBit(bool bit)
{
	if (bufBitIndex >= bufSize * 8)
	{
		file.write(buf, bufSize);
		file.flush();
		memset(buf, 0, bufSize);
		bufBitIndex = 0;
	}

	if (bit)
		buf[bufBitIndex / 8] |= 1 << (bufBitIndex % 8);
	else
		buf[bufBitIndex / 8] &= ~(1 << (bufBitIndex % 8));

	bufBitIndex++;
}

void BinWriter::writeByte(char c)
{
	for (size_t i = 0; i < 8; i++)
	{
		writeBit((c >> i) & 1);
	}
}

void BinWriter::writeInt(int num)
{
	char* b = (char*)&num;
	for (size_t i = 0; i < sizeof(num); i++)
	{
		writeByte(*(b + i));
	}
}

void BinWriter::writeFloat(float single)
{
	char* b = (char*)&single;
	for (size_t i = 0; i < sizeof(single); i++)
	{
		writeByte(*(b + i));
	}
}
