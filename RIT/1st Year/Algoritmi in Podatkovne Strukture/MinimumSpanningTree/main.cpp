#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>

using namespace std;


#pragma region Stack.h

namespace timiimit
{
	namespace GenericStructures
	{
		template <class T, class IndexType = size_t>
		class Stack
		{
		private:
#ifdef _DEBUG
			IndexType maxSize;
#endif
			IndexType size;
			IndexType capacity;
			T* data;

			void resize(IndexType newSize);

		public:
			Stack(IndexType capacity);
			Stack();
			~Stack();

			IndexType GetCurrentCapacity() const;
			IndexType GetSize() const;
			void Push(const T& p);
			T& Top() const;
			T& Pop();
			T& operator[](IndexType index) const;
		};

		///////////////////////////////////////////
		//			  IMPLEMENTATION			 //
		///////////////////////////////////////////

		template <class T, class IndexType>
		inline void Stack<T, IndexType>::resize(IndexType newCapacity)
		{
			T* larger = new T[newCapacity];
			std::memcpy(larger, data, size * sizeof(T));
			delete[] data;
			data = larger;
			capacity = newCapacity;
		}

		template <class T, class IndexType>
		Stack<T, IndexType>::Stack() : Stack<T, IndexType>::Stack(16)
		{
		}

		template <class T, class IndexType>
		Stack<T, IndexType>::Stack(IndexType capacity) :
			size(0),
#ifdef _DEBUG
			maxSize(0),
#endif
			capacity(capacity),
			data(new T[capacity])
		{
		}


		template <class T, class IndexType>
		Stack<T, IndexType>::~Stack()
		{
			delete[] data;
		}

		template<class T, class IndexType>
		inline IndexType Stack<T, IndexType>::GetCurrentCapacity() const
		{
			return capacity;
		}

		template <class T, class IndexType>
		inline IndexType Stack<T, IndexType>::GetSize() const
		{
			return size;
		}

		template <class T, class IndexType>
		inline void Stack<T, IndexType>::Push(const T& p)
		{
			if (size >= capacity)
			{
				resize(size + 16);
			}
			data[size++] = p;

#ifdef _DEBUG
			if (size > maxSize)
				maxSize = size;
#endif
		}

		template <class T, class IndexType>
		inline T& Stack<T, IndexType>::Top() const
		{
			if (size <= 0)
				throw std::exception("can't call Top() upon an empty stack");
			return data[size - 1];
		}

		template <class T, class IndexType>
		inline T& Stack<T, IndexType>::Pop()
		{
			if (size <= 0)
				throw std::exception("can't call Pop() upon an empty stack");
			return data[--size];
		}

		template<class T, class IndexType>
		inline T& Stack<T, IndexType>::operator[](IndexType index) const
		{
			if (index >= size || index < 0)
				throw std::exception("index out of range");
			return data[index];
		}
	}
}

#pragma endregion

using namespace timiimit::GenericStructures;

typedef unsigned int uint;
typedef unsigned short ushort;

struct Node
{
	string name;
};

struct Connection
{
	int a;
	int b;
	float cost;
};

bool operator<(Connection& a, Connection& b)
{
	return a.cost < b.cost;
}
bool operator>(Connection& a, Connection& b)
{
	return a.cost > b.cost;
}
bool operator<=(Connection& a, Connection& b)
{
	return a.cost <= b.cost;
}
bool operator>=(Connection& a, Connection& b)
{
	return a.cost >= b.cost;
}

int GetIndexByName(Node* nodes, int nodeCount, string name)
{
	for (int i = 0; i < nodeCount; i++)
	{
		if (nodes[i].name == name)
		{
			return i;
		}
	}
	return -1;
}

bool LoadFromFile(const char* const filename, Node** nodes, int* nodeCount, Connection** connections, int* connectionCount)
{
	ifstream file(filename);
	if (!file.is_open())
		return false;

	file >> *nodeCount;
	file >> *connectionCount;

	*nodes = new Node[*nodeCount];
	*connections = new Connection[*connectionCount];

	int nodeIndex = 0;
	for (size_t i = 0; i < *connectionCount; i++)
	{
		string name1;
		string name2;
		float cost;
		file >> name1 >> name2 >> cost;

		int index1 = GetIndexByName(*nodes, *nodeCount, name1);
		int index2 = GetIndexByName(*nodes, *nodeCount, name2);

		if (index1 < 0)
		{
			Node& n = (*nodes)[nodeIndex];

			index1 = nodeIndex;
			n.name = name1;
			nodeIndex++;
		}

		if (index2 < 0)
		{
			Node& n = (*nodes)[nodeIndex];

			index2 = nodeIndex;
			n.name = name2;
			nodeIndex++;
		}

		Connection& c = (*connections)[i];
		c.a = index1;
		c.b = index2;
		c.cost = cost;
	}

	return true;
}

