#pragma once
#include <memory>

namespace timiimit
{
	namespace GenericStructures
	{
		template <class T>
		class ArrayList
		{
		private:
			size_t resizeCapacityCount;
			size_t size;
			size_t capacity;
			T* data;

			void resize(size_t newSize);

		public:
			ArrayList(size_t capacity, size_t resizeCapacityAdditionCount);
			ArrayList(size_t capacity);
			ArrayList();
			ArrayList(const ArrayList<T>& o);
			~ArrayList();

			ArrayList<T>& operator=(const ArrayList<T>& that);

			size_t GetCurrentCapacity() const;
			size_t GetSize() const;
			T& operator[](size_t index) const;
			T* GetData() const;
			size_t FindNearestTo(const T& value) const;
			size_t Find(const T& value) const;

			bool Contains(const T& val) const;

			void Add(const T& val);
			void Insert(const T& val, size_t index);
			void Insert(const T* vals, size_t count, size_t index);

			void Move(size_t destinationIndex, size_t sourceIndex);

			void Swap(size_t index1, size_t index2);

			void Remove(size_t index);
			void Remove(size_t index, size_t count);
			void Remove(T* pointer);
			void Clear();

			void ShiftRight(size_t start, size_t count);
			void ShiftLeft(size_t start, size_t count);

			void ShrinkToFit();
		};

		///////////////////////////////////////////
		//			  IMPLEMENTATION			 //
		///////////////////////////////////////////

		template <class T>
		ArrayList<T>::ArrayList() : ArrayList<T>::ArrayList(16)
		{
		}

		template<class T>
		inline ArrayList<T>::ArrayList(const ArrayList<T>& o) :
			resizeCapacityCount(o.resizeCapacityCount),
			size(0),
			capacity(o.capacity),
			data(new T[o.capacity])
		{
			for (size_t i = 0; i < o.size; ++i)
			{
				this->Insert(o[i], i);
			}
		}

		template <class T>
		ArrayList<T>::ArrayList(size_t capacity) : ArrayList<T>::ArrayList(capacity, 16)
		{
		}

		template <class T>
		ArrayList<T>::ArrayList(size_t capacity, size_t resizeCapacityAdditionCount) :
			resizeCapacityCount(resizeCapacityAdditionCount),
			size(0),
			capacity(capacity),
			data(new T[capacity])
		{
		}


		template <class T>
		ArrayList<T>::~ArrayList()
		{
			delete[] data;
			data = nullptr;
			size = 0;
			capacity = 0;
		}

		template<class T>
		inline ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& that)
		{
			/*
			resizeCapacityCount = that.resizeCapacityCount;
			if (that.size > capacity)
			{
				capacity = that.capacity;
				resize(capacity);
			}
			else
			{
				// capacity stays since we dont need to make capacity larger
			}
			size = that.size;
			*/

			for (size_t i = 0; i < that.size; ++i)
			{
				this->Insert(that[i], i);
			}
			//memcpy(data, that.data, that.size);

			return *this;
		}

		template<class T>
		inline size_t ArrayList<T>::GetCurrentCapacity() const
		{
			return capacity;
		}

		template <class T>
		inline size_t ArrayList<T>::GetSize() const
		{
			return size;
		}

		template<class T>
		inline T& ArrayList<T>::operator[](size_t index) const
		{
			if (index >= size)
			{
				throw std::exception("index out of range");;
			}
			return *(data + index);
		}

		template<class T>
		inline T* ArrayList<T>::GetData() const
		{
			return data;
		}

		template<class T>
		inline size_t ArrayList<T>::FindNearestTo(const T& value) const
		{
			size_t min = 0;
			size_t max = size - 1;

			while (min < max)
			{
				size_t mid = (max + min) / 2;
				if (data[mid] < value)
				{
					min = mid + 1;
				}
				else if (data[mid] > value)
				{
					max = mid;
				}
				else
				{
					return mid;
				}
			}
			return min;
		}

		template<class T>
		inline size_t ArrayList<T>::Find(const T& value) const
		{
			size_t index = FindNearestTo(value);
			if (*(data + index) == value)
				return index;
			return -1;
		}

		template<class T>
		inline bool ArrayList<T>::Contains(const T& val) const
		{
			T* p = data;
			T* end = data + size;
			while (p < end)
			{
				if (*p == val)
					return true;
				p++;
			}
			return false;
		}

		template <class T>
		inline void ArrayList<T>::Add(const T& val)
		{
			if (size >= capacity)
			{
				resize(capacity + resizeCapacityCount);
			}
			data[size++] = T(val);
		}

