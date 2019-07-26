#include <cstdio>
#include <algorithm>

using namespace std;

int mem[101], cost[101];	// mem[i] : i가 사용 중인 메모리 바이트, cost[i] : i를 재활성 시키는데 필요한 비용
int dp[10001];	// dp[cost] : 재활성화 비용이 cost일 때 확보할 수 있는 최대 메모리


int main(void) {
	int n, m, maxi;	// 활성화된 앱의 개수, 필요한 메모리, 최대 비용 저장
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) scanf("%d", mem + i);
	for (int i = 0; i < n; i++) {
		scanf("%d", cost + i);
		maxi += cost[i];	// 모든 비용을 다 더한 것이 최대 비용
	}

	// 모든 앱에 대해서 해봄
	for (int i = 0; i < n; i++) {
		// 최대 비용에서 하나씩 줄여서 마지막 앱 비용만 남기기
		for (int j = maxi; j >= cost[i]; j--) {
			// 현재 값과 i번째 앱을 비활성화 시키지 않았을 때의 메모리를 비교하여 최대값 저장
			dp[j] = max(dp[j], dp[j - cost[i]] + mem[i]);
		}
	}

	int mini;	// 어떤 값이 최소 비용인가
	for (mini = 0; mini < maxi && dp[mini] < m; mini++);

	printf("%d\n", mini);

	return 0;
}
