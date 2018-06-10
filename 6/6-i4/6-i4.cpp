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

	int currWeight;
	int currValue;
	int itemNo;
	int providerNo;
	Node *parent;

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

	static Node& factory()
	{
		Node *newNode = new Node();
		nodeField[usedNode++] = newNode;
		return (*newNode);
	}

	static Node& factory(int currWeight_, int currValue_, int itemNo_, int providerNo_, Node *parent_)
	{
		Node *newNode = new Node();
		nodeField[usedNode++] = newNode;

		newNode->currWeight = currWeight_;
		newNode->currValue = currValue_;
		newNode->itemNo = itemNo_;
		newNode->providerNo = providerNo_;
		newNode->parent = parent_;
		return (*newNode);
	}

	Node() = default;

};

Node **Node::nodeField = nullptr;
int Node::usedNode = 0;

class MinWeightMachineSearcher
{
public:

	int **weights;
	int **values;

	int *result;

	int n;
	int m;
	int currWeight;
	int currValue;
	int maxValue;

	Node * bestNode;
	int bestWeight;
	int bestValue;


	Heap<Node*, int, MinHeap> heap{ 10000, ([](Node *const &node) -> int {return node->currWeight; }) };


	void applyNode(const Node &node)
	{
		currWeight = node.currWeight;
		currValue = node.currValue;
	}

	MinWeightMachineSearcher(int n_, int m_)
	{
		n = n_;
		m = m_;
		weights = new int*[n];
		values = new int*[n];
		for (int i = 0; i < n; i++)
		{
			weights[i] = new int[m];
			values[i] = new int[m];
		}

		result = new int[n];
	}

	~MinWeightMachineSearcher()
	{
		delete[]weights;
		delete[]values;
		delete[]result;
	}

	void readInWeights()
	{
		int weight;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cin >> weight;
				weights[i][j] = weight;
			}
		}
	}

	void readInValues()
	{
		int value;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cin >> value;
				values[i][j] = value;
			}
		}
	}

	void setMaxValue(int value_)
	{
		maxValue = value_;
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
			applyNode(*currNode);

			if (currNode->itemNo == n - 1)
			{
				bestNode = currNode;
				return;
			}

			for (int j = 0; j < m; j++)
			{
				if (currValue + values[currNode->itemNo + 1][j] <= maxValue)
				{
					heap.insert(&(Node::factory(currWeight + weights[currNode->itemNo + 1][j], currValue + values[currNode->itemNo + 1][j], currNode->itemNo + 1, j, currNode)));
				}
			}
		}
	}

	void startSearch()
	{
		currWeight = 0;
		currValue = 0;
		bestNode = nullptr;

		for (int i = 0; i < n; i++)
		{
			result[i] = -1;
		}

		heap.insert(&(Node::factory(0, 0, -1, 0, nullptr)));
		search();

		if (bestNode == nullptr)
		{
			throw invalid_argument("No Solution.");
		}
		Node * currNode = bestNode;

		for (int i = n - 1; i >= 0; i--)
		{
			result[i] = currNode->providerNo + 1;
			currNode = currNode->parent;
		}

		assert(currNode->parent == nullptr);

		bestWeight = bestNode->currWeight;
		bestValue = bestNode->currValue;

		Node::dispose();
	}
};

int main()
{
	Node::init();

	int n, m;
	cout << "输入 n : ";
	cin >> n;

	cout << "输入 m : ";
	cin >> m;

	MinWeightMachineSearcher mwm(n, m);
	cout << "输入部件-供应商-重量矩阵：";
	mwm.readInWeights();
	cout << "输入部件-供应商-价值矩阵：";
	mwm.readInValues();
	cout << "输入最大允许价格：";
	int maxValue;
	cin >> maxValue;
	mwm.setMaxValue(maxValue);
	mwm.startSearch();
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << " 部件 : 选供应商 " << (mwm.result[i]) << ";  ";
	}
	cout << endl;
	cout << "最高价值：" << mwm.bestValue << endl;
	cout << "当前重量：" << mwm.bestWeight << endl;

	Node::disposeField();
	return 0;
}