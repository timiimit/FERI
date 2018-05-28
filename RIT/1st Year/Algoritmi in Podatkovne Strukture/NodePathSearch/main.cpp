#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <chrono>

using namespace std;

struct Node
{
	string name;
	float cost;
	int prev;
};

struct Connection
{
	int a;
	int b;
	float cost;
};

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
			n.cost = 0;
			n.name = name1;
			n.prev = -1;
			nodeIndex++;
		}

		if (index2 < 0)
		{
			Node& n = (*nodes)[nodeIndex];

			index2 = nodeIndex;
			n.cost = 0;
			n.name = name2;
			n.prev = -1;
			nodeIndex++;
		}

		Connection& c = (*connections)[i];
		c.a = index1;
		c.b = index2;
		c.cost = cost;
	}

	return true;
}

Connection* FindConnection(int a, int b, Connection* connections, int connectionCount)
{
	for (size_t i = 0; i < connectionCount; i++)
	{
		if ((connections[i].a == a && connections[i].b == b) || (connections[i].b == a && connections[i].a == b))
		{
			return connections + i;
		}
	}
	return nullptr;
}

Connection* FindConnections(int a, Connection* connections, int connectionCount)
{
	for (size_t i = 0; i < connectionCount; i++)
	{
		if (connections[i].a == a || connections[i].b == a)
		{
			return connections + i;
		}
	}
	return nullptr;
}

enum PathSearchType
{
	BreadthFirst,
	DepthFirst
};


template<enum PathSearchType type>
void CreatePath(int a, int b, Node* nodes, int nodeCount, Connection* connections, int connectionCount);

template<>
void CreatePath<DepthFirst>(int a, int b, Node* nodes, int nodeCount, Connection* connections, int connectionCount)
{
	bool found = false;
	stack<int> s;
	s.push(a);
	nodes[a].prev = a;
	while (s.size())
	{
		int node = s.top();
		s.pop();

		for (size_t i = 0; i < connectionCount; i++)
		{
			int otherNode = -1;
			if (connections[i].a == node)
			{
				otherNode = connections[i].b;
			}
			else if (connections[i].b == node)
			{
				otherNode = connections[i].a;
			}

			if (otherNode < 0)
				continue;

			if (nodes[otherNode].prev == -1)
			{
				nodes[otherNode].prev = node;
				nodes[otherNode].cost = connections[i].cost;

				if (otherNode == b)
				{
					return; // path found
				}
				s.push(otherNode);
			}
		}
	}
}

template<>
void CreatePath<BreadthFirst>(int a, int b, Node* nodes, int nodeCount, Connection* connections, int connectionCount)
{
	bool found = false;
	queue<int> s;
	s.push(a);
	nodes[a].prev = a;
	while (s.size())
	{
		int node = s.front();
		s.pop();

		for (size_t i = 0; i < connectionCount; i++)
		{
			int otherNode = -1;
			if (connections[i].a == node)
			{
				otherNode = connections[i].b;
			}
			else if (connections[i].b == node)
			{
				otherNode = connections[i].a;
			}

			if (otherNode < 0)
				continue;

			if (nodes[otherNode].prev == -1)
			{
				nodes[otherNode].prev = node;
				nodes[otherNode].cost = connections[i].cost;

				if (otherNode == b)
				{
					return; // path found
				}
				s.push(otherNode);
			}
		}
	}
}

void PrintCreatedPath(int a, int b, Node* nodes, int nodeCount, Connection* connections, int connectionCount)
{
	stack<int> result;

	// backtrack and push to stack
	int prev = b;
	while (prev != a) // while prev is valid
	{
		result.push(prev);
		prev = nodes[prev].prev;
		if (prev == -1)
		{
			cout << "No path found!" << endl;
			return;
		}
	}
	result.push(a);

	// print names from node indices on stack
	if (result.size() > 1)
	{
		float cost = nodes[result.top()].cost;
		cout << nodes[result.top()].name;
		result.pop();

		while (result.size())
		{
			cost += nodes[result.top()].cost;
			cout << " --> " << nodes[result.top()].name;
			result.pop();
		}
		cout << endl << "Cost: " << cost;
	}
	else
	{
		cout << "path not found";
	}
	cout << endl;
}

void ResetPath(Node* nodes, int nodeCount)
{
	for (size_t i = 0; i < nodeCount; i++)
	{
		nodes[i].cost = 0;
		nodes[i].prev = -1;
	}
}

#define MEASURETIME(x, time) { auto start = std::chrono::system_clock::now(); x; auto end=std::chrono::system_clock::now(); time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0; }


int main()
{
	int nodeCount = 0;
	Node* nodes = nullptr;
	int connectionCount = 0;
	Connection* connections = nullptr;
	bool running = true;

	while (running)
	{
		cout << R"(
Iskanje v globino in sirino - izbira:
1) Preberi graf iz datoteke
2) Pozeni iskanje v globino iz vozlisca s do d
3) Pozeni iskanje v sirino iz vozlisca s do d
4) Konec
Izbira: )";
		int choice;
		cin >> choice;

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
			case 3:
			{
				if (nodeCount == 0)
				{
					cout << "No nodes to find path between!" << endl;
					break;
				}

				cout << "Enter starting node name: ";
				string startName = "1";
				cin >> startName;
				cout << "Enter destination node name: ";
				string endName = "2000";
				cin >> endName;
				int sIndex = GetIndexByName(nodes, nodeCount, startName);
				int eIndex = GetIndexByName(nodes, nodeCount, endName);
				if (sIndex < 0 || eIndex < 0)
				{
					cout << "starting node or destination node does not exist" << endl;
					break;
				}

				double time;
				switch (choice)
				{
					case 2:
						MEASURETIME(CreatePath<DepthFirst>(sIndex, eIndex, nodes, nodeCount, connections, connectionCount), time);
						break;

					case 3:
						MEASURETIME(CreatePath<BreadthFirst>(sIndex, eIndex, nodes, nodeCount, connections, connectionCount), time);
						break;

				}

				PrintCreatedPath(sIndex, eIndex, nodes, nodeCount, connections, connectionCount);
				ResetPath(nodes, nodeCount);

				cout << "Time: " << time << " ms" << endl;
				break;
			}

			case 4:
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