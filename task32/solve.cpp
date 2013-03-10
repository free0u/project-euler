#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> nums(int x) {
	vector<int> res;
	while (x) {
		res.push_back(x % 10);
		x /= 10;
	}
	return res;
}

bool is_pan(int a, int b, int c) {
	vector<int> v, t;
	
	t = nums(a);
	v.insert(v.end(), t.begin(), t.end());

	t = nums(b);
	v.insert(v.end(), t.begin(), t.end());

	t = nums(c);
	v.insert(v.end(), t.begin(), t.end());


	vector<int> cnt(10);

	for_each(v.begin(), v.end(), [&cnt] (int x) {
		++cnt[x];
	});
	
	for (int i = 1; i < 10; ++i) {
		if (cnt[i] != 1) return false;
	}
	return cnt[0] == 0;
}

bool product_is_pan(int x) {
	for (int i = 1; i <= x; ++i) {
		int j = x / i;
		if (i * j == x) {
			if (is_pan(i, j, x)) {
				return true;
			}
		}
	}
	return false;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int sum = 0;
	for (int i = 1; i < 100000; ++i) {
		cerr << i << endl;
		if (product_is_pan(i)) {
			cout << i << endl;
			sum += i;
		}
	}

	cout << endl << sum;

	return 0;
}
