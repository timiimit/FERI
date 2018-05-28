#include <iostream>
#include <Windows.h>
#include <chrono>
//#include <iomanip> // if i include this, it breaks the compiler

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

#pragma region DLList

namespace timiimit
{
	namespace GenericStructures
	{


		template<class T>
		class DLList
		{
		public:

			template<class T>
			struct Node
			{
			public:
				Node * next;
				Node* previous;
				T userdata;

				Node() :
					next(nullptr),
					previous(nullptr),
					userdata(nullptr)
				{

				}

				Node(const T& userdata) :
					next(nullptr),
					previous(nullptr),
					userdata(userdata)
				{

				}
			};

		private:
			Node<T>* first;
			Node<T>* last;
			size_t size;

		public:

			DLList();
			~DLList();

			void Add(const T& element);
			void Insert(const T& element, size_t index);
			void Remove(size_t index);
			Node<T>& GetFirst() const;
			Node<T>& GetLast() const;
			T& operator[](size_t index) const;
			size_t GetSize() const;
		};

		///////////////////////////////////////////
		//			  IMPLEMENTATION			 //
		///////////////////////////////////////////

		template<class T>
		inline DLList<T>::DLList() :
			first(nullptr),
			size(0u)
		{

		}

		template<class T>
		inline DLList<T>::~DLList()
		{
			DLList<T>::Node<T>* n = first;
			while (n)
			{
				DLList<T>::Node<T>* next = n->next;
				delete n;
				n = next;
			}
			first = nullptr;
			size = 0;
		}

		template<class T>
		inline void DLList<T>::Add(const T& element)
		{
			if (first == nullptr)
			{
				first = new DLList<T>::Node<T>(element);
				last = first;
			}
			else
			{
				DLList<T>::Node<T>* n = last;
				n->next = new DLList<T>::Node<T>(element);
				last = n->next;
				n->next->previous = n;
			}
			size++;
		}

		template<class T>
		inline void DLList<T>::Insert(const T& element, size_t index)
		{
			if (index > size)
				throw exception("index was out of range");
			else if (index == size)
			{
				Add(element);
				return;
			}

			DLList<T>::Node<T>* n = first;
			size_t targetIndex = index - 1;
			if (index == 0)
			{
				first = new DLList<T>::Node<T>(element);
				first->next = n;
				n->previous = first;
			}
			else
			{
				size_t current = 0;
				while (current < targetIndex)
				{
					n = n->next;
					current++;
				}

				DLList<T>::Node<T>* nodenew = new DLList<T>::Node<T>(element);
				DLList<T>::Node<T>* afternew = n->next;
				n->next = nodenew;
				n->next->previous = n;
				nodenew->next = afternew;
				afternew->previous = nodenew;
			}
			size++;
		}

		template<class T>
		inline void DLList<T>::Remove(size_t index)
		{
			if (index >= size)
				throw exception("index was out of range");

			if (index == 0)
			{
				DLList<T>::Node<T>* firstnew = first->next;
				delete first;
				first = firstnew;
				if (first)
					first->previous = nullptr;
			}
			else
			{
				DLList<T>::Node<T>* n = first;
				size_t targetIndex = index - 1;
				size_t current = 0;
				while (current < targetIndex)
				{
					n = n->next;
					current++;
				}

				DLList<T>::Node<T>* nextnew = n->next->next;
				delete n->next;
				n->next = nextnew;
				if (nextnew)
					nextnew->previous = n;
			}
			size--;
		}

		template<class T>
		inline DLList<T>::Node<T>& DLList<T>::GetFirst() const
		{
			return *first;
		}

		template<class T>
		inline DLList<T>::Node<T>& DLList<T>::GetLast() const
		{
			return *last;
		}

		template<class T>
		inline T& DLList<T>::operator[](size_t index) const
		{
			if (index >= size)
				throw exception("index was out of range");

			DLList<T>::Node<T>* n = first;
			size_t current = 0;
			while (current < index)
			{
				n = n->next;
				current++;
			}

			return n->userdata;
		}

		template<class T>
		inline size_t DLList<T>::GetSize() const
		{
			return size;
		}
	}
}

#pragma endregion

using namespace timiimit::GenericStructures;

struct Node
{
public:
	DLList<int>::Node<int>* left;
	DLList<int>::Node<int>* right;

