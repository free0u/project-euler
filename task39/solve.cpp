#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

template<typename T>
inline T sqr(T x) {
	return x * x;
}

int cnt(int x) {
	int res = 0;
	for (int a = 1; a < x; ++a) {
		for (int b = 1; b < x; ++b) {
			int c = x - a - b;
			if (c < 1) continue;

			if (sqr(a) == sqr(b) + sqr(c) ||
				sqr(b) == sqr(a) + sqr(c) ||
				sqr(c) == sqr(a) + sqr(b)) {
				++res;
			}
		}
	}

	return res / 6;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int ans = -1;
	for (int i = 1; i < 1000; ++i) {
		cerr << i << endl;
		ans = max(ans, cnt(i));

		if (ans == 8) cout << i << endl;
	}
	cout << ans;

	return 0;
}
