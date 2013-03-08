#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int max_cicle = -1;
int ans_d = -1;

string mydiv(int x) {
	string res = "";

	int a = 1;

	for (int i = 0; i < 2000; ++i) {
		a *= 10;
	
		int d = a / x;
		res += (char)(d + '0');


		a = a - d * x;
	}

	return res;
}


bool is_period(string const& s, int pos_start, int len) {

	if (pos_start + len >= s.length() - 1) return false;

	for (int start = pos_start; start < s.length(); start += len) {
		bool f = true;

		for (int i = 0; i < len; ++i) {
			if (start + i + len < s.length()) {
				if (s[start + i] != s[start + i + len]) {
					f = false;
					break;
				}
			}
		}

		if (!f) {
			return false;
		}
	}

	return true;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);


	int max_d = -1;
	int ans = -1;

	for (int tt = 2; tt < 1000; ++tt) {
		cerr << tt << endl;
		string r = mydiv(tt);
		bool zero_in_end = true;
		for (int i = r.size() - 10; i < r.size(); ++i) {
			if (r[i] != '0') {
				zero_in_end = false;
			}
		}
		if (zero_in_end) continue;

		for (int start = 0; start < r.length(); ++start) {
			for (int len = 1; len < r.length(); ++len) {
				if (is_period(r, start, len)) {
					if (len > 1500) continue;
					if (len > max_d) {
						max_d = len;
						ans = tt;
					}
					break;
				}
			}
		}
	}



	cout << ans << endl;
	cout << max_d;

	cout << endl;
	cout << mydiv(ans);
	
	return 0;
}
