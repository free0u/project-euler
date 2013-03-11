#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

#include "big_integer.h"

using namespace std;

big_integer pow(int x, int y) {
	big_integer res = 1;
	for (int i = 0; i < y; ++i) {
		res *= x;
	}

	return res;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int ans = -1;

	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 100; ++j) {
			cerr << i << "^" << j << endl;

			string s = to_string(pow(i, j));
			int sum = 0;
			for (int i = 0; i < s.length(); ++i) {
				sum += (s[i] - '0');
			}
			ans = max(ans, sum);
		}
	}

	cout << ans;

	return 0;
}
