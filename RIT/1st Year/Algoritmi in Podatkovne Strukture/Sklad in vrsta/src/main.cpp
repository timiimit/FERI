#include <memory>
#include <string>
#include <iostream>
#include <conio.h>
//#include "Stack.h"
//#include "Queue.h"

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

#pragma region main.cpp

using namespace timiimit::GenericStructures;
using namespace std;

typedef unsigned int uint;
const uint towerCount = 3;
uint towerHeight(0);
uint towerWidth = towerHeight * 2 + 1;

template<class T, class IndexType>
void Print(Stack<T, IndexType>* s, uint selected)
{
	for (int i = towerHeight-1; i >= 0; --i)
	{
		for (uint ti = 0; ti < towerCount; ti++)
		{
			if (i < s[ti].GetSize())
			{
				if (selected == ti && s[ti].GetSize() - 1 == i)
				{
					PrintDisc(s[ti][i], '#');
				}
				else
				{
					PrintDisc(s[ti][i], '-');
				}
			}
			else
			{
				PrintDisc(0, ' ');
			}
		}
		cout << endl;
	}
}

void PrintDisc(uint val, char c)
{
	if (val == 0)
	{
		for (uint i = 0; i < towerWidth; i++)
		{
			cout << ' ';
		}
		return;
	}
	val--;
	uint actualWidth = val * 2 + 1;

	uint spaces = (towerWidth - actualWidth) / 2;
	for (uint i = 0; i < spaces; ++i)
	{
		cout << ' ';
	}

	for (uint i = 0; i < actualWidth; ++i)
	{
		cout << c;
	}
	
	for (uint i = 0; i < spaces; ++i)
	{
		cout << ' ';
	}
}

void PrintTowerNames()
{
	const char name[] = "tower ";
	for (uint i = 0; i < towerCount; ++i)
	{
		if (towerWidth < sizeof(name))
		{
			uint w = towerWidth - (2);
			for (uint j = 0; j < w / 2; j++)
			{
				cout << ' ';
			}
			cout << "t" << i + 1;
			for (uint j = 0; j < w - (w / 2); j++)
			{
				cout << ' ';
			}
		}
		else
		{
			uint w;
			if (sizeof(name) + 1 > towerWidth)
			{
				w = 1;
			}
			else
			{
				w = towerWidth - (sizeof(name) + 1);
			}
			for (uint j = 0; j < w / 2; j++)
			{
				cout << ' ';
			}
			cout << name << i + 1;
			for (uint j = 0; j < w - (w / 2); j++)
			{
				cout << ' ';
			}
		}
	}
}

int main()
{
	cout << "Choose tower height: ";
	cin >> towerHeight;

	towerWidth = towerHeight * 2 + 1;
	Stack<int> s[towerCount];

	for (uint i = 0; i < towerHeight; i++)
	{
		s[0].Push(towerHeight - i);
	}

	cout << skipws;

	int moves = 0;

	while (true)
	{
		system("cls");
		PrintTowerNames();
		cout << endl << endl;

		Print(s, -1);
		cout << endl << "select disc to move: ";
		char tomove = _getch() - '1';
		system("cls");
		if (tomove < 0 || tomove >= towerCount || s[tomove].GetSize() <= 0)
		{
			continue;
		}
		PrintTowerNames();
		cout << endl << endl;

		Print(s, tomove);
		cout << endl << "select where to place: ";
		char dest = _getch() - '1';

		cout << endl;

		if (dest < 0 || dest >= towerCount || dest == tomove)
		{
			continue;
		}


		if (s[dest].GetSize() == 0 || (s[dest].GetSize() > 0 && s[dest].Top() > s[tomove].Top()))
		{
			s[dest].Push(s[tomove].Pop());
			moves++;

			if (s[towerCount - 1].GetSize() == towerHeight)
				break;
		}
	}

	system("cls");
	cout << "you won in " << moves << " moves!" << endl;
	system("pause");
	return 0;
}

#pragma endregion