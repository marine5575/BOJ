/**********************/
// BOJ 2589 보물섬
// 핵심: BFS + 중간에 있는거 가지치기
/**********************/
#include <stdio.h>
#include <queue>
#define MAX 60

using namespace std;

typedef struct pt {
	int x, y, t;
} pt;

int h, w;	// 지도의 세로, 가로
int dx[] = { 1, 0, -1, 0 };	// right, down, left, up
int dy[] = { 0, 1, 0, -1 };
char map[MAX][MAX];

void input_Data(void) {
	scanf("%d %d", &h, &w);

	for (int j = 1; j <= h; j++) {
		scanf("%s", &map[j][1]);
	}
}

int bfs(int x, int y) {
	// start에서 시작해서 모든 곳을 가면서 가장 먼 곳까지의 거리 반환

	char visited[MAX][MAX] = { 0, };
	int dist = 0;	// 최대 거리
	queue<pt> q;
	pt init = { x, y, 0 };
	q.push(init);
	visited[y][x] = 1;

	while (!q.empty()) {
		pt cur = q.front(); q.pop();	// 현재 위치

		// 최대 거리 갱신
		if (dist < cur.t) dist = cur.t;

		for (int i = 0; i < 4; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];

			// 범위 확인
			if (mx <= 0 || mx > w || my <= 0 || my > h) continue;
			// 바다 or 이미 경험함
			if (map[my][mx] != 'L' || visited[my][mx]) continue;

			pt tmp = { mx, my, cur.t + 1 };
			q.push(tmp);
			visited[my][mx] = 1;
		}
	}

	return dist;
}

int sol(void) {
	int dist = 0;	// 최단 거리

	for (int j = 1; j <= h; j++) {
		for (int i = 1; i <= w; i++) {
			// 바다
			if (map[j][i] != 'L') continue;
			// 중간임 => 가지치기
			if (map[j][i - 1] == 'L' && map[j][i + 1] == 'L') continue;
			if (map[j - 1][i] == 'L' && map[j + 1][i] == 'L') continue;

			int result = bfs(i, j);

			// 최단 거리 갱신
			if (dist < result) dist = result;
		}
	}

	return dist;
}


int main(void) {
	input_Data();
	printf("%d\n", sol());

	return 0;
}
