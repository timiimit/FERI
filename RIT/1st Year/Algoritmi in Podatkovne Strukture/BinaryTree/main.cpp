#include <sstream>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

#pragma region Queue.h

namespace timiimit
{
	namespace GenericStructures
	{
		template <class T, class IndexType = size_t>
		class Queue
		{
		private:
#ifdef _DEBUG
			IndexType maxSize;
#endif
			IndexType startIndex;
			IndexType size;
			IndexType capacity;
			T* data;

			void resize(IndexType newSize);

		public:
			Queue(IndexType capacity);
			Queue();
			~Queue();

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
		inline void Queue<T, IndexType>::resize(IndexType newCapacity)
		{
			T* larger = new T[newCapacity];
			std::memcpy(larger, data + startIndex, (capacity - startIndex) * sizeof(T));
			std::memcpy(larger, data, startIndex * sizeof(T));
			delete[] data;
			data = larger;
			capacity = newCapacity;
		}

		template <class T, class IndexType>
		Queue<T, IndexType>::Queue() : Queue<T, IndexType>::Queue(16)
		{
		}

		template <class T, class IndexType>
		Queue<T, IndexType>::Queue(IndexType capacity) :
			size(0),
			startIndex(0),
#ifdef _DEBUG
			maxSize(0),
#endif
			capacity(capacity),
			data(new T[capacity])
		{
		}


		template <class T, class IndexType>
		Queue<T, IndexType>::~Queue()
		{
			delete[] data;
		}

		template <class T, class IndexType>
		inline IndexType Queue<T, IndexType>::GetCurrentCapacity() const
		{
			return capacity;
		}

		template <class T, class IndexType>
		inline IndexType Queue<T, IndexType>::GetSize() const
		{
			return size;
		}

		template <class T, class IndexType>
		inline void Queue<T, IndexType>::Push(const T& p)
		{
			if (size >= capacity)
			{
				resize(size + 16);
			}
			IndexType pushIndex = startIndex + size;
			if (pushIndex >= capacity)
			{
				pushIndex -= capacity;
			}
			data[pushIndex] = p;
			size++;

#ifdef _DEBUG
			if (size > maxSize)
				maxSize = size;
#endif
		}

		template <class T, class IndexType>
		inline T& Queue<T, IndexType>::Top() const
		{
			if (size <= 0)
				throw std::exception("can't call Top() upon an empty queue");
			return data[startIndex];
		}

		template <class T, class IndexType>
		inline T& Queue<T, IndexType>::Pop()
		{
			if (size <= 0)
				throw std::exception("can't call Pop() upon an empty queue");
			size--;
			T& tmp = data[startIndex++];
			if (startIndex >= capacity)
				startIndex -= capacity;
			return tmp;
		}

		template <class T, class IndexType>
		inline T& Queue<T, IndexType>::operator[](IndexType index) const
		{
			if (index >= size || index < 0)
				throw std::exception("index out of range");

			if (startIndex + index > capacity)
			{
				index -= capacity;
			}
			return data[index + startIndex];
		}
	}
}

#pragma endregion 

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

#pragma region BinaryTree.h

template<class T>
class BinaryTree
{
public:
	class Node;

private:
	Node * root;

public:

	BinaryTree() :
		root(nullptr)
	{

	}

	~BinaryTree()
	{
		delete root;
	}

	const Node* GetRoot() const;

	int GetDepth();
	void Insert(T& userdata);
	void Remove(T& userdata);
	Node* Find(T& userdata);

	T Min();
	T Max();

};

template<class T>
class BinaryTree<T>::Node
{
public:
	Node * parent;
	Node* left;
	Node* right;

	T userdata;


	Node() :
		parent(nullptr),
		left(nullptr),
		right(nullptr),
		userdata()
	{

	}

	Node(T data) :
		parent(nullptr),
		left(nullptr),
		right(nullptr),
		userdata(data)
	{

	}

	Node(T data, Node* parent) :
		parent(parent),
		left(nullptr),
		right(nullptr),
		userdata(data)
	{

	}

	~Node()
	{
		if (left)
			delete left;
		if (right)
			delete right;

		left = nullptr;
		right = nullptr;
	}

	bool IsLeaf() const
	{
		return !left && !right;
	}

	bool IsRoot() const
	{
		return !parent;
	}

