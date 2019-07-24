#include <cstdio>
#include <algorithm>
#define INF 9876546321

using namespace std;

int dp[201][201];	// dp[i][j] : i번째부터 j번째까지 색을 바꾼 횟수
int arr[201];	// input


int main(void) {
	int n, h;	// 전구의 수, 색의 수
	scanf("%d %d", &n, &h);

	// 전구의 수만큼
	for (int i = 0; i < n; i++) {
		scanf("%d", arr + i);

		// 0 ~ 입력 받은 값까지의 횟수 살펴봄
		for (int j = i - 1; j >= 0; j--) {
			// 초기화
			dp[j][i] = INF;

			// k로 나눠서 각각 횟수 살펴봄
			for (int k = j - 1; k < i; k++) {
				// 더 작은 값으로 갱신
				dp[j][i] = min(dp[j][i], dp[j][k] + dp[k + 1][i] + (arr[j] != arr[k + 1]));
			}
		}
	}

	printf("%d\n", dp[0][n - 1]);

	return 0;
}
