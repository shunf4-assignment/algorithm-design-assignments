#include <iostream>
using namespace std;
#include "auxiliary.h"
using namespace AuxiliaryDataStructures;
#include <ctime>
#include <cassert>

class Node
{
public:
	static const int maxNodeNum = 99999;
	static int usedNode;
	static Node **nodeField;

	int rowNo;
	int *board;

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

	static Node& factory(int n_, int rowNo_, int *board)
	{
		Node *newNode = new Node();
		nodeField[usedNode++] = newNode;

		newNode->board = new int[n_];
		newNode->rowNo = rowNo_;
		memcpy(newNode->board, board, sizeof(int) * n_);
		return (*newNode);
	}

	Node() = default;
	~Node() { delete[]board; }
};

Node **Node::nodeField = nullptr;
int Node::usedNode = 0;

class NQueensSearcher
{
public:

	int *board;
	int *result;

	int n;
	int validBoardNum;

	Node * firstResultNode;


	Queue<Node*> queue{ 10000 };


	void applyNode(const Node &node)
	{
		memcpy(board, node.board, sizeof(int) * n);
	}

	NQueensSearcher(int n_)
	{
		n = n_;

		board = new int[n];
		for (int i = 0; i < n; i++)
		{
			board[i] = -1;
		}

		result = new int[n];
	}

	~NQueensSearcher()
	{
		delete[]board;
		delete[]result;
	}

	bool boardValid(int rowNum)
	{
		for (int i = 0; i < rowNum; i++)
		{
			if (board[i] == board[rowNum])
				return false;

			if (abs(board[i] - board[rowNum]) == abs(i - rowNum))
				return false;
		}
		return true;
	}

	void search()
	{
		Node *currNode;
		while (true)
		{
			if (queue.isEmpty())
			{
				return;
			}

			queue.dequeue(currNode);
			applyNode(*currNode);

			if (currNode->rowNo == n - 1)
			{
				if(firstResultNode == nullptr)
					firstResultNode = currNode;
				validBoardNum++;
				continue;
			}

			for (int j = 0; j < n; j++)
			{
				board[currNode->rowNo + 1] = j;
				if (boardValid(currNode->rowNo + 1))
				{
					queue.enqueue(&Node::factory(n, currNode->rowNo + 1, board));

				}
			}
		}
	}

	void startSearch()
	{
		for (int i = 0; i < n; i++)
		{
			board[i] = -1;
			result[i] = -1;
		}
		firstResultNode = nullptr;
		validBoardNum = 0;
		
		queue.enqueue(&(Node::factory(n, -1, board)));
		search();

		if (firstResultNode == nullptr)
		{
			;
		}
		else
		{
			Node * currNode = firstResultNode;

			for (int i = 0; i < n; i++)
			{
				result[i] = currNode->board[i] + 1;
			}
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

	NQueensSearcher nqs(n);
	
	nqs.startSearch();

	for (int i = 0; i < n; i++)
	{
		cout << nqs.result[i] << " ";
	}
	cout << endl;
	cout << n << " 皇后的合法棋盘有 " << nqs.validBoardNum << " 种。"<< endl;

	Node::disposeField();
	return 0;
}