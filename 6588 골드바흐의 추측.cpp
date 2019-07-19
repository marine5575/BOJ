#include <iostream>
#include <queue>
#include <vector>
#define MAX 1000001

using namespace std;
typedef pair<int, int> pii;

int n;
pii ans;
int num[MAX];

void findPrime() {
	// 모든 수 탐색
	for (int i = 2; i <= MAX; i++) {
		// 소수인가?
		if (num[i] == 0) {
			// 소수의 배수 표시
			for (int j = 2; i*j <= MAX; j++) {
				if (num[i*j] == 1) continue;	// 이미 표시한 곳인가?
				
				num[i*j] = 1;
			}
		}
	}
}

void findPair() {
	// 가장 차이가 큰 값을 뭘어봤음
	// 홀수인 두 소수의 합
	int left = 3, right = n - 3;

	// 가운데 지점까지만 보면 된다
	while (left <= right && left <= n / 2 && right >= n / 2) {
		// 원하는 값들인가? 소수들인가?
		if (n == left + right && num[left] == 0 && num[right] == 0) {
			printf("%d = %d + %d\n", n, left, right);
			return;
		}
		left++; right--;	// 합은 유지시켜야 됨
	}

	printf("Goldbach's conjecture is wrong.\n");	// 골드바흐의 추측은 틀렸음
}


int main(void) {
	findPrime();	// 소수 테이블 생성

	while (1) {
		scanf("%d", &n);

		if (n == 0) break;	// 종료 조건

		findPair();
	}

	return 0;
}