	Node() : left(nullptr), right(nullptr) {}
	Node(DLList<int>::Node<int>* l, DLList<int>::Node<int>* r) : left(l), right(r) {}
};

DLList<int>::Node<int>* Deli(DLList<int>::Node<int>* left, DLList<int>::Node<int>* right)
{
	auto pe = left->userdata;
	auto l = left;
	auto r = right;

	bool stop = false;
	while (!stop)
	{
		while (l->userdata <= pe && l != right)
		{
			l = l->next;
			if (r == l)
				stop = true;
		}
		while (r->userdata >= pe && r != left)
		{
			r = r->previous;
			if (l == r)
				stop = true;
		}

		if (!stop)
			swap(l->userdata, r->userdata);
	}

	swap(left->userdata, r->userdata);
	return r;
}

void Uredi(DLList<int>::Node<int>* left, DLList<int>::Node<int>* right)
{
	if (left != right)
	{
		DLList<int>::Node<int>* j = Deli(left, right);

		if (left != j)
			Uredi(left, j->previous);
		if (right != j)
			Uredi(j->next, right);
	}
}

void quicksort(DLList<int>& list)
{
	Stack<Node> s;
	Node a = Node(&list.GetFirst(), &list.GetLast());
	s.Push(a);
	while (s.GetSize())
	{
		Node n = s.Pop();
		auto* pivot = n.left;
		auto* l = n.left;
		auto* r = n.right;
		if (l->userdata >= r->userdata)
			continue;
		while (l->userdata < r->userdata)
		{
			while (l->userdata <= pivot->userdata && l->userdata < n.right->userdata && l->next)
				l = l->next;
			while (r->userdata >= pivot->userdata && r->userdata > n.left->userdata && r->previous)
				r = r->previous;

			if (l->userdata < r->userdata)
				swap(l->userdata, r->userdata);
		}
		swap(n.left->userdata, r->userdata);

		if (n.left->userdata < n.right->userdata)
		{
			s.Push(Node(n.left, r->previous));
			s.Push(Node(r->next, n.right));
			l = n.left;
			r = r->previous;
		}
	}
}

void GenerateRandomArray(DLList<int>& list, int size)
{
	for (int i = 0; i < size; i++)
	{
		list.Add(rand());
	}
}


void GenerateRandomArrayAscending(DLList<int>& list, int size)
{
	for (int i = 0; i < size; i++)
	{
		list.Add(rand());
	}
	Uredi(&list.GetFirst(), &list.GetLast());;
}


#define MEASURETIME(x, time) { auto start = std::chrono::system_clock::now(); x; auto end=std::chrono::system_clock::now(); time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0; }

int main()
{
	DLList<int> list;
	bool running = true;

	while (running)
	{
		cout << R"(Hitro uredi dvojno-povezan seznam - izbira:
1 Generiraj nakljucno zaporedje
2 Generiraj narascajoce zaporedje
3 Izpis zaporedja
4 Preveri urejenost zaporedja
5 Izpiši vsoto elementov
6 Uredi
7 Konec
Vaša izbira: )" << endl << endl;

		int choice;
		cin >> choice;

		switch (choice)
		{
			case 1:
			case 2:
			{
				cout << "Velikost: ";
				list = DLList<int>();
				int size;
				cin >> size;

				switch (choice)
				{
					case 1:
						GenerateRandomArray(list, size);
						break;

					case 2:
						GenerateRandomArrayAscending(list, size);
						break;
				}
			}
			break;

			case 3:
			{
				auto tmp = &list.GetFirst();
				while (tmp)
				{
					cout << tmp->userdata << "\n";
					tmp = tmp->next;
				}
				cout << endl;
				break;
			}

			case 4:
			{
				auto tmp = list.GetFirst().next;
				int i = 1;
				while (tmp)
				{
					if (tmp->previous->userdata > tmp->userdata)
					{
						cout << "Not ascending at index " << i << endl;
						break;
					}
					i++;
				}
			}
			break;

			case 5:
			{
				cout << "Sum of everything: ";
				ULONG sum = 0;
				auto tmp = &list.GetFirst();
				while (tmp)
				{
					sum += tmp->userdata;
					tmp = tmp->next;
				}
				cout << sum << endl;
			}
			break;

			case 6:
				Uredi(&list.GetFirst(), &list.GetLast());
				break;

			case 7:
				running = false;
				break;

		}

	}
	return 0;
}