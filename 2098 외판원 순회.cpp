#include <cstdio>
#include <algorithm>
#include <cstring>
#define INF 987654321

using namespace std;

int w[17][17];	// w[i][j] : i에서 j로 갈 때 드는 비용. 대칭 x
int dp[17][1 << 17];	// dp[i][visited] : i까지 오는데 visited (2진수)를 들리면서 들었던 비용
int n;	// 도시 개수

int TSP(int i, int visited) {
	// 모두 들렀을 때
	if (visited == (1 << n) - 1) {
		// 시작점으로 갈 수 있는가?
		if (w[i][0] != 0) return w[i][0];

		return INF;
	}

	int &result = dp[i][visited];

	// 이미 들렀었다면 그 비용 반환
	if (result != -1) return result;

	result = INF;

	// 모든 도시에 대해서 다 해봄
	for (int next = 0; next < n; next++) {
		// 이미 들렀거나, 갈 수 없는 곳이면 PASS
		if (visited & (1 << next) || w[i][next] == 0) continue;

		// 다음 노드로부터 나오는 경로 최소 비용 + 이곳에서 다음 노드까지의 비용
		int cand = TSP(next, visited | (1 << next)) + w[i][next];

		// 최솟값 갱신
		result = min(cand, result);
	}

	return result;
}


int main(void) {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &w[i][j]);
		}
	}

	// 초기화
	memset(dp, -1, sizeof(dp));

	// 1번 도시에서 시작
	printf("%d\n", TSP(0, 1));

	return 0;
}
