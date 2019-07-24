#include <cstdio>
#include <algorithm>

using namespace std;

int sum[1001];	// 지금까지의 카드 합
int dp[1001][1001];	// dp[i][j] : j번째까지 i장의 카드로 얻는 점수


int main(void) {
	int t;	// 테스트 케이스 개수
	scanf("%d", &t);

	while (t--) {
		int n;	// 카드 개수
		scanf("%d", &n);

		// 모든 카드에 대해서 카드 합
		for (int i = 1; i <= n; i++) {
			scanf("%d", sum + i);
			sum[i] += sum[i - 1];
		}

		// i장 가지고 있을 때
		for (int i = 1; i <= n; i++) {
			// j번째까지
			for (int j = n; j >= i; j--) {
				// j번째까지 i장 가지고 있을 때의 최선의 점수
				// 현재 가질 수 있는 모든 카드들의 합 - 명우가 최선의 전략을 택했지만 점수가 더 작은 걸 택할 때
				dp[i][j] = sum[j] - sum[j - i] - min(dp[i - 1][j - 1], dp[i - 1][j]);
			}
		}

		// n번째까지 n장 가지고 있을 때의 최선의 점수
		printf("%d\n", dp[n][n]);
	}

	return 0;
}
