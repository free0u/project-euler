#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

bool is_prime(int x) {
	if (x < 2) return false;
	if (x == 2) return true;
	for (int i = 2; i < (int)sqrt((double)x); ++i) {
		if (x % i == 0) return false;
	}
	return true;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);


	vector<int> v;
	for (int i = 1; i < 8; ++i) { // for 9 -> none
		v.push_back(i);
	}

	do {
		int x = 0;
		for (int i = 0; i < v.size(); ++i) {
			x = x * 10 + v[i];
		}
		if (is_prime(x)) {
			cout << x << endl;
		}
	} while (next_permutation(v.begin(), v.end()));

	return 0;
}
