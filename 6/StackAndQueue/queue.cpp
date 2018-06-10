#pragma once

namespace AuxiliaryDataStructures {
	CyclicNumber::CyclicNumber(size_t divisor) : divisor(divisor)
	{
		number = 0;
	}

	CyclicNumber::CyclicNumber() : divisor(1)
	{
		number = 0;
	}

	CyclicNumber::operator size_t& ()
	{
		return number;
	}

	size_t CyclicNumber::operator++(int)
	{
		size_t num_ = number;
		++number;
		if (number == divisor)
			number = 0;
		return num_;
	}

	size_t& CyclicNumber::operator++()
	{
		++number;
		if (number == divisor)
			number = 0;
		return number;
	}

	size_t CyclicNumber::operator+(size_t addition)
	{
		size_t num_ = (number + addition) % divisor;
		return num_;
	}

	size_t& CyclicNumber::operator+=(size_t addition)
	{
		number = number + addition;
		return number;
	}
	
	template <typename E>
	Queue<E>::Queue(size_t capacity_) : capacity(capacity_ + 1)
	{
		space = new E[capacity];
		frontNext.divisor = capacity;
		rear.divisor = capacity;

		(size_t&)frontNext = 0;
		(size_t&)rear = 0;
	}
	
	template <typename E>
	bool Queue<E>::isEmpty() { return frontNext == rear; }

	template <typename E>
	void Queue<E>::enqueue(const E &e)
	{
		if (frontNext + size_t(1) == rear)
		{
			throw out_of_range("Queue Full");
		}
		else
		{
			size_t f = frontNext++;
			space[f] = e;
		}
	}

	template <typename E>
	void Queue<E>::dequeue(E& e)
	{
		if (isEmpty())
			throw out_of_range("Queue Empty");
		else
			e = space[rear++];
	}

	template <typename E>
	Queue<E>::~Queue()
	{
		delete[] space;
	}