template<class T>
void quicksort(T* l, T* r)
{
	struct Node
	{
	public:
		T * left;
		T* right;
		Node() : left(nullptr), right(nullptr) {}
		Node(T* l, T* r) : left(l), right(r) {}
	};
	Stack<Node> s;
	s.Push(Node(l, r));
	while (s.GetSize())
	{
		Node n = s.Pop();
		T* pivot = n.left;
		l = n.left;
		r = n.right;
		if (l >= r)
			continue;
		while (l < r)
		{
			while (*l <= *pivot && l < n.right)
				l++;
			while (*r >= *pivot && r > n.left)
				r--;

			if (l < r)
				swap(*l, *r);
		}
		swap(*n.left, *r);

		if (n.left < n.right)
		{
			s.Push(Node(n.left, r - 1));
			s.Push(Node(r + 1, n.right));
			l = n.left;
			r = r - 1;
		}
	}
}

template<class T>
void quicksort_median(T* l, T* r)
{
	struct Node
	{
	public:
		T * left;
		T* right;
		Node() : left(nullptr), right(nullptr) {}
		Node(T* l, T* r) : left(l), right(r) {}
	};
	Stack<Node> s;
	s.Push(Node(l, r));
	while (s.GetSize())
	{
		Node n = s.Pop();
		T* pivot = n.left + ((n.right - n.left) / 2);
		l = n.left;
		r = n.right;
		if (l >= r)
			continue;
		while (l < r)
		{
			while (*l <= *pivot && l < n.right)
				l++;
			while (*r >= *pivot && r > n.left)
				r--;

			if (l < r)
				swap(*l, *r);
		}
		swap(*n.left, *r);

		if (n.left < n.right)
		{
			s.Push(Node(n.left, r - 1));
			s.Push(Node(r + 1, n.right));
			l = n.left;
			r = r - 1;
		}
	}
}


void GetGroupIndex(vector<vector<int>>& groups, int& nodeIndex1, int& nodeIndex2)
{
	char flags = 0;
	size_t groupCount = groups.size();
	vector<int>* gPtr = groups.data();
	vector<int>* gPtr_end = gPtr + groupCount;

	while (gPtr < gPtr_end)
	{
		size_t groupElementCount = gPtr->size();
		int* iPtr = gPtr->data();
		int* iPtr_end = iPtr + groupElementCount;

		while (iPtr < iPtr_end)
		{
			if (*iPtr == nodeIndex1 && !(flags & 1))
			{
				nodeIndex1 = (gPtr - groups.data());
				flags |= 1;
			}
			else if (*iPtr == nodeIndex2 && !(flags & 2))
			{
				nodeIndex2 = (gPtr - groups.data());
				flags |= 2;
			}

			if (flags == 3)
			{
				gPtr = gPtr_end;
				break;
			}
			iPtr++;
		}
		gPtr++;
	}

	if (!(flags & 1))
		nodeIndex1 = -1;

	if (!(flags & 2))
		nodeIndex2 = -1;
}

void CreateMinimumSpanningTree(Node* nodes, int nodeCount, Connection** connections, int* connectionCount)
{
	vector<Connection> cs;
	vector<vector<int>> groups;
	ushort* nodeLocations = new ushort[*connectionCount];
	memset(nodeLocations, -1, sizeof(*nodeLocations) * *connectionCount);
	for (size_t i = 0; i < *connectionCount; i++)
	{
		Connection& c = (*connections)[i];
		uint a1 = c.a;
		uint b1 = c.b;
		ushort a = nodeLocations[a1];
		ushort b = nodeLocations[b1];
		//GetGroupIndex(groups, a, b);


		if (a == UINT16_MAX && b == UINT16_MAX)
		{
			// new group

			vector<int> group;
			group.push_back(a1);
			group.push_back(b1);
			groups.push_back(group);

			cs.push_back(c);
			nodeLocations[a1] = groups.size() - 1;
			nodeLocations[b1] = nodeLocations[a1];
		}
		else if (a != UINT16_MAX && b != UINT16_MAX && a != b)
		{
			// combine two groups

			groups[a].insert(groups[a].end(), groups[b].begin(), groups[b].end());
			groups.erase(groups.begin() + b);
			cs.push_back(c);
			
			for (size_t i = 0; i < *connectionCount; i++)
			{
				if (nodeLocations[i] == b)
					nodeLocations[i] = a;
				if (nodeLocations[i] > b && nodeLocations[i] != UINT16_MAX)
					nodeLocations[i]--;
			}
		}
		else if (a != UINT16_MAX && b == UINT16_MAX)
		{
			groups[a].push_back(c.b);
			cs.push_back(c);
			nodeLocations[b1] = a;
		}
		else if (b != UINT16_MAX && a == UINT16_MAX)
		{
			groups[b].push_back(c.a);
			cs.push_back(c);
			nodeLocations[a1] = b;
		}
		else
		{
			// reject connection
		}
	}

	delete[] *connections;
	*connections = new Connection[cs.size()];
	memcpy(*connections, cs.data(), cs.size() * sizeof(**connections));
	*connectionCount = cs.size();
}

