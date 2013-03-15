#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

bool is_sqr(int x) {
 	double s = sqrt((double)x);
	return abs(((int)s) - (s)) < 1e-6;
}

bool is_prime(int x) {
	if (x < 2) return false;
	if (x == 2) return true;
	for (int i = 2; i < sqrt((double)x) + 1; ++i) {
		if (x % i == 0) return false;
	}
	return true;
}

vector<int> primes;

bool is_g(int x) {
	for (int i = 1; i < primes.size(); ++i) {
		int t = (x - primes[i]) / 2;
		if (is_sqr(t)) {
			return true;
		}
	}
	return false;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	for (int i = 0; primes.size() < 1000; ++i) {
		if (is_prime(i)) {
			primes.push_back(i);
		}
	}

	for (int i = 3; ; i += 2) {
		cerr << i << endl;
		if (is_prime(i)) continue;

		if (!is_g(i)) {
			cout << i << endl;
			break;
		}
	}

	return 0;
}
