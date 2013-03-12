#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

bool is_prime(int x) {
	if (x < 2) return false;
	if (x == 2) return true;
	for (int i = 2; i < (int)sqrt((double)x) + 1; ++i) {
		if (x % i == 0) return false;
	}
	return true;
}

vector<int> get_primes(int biggest) {
	vector<int> res;
	for (int i = 2; i < biggest; ++i) {
		if (is_prime(i)) {
			res.push_back(i);
		}
	}
	return res;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	vector<int> primes = get_primes(1000000 + 100);

//	copy(primes.begin(), primes.end(), ostream_iterator<int> (cout, "\n"));

	int ans = 0;
	int d = -1;
	
	for (int i = 0; i < primes.size(); ++i) {
		cerr << i << endl;

		int sum = 0;
		for (int j = i; j < primes.size(); ++j) {
			sum += primes[j];

			if (sum < 1000000) {
				if (is_prime(sum)) {
					if (j - i > d) {
						d = j - i;
						ans = sum;
					}
				}
			} else {
				break;
			}
		}
	}
	cout << ans;

	return 0;
}
