#include <iostream>
#include <cstdio>
#include <vector>
#define MAX 4000001

using namespace std;

int cnt = 0, n;	// 개수 카운트, 주어진 자연수
int num[MAX];	// 에라토스테네스 체망
vector<int> prime;	// 소수 모음


int main(void) {
	scanf("%d", &n);

	// 소수 찾기
	for (int i = 2; i <= n; i++) {
		if (num[i] == 0) {
			prime.push_back(i);	// 소수 찾으면 넣어 놓음

			for (int j = 2; i *j <= n; j++) {
				if (num[i*j] == 1) continue;

				num[i*j] = 1;
			}
		}
	}

	int left = 0, right = 0, ans = 0;	// 왼쪽, 오른쪽 포인터, 중간 합

	// 절대식: 왼쪽은 오른쪽보다 작거나 같음
	while (left <= right) {
		// 값이 크면 일단 갱신하고, left 오른쪽으로 옮김
		if (n <= ans) ans -= prime[left++];
		// 끝에 도달했으면 나가기
		else if (right == prime.size()) break;
		// 값이 작으면 일단 갱신하고, right 왼쪽으로 옮김
		else ans += prime[right++];

		// 최종적으로 결과 비교
		if (n == ans) cnt++;
	}

	printf("%d\n", cnt);

	return 0;
}