	const Node* NextSibling() const;
	const Node* PrevSibling() const;
	const Node* Min() const;
	const Node* Max() const;
};


template<class T>
typename const BinaryTree<T>::Node* BinaryTree<T>::GetRoot() const
{
	return root;
}

template<class T>
int BinaryTree<T>::GetDepth()
{
	struct A
	{
		Node* node;
		int depth;

		A() :
			node(nullptr),
			depth(-1)
		{
		}

		A(Node* n, int d) :
			node(n),
			depth(d)
		{}
	};
	int depth = 0;
	Stack<A> s;
	s.Push(A(root, 0));
	while (s.GetSize())
	{
		A node = s.Pop();

		if (node.depth > depth)
			depth = node.depth;

		if (node.node->left)
			s.Push(A(node.node->left, node.depth + 1));
		if (node.node->right)
			s.Push(A(node.node->right, node.depth + 1));
	}
	return depth;
}

template<class T>
inline void BinaryTree<T>::Insert(T& userdata)
{
	Node* tmp = root;
	if (!tmp)
	{
		root = new BinaryTree<T>::Node(userdata);
		return;
	}
	while (true)
	{
		if (userdata < tmp->userdata)
		{
			if (!tmp->left)
				break;
			tmp = tmp->left;
		}
		else if (userdata > tmp->userdata)
		{
			if (!tmp->right)
				break;
			tmp = tmp->right;
		}
		else
		{
			// update userdata contents
			// prev->userdata = userdata;
			tmp->userdata.titles.push_back(userdata.titles[0]);
			return;
		}
	}

	if (userdata < tmp->userdata)
	{
		tmp->left = new Node(userdata, tmp);
	}
	else
	{
		tmp->right = new Node(userdata, tmp);
	}
}

template<class T>
inline void BinaryTree<T>::Remove(T& userdata)
{
	Node* tmp = Find(userdata);

	if (!tmp)
		return;


	Node* parent = tmp->parent;
	if (tmp->IsLeaf())
	{
		if (parent->left == tmp)
			parent->left = nullptr;
		else
			parent->right = nullptr;
	}
	else if (tmp->left && tmp->right)
	{
		if (parent->left == tmp)
		{
			parent->left = tmp->right;
			auto rMin = (typename BinaryTree<T>::Node*)tmp->right->Min();
			rMin->left = tmp->left;
		}
		else // if (parent->right == tmp)
		{
			parent->right = tmp->right;
			auto rMin = (typename BinaryTree<T>::Node*)tmp->right->Min();
			rMin->left = tmp->left;
		}
	}
	else if (tmp->right)
	{
		if (parent->right == tmp)
			parent->right = tmp->right;
		else
			parent->left = tmp->right;
	}
	else // if has only left child
	{
		if (parent->left == tmp)
			parent->left = tmp->left;
		else
			parent->right = tmp->left;
	}
	delete tmp;
}

template<class T>
typename inline BinaryTree<T>::Node* BinaryTree<T>::Find(T& userdata)
{
	Node* node = root;
	while (node)
	{
		if (userdata < node->userdata)
			node = node->left;
		else if (userdata > node->userdata)
			node = node->right;
		else
			return node;
	}
	return nullptr;
}

template<class T>
inline T BinaryTree<T>::Min()
{
	return root->Min()->userdata;
}

template<class T>
inline T BinaryTree<T>::Max()
{
	return root->Max()->userdata;
}

template<class T>
typename inline const BinaryTree<T>::Node* BinaryTree<T>::Node::NextSibling() const
{
	const Node* node = this;
	if (node->right)
	{
		return node->right->Min();
	}

	const Node* prev = node->parent;
	while (prev && node == prev->right)
	{
		node = prev;
		prev = prev->parent;
	}
	return prev;
}

template<class T>
typename inline const BinaryTree<T>::Node* BinaryTree<T>::Node::PrevSibling() const
{
	const Node* node = this;
	if (node->left)
	{
		return node->left->Max();
	}

	const Node* prev = node->parent;
	while (prev && node == prev->left)
	{
		node = prev;
		prev = prev->parent;
	}
	return prev;
}

template<class T>
typename const BinaryTree<T>::Node* BinaryTree<T>::Node::Min() const
{
	const Node* node = this;
	while (node->left)
	{
		node = node->left;
	}
	return node;
}

template<class T>
typename const BinaryTree<T>::Node* BinaryTree<T>::Node::Max() const
{
	const Node* node = this;
	while (node->right)
	{
		node = node->right;
	}
	return node;
}


#pragma endregion

using namespace std;

class Movie
{
public:
	int releasedate;
	vector<string> titles;

	Movie() : Movie(0, vector<string>()) {}

	Movie(int releasedate, string title) : Movie(releasedate, vector<string>())
	{
		titles.push_back(title);
	}
	Movie(int releasedate, vector<string> titles) :
		//relasedate(releasedate),
		titles(titles)
	{
		this->releasedate = releasedate;
	}

	bool operator<(const Movie& m) const
	{
		return releasedate < m.releasedate;
	}

