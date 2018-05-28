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

using namespace timiimit::GenericStructures;

template<class T>
void bubblesort(T* arr, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (arr[i] < arr[j])
			{
				swap(arr[i], arr[j]);
			}
		}
	}
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

void GenerateRandomArray(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand();
	}
}


void GenerateRandomArrayAscending(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = arr[i - 1] + (rand() % 100);
	}
}

void GenerateRandomArrayDecending(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = arr[i - 1] - (rand() % 100);
	}
}


#define MEASURETIME(x, time) { auto start = std::chrono::system_clock::now(); x; auto end=std::chrono::system_clock::now(); time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0; }

int main()
{
	int* arr = nullptr;
	int size = 0;
	bool running = true;

	while (running)
	{
		cout << R"(Hitro uredi - izbira:
1) Generiraj nakljucno zaporedje
2) Generiraj narascajoce zaporedje
3) Generiraj padajoce zaporedje
4) Izpis zaporedja
5) Preveri ali je zaporedje urejeno
6) Uredi s hitrim urejanjem brez mediane
7) Uredi s hitrim urejanjem z mediano
8) Uredi z drugim algoritmom za urejanjem
9) Konec
Izbira: )" << endl << endl;

		int choice;
		cin >> choice;

		switch (choice)
		{
			case 1:
			case 2:
			case 3:
			{
				cout << "Velikost: ";
				if (arr)
					delete[] arr;
				cin >> size;
				//size = 3;
				arr = new int[size];

				switch (choice)
				{
					case 1:
						GenerateRandomArray(arr, size);
						break;

					case 2:
						GenerateRandomArrayAscending(arr, size);
						break;

					case 3:
						GenerateRandomArrayDecending(arr, size);
						break;
				}
			}
			break;

			case 4:
				for (int i = 0; i < size; i++)
				{
					cout << arr[i] << ' ';
				}
				cout << endl;
				break;

			case 5:
			{
				for (int i = 1; i < size; i++)
				{
					if (arr[i - 1] > arr[i])
					{
						cout << "Not ascending at index " << i << endl;
						break;
					}
				}
			}
			break;

			case 6:
			case 7:
			case 8:
			{
				DWORD start = GetTickCount();
				switch (choice)
				{
					case 6:
						quicksort(arr, arr + size - 1);
						break;

					case 7:
						quicksort_median(arr, arr + size - 1);
						break;

					case 8:
						bubblesort(arr, size);
						break;
				}
				DWORD end = GetTickCount();

				cout << "Sorting took " << (end - start) << "ms" << endl;

			}
			break;

			case 9:
				running = false;
				break;

			case 10:
			{
				cout << "Starting size: ";
				cin >> size;

				cout << "Step size: ";
				int step;
				cin >> step;

				cout << "Step count: ";
				int count;
				cin >> count;

				cout << "Average over how many attempts: ";
				int repeat;
				cin >> repeat;

				cout << "QuickSort, QuickSort + middle, BubbleSort: " << endl;

				for (int i = 0; i < count; i++)
				{
					if (arr)
						delete[] arr;

					arr = new int[size];
					int* tmp = new int[size];

					for (size_t k = 0; k < 3; k++)
					{
						switch (k)
						{
							case 0:
								GenerateRandomArray(arr, size);
								cout << "RANDOM ARRAY" << endl;
								break;

							case 1:
								GenerateRandomArrayAscending(arr, size);
								cout << "RANDOM ASCENDING ARRAY" << endl;
								break;

							case 2:
								GenerateRandomArrayDecending(arr, size);
								cout << "RANDOM DECENDING ARRAY" << endl;
								break;
						}


						double avg_qs = 0;
						double avg_qsm = 0;
						double avg_bs = 0;

						cout << "array size: " << size << endl;
						cout << "QuickSort\tQuickSort+M\tBubbleSort" << endl;
						for (int j = 0; j < repeat; j++)
						{
							memcpy(tmp, arr, sizeof(*tmp) * size);
							double timespan;
							MEASURETIME(quicksort(tmp, tmp + size - 1), timespan);
							avg_qs += timespan;

							//cout << timespan << "ms\t\t";

							memcpy(tmp, arr, sizeof(*tmp) * size);
							MEASURETIME(quicksort_median(tmp, tmp + size - 1), timespan);;
							avg_qsm += timespan;

							//cout << timespan << "ms\t\t";

							memcpy(tmp, arr, sizeof(*tmp) * size);
							MEASURETIME(bubblesort(tmp, size), timespan);
							avg_bs += timespan;

							//cout << timespan << "ms" << endl;
						}

						cout << "AVERAGE" << endl;
						double avg = avg_qs / repeat;
						cout << avg << "\t\t";
						avg = avg_qsm / repeat;
						cout << avg << "\t\t";
						avg = avg_bs / repeat;
						cout << avg << endl << endl << endl;
					}

					size += step;
				}
			}
		}

	}
	if (arr)
		delete[] arr;

	return 0;
}