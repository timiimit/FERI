#include <Windows.h>
#include <iostream>

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
using namespace std;

int findIndex(DLList<int>& list, int value)
{
	if (list.GetSize() == 0)
		return -1;

	DLList<int>::Node<int>* var = &list.GetFirst();
	int index = 0;
	while (var->userdata != value)
	{
		var = var->next;
		index++;

		if (!var)
			return -1;
	}
	return index;
}

void main()
{
	DLList<int> test;

	while (true)
	{
		cout << endl << endl <<
			"Dvojno povezan seznam - izbira:" << endl <<
			"1) Iskanje podatka" << endl <<
			"2) Vnos podatka v glavo" << endl <<
			"3) Vnos podatka za elementom" << endl <<
			"4) Vnos podatka za repom" << endl <<
			"5) Brisanje podatka" << endl <<
			"6) Izpis seznama od glave proti repu" << endl <<
			"7) Izpis seznama od repa proti glavi" << endl <<
			"8) Testiraj hitrost" << endl <<
			"9) Konec" << endl << endl <<
			"Izbira: ";

		int option;
		cin >> option;
		system("cls");

		switch (option)
		{
			case 1:
			{
				cout << "what to find?";
				int num;
				cin >> num;
				int index = findIndex(test, num);
				if (index >= 0)
					cout << num << " is located at index " << index << endl;
				else
					cout << num << " is not in the list" << endl;
				break;
			}

			case 2:
			{
				cout << "what to insert?";
				int num;
				cin >> num;
				test.Insert(num, 0);
				break;
			}

			case 3:
			{
				cout << "what to insert?";
				int num;
				cin >> num;
				cout << "after what to insert?";
				int key;
				cin >> key;
				int index = findIndex(test, key);
				if (index >= 0)
				{
					test.Insert(num, index + 1);
				}
				else
				{
					cout << key << " is not in the list" << endl << "insertion failed" << endl;
				}
				break;
			}

			case 4:
			{
				cout << "what to insert?";
				int num;
				cin >> num;
				test.Add(num);
				break;
			}

			case 5:
			{
				cout << "delete 1st occurance of: ";
				int key;
				cin >> key;
				int index = findIndex(test, key);
				if (index >= 0)
				{
					test.Remove(index);
					cout << "deleted element " << key << " at index " << index << endl;
				}
				else
				{
					cout << key << " is not in the list" << endl << "deletion failed" << endl;
				}
				break;
			}

			case 6:
			{
				auto var = &test.GetFirst();
				while (var)
				{
					cout << var->userdata << " ";
					var = var->next;
				}
				break;
			}

			case 7:
			{
				auto var = &test.GetLast();
				if (var)
				{
					while (var)
					{
						cout << var->userdata << " ";
						var = var->previous;
					}
				}
				break;
			}

			case 8:
			{
				cout << "stevilo elementnov: ";
				int count;
				cin >> count;

				DLList<int> list;
				cout << "Testing: DLList" << endl;
				cout << "inserting..." << endl;
				DWORD start = GetTickCount();
				for (DWORD i = 0; i < count; i++)
				{
					list.Insert(i + 1, 0);
				}
				DWORD end = GetTickCount();
				cout << "insertion took " << (end - start) << "ms" << endl;
				cout << "adding all values..." << endl;
				start = GetTickCount();
				auto node = &list.GetFirst();
				ULONGLONG sum = 0;
				while (node)
				{
					sum += node->userdata;
					node = node->next;
				}
				end = GetTickCount();
				cout << "sum of all inserted values is " << sum << " and it took " << (end - start) << "ms" << endl;
				cout << endl;

				cout << "Testing: Array" << endl;
				int* arr = new int[count];
				cout << "insetring..." << endl;
				start = GetTickCount();
				for (DWORD i = 0; i < count; ++i)
				{
					memmove(arr + 1, arr, i * sizeof(*arr));
					arr[0] = i + 1;
				}
				end = GetTickCount();
				cout << "insertion took " << (end - start) << "ms" << endl;

				cout << "adding all values..." << endl;
				start = GetTickCount();
				sum = 0;
				for (DWORD i = 0; i < count; ++i)
				{
					sum += arr[i];
				}
				end = GetTickCount();
				cout << "sum of all inserted values is " << sum << " and it took " << (end - start) << "ms" << endl;

				delete[] arr;
				arr = new int[count];

				cout << "inserting at back..." << endl;
				start = GetTickCount();
				for (DWORD i = 0; i < count; i++)
				{
					arr[i] = i;
				}
				end = GetTickCount();
				cout << "insertion at back took " << (end - start) << "ms" << endl;
				break;
			}

			case 9:
				return;

			default:
				cout << "napacna izbira" << endl;
				break;
		}
	}
}