#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

namespace AuxiliaryDataStructures {
	enum HeapType
	{
		MinHeap,
		MaxHeap
	};

	const int defaultCapacity = 100;

	template <typename E>
	class Stack
	{
	public:
		E * space;
		size_t capacity;
		size_t topNext;

		Stack(size_t capacity);
		bool isEmpty();
		void push(const E& e);
		void pop(E& e);
		~Stack();
	};

	class CyclicNumber
	{
	public:
		size_t number;
		size_t divisor;
		explicit CyclicNumber(size_t divisor);
		explicit CyclicNumber();
		operator size_t& ();
		size_t operator++(int);
		size_t& operator++();
		size_t operator+(size_t addition);
		size_t& operator+=(size_t addition);
	};

	template <typename E>
	class Queue
	{
	public:
		E * space;
		CyclicNumber frontNext;
		CyclicNumber rear;
		size_t capacity;

		Queue(size_t capacity_);
		bool isEmpty();

		void enqueue(const E &e);

		void dequeue(E& e);

		~Queue();
	};

	template <typename E, typename Key, HeapType type>
	class Heap
	{
	public:
		E *space;
		size_t capacity;
		size_t lastNext;
		Key (*keyFunc)(const E&);

		static size_t parent(size_t currNode);
		static size_t leftChild(size_t currNode);
		static size_t rightChild(size_t currNode);
		static void swap(E& e1, E& e2);
		bool less(const E& e1, const E& e2);

		Heap(size_t capacity_, Key(*key_)(const E &) = nullptr);
		~Heap();

		bool isEmpty();
		void insert(const E& e);
		void print();
		void adjustUp(size_t last = SIZE_MAX);
		void sort();
		void adjustDown(size_t currNode = SIZE_MAX);
		void popTop(E& e);
	};
}

#include "heap.cpp"
#include "queue.cpp"
#include "stack.cpp"