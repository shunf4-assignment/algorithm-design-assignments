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
	bool select;
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

	static Node& factory(int currWeight_, int currValue_, int itemNo_, bool select_, Node *parent_)
	{
		Node *newNode = new Node();
		nodeField[usedNode++] = newNode;

		newNode->currWeight = currWeight_;
		newNode->currValue = currValue_;
		newNode->itemNo = itemNo_;
		newNode->select = select_;
		newNode->parent = parent_;
		return (*newNode);
	}

	Node() = default;

};

Node **Node::nodeField = nullptr;
int Node::usedNode = 0;

class KnapsackStackSearcher
{
public:

	int *weights;
	int *values;
	double *vwRatios;
	int *arrangedIndex;
	bool *result;

	int n;
	int currWeight;
	int currValue;
	int capacity;

	Node * bestNode;
	int bestWeight;
	int bestValue;


	Stack<Node *> stack{ 10000 };
	

	void applyNode(const Node &node)
	{
		currWeight = node.currWeight;
		currValue = node.currValue;
	}

	KnapsackStackSearcher(int n_)
	{
		n = n_;
		weights = new int[n];
		values = new int[n];
		vwRatios = new double [n];
		arrangedIndex = new int[n];
		result = new bool[n];
	}

	~KnapsackStackSearcher()
	{
		delete[]weights;
		delete[]values;
		delete[]vwRatios;
		delete[]arrangedIndex;
		delete[]result;
	}

	void genVWRatios()
	{
		for (int i = 0; i < n; i++)
		{
			vwRatios[i] = double(values[i]) / weights[i];
		}
	}

	static int partition(double *vwRatios, int *arr, int beg, int end)
	{
		int pivot = arr[beg];
		int leftI = beg, rightI = end;
		while (true)
		{
			while (leftI < rightI)
			{
				if (vwRatios[arr[rightI]] < vwRatios[pivot])
				{
					break;
				}
				rightI--;
			}
			if (!(leftI < rightI)) break;
			arr[leftI] = arr[rightI];

			while (leftI < rightI)
			{
				if (vwRatios[arr[leftI]] > vwRatios[pivot])
				{
					break;
				}
				leftI++;
			}
			if (!(leftI < rightI)) break;
			arr[rightI] = arr[leftI];
		}
		arr[leftI] = pivot;
		return leftI;
	}

	static void sortArrangedIndex(double *vwRatios, int *arr, int beg, int end)
	{
		if (beg <= end) return;
		int pivotIndex;
		pivotIndex = partition(vwRatios, arr, beg, end);
		sortArrangedIndex(vwRatios, arr, beg, pivotIndex - 1);
		sortArrangedIndex(vwRatios, arr, pivotIndex + 1, end);
	}

	void genArrangedIndexAccordingToVWRatios()
	{
		for (int i = 0; i < n; i++)
		{
			arrangedIndex[i] = i;
		}

		sortArrangedIndex(vwRatios, arrangedIndex, 0, n - 1);
	}

	void readInWeights()
	{
		int weight;
		for (int i = 0; i < n; i++)
		{
			cin >> weight;
			weights[i] = weight;
		}
	}

	void readInValues()
	{
		int value;
		for (int i = 0; i < n; i++)
		{
			cin >> value;
			values[i] = value;
		}
	}

	void setCapacity(int capacity_)
	{
		capacity = capacity_;
	}

	int getUpperBound(int currItemNo)
	{
		int estimatingWeight = currWeight;
		int estimatingValue = currValue;
		for (int i = currItemNo + 1; i < n; i++)
		{
			estimatingWeight += weights[arrangedIndex[i]];
			estimatingValue += values[arrangedIndex[i]];
			if (estimatingWeight > capacity)
			{
				estimatingWeight -= weights[arrangedIndex[i]];
				estimatingValue -= values[arrangedIndex[i]];
				break;
			}
		}

		return estimatingValue;
	}

	void search()
	{
		Node *currNode;
		size_t item = 0;
		while (true)
		{
			if (stack.isEmpty())
			{
				return;
			}
			
			stack.pop(currNode);
			applyNode(*currNode);
			
			if (currNode->itemNo == n - 1)
			{
				bestNode = currNode;
				continue;
			}

			Node &leftChild = Node::factory(currWeight + weights[arrangedIndex[currNode->itemNo + 1]], currValue + values[arrangedIndex[currNode->itemNo + 1]], currNode->itemNo + 1, true, currNode);
			Node &rightChild = Node::factory(currWeight, currValue, currNode->itemNo + 1, false, currNode);

			applyNode(rightChild);
			int upperBound = getUpperBound(rightChild.itemNo);
			if (bestNode == nullptr || upperBound > bestNode->currValue)
			{
				stack.push(&rightChild);
			}

			if (leftChild.currWeight <= capacity)
			{
				stack.push(&leftChild);
			}
		}
	}

	void startSearch()
	{
		currWeight = 0;
		currValue = 0;
		genVWRatios();
		genArrangedIndexAccordingToVWRatios();
		bestNode = nullptr;
		for (int i = 0; i < n; i++)
		{
			result[i] = false;
		}
		stack.push(&(Node::factory(0, 0, -1, 0, nullptr)));
		search();
		if (bestNode == nullptr)
		{
			throw invalid_argument("No Solution.");
		}
		Node * currNode = bestNode;
		
		for (int i = n - 1; i >= 0; i--)
		{
			result[arrangedIndex[i]] = currNode->select;
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

	int n;
	cout << "输入 n : ";
	cin >> n;
	KnapsackStackSearcher knapsack(n);
	cout << "输入重量：";
	knapsack.readInWeights();
	cout << "输入价值：";
	knapsack.readInValues();
	cout << "输入背包容量：";
	int capacity;
	cin >> capacity;
	knapsack.setCapacity(capacity);
	knapsack.startSearch();
	for (int i = 0; i < n; i++)
	{
		cout << i << " : " << (knapsack.result[i] ? "选" : "不选") << ";  ";
	}
	cout << endl;
	cout << "最高价值：" << knapsack.bestValue << endl;
	cout << "当前重量：" << knapsack.bestWeight << endl;

	Node::disposeField();
	return 0;
}