	void queueUnitTest()
	{
		Queue<int> q(3);
		cout << "Queue q initialized with capacity 3." << endl;
		int receiver;
		bool receiverBool;

		int no = 1;
		bool exception = false;


		exception = false;
		cout << no << ". q.isEmpty();" << endl;
		receiverBool = q.isEmpty();
		cout << (receiverBool ? "true" : "false") << endl;
		if (!receiverBool)
		{
			cout << no << ". Fails." << endl;
			return;
		}

		no++;

		try
		{
			exception = false;
			cout << no << ". q.dequeue(receiver)" << endl;
			q.dequeue(receiver);
		}
		catch (out_of_range e)
		{
			cout << no << ". Exception encountered: " << endl;
			cout << e.what() << endl;
			exception = true;
		}

		cout << "q.frontNext == " << q.frontNext << endl;
		cout << "q.rear == " << q.rear << endl;

		if (!exception)
		{
			cout << no << ". Fails." << endl;
			return;
		}

		no++;

		try
		{
			exception = false;
			cout << no << ". q.enqueue(1);" << endl;
			q.enqueue(1);
		}
		catch (out_of_range e)
		{
			cout << no << ". Exception encountered: " << endl;
			cout << e.what() << endl;
			exception = true;
		}

		cout << "q.frontNext == " << q.frontNext << endl;
		cout << "q.rear == " << q.rear << endl;

		if (exception)
		{
			cout << no << ". Fails." << endl;
			return;
		}

		no++;

		try
		{
			exception = false;
			cout << no << ". q.enqueue(2);" << endl;
			q.enqueue(2);
		}
		catch (out_of_range e)
		{
			cout << no << ". Exception encountered: " << endl;
			cout << e.what() << endl;
			exception = true;
		}

		cout << "q.frontNext == " << q.frontNext << endl;
		cout << "q.rear == " << q.rear << endl;

		if (exception)
		{
			cout << no << ". Fails." << endl;
			return;
		}

		no++;

		try
		{
			exception = false;
			cout << no << ". q.enqueue(3);" << endl;
			q.enqueue(3);
		}
		catch (out_of_range e)
		{
			cout << no << ". Exception encountered: " << endl;
			cout << e.what() << endl;
			exception = true;
		}
		cout << "q.frontNext == " << q.frontNext << endl;
		cout << "q.rear == " << q.rear << endl;

		if (exception)
		{
			cout << no << ". Fails." << endl;
			return;
		}

		no++;

		try
		{
			exception = false;
			cout << no << ". q.enqueue(4);" << endl;
			q.enqueue(4);
		}
		catch (out_of_range e)
		{
			cout << no << ". Exception encountered: " << endl;
			cout << e.what() << endl;
			exception = true;
		}
		cout << "q.frontNext == " << q.frontNext << endl;
		cout << "q.rear == " << q.rear << endl;

		if (!exception)
		{
			cout << no << ". Fails." << endl;
			return;
		}

		no++;

		try
		{
			exception = false;
			cout << no << ". q.dequeue(receiver);" << endl;
			q.dequeue(receiver);
		}
		catch (out_of_range e)
		{
			cout << no << ". Exception encountered: " << endl;
			cout << e.what() << endl;
			exception = true;
		}
		cout << "q.frontNext == " << q.frontNext << endl;
		cout << "q.rear == " << q.rear << endl;
		cout << "receiver == " << receiver << endl;

		if (exception)
		{
			cout << no << ". Fails." << endl;
			return;
		}


		no++;

		try
		{
			exception = false;
			cout << no << ". q.dequeue(receiver);" << endl;
			q.dequeue(receiver);
		}
		catch (out_of_range e)
		{
			cout << no << ". Exception encountered: " << endl;
			cout << e.what() << endl;
			exception = true;
		}
		cout << "q.frontNext == " << q.frontNext << endl;
		cout << "q.rear == " << q.rear << endl;
		cout << "receiver == " << receiver << endl;

		if (exception)
		{
			cout << no << ". Fails." << endl;
			return;
		}

		no++;

		try
		{
			exception = false;
			cout << no << ". q.enqueue(99);" << endl;
			q.enqueue(99);
		}
		catch (out_of_range e)
		{
			cout << no << ". Exception encountered: " << endl;
			cout << e.what() << endl;
			exception = true;
		}
		cout << "q.frontNext == " << q.frontNext << endl;
		cout << "q.rear == " << q.rear << endl;

		if (exception)
		{
			cout << no << ". Fails." << endl;
			return;
		}

		no++;

		try
		{
			exception = false;
			cout << no << ". q.dequeue(receiver);" << endl;
			q.dequeue(receiver);
		}
		catch (out_of_range e)
		{
			cout << no << ". Exception encountered: " << endl;
			cout << e.what() << endl;
			exception = true;
		}
		cout << "q.frontNext == " << q.frontNext << endl;
		cout << "q.rear == " << q.rear << endl;
		cout << "receiver == " << receiver << endl;

		if (exception)
		{
			cout << no << ". Fails." << endl;
			return;
		}


		no++;

		try
		{
			exception = false;
			cout << no << ". q.dequeue(receiver);" << endl;
			q.dequeue(receiver);
		}
		catch (out_of_range e)
		{
			cout << no << ". Exception encountered: " << endl;
			cout << e.what() << endl;
			exception = true;
		}
		cout << "q.frontNext == " << q.frontNext << endl;
		cout << "q.rear == " << q.rear << endl;
		cout << "receiver == " << receiver << endl;

		if (exception)
		{
			cout << no << ". Fails." << endl;
			return;
		}

		no++;

		try
		{
			exception = false;
			cout << no << ". q.dequeue(receiver);" << endl;
			q.dequeue(receiver);
		}
		catch (out_of_range e)
		{
			cout << no << ". Exception encountered: " << endl;
			cout << e.what() << endl;
			exception = true;
		}
		cout << "q.frontNext == " << q.frontNext << endl;
		cout << "q.rear == " << q.rear << endl;
		cout << "receiver == " << receiver << endl;

		if (!exception)
		{
			cout << no << ". Fails." << endl;
			return;
		}

		cout << "Unit Test Ends." << endl;
	}
}