int GetMaxNodeNameLength(Node* nodes, int nodeCount)
{
	int maxlen = 0;
	for (size_t i = 0; i < nodeCount; i++)
	{
		if (nodes[i].name.length() > maxlen)
			maxlen = nodes[i].name.length();
	}
	return maxlen;
}

#define MEASURETIME(x, time) { auto start = std::chrono::system_clock::now(); x; auto end=std::chrono::system_clock::now(); time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0; }


int main()
{
	int maxNodeNameLength = 0;
	int nodeCount = 0;
	Node* nodes = nullptr;
	int connectionCount = 0;
	Connection* connections = nullptr;
	bool running = true;

	while (running)
	{
		cout << R"(
Kruskalov algoritem - izbira:
1) Preberi graf iz datoteke
2) Generiraj nakljucni graf
3) Pozeni
4) Izpis sprejetih povezav
5) Konec
Izbira: )";
		int choice;
		cin >> choice;

		switch (choice)
		{
			case 1:
			case 2:
			{
				switch (choice)
				{
					case 1:
					{
						cout << "enter filename to load: ";
						string filename = "grafBig.txt";
						cin >> filename;



						Node* ns = nullptr;
						Connection* cs = nullptr;
						if (!LoadFromFile(filename.c_str(), &ns, &nodeCount, &cs, &connectionCount))
						{
							cout << "Failed to load file." << endl;
						}
						else
						{
							if (connections)
								delete[] connections;
							if (nodes)
								delete[] nodes;

							nodes = ns;
							connections = cs;
						}
						break;
					}

					case 2:
					{
						cout << "Number of nodes: ";
						cin >> nodeCount;

						if (connections)
							delete[] connections;
						if (nodes)
							delete[] nodes;

						nodes = new Node[nodeCount];
						connectionCount = 0;
						connections = new Connection[(nodeCount * (nodeCount - 1)) / 2];
						for (size_t i = 0; i < nodeCount; i++)
						{
							nodes[i].name = to_string(i);
						}

						for (size_t i = 0; i < nodeCount; i++)
						{
							for (size_t j = 0; j < nodeCount; j++)
							{
								if (i >= j)
									continue;

								if (rand() & 1)
								{
									connections[connectionCount].a = i;
									connections[connectionCount].b = j;
									connections[connectionCount].cost = (rand() % 1000) / 10.0f; // between 0 and 999.9
									connectionCount++;
								}
							}
						}

						Connection* cs = new Connection[connectionCount];
						memcpy(cs, connections, connectionCount * sizeof(*connections));
						delete[] connections;
						connections = cs;
						break;
					}
				}

				maxNodeNameLength = GetMaxNodeNameLength(nodes, nodeCount);

				quicksort_median(connections, connections + connectionCount - 1);
				break;
			}

			case 3:
			{
				if (nodeCount == 0)
				{
					cout << "No nodes loaded!" << endl;
					break;
				}
				int connectionCountBefore = connectionCount;
				double time;
				MEASURETIME(CreateMinimumSpanningTree(nodes, nodeCount, &connections, &connectionCount), time);


				cout << "Node count: " << nodeCount << endl
					<< "Connection count before: " << connectionCountBefore << endl
					<< "Connection count after: " << connectionCount << endl
					<< "Time: " << time << "ms" << endl << endl;

				break;
			}

			case 4:
			{
				if (connectionCount == 0)
				{
					cout << "No connections between nodes!" << endl;
					break;
				}

				stringstream ss;
				ss << "%" << maxNodeNameLength + 2 << "s%" << maxNodeNameLength + 2 << "s  %2.2f\n";
				string s = ss.str();
				for (size_t i = 0; i < connectionCount; i++)
				{
					printf(s.c_str(), nodes[connections[i].a].name.c_str(), nodes[connections[i].b].name.c_str(), connections[i].cost);
				}
				break;
			}

			case 5:
				running = false;
				break;
		}
	}

	if (connections)
		delete[] connections;
	if (nodes)
		delete[] nodes;

	return 0;
}