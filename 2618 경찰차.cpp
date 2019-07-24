#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>  // abs 함수

using namespace std;
typedef pair<int, int> pii;

int dp[1001][1001];  // dp[x][y] : 1번 경찰차가 x번, 2번 경찰차가 y번 사건을 맡을 때 걸린 거리의 최소 합
vector<pii> arr;  // 사건들
int w;  // 사건 수

int dist(int x1, int x2, int y1, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

// 1번 경찰차가 최근에 맡은 사건 번호 : x
// 2번 경찰차가 최근에 맡은 사건 번호 : y
int solve(int x, int y) {
	int &result = dp[x][y];  // 최소 거리합 저장

        // 예전에 이미 저장했었나?
	if (result != -1) return result;

	int next = max(x, y) + 1;  // 현재 사건 번호. 1, 2번 경찰차 중 하나는 직전 사건 맡음

        // 0, 1번 사건은 초기 상태
        // 그래서 사실 사건 번호 전체적으로 2개씩 밀림
	if (next > w + 1) return 0;

        //
	int x1 = arr[x].first, x2 = arr[y].first, x3 = arr[next].first;
	int y1 = arr[x].second, y2 = arr[y].second, y3 = arr[next].second;

	return result = min(solve(next, y) + dist(x1, x3, y1, y3), solve(x, next) + dist(x2, x3, y2, y3));
}

void get(int car1, int car2) {
	int next = max(car1, car2) + 1;

	if (next > w + 1) return;

	int x1 = arr[car1].first, x3 = arr[next].first;
	int y1 = arr[car1].second, y3 = arr[next].second;

	if (dp[next][car2] == -1) dp[next][car2] = 0;
	if (dp[car1][next] == -1) dp[car1][next] = 0;

	if (dp[car1][car2] == dp[next][car2] + dist(x1, y1, x3, y3)) {
		printf("1\n");
		get(next, car2);
	}
	else {
		printf("2\n");
		get(car1, next);
	}
}


int main(void) {
	int n;
	scanf("%d", &n);
	scanf("%d", &w);
	
	arr.push_back({1, 1});
	arr.push_back({n, n});

	for (int i = 0, a, b; i < w; i++) {
		scanf("%d %d", &a, &b);
		arr.push_back({a, b});
	}

	memset(dp, -1, sizeof(dp));

	printf("%d\n", solve(0, 1));

	get(0, 1);

	return 0;
}
