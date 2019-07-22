#include <cstdio>

using namespace std;


int main(void) {
	int n, k, nu = 1, den = 1;	// 자연수, 정수, 분자, 분모

	scanf("%d %d", &n, &k);

	for (int i = k; i > 0; i--) {
		nu *= n--;
		den *= i;
	}

	printf("%d\n", nu / den);

	return 0;
}
