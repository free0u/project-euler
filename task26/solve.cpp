#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

string mydiv(int x) {
	string res = "";
	
	int a = 1;
	for (int i = 0; i < 20; ++i) {
		a *= 10;
	
		int d = a / x;
		res += (char)(d + '0');
		a = a - d * x;
	}

	return res;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	for (int i = 2; i <= 10; ++i) {
		string r = mydiv(i);
	}

	return 0;
}
