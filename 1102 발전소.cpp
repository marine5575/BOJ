#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>
#define INF 987654321

using namespace std;

int w[17][17];	// w[i][j] : 발전소 i가 j를 켤 때 걸리는 시간
int dp[17][1 << 17];	// dp[i][state] : i번째 들렀을 때 state 상태였다면 들어간 최소 비용
int n, p, bit = 0;	// 발전소 수, 켜져 있어야 하는 최소 발전소, 현재 발전소 상태

int TSP(int i, int visited) {
	int num = 0, tmp = visited;	// 켜져 있는 수, 상태

	// 켜져 있는 수 세기
	while (tmp != 0) {
		num += tmp & 1;
		tmp >>= 1;
	}

	// 켜져 있는 수가 우리가 원하는 값 이상
	if (num >= p) return 0;

	int &result = dp[i][visited];	// 최소 비용

	// 이미 값이 있을 때
	if (result != -1) return result;

	result = INF;

	// 모든 발전소에 대해서 실행
	for (int k = 0; k < n; k++) {
		// 켜져 있을 경우 PASS
		if (visited & (1 << k)) continue;

		int nextV = visited | (1 << k);	// 이번에 들린 곳 켜줌

		// 다른 발전소 찾기
		for (int next = 0; next < n; next++) {
			// 다음에 들릴 곳이 이미 켜져 있을 때
			if (nextV & (1 << next)) {
				// 최소값으로 갱신
				result = min(result, TSP(next, nextV) + w[i][k]);
			}
		}
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

	string s;

	cin >> s;
	scanf("%d", &p);

	// 원하는 값이 없을 때
	if (p == 0) {
		printf("0\n");
		return 0;
	}

	// 켜져 있는 곳 체크
	for (int i = 0; i < n; i++) {
		if (s[i] == 'Y') {
			bit |= (1 << i);
		}
	}

	// 초기화
	memset(dp, -1, sizeof(dp));

	int ans = INF;

	// 모든 켜져 있는 곳을 시작점으로 해봄
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 'Y') {
			ans = min(ans, TSP(i, bit));
		}
	}

	ans != INF ? printf("%d\n", ans) : printf("-1\n");

	return 0;
}
