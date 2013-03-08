#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

int values[] = {1, 2, 5, 10, 20, 50, 100, 200};

int foo(int cur_cnt, int m = 0) {
	if (cur_cnt == 0) return 1;
	if (cur_cnt < 0) return 0;

	int res = 0;
	for (int i = m; i < 8; ++i) {
		res += foo(cur_cnt - values[i], i);
	}

	return res;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cout << foo(200);

	return 0;
}
