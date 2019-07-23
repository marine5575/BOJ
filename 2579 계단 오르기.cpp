#include <cstdio>
#include <algorithm>

using namespace std;

int stair[301];	// 계단 점수
int dp[301];	// 여태까지의 가장 큰 경로 값


int main(void) {
	int n;	// 계단 수
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", stair + i);
	}

	// 이전에 계단 없었음
	dp[0] = stair[0];
	// 두번 밟는게 더 큰 가, 바로 밟는게 더 큰가?
	dp[1] = max(stair[0] + stair[1], stair[1]);
	// 0번을 밟고 올 것인가, 1번을 밟고 올 것인가?
	dp[2] = max(stair[0] + stair[2], stair[1] + stair[2]);

	for (int i = 3; i < n; i++) {
		// 맨 마지막 직전 계단을 밟는 경우 vs 밟지 않는 경우
		dp[i] = max(dp[i - 3] + stair[i - 1] + stair[i], dp[i - 2] + stair[i]);
	}

	printf("%d\n", dp[n - 1]);

	return 0;
}
