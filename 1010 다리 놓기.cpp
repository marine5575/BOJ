#include <cstdio>

using namespace std;

int DP[31][31];	// x에서 y로 가는 경우의 수


int main(void) {
	int t;	// 테스트 케이스

	scanf("%d", &t);

	while (t--) {
		int n, m;	// 서쪽 사이트, 동쪽 사이트

		scanf("%d %d", &n, &m);

		// 동쪽 사이트의 갯수는 1개 이상
		for (int i = 1; i <= m; i++) {
			// 서쪽 사이트의 개수는 0개 이상
			for (int j = 0; j <= n; j++) {
				// 모두 고르거나, 아무것도 안 고를 때
				if (i == j || j == 0) {
					DP[i][j] = 1;
					continue;
				}

				DP[i][j] = DP[i - 1][j - 1] + DP[i - 1][j];	// 파스칼의 삼각형
			}
		}

		printf("%d\n", DP[m][n]);
	}


	return 0;
}