	bool operator>(const Movie& m) const
	{
		return releasedate > m.releasedate;
	}

	bool operator==(const Movie& m) const
	{
		return releasedate == m.releasedate;
	}

	bool operator<=(const Movie& m) const
	{
		return releasedate <= m.releasedate;
	}

	bool operator>=(const Movie& m) const
	{
		return releasedate >= m.releasedate;
	}

	string ToString() const
	{
		stringstream ss;
		ss << releasedate << endl;
		for (int i = 0; i < titles.size(); i++)
		{
			ss << '\t' << titles[i] << endl;
		}
		return ss.str();
	}
};


int GetDigitCount(int x)
{
	int digits = 0;
	if (x < 0)
	{
		digits++;
		x = -x;
	}
	if (x > 0)
	{
		while (x > 0)
		{
			digits++;
			x /= 10;
		}
	}
	else
	{
		digits = 1;
	}
	return digits;
}

void PrintTree(BinaryTree<Movie>& tree)
{
	auto node = tree.GetRoot();

	Stack<const BinaryTree<Movie>::Node*> s;
	s.Push(node);
	while (s.GetSize())
	{
		node = s.Pop();



		if (node->left)
		{
			s.Push(node->left);
			cout << node->userdata.releasedate << " -> " << node->left->userdata.releasedate << endl;
		}
		if (node->right)
		{
			s.Push(node->right);
			cout << node->userdata.releasedate << " -> " << node->right->userdata.releasedate << endl;
		}
	}

	/*int maxDepth = tree.GetDepth();

	struct A
	{
		typename BinaryTree<Movie>::Node* node;
		int depth;

		A() :
			node(nullptr),
			depth(-1)
		{
		}

		A(typename BinaryTree<Movie>::Node* n, int d) :
			node(n),
			depth(d)
		{}
	};

	Movie max(tree.Max());
	int maxdigits = GetDigitCount(max.releasedate);


	Queue<A> s;
	A a((typename BinaryTree<Movie>::Node*)tree.GetRoot(), 0);
	s.Push(a);
	for (int depth = 0; depth <= maxDepth; depth++)
	{
		int sizePerNode = (int)pow(2, maxDepth + 1 - depth) - 1 + maxdigits;
		size_t loopCount = s.GetSize();
		for (int ni = 0; ni < loopCount; ni++)
		{
			A node = s.Pop();

			if (node.node)
			{
				int digits = GetDigitCount(node.node->userdata.releasedate);

				cout << node.node->userdata.releasedate;
				for (int i = 0; i < sizePerNode - digits - 1; i++)
				{
					cout << '-';
				}
				cout << '+';

				for (int i = 0; i < sizePerNode; i++)
				{
					cout << ' ';
				}
			}
			else
			{
				for (int i = 0; i < sizePerNode; i++)
				{
					cout << ' ';
				}
				for (int i = 0; i < sizePerNode; i++)
				{
					cout << ' ';
				}
			}

			if (node.node && node.node->left)
				s.Push(A(node.node->left, node.depth + 1));
			else
				s.Push(A(nullptr, node.depth + 1));

			if (node.node && node.node->right)
				s.Push(A(node.node->right, node.depth + 1));
			else
				s.Push(A(nullptr, node.depth + 1));
		}

		cout << endl;

	}*/
}

void PrintSorted(BinaryTree<Movie>& tree)
{
	const BinaryTree<Movie>::Node* node = tree.GetRoot();
	while (node->left)
		node = node->left;

	while (node)
	{
		cout << node->userdata.ToString() << endl;
		node = node->NextSibling();
	}
	cout << endl;
}

istream& operator>>(istream& stream, Movie& movie)
{
	int date;
	stream >> date;
	string name;
	getline(stream, name, '\n');
	movie = Movie(date, name);
	return stream;
}

void ReadTree(BinaryTree<Movie>& tree, const char* filename)
{
	std::ifstream in(filename);
	int N;
	in >> N;

	cout << "Loading '" << filename << "'" << endl << '[';
	size_t progresssize = 100;
	for (size_t i = 0; i < progresssize; i++)
	{
		cout << ' ';
	}
	cout << "]\r[";
	int lastpercent = 0;
	for (int i = 0; i < N; i++)
	{
		Movie m;
		in >> m;
		tree.Insert(m);

		float percent = (float)i / N * progresssize;
		if ((int)percent > lastpercent)
		{
			lastpercent = (int)percent;
			cout << '-';
		}
	}
	cout << "-]" << endl;
}

int ReadArray(Movie*& arr, const char* filename)
{
	std::ifstream in(filename);
	int N;
	in >> N;

	arr = new Movie[N];

	cout << "Loading '" << filename << "'" << endl << '[';
	size_t progresssize = 100;
	for (size_t i = 0; i < progresssize; i++)
	{
		cout << ' ';
	}
	cout << "]\r[";
	int lastpercent = 0;
	for (int i = 0; i < N; i++)
	{
		in >> arr[i];

		float percent = (float)i / N * progresssize;
		if ((int)percent > lastpercent)
		{
			lastpercent = (int)percent;
			cout << '-';
		}
	}
	cout << "-]" << endl;
	return N;
}

void main()
{
	BinaryTree<Movie> tree;
	/*tree.Insert(11);
	tree.Insert(6);
	tree.Insert(19);
	tree.Insert(4);
	tree.Insert(5);
	tree.Insert(8);
	tree.Insert(10);
	tree.Insert(17);
	tree.Insert(43);
	tree.Insert(31);
	tree.Insert(49);*/

	//PrintTree(tree);
	const char* filename = "IMDB_date_name_mini_sorted.list";


	while (true)
	{
		cout <<
			R"(Binarno iskalno drevo – izbira:

1) Vnos podatka
2) Urejen izpis vrednosti
3) Izpis povezav
4) Iskanje
5) Poisci minimum in maksimum
6) Poisci predhodnika in naslednika
7) Brisi vrednost
8) Nalaganje filmov iz datoteke
9) Testiraj hitrost
10) Konec

