#pragma once
#include <iomanip>

namespace AuxiliaryDataStructures {
	template <typename E, typename Key, HeapType type>
	Heap<E, Key, type>::Heap(size_t capacity_, Key(*keyFunc_)(const E&)) : capacity(capacity_), keyFunc(keyFunc_)
	{
		space = new E[capacity];
		lastNext = 0;
		if (keyFunc_ == nullptr)
		{
			keyFunc = ([](const E&e) -> Key {return Key(e); });
		}
	}

	template <typename E, typename Key, HeapType type>
	Heap<E, Key, type>::~Heap()
	{
		delete[] space;
	}

	template <typename E, typename Key, HeapType type>
	bool Heap<E, Key, type>::isEmpty()
	{
		return lastNext == 0;
	}

	template <typename E, typename Key, HeapType type>
	void Heap<E, Key, type>::insert(const E& e)
	{
		if (lastNext == capacity)
			throw out_of_range("Heap Full");
		space[lastNext++] = e;
		adjustUp();
	}

	template <typename E, typename Key, HeapType type>
	size_t Heap<E, Key, type>::parent(size_t currNode)
	{
		return (currNode - 1) / 2;
	}

	template <typename E, typename Key, HeapType type>
	size_t Heap<E, Key, type>::leftChild(size_t currNode)
	{
		return currNode * 2 + 1;
	}

	template <typename E, typename Key, HeapType type>
	size_t Heap<E, Key, type>::rightChild(size_t currNode)
	{
		return currNode * 2 + 2;
	}

	template <typename E, typename Key, HeapType type>
	void Heap<E, Key, type>::swap(E& e1, E& e2)
	{
		E tmp = e1;
		e1 = e2;
		e2 = tmp;
	}

	template <typename E, typename Key, HeapType type>
	bool Heap<E, Key, type>::less(const E& e1, const E& e2)
	{
		if (type == MinHeap)
		{
			if ((*keyFunc)(e1) < (*keyFunc)(e2))
				return true;
		}
		else
		{
			if ((*keyFunc)(e1) > (*keyFunc)(e2))
				return true;
		}
		return false;
	}

	template <typename E, typename Key, HeapType type>
	void Heap<E, Key, type>::adjustUp(size_t last)
	{
		if (last == SIZE_MAX)
			last = lastNext - 1;
		size_t currNode = last;
		size_t currParent = 0;
		while (currNode != 0)
		{
			currParent = parent(currNode);
			if (less(space[currNode], space[currParent]))
			{
				swap(space[currNode], space[currParent]);
			}
			else
				break;
			currNode = currParent;
		}
	}

	template <typename E, typename Key, HeapType type>
	void Heap<E, Key, type>::adjustDown(size_t currNode)
	{
		if (currNode == SIZE_MAX)
			currNode = 0;

		size_t nextNode, leftChildNode, rightChildNode;
		while (currNode < lastNext)
		{
			nextNode = currNode;
			if ((leftChildNode = leftChild(currNode)) < lastNext && less(space[leftChildNode], space[nextNode]))
			{
				nextNode = leftChildNode;
			}
			if ((rightChildNode = rightChild(currNode)) < lastNext && less(space[rightChildNode], space[nextNode]))
			{
				nextNode = rightChildNode;
			}

			if (currNode == nextNode)
				break;
			
			swap(space[currNode], space[nextNode]);

			currNode = nextNode;
		}
	}

	template <typename E, typename Key, HeapType type>
	void Heap<E, Key, type>::print()
	{
		size_t lineMargin = 1;
		size_t spaces = capacity / 2;
		for (size_t i = 0; i < lastNext; i++)
		{
			if (i == lineMargin)
			{
				cout << endl;
				lineMargin = lineMargin * 2 + 1;
				spaces = spaces / 2;
			}
			cout << setw(spaces * 4) << "" << setw(4) << keyFunc(space[i]) << setw(spaces * 4) << "";
		}
		cout << endl;
	}

	template <typename E, typename Key, HeapType type>
	void Heap<E, Key, type>::sort()
	{
		for (size_t i = lastNext; i != 0; i--)
		{
			adjustUp(i - 1);
		}
	}

	template <typename E, typename Key, HeapType type>
	void Heap<E, Key, type>::popTop(E &e)
	{
		if (lastNext == 0)
			throw out_of_range("Heap Empty");

		e = space[0];
		swap(space[0], space[--lastNext]);

		adjustDown();
	}
}