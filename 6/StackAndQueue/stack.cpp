#pragma once

namespace AuxiliaryDataStructures {
	template <typename E>
	Stack<E>::Stack(size_t capacity) : capacity(capacity)
	{
		topNext = 0;
		space = new E[capacity];
	}

	template <typename E>
	bool Stack<E>::isEmpty()
	{
		return topNext == 0;
	}

	template <typename E>
	void Stack<E>::push(const E& e)
	{
		if (topNext == capacity)
		{
			throw out_of_range("Stack Full");
		}
		else
			space[topNext++] = e;
	}

	template <typename E>
	void Stack<E>::pop(E& e)
	{
		if (topNext == 0)
		{
			throw out_of_range("Stack Empty");
		}
		else
			e = space[--topNext];
	}

	template <typename E>
	Stack<E>::~Stack()
	{
		delete[] space;
	}

	void stackUnitTest()
	{
		Stack<int> s(1);
		cout << "Stack s initialized with capacity 1." << endl;
		int receiver;
		int pushedNum;

		int no = 1;
		bool exception = false;

		try
		{
			exception = false;
			cout << no << ". s.pop(receiver);" << endl;
			s.pop(receiver);
		}
		catch (out_of_range e)
		{
			cout << no << ". Exception encountered: " << endl;
			cout << e.what() << endl;
			exception = true;
		}
		if (!exception)
		{
			cout << no << ". Fails." << endl;
			return;
		}

		no++;

		pushedNum = 2;
		try
		{
			exception = false;
			cout << no << ". s.push(pushedNum); //2" << endl;
			s.push(pushedNum);
		}
		catch (out_of_range e)
		{
			cout << no << ". Exception encountered: " << endl;
			cout << e.what() << endl;
			exception = true;
		}
		if (exception)
		{
			cout << no << ". Fails." << endl;
			return;
		}

		no++;

		pushedNum = 3;
		try
		{
			exception = false;
			cout << no << ". s.push(pushedNum); //3" << endl;
			s.push(pushedNum);
		}
		catch (out_of_range e)
		{
			cout << no << ". Exception encountered: " << endl;
			cout << e.what() << endl;
			exception = true;
		}
		if (!exception)
		{
			cout << no << ". Fails." << endl;
			return;
		}

		no++;

		try
		{
			exception = false;
			cout << no << ". s.pop(receiver);" << endl;
			s.pop(receiver);
		}
		catch (out_of_range e)
		{
			cout << no << ". Exception encountered: " << endl;
			cout << e.what() << endl;
			exception = true;
		}
		if (exception)
		{
			cout << no << ". Fails." << endl;
			return;
		}
		cout << "Result : " << receiver << endl;

		no++;

		try
		{
			exception = false;
			cout << no << ". s.pop(receiver);" << endl;
			s.pop(receiver);
		}
		catch (out_of_range e)
		{
			cout << no << ". Exception encountered: " << endl;
			cout << e.what() << endl;
			exception = true;
		}
		if (!exception)
		{
			cout << no << ". Fails." << endl;
			return;
		}

		cout << "Unit Test Ends." << endl;
	}
}