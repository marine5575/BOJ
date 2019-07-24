/*
D[i][S] = 1~i번째 앱까지만 활용하여 비활성화 비용의 합이 S일 때 확보할 수 있는 최대 메모리
D[i][S] = max(D[i-1][S], D[i-1][S-C[i]]+M[i])
ans = D[N][S]를 탐색하면서..?
*/


#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int mem[101];	// 메모리
int cost[101];	// 재실행시 걸리는 시간
int ans[101][10001];	// ans[i][j] : i까지 실행할 때 j의 재실행 시간을 가지는 총 메모리

int n;	// 앱 개수

int find(int i, int totCost) {
	if (i >= n) return 0;	// 범위 체크

	int &result = ans[i][totCost];

	// 이미 계산 했는가?
	if (result != -1) return result;

	result = find(i + 1, totCost);	// 최대 메모리 찾기(?)

	// 최소 시간이어야 하므로
	if (cost[i] <= totCost) {
		result = max(result, mem[i] + find(i + 1, totCost - cost[i]));	// 최대 메모리
	}

	return result;
}


int main(void) {
	int m;	// 필요한 메모리

	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		scanf("%d", mem + i);
	}

	for (int i = 0; i < n; i++) {
		scanf("%d", cost + i);
	}

	memset(ans, -1, sizeof(ans));

	int totCost = 0;	// 총 시간

	while (1) {
		// totCost를 가지면서 비울 수 있는 메모리
		if (find(0, totCost) >= m) {
			printf("%d\n", totCost);
			break;
		}
		totCost++;
	}

	return 0;
}
