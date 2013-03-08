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
	int sq = sqrt(double(x)) + 1;
	for (int i = 2; i <= sq; ++i) {
		if (x % i == 0) return false;
	}
	return true;
}

int make_num(vector<int> const& a, int pos_start, int pos_end) {
	int res = 0;
	for (int i = pos_start; i <= pos_end; ++i) {
		res = res * 10 + a[i];
	}
	return res;
}

bool is_truncatable(int x) {
	vector<int> a;
	while(x) {
		a.push_back(x % 10);
		x /= 10;
	}
	reverse(a.begin(), a.end());

	for (int i = 0; i < a.size(); ++i) {
		int x = make_num(a, i, a.size() - 1);
		if (!is_prime(x)) 
			return false;		
	}
	for (int i = 0; i < a.size(); ++i) {
		int x = make_num(a, 0, i);
		if (!is_prime(x)) 
			return false;		
	}

	return true;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int res = 0;
	int cnt = 0;
	for (int i = 8;; ++i) {
		if (is_truncatable(i)) {
			res += i;

			if (++cnt == 11) break;
		}
	}
	cout << res;

	return 0;
}
