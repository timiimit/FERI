#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include "ArrayList.h"

using namespace std;
using namespace timiimit::GenericStructures;

typedef unsigned char byte;
typedef unsigned int uint;

template<class T = byte>
void RadixSortSlow(T* arr, size_t count)
{
	size_t bits = sizeof(T) * 8;
	ArrayList<T> zero = ArrayList<T>(count);
	ArrayList<T> one = ArrayList<T>(count);

	for (size_t bit = 0; bit < bits; bit++)
	{
		// put in buckets
		for (size_t i = 0; i < count; i++)
		{
			if (((arr[i] >> bit) & 1))
			{
				one.Add(arr[i]);
			}
			else
			{
				zero.Add(arr[i]);
			}
		}

		// take out of buckets;
		size_t zerosize = zero.GetSize();
		size_t onesize = one.GetSize();
		for (size_t i = 0; i < zerosize; i++)
		{
			arr[i] = zero.GetData()[i];
		}
		for (size_t i = 0; i < onesize; i++)
		{
			arr[i + zerosize] = one.GetData()[i];
		}

		zero.Clear();
		one.Clear();
	}
}

template<class T = byte>
inline void RadixSort(T* arr, size_t count)
{
	T* arrend = arr + count;
	register byte bits = sizeof(T) * 8;
	//ArrayList<T> zero = ArrayList<T>(count);
	//ArrayList<T> one = ArrayList<T>(count);
	T* zeroarr = new T[count];// zero.GetData();
	T* onearr = new T[count];// one.GetData();

	register T* iter;
	register T* zeroiter = zeroarr;
	register T* zeroiter2 = zeroiter;
	register T* oneiter = onearr;
	register T* oneiter2 = oneiter;


	for (byte bit = 0; bit < bits; bit++)
	{
		zeroiter2 = zeroiter = zeroarr;
		oneiter2 = oneiter = onearr;

		// put in buckets
		iter = arr;
		while (iter < arrend)
		{
			if (((*iter >> bit) & 1))
			{
				//one.Add(buckets[i])
				*oneiter = *iter;
				oneiter++;
			}
			else
			{
				//zero.Add(buckets[i]);
				*zeroiter = *iter;
				zeroiter++;
			}
			iter++;
		}

		iter = arr;

		// take out of buckets;
		while (zeroiter2 < zeroiter)
		{
			*iter = *zeroiter2;
			iter++;
			zeroiter2++;
		}
		while (oneiter2 < oneiter)
		{
			*iter = *oneiter2;
			iter++;
			oneiter2++;
		}
	}

	delete[] zeroarr;
	delete[] onearr;
}


template<class T = byte>
inline void RadixSort2(T* arr, size_t count)
{
	T* arrend = arr + count;
	register byte bits = sizeof(T) * 8;
	T* zeroarr = new T[count << 1];
	T* onearr = zeroarr + count;

	register T* iter;
	register T* bucketiter;
	register T* zeroiter;
	register T* oneiter;


	for (byte bit = 0; bit < bits; bit++)
	{
		oneiter = ((bucketiter = zeroiter = zeroarr) + count);
		// put in buckets
		iter = arr;
		while (iter < arrend)
		{
			if (((*iter >> bit) & 1))
			{
				*oneiter = *iter;
				oneiter++;
			}
			else
			{
				*zeroiter = *iter;
				zeroiter++;
			}
			iter++;
		}

		iter = arr;
		//bucketiter = arr0;

		// take out of buckets;
		while (bucketiter < zeroiter)
		{
			*iter = *bucketiter;
			iter++;
			bucketiter++;
		}
		bucketiter = onearr;
		while (bucketiter < oneiter)
		{
			*iter = *bucketiter;
			iter++;
			bucketiter++;
		}
	}

	delete[] zeroarr;
}

