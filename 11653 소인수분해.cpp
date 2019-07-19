#include <iostream>

using namespace std;

int n;	// 입력값


int main(void) {
	scanf("%d", &n);

	// 일일이 걍 찾기
	for (int i = 2; i * i <= n; i++) {
		// 나누어 지면 그냥 계속 나누기
		while (n % i == 0) {
			printf("%d\n", i);
			n /= i;
		}
	}

	// 안 나눠졌을 경우
	if (n > 1) printf("%d\n", n);

	return 0;
}
