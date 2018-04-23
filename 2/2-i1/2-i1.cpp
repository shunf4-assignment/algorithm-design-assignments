#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

template <typename T>
void partition(T *a, size_t start, size_t end, size_t &pivotPos, T &pivotKey, size_t &lastLeftPos, size_t &lastEqualPos)
{
	//size_t randomPos = start + rand() * (end - start + 1) / 32768;
	size_t randomPos = start + rand() % (end - start + 1);
	T swap;

	pivotKey = a[randomPos];
	size_t lastPartitionPos;
	lastLeftPos = lastEqualPos = lastPartitionPos = start - 1;

	for (; lastPartitionPos + 1 < end + 1; lastPartitionPos++)
	{
		if (a[lastPartitionPos + 1] < pivotKey)
		{
			swap = a[lastEqualPos + 1];
			a[lastEqualPos + 1] = a[lastPartitionPos + 1];
			a[lastPartitionPos + 1] = swap;
			swap = a[lastLeftPos + 1];
			a[lastLeftPos + 1] = a[lastEqualPos + 1];
			a[lastEqualPos + 1] = swap;
			lastLeftPos++;
			lastEqualPos++;
		}
		else if (a[lastPartitionPos + 1] == pivotKey)
		{
			swap = a[lastEqualPos + 1];
			a[lastEqualPos + 1] = a[lastPartitionPos + 1];
			a[lastPartitionPos + 1] = swap;
			lastEqualPos++;
		}
		else
		{
			;
		}
	}
	pivotPos = (lastLeftPos + 1 + lastEqualPos) / 2;
	//for (auto i = start; i <= end; i++)
	//{
	//	if (i == lastLeftPos) cout << "[";
	//	if (i == lastEqualPos) cout << "<";
	//	if (i == lastPartitionPos) cout << "(";
	//	
	//	cout << a[i] << " ";
	//}
	//cout << endl;
}

template <typename T>
void select(T *a, size_t start, size_t end, size_t rank, T &result, size_t &outLastLeftPos, size_t &outLastEqualPos)
{
	size_t pivotPos;
	T pivotKey;
	size_t lastLeftPos, lastEqualPos;
	partition(a, start, end, pivotPos, pivotKey, lastLeftPos, lastEqualPos);

	if ((lastLeftPos+1 < start+1 || lastLeftPos - start < rank) && lastEqualPos - start >= rank)
	{
		result = pivotKey;
		outLastLeftPos = lastLeftPos;
		outLastEqualPos = lastEqualPos;
	}
	else if (lastLeftPos+1 < start+1 || lastLeftPos - start < rank)
	{
		select(a, lastEqualPos + 1, end, rank - lastEqualPos + start - 1, result, outLastLeftPos, outLastEqualPos);
	}
	else
	{
		select(a, start, lastLeftPos, rank, result, outLastLeftPos, outLastEqualPos);
	}
	
}

template <typename T>
void mode(T *a, size_t start, size_t end, T &modeResult, size_t &mulResult)
{
	T median;
	size_t lastLeftPos, lastEqualPos;
	select(a, start, end, (end - start + 1) / 2, median, lastLeftPos, lastEqualPos);
	size_t medianMul = lastEqualPos - lastLeftPos;
	size_t leftMul = 0, rightMul = 0;
	T leftMode, rightMode;
	if (lastLeftPos + 1 > start + 1 && lastLeftPos - start >= medianMul)
	{
		mode(a, start, lastLeftPos, leftMode, leftMul);
	}
	if (end - lastEqualPos >= medianMul)
	{
		mode(a, lastEqualPos + 1, end, rightMode, rightMul);
	}
	if (rightMul >= leftMul && rightMul >= medianMul)
	{
		modeResult = rightMode;
		mulResult = rightMul;
	}
	else if (leftMul >= rightMul && leftMul >= medianMul)
	{
		modeResult = leftMode;
		mulResult = leftMul;
	}
	else
	{
		modeResult = median;
		mulResult = medianMul;
	}
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	ifstream f;
	ofstream fo;
	f.open("input.txt", ios::in);

	vector<int> x;
	int readInt;
	while (true)
	{
		f >> readInt;
		if (f.eof())
			break;
		x.push_back(readInt);
	}
	f.close();


	int modeResult;
	size_t mulResult;
	mode(&x[0], 0, x.size()-1, modeResult, mulResult);
	cout << "Mode: " << modeResult << endl;
	cout << "Multiplicity: " << mulResult << endl;
	for (auto p = x.cbegin(); p != x.cend(); p++)
	{
		cout << *p << " ";
	}
	cout << endl;

	fo.open("output.txt", ios::out);
	fo << modeResult << endl;
	fo << mulResult << endl;
	fo.close();

	return 0;
}