Izbira: )";

		int option;
		cin >> option;

		switch (option)
		{
			case 1:
			{
				Movie m;
				cin >> m;
				tree.Insert(m);
				break;
			}

			case 2:
				PrintSorted(tree);
				break;

			case 3:
				PrintTree(tree);
				break;

			case 4:
			{
				Movie m;
				cin >> m;
				typename const BinaryTree<Movie>::Node* found = tree.Find(m);
				if (found)
				{
					cout << "found " << found->userdata.titles.size() << " movies released on this date:" << endl;
					for (size_t i = 0; i < found->userdata.titles.size(); i++)
					{
						cout << '\t' << found->userdata.titles[i] << endl;
					}
				}
				else
					cout << "no such movie." << endl;
				break;
			}

			case 5:
			{
				Movie min = tree.Min();
				Movie max = tree.Max();
				cout << "min: " << min.ToString() << endl;
				cout << "max: " << max.ToString() << endl;
				break;
			}

			case 6:
			{
				Movie m;
				cin >> m;
				typename const BinaryTree<Movie>::Node* a = tree.Find(m);
				if (!a)
				{
					cout << "no such movie." << endl;
					break;
				}

				typename const BinaryTree<Movie>::Node* next = a->NextSibling();
				a = a->PrevSibling();

				cout << "previous sibling: " << (a ? a->userdata.ToString() : "nullptr") << endl;
				cout << "next sibling: " << (next ? next->userdata.ToString() : "nullptr") << endl;
				break;
			}

			case 7:
			{
				Movie m;
				cin >> m;
				tree.Remove(m);
				break;
			}

			case 8:
			{
				ReadTree(tree, filename);

				break;
			}

			case 9:
			{
				DWORD start;
				DWORD end;
				{
					start = GetTickCount();
					BinaryTree<Movie> mini;
					ReadTree(mini, "IMDB_date_name_mini.list");
					end = GetTickCount();
					cout << "mini: " << (end - start) << "ms" << endl;
				}
				{
					start = GetTickCount();
					BinaryTree<Movie> minisorted;
					ReadTree(minisorted, "IMDB_date_name_mini_sorted.list");
					end = GetTickCount();
					cout << "minisorted: " << (end - start) << "ms" << endl;
				}
				{
					start = GetTickCount();
					BinaryTree<Movie> full;
					ReadTree(full, "IMDB_date_name_full.list");
					end = GetTickCount();
					cout << "full: " << (end - start) << "ms" << endl;
				}
				{
					start = GetTickCount();
					BinaryTree<Movie> fullsorted;
					ReadTree(fullsorted, "IMDB_date_name_full_sorted.list");
					end = GetTickCount();
					cout << "fullsorted: " << (end - start) << "ms" << endl;
				}
				break;

			}

			case 10:
				return;

			case 11:
			{
				// test access time

				Movie* movies;
				cout << "reading file into array..." << endl;
				int size = ReadArray(movies, filename);
				int repeatcount = 10;

				DWORD start = GetTickCount();
				for (size_t j = 0; j < repeatcount; j++)
				{
					for (size_t i = 0; i < size; i++)
					{
						tree.Find(movies[i]);
					}
				}
				DWORD end = GetTickCount();
				cout << "finding all " << (size * repeatcount) << " items took " << (end - start) << "ms" << endl;

				delete[] movies;

				break;
			}
		}
	}

}