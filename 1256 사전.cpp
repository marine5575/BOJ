#include <cstdio>
#include <algorithm>
#define MAX 2000000000

using namespace std;

int DP[201][201];


int main(void) {
	int n, m, k;	// a 개수, z 개수, 찾는 순서

	scanf("%d %d %d", &n, &m, &k);

	// 파스칼의 삼각형
	for (int i = 0; i <= 200; i++) {
		DP[i][0] = 1;

		for (int j = 1; j <= i; j++) {
			DP[i][j] = min(DP[i - 1][j] + DP[i - 1][j - 1], (int)1e9);	// 어차피 k번째는 1e9까지만 존재
		}
	}

	int sum = n + m;	// 미리 저장

	// 문자열 경우의 수가 더 작은가?
	if (k > DP[sum][n]) printf("-1");
	else {
		// 문자열 크기
		for (int i = 0; i < sum; i++) {
			// 'a'가 앞에 올 경우의 수가 k보다 작은가?
			if (DP[n + m - 1][m] < k) {
				printf("z");
				k -= DP[n + m - 1][m];	// 'z'가 앞에 올 경우의 수
				m--;
			}
			else {
				printf("a");
				n--;
			}
		}
	}
	printf("\n");


	return 0;
}
