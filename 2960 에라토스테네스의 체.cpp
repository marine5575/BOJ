#include <iostream>
#include <cstdio>

using namespace std;

int num[1002];	// 지웠는지 확인할 배열
int N, K, cnt;	// 최대 숫자, 찾는 순서, 지금이 몇 번째인지 찾을 것

int findPrime() {
	// 2부터 찾아봄
	for (int i = 2; i <= N; i++) {
		// 지우지 않은 수인가?
		if (num[i] == 0) {
			// 모든 배수에 대해서 지움
			for (int j = 1; i*j <= N; j++) {
				if (num[i * j] == 1) continue;	// 혹시 배수가 이전에 지워졌나?

				num[i * j] = 1;
				cnt++;

				// k번째 도달했나?
				if (cnt == K) return i * j;
			}
		}
	}
}


int main(void) {
	scanf("%d %d", &N, &K);

	int num = findPrime();	// k번째 지운 값

	printf("%d\n", num);

	return 0;
}
