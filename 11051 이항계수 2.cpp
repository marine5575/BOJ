#include <cstdio>

using namespace std;


int main(void) {
	int n, k;	// 전체 개수, 뽑는 개수
	int DP[1001][1001] = { 0 };	// 배열

	scanf("%d %d", &n, &k);

	// 전체 개수는 1 이상
	for (int i = 1; i <= n; i++) {
		// 뽑는 개수는 0 이상
		for (int j = 0; j <= n; j++) {
			// 모두 뽑는가? 아예 뽑지 않는가?
			if (i == j || j == 0) {
				DP[i][j] = 1;
				continue;
			}

			DP[i][j] = (DP[i - 1][j - 1] + DP[i - 1][j]) % 10007;	// 파스칼의 삼각형
		}
	}

	printf("%d\n", DP[n][k]);

	return 0;
}
