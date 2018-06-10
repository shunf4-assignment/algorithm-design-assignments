#include <iostream>
using namespace std;
#include "auxiliary.h"
using namespace AuxiliaryDataStructures;
#include <ctime>
#include <cassert>
#include <string>

enum Operator
{
	Add = 0,
	Substract = 1,
	Multiply = 2,
	Divide = 3
};

const char operatorSymbols[] = { '+', '-', '*', '/' };

int answerCalculate(int prevAnswer, Operator o, int integer)
{
	switch (o)
	{
	case Add:
		return prevAnswer + integer;
	case Substract:
		return prevAnswer - integer;
	case Multiply:
		return prevAnswer * integer;
	case Divide:
		return prevAnswer / integer;
	default:
		throw invalid_argument("Invalid operator");
	}
	
}

class Node
{
public:
	static const int maxNodeNum = 99999;
	static int usedNode;
	static Node **nodeField;

	bool *integersUsedIndex;
	int integerNo;
	string expression;
	int answer;


	static void init()
	{
		nodeField = new Node*[maxNodeNum];
		usedNode = 0;
	}

	static void dispose()
	{
		for (int i = 0; i < usedNode; i++)
		{
			if (nodeField[i] != nullptr)
			{
				delete nodeField[i];
			}
		}
		usedNode = 0;
	}

	static void disposeField()
	{
		dispose();
		delete[] nodeField;
	}

	static Node& factory(int n_, bool *integerUsedIndex_, int integerNo_, string expression_, int answer_)
	{
		Node *newNode = new Node();
		nodeField[usedNode++] = newNode;

		newNode->integersUsedIndex = new bool[n_];
		newNode->integerNo = integerNo_;
		newNode->expression = expression_;
		newNode->answer = answer_;
		memcpy(newNode->integersUsedIndex, integerUsedIndex_, sizeof(bool) * n_);
		return (*newNode);
	}

	Node() = default;
	~Node() { delete[]integersUsedIndex; }
};

Node **Node::nodeField = nullptr;
int Node::usedNode = 0;

class ExpressionSearcher
{
public:
	string result;

	int n;
	int *integers;
	int answer;

	Node * firstResultNode;


	Heap<Node*, int, MinHeap> heap{ 10000, ([](Node * const &node) -> int {return node->integerNo; }) };

	ExpressionSearcher(int n_, int answer_)
	{
		n = n_;
		answer = answer_;
		integers = new int[n];

		result = "";
	}

	void readInIntegers()
	{
		for (int i = 0; i < n; i++)
		{
			int integer;
			cin >> integer;
			integers[i] = integer;
		}
	}

	~ExpressionSearcher()
	{
		delete[]integers;
	}

	void search()
	{
		Node *currNode;
		while (true)
		{
			if (heap.isEmpty())
			{
				return;
			}

			heap.popTop(currNode);

			if (currNode->answer == answer)
			{
				firstResultNode = currNode;
				return;
			}

			for (int j = n-1; j >= 0; j--)
			{
				if (!(currNode->integersUsedIndex[j]))
				{
					currNode->integersUsedIndex[j] = true;
					for (Operator o = Add; o <= Divide && (o == Add || currNode->integerNo != -1); o = Operator(o + 1))
					{
						heap.insert(&Node::factory(n, currNode->integersUsedIndex, currNode->integerNo + 1, currNode->expression + ((currNode->integerNo != -1) ? string(1, operatorSymbols[int(o)]) : string("")) + to_string(integers[j]), answerCalculate(currNode->answer, o, integers[j])));
					}
					currNode->integersUsedIndex[j] = false;
				}
			}
		}
	}

	void startSearch()
	{
		result = "";
		firstResultNode = nullptr;

		bool *integersUsedIndex = new bool[n];
		for (int i = 0; i < n; i++)
		{
			integersUsedIndex[i] = false;
		}

		heap.insert(&(Node::factory(n, integersUsedIndex, -1, "", 0)));

		delete[]integersUsedIndex;
		search();

		if (firstResultNode == nullptr)
		{
			throw invalid_argument("No Solution.");
		}
		else
		{
			Node * currNode = firstResultNode;

			result = currNode->expression;
		}

		Node::dispose();
	}
};

int main()
{
	Node::init();

	int n;
	cout << "输入 n : ";
	cin >> n;

	int m;
	cout << "输入 m : ";
	cin >> m;

	ExpressionSearcher es(n, m);

	cout << "依次输入 n 个整数：" << endl;
	es.readInIntegers();

	es.startSearch();

	cout << es.result << endl;

	Node::disposeField();
	return 0;
}