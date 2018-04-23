#include <iostream>
#include <climits>
#include <vector>
using namespace std;

template<typename T>
void binarySearch_allowNotFound(T * a, size_t start, size_t end, const T& x, size_t &outI, size_t &outJ)
{
	if (start == end)
	{
		outI = outJ = (a[start] == x ? start : SIZE_MAX);
		return;
	}
	else if (start + 1 == end)
	{
		if (x == a[start])
		{
			outI = outJ = start;
			return;
		}
		else if (x == a[end])
		{
			outI = outJ = end;
			return;
		}
		else if (x < a[start])
		{
			outI = SIZE_MAX;
			outJ = start;
			return;
		}
		else if (x > a[end])
		{
			outI = end;
			outJ = SIZE_MAX;
			return;
		}
		else
		{
			outI = start;
			outJ = end;
			return;
		}
	}

	size_t mid = (start + end + 1) / 2;
	if (x == a[mid])
	{
		outI = outJ = mid;
		return;
	}
	else if (x < a[mid])
	{
		binarySearch_allowNotFound(a, start, mid, x, outI, outJ);
		return;
	}
	else
	{
		binarySearch_allowNotFound(a, mid, end, x, outI, outJ);
	}
}

int main()
{
	while (true)
	{
		vector< int> v = {};
		cout << "Input num for sequence, NaN for end: ";
		while (true)
		{
			int x;
			
			cin >> x;
			if (cin.good())
			{
				v.push_back(x);
				continue;
			}
			else {
				break;
			}
		}

		cin.clear();
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');

		int numForSearch;
		cout << "Input num for searching: ";
		cin >> numForSearch;
		size_t i, j;
		binarySearch_allowNotFound< int>(&v[0], 0, v.size() - 1, numForSearch, i, j);

		for (auto vp = v.cbegin(); vp != v.cend(); vp++)
		{
			cout << *vp << " ";
		}
		cout << endl;
		cout << "i = " << i << endl;
		cout << "j = " << j << endl;

		
	}
	return 0;
}