		template<class T>
		inline void ArrayList<T>::Insert(const T& val, size_t index)
		{
			if (index > size)
			{
				throw std::exception("index out of range");;
			}
			if (size >= capacity)
			{
				resize(capacity + resizeCapacityCount);
			}
			if (index > size)
			{
				return;
			}
			if (size + 1 > capacity)
			{
				size_t newCapacity = size + 1 + resizeCapacityCount;
				size_t sameCpyCount = index;
				size_t shiftedCpyCount = size - index;
				T* larger = new T[newCapacity];
				std::memcpy(larger, data, sameCpyCount * sizeof(T));
				std::memcpy(larger + index + 1, data + index, shiftedCpyCount * sizeof(T));
				larger[index] = T(val);
				delete[] data;
				data = larger;
				capacity = newCapacity;
			}
			else
			{
				size_t sameCpyCount = index;
				size_t shiftedCpyCount = size - index;
				std::memmove(data + index + 1, data + index, shiftedCpyCount * sizeof(T));
				data[index] = T(val);
			}
			size++;
		}

		template<class T>
		inline void ArrayList<T>::Insert(const T* vals, size_t count, size_t index)
		{
			if (index > size)
			{
				throw std::exception("index out of range");;
			}
			if (size + count > capacity)
			{
				size_t newCapacity = size + count + resizeCapacityCount;
				size_t sameCpyCount = index;
				size_t shiftedCpyCount = size - index;
				T* larger = new T[newCapacity];
				std::memcpy(larger, data, sameCpyCount * sizeof(T));
				std::memcpy(larger + index + count, data + index, shiftedCpyCount * sizeof(T));
				std::memcpy(larger + index, vals, count * sizeof(T)); // copy data to array
				delete[] data;
				data = larger;
				capacity = newCapacity;
			}
			else
			{
				size_t sameCpyCount = index;
				size_t shiftedCpyCount = size - index;
				std::memmove(data + index + count, data + index, shiftedCpyCount * sizeof(T));
				std::memmove(data + index, vals, count * sizeof(T)); // copy data to array
			}
			size += count;
		}

		template<class T>
		inline void ArrayList<T>::Move(size_t destinationIndex, size_t sourceIndex)
		{
			if (destinationIndex >= size)
			{
				throw std::exception("destinationIndex out of range");
			}
			else if (sourceIndex >= size)
			{
				throw std::exception("sourceIndex out of range");
			}

			T tmp = *(data + sourceIndex);
			//memcpy(&tmp, data + sourceIndex, sizeof(T));
			if (sourceIndex < destinationIndex) // move element to right
			{
				std::memmove(data + sourceIndex, data + sourceIndex + 1, (destinationIndex - sourceIndex) * sizeof(T));
			}
			else if (sourceIndex > destinationIndex) // move element to left
			{
				std::memmove(data + destinationIndex + 1, data + destinationIndex, (sourceIndex - destinationIndex) * sizeof(T));
			}
			*(data + destinationIndex) = tmp;
			//memcpy(data + destinationIndex, &tmp, sizeof(T));
		}

		template<class T>
		inline void ArrayList<T>::Swap(size_t index1, size_t index2)
		{
			if (index1 >= size)
			{
				throw std::exception("index1 out of range");
			}
			else if (index2 >= size)
			{
				throw std::exception("index2 out of range");
			}

			T tmp = data[index1];
			data[index1] = data[index2];
			data[index2] = tmp;
		}

		template<class T>
		inline void ArrayList<T>::Remove(size_t index)
		{
			ShiftLeft(index, 1);
			size--;
		}

		template<class T>
		inline void ArrayList<T>::Remove(T* pointer)
		{
			Remove(size_t(pointer - data) / sizeof(T));
		}

		template<class T>
		inline void ArrayList<T>::Remove(size_t index, size_t count)
		{
			if (index + count > size)
			{
				throw std::exception("selection out of range");
			}
			ShiftLeft(index + count, count);
			size -= count;
		}

		template <class T>
		inline void ArrayList<T>::resize(size_t newCapacity)
		{
			T* larger = new T[newCapacity];
			if (newCapacity >= size)
			{
				std::memcpy(larger, data, size * sizeof(T));
			}
			else
			{
				std::memcpy(larger, data, newCapacity * sizeof(T));
			}
			delete[] data;
			data = larger;
			capacity = newCapacity;
		}

		template<class T>
		inline void ArrayList<T>::ShiftLeft(size_t start, size_t count)
		{
			std::memmove(data + start - count, data + start, (size - start) * sizeof(T));
		}

		template<class T>
		inline void ArrayList<T>::ShiftRight(size_t start, size_t count)
		{
			if (size + count > capacity)
			{
				size_t newCapacity = size + count + resizeCapacityCount;
				size_t shiftedCpyCount = size - start;
				T* larger = new T[newCapacity];
				std::memcpy(larger, data, start * sizeof(T));
				std::memcpy(larger + start, data + start, count * sizeof(T));
				std::memcpy(larger + start + count, data + start, shiftedCpyCount * sizeof(T));
				delete[] data;
				data = larger;
				capacity = newCapacity;
			}
			else
			{
				size_t sameCpyCount = start;
				size_t shiftedCpyCount = size - start;
				std::memmove(data + start + count, data + start, shiftedCpyCount * sizeof(T));
			}
			size += count;
		}

		template<class T>
		inline void ArrayList<T>::Clear()
		{
			size = 0;
		}

		template<class T>
		inline void ArrayList<T>::ShrinkToFit()
		{
			resize(size);
		}
	}
}