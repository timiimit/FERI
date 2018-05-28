#pragma once

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
				Node* next;
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
			size_t size;

		public:

			DLList();
			~DLList();

			void Add(const T& element);
			void Insert(const T& element, size_t index);
			void Remove(size_t index);
			Node<T>& GetFirst() const;
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
			}
			else
			{
				DLList<T>::Node<T>* n = first;
				while (n->next)
					n = n->next;

				n->next = new DLList<T>::Node<T>(element);
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