template<class T = byte>
inline void RadixSort2Bit(T* arr, size_t count)
{
	T* arrend = arr + count;
	register byte bits = sizeof(T) * 8;
	T* arr0 = new T[count];
	T* arr1 = new T[count];
	T* arr2 = new T[count];
	T* arr3 = new T[count];

	register T* iter;
	register T* iter0 = arr0;
	register T* _iter0 = iter0;
	register T* iter1 = arr1;
	register T* _iter1 = iter1;
	register T* iter2 = arr2;
	register T* _iter2 = arr2;
	register T* iter3 = arr3;
	register T* _iter3 = arr3;


	for (byte bit = 0; bit < bits; bit += 2)
	{
		_iter0 = iter0 = arr0;
		_iter1 = iter1 = arr1;
		_iter2 = iter2 = arr2;
		_iter3 = iter3 = arr3;

		// put in buckets
		iter = arr;
		while (iter < arrend)
		{
			switch ((*iter >> bit) & 0b11)
			{
				case 0b00:
					*iter0 = *iter;
					iter0++;
					break;

				case 0b01:
					*iter1 = *iter;
					iter1++;
					break;

				case 0b10:
					*iter2 = *iter;
					iter2++;
					break;

				case 0b11:
					*iter3 = *iter;
					iter3++;
					break;
			}
			iter++;
		}


		iter = arr;

		// take out of buckets;
		while (_iter0 < iter0)
		{
			*iter = *_iter0;
			iter++;
			_iter0++;
		}
		while (_iter1 < iter1)
		{
			*iter = *_iter1;
			iter++;
			_iter1++;
		}
		while (_iter2 < iter2)
		{
			*iter = *_iter2;
			iter++;
			_iter2++;
		}
		while (_iter3 < iter3)
		{
			*iter = *_iter3;
			iter++;
			_iter3++;
		}
	}

	delete[] arr0;
	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
}


template<class T = byte>
inline void RadixSortAnyBitCount(T* arr, size_t count, byte bucketBitCount)
{
	T* arrend = arr + count;
	register byte bits = sizeof(T) * 8;
	size_t bucketCount = (size_t)pow(2, bucketBitCount);
	size_t mask = 0;
	for (size_t i = 0; i < bucketBitCount; i++)
	{
		mask <<= 1;
		mask |= 1;
	}

	T** buckets = new T*[bucketCount];
	for (size_t i = 0; i < bucketCount; i++)
	{
		buckets[i] = new T[count];
	}

	register T* iter;

	T** iters = new T*[bucketCount];
	T** _iters = new T*[bucketCount];


	for (byte bit = 0; bit < bits; bit += bucketBitCount)
	{
		for (size_t i = 0; i < bucketCount; i++)
		{
			iters[i] = _iters[i] = buckets[i];
		}

		// put in buckets
		iter = arr;
		while (iter < arrend)
		{
			byte b = (*iter >> bit) & mask;
			
			*iters[b] = *iter;
			iters[b]++;
			
			iter++;
		}


		iter = arr;

		// take out of buckets;
		for (size_t i = 0; i < bucketCount; i++)
		{
			while (_iters[i] < iters[i])
			{
				*iter = *_iters[i];
				iter++;
				_iters[i]++;
			}

		}
	}

	for (size_t i = 0; i < bucketCount; i++)
	{
		delete buckets[i];
	}
	delete[] buckets;
	delete[] iters;
	delete[] _iters;
}

template<class T>
void Print(T* arr, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

#define MEASURETIME(x, time) { auto start = std::chrono::system_clock::now(); x; auto end=std::chrono::system_clock::now(); time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0; }

byte* ReadInts(const char* const filename, size_t* count)
{
	ifstream in(filename);
	if (in.is_open())
	{
		ArrayList<byte> arr(100, 100);
		int num;
		while (in.good())
		{
			in >> num;
			arr.Add((byte)num);
		}
		byte* ret = new byte[arr.GetSize()];
		memcpy(ret, arr.GetData(), sizeof(byte) * arr.GetSize());
		*count = arr.GetSize();
		return ret;
	}
	return nullptr;
}

template<class T>
void WriteInts(const char* const filename, const T* const ints, const size_t count)
{
	ofstream out(filename);
	if (out.is_open())
	{
		for (size_t i = 0; i < count; i++)
		{
			out << (int)ints[i] << " ";
		}
	}
	delete[] ints;
}

int main(int argc, char** argv)
{
	if (argc != 2)
		return 1;

	size_t count;// = 10000;
	byte* ints = ReadInts(argv[1], &count);
	//int* ints = new int[count];

	if (!ints)
		return 2;

	/*double avg = 0;
	size_t repeat = 100;
	for (size_t i = 0; i < repeat; i++)
	{
		for (size_t j = 0; j < count; j++)
		{
			ints[j] = rand();
		}
		double time;
		MEASURETIME(RadixSortAnyBitCount(ints, count, 6), time);
		avg += time;
	}
	cout << "sort time: " << (avg / repeat) << "ms" << endl;*/
	RadixSort(ints, count);

	WriteInts("out.txt", ints, count);
	// delete ints;
	system("pause");
	return 0;
}