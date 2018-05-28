#include "BinReader.h"
#include "BinWriter.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node
{
	string str;
	size_t count;
	Node* left;
	Node* right;

	Node(char c) :
		str(1, c),
		count(1),
		left(nullptr),
		right(nullptr)
	{

	}

	Node(char c, size_t count) :
		str(1, c),
		count(count),
		left(nullptr),
		right(nullptr)
	{

	}

	Node(string s, size_t count) :
		str(s),
		count(count),
		left(nullptr),
		right(nullptr)
	{

	}

	~Node()
	{
		if (left)
			delete left;
		if (right)
			delete right;
	}
};

int FindOccurances(vector<Node*>& nodes, BinReader* reader)
{
	int charCount = 0;
	while (!reader->isEOF())
	{
		char c = reader->readByte();
		charCount++;

		bool found = false;
		for (size_t j = 0; j < nodes.size(); j++)
		{
			if (nodes[j]->str[0] == c)
			{
				nodes[j]->count++;
				found = true;
				break;
			}
		}
		if (!found)
			nodes.push_back(new Node(c));
	}
	return charCount;
}

Node* BuildHuffmanTree(vector<Node*>& nodes)
{
	while (nodes.size() > 1)
	{
		// find 2 smallest values
		size_t min = 0;
		for (size_t i = 1; i < nodes.size(); i++)
		{
			if (nodes[i]->count < nodes[min]->count)
				min = i;
		}
		Node* right = nodes[min];
		nodes.erase(nodes.begin() + min);

		min = 0;
		for (size_t i = 1; i < nodes.size(); i++)
		{
			if (nodes[i]->count < nodes[min]->count && i != min)
				min = i;
		}
		Node* left = nodes[min];
		nodes.erase(nodes.begin() + min);

		Node* n = new Node(left->str + right->str, left->count + right->count);
		n->left = left;
		n->right = right;
		nodes.push_back(n);
		//nodes.erase(nodes.begin() + min);
		//nodes.erase(nodes.begin() + min2);
	}
	return nodes[0];
}

void WriteCompressedChar(char c, Node* root, BinWriter* writer)
{
	while (root->str.length() > 1)
	{
		if (root->left)
		{
			if (root->left->str.find(c) != string::npos)
			{
				root = root->left;
				writer->writeBit(0);
			}
		}

		if (root->right)
		{
			if (root->right->str.find(c) != string::npos)
			{
				root = root->right;
				writer->writeBit(1);
			}
		}
	}
}

char DecompressChar(BinReader* reader, Node* root)
{
	while (root->str.length() > 1 && !reader->isEOF())
	{
		bool bit = reader->readBit();
		if (bit)
		{
			root = root->right;
		}
		else
		{
			root = root->left;
		}
	}
	return root->str[0];
}

int main(int argc, char** argv)
{
	if (argc != 3)
		return 1;

	char type = argv[1][0];
	char* filename = argv[2];

	if (type == 'c')
	{
		vector<Node*> nodes;
		int charCount = FindOccurances(nodes, &BinReader(filename));

		BinWriter writer("out.bin");
		writer.writeByte((char)nodes.size());
		for (size_t i = 0; i < nodes.size(); i++)
		{
			writer.writeByte(nodes[i]->str[0]);
			writer.writeInt(nodes[i]->count);
		}
		writer.writeInt(charCount);

		Node* root = BuildHuffmanTree(nodes);

		BinReader reader(filename);

		char c;
		while (!reader.isEOF())
		{
			c = reader.readByte();
			WriteCompressedChar(c, root, &writer);
		}
	}
	else if (type == 'd')
	{
		vector<Node*> nodes;
		BinReader reader(filename);
		BinWriter writer("out_d.bin");
		size_t charCount = reader.readByte();
		for (size_t i = 0; i < charCount; i++)
		{
			char c = reader.readByte();
			int count = reader.readInt();
			nodes.push_back(new Node(c, count));
		}
		charCount = reader.readInt();

		Node* root = BuildHuffmanTree(nodes);

		int writtenCharCount = 0;
		while (!reader.isEOF() && writtenCharCount < charCount)
		{
			char c = DecompressChar(&reader, root);
			writtenCharCount++;
			if (c == '\0')
				int brekpoint = 0;
			writer.writeByte(c);
		}
	}

	return 0;
}