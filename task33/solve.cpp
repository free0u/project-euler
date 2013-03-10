#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int gen_num(vector<int> const& nums, int pos) {
	int res = 0;
	for (int i = 0; i < nums.size(); ++i) {
		if (i == pos) continue;
		res = res * 10 + nums[i];
	}

	return res;
}

bool equal(int a, int b, int x, int y) {
	double r1 = (double)a / b;
	double r2 = (double)x / y;

	return abs(r1 - r2) < 1e-6;
}

bool is_curious(int a, int b) {
	int save_a = a, save_b = b;


	vector<int> a_num, b_num;
	while (a) {
		a_num.push_back(a % 10);
		a /= 10;
	}
	reverse(a_num.begin(), a_num.end());

	while (b) {
		b_num.push_back(b % 10);
		b /= 10;
	}
	reverse(b_num.begin(), b_num.end());

	for (int i = 0; i < a_num.size(); ++i) {
		for (int j = 0; j < b_num.size(); ++j) {
			if (a_num[i] != b_num[j]) continue;
			int x = gen_num(a_num, i);
			int y = gen_num(b_num, j);

			if (save_a % 10 == 0 && save_b % 10 == 0) continue;
			if (equal(save_a, save_b, x, y)) {
				//printf("%d/%d == %d/%d\n", save_a, save_b, x, y);
				return true;
			}
		}
	}

	return false;

}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int a, b;
	a = b = 1;
	for (int i = 10; i < 100; ++i) {
		for (int j = i + 1; j < 100; ++j) {
			if (is_curious(i, j)) {
				a *= i;
				b *= j;
			}
		}
	}
	cout << a << " " << b << endl;
	
	while (true) {
		bool fl = false;
		for (int i = 2; i <= a; ++i) {
			if (a % i == 0 && b % i == 0) {
				a /= i;
				b /= i;
				fl = true;
				break;
			}
		}
		if (!fl) break;
	}
	cout << a << " " << b << endl;

	return 0;
}
