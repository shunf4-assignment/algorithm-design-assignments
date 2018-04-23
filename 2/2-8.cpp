#include <iostream>
#include <vector>
using namespace std;

size_t counter;

template<typename T>
void swapSubarrays(T * a, size_t &start, size_t &end, const size_t &k)
{
	static T swapSpc;
	static size_t i;
	if (k - start == end - k + 1)
	{
		for (i = start; i < k; i++)
		{
			swapSpc = a[i];
			a[i] = a[k + i - start];
			a[k + i - start] = swapSpc;
			counter++;
		}
	}
	else
	{
		if (k - start > end - k + 1)
		{
			for (i = k; i <= end; i++)
			{
				swapSpc = a[i - k + start];
				a[i - k + start] = a[i];
				a[i] = swapSpc;
				counter++;
			}
			start = end - k + start + 1;
			swapSubarrays(a, start, end, k);
		}
		else
		{
			for (i = start; i < k; i++)
			{
				swapSpc = a[i];
				a[i] = a[end - k + i + 1];
				a[end - k + i + 1] = swapSpc;
				counter++;
			}
			end = end + start - k;
			swapSubarrays(a, start, end, k);
		}
	}
}

int main()
{
	while (true)
	{
		vector< int> v = {};
		counter = 0;
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

		int k;
		cout << "Input k: ";
		cin >> k;
		size_t start = 0, end = v.size() - 1;
		swapSubarrays< int>(&v[0], start, end, k);

		for (auto vp = v.cbegin(); vp != v.cend(); vp++)
		{
			cout << *vp << " ";
		}
		cout << endl;
		cout << "Swap Time: " << counter << endl;

	}
	return 0;
}