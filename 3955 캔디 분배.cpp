#include <iostream>
#include <cstdio>
#include <string>
#define MAX 1000000000

using namespace std;
typedef long long ll;


int main(void) {
	int t;

	scanf("%d\n", &t);

	for (int i = 0; i < t; i++) {
		int c;
		string k;

		cin >> k >> c;

		int tmp = 0;

		for (int j = 0; j < k.size(); j++) {
			int at = k[j] - '0';
			tmp *= 10;
			at %= c;
			tmp += at;

			if (tmp >= c) tmp %= c;
		}

		if (tmp == 0) {
			printf("IMPOSSIBLE\n");
			continue;
		}

		for (int j = 0; j < MAX; j++) {

		}
	}

	return 0;
}
