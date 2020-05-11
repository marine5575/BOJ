/************************************/
// BOJ 2206 벽 부수고 이동하기
// 핵심: BFS & 경험 배열의 의미
/************************************/
#include <stdio.h>
#include <queue>
#define MAX 1010

using namespace std;

typedef struct pt {
	int x, y, t, flag;	// 위치(x, y), 여기까지 걸린 시간, 망치 사용 여부
} pt;

int n, m;	// 지도의 세로, 가로
int dx[] = { 1, 0, -1, 0 };	// right, down, left, up
int dy[] = { 0, 1, 0, -1 };
char map[MAX][MAX];
char visited[MAX][MAX][2];	// visited[y][x][0 or 1] = (x, y)에 망치를 (사용하지 않고 or 사용하고) 도착했음

void input_Data(void) {
	scanf("%d %d", &n, &m);

	for (int j = 1; j <= n; j++) {
		scanf("%s", &map[j][1]);
	}
}

int bfs(void) {
	// (1, 1)에서 출발해서 (m, n)까지 가는 함수

	queue<pt> q;
	pt init = { 1, 1, 1, 0 };
	q.push(init);
	visited[1][1][0] = 1;

	while (!q.empty()) {
		pt cur = q.front(); q.pop();	// 현재 위치

		// 도착 지점이 (1, 1)일 수도 있음
		if (cur.x == m && cur.y == n) return cur.t;

		for (int i = 0; i < 4; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];

			// 범위 체크
			if (!map[my][mx]) continue;
			// 이미 망치를 사용했음 & 이미 경험함
			if (cur.flag && visited[my][mx][cur.flag]) continue;
			// 도착했음
			if (mx == m && my == n) return cur.t + 1;

			// 갈 수 있는 곳 & 아직 경험하지 않음
			if (map[my][mx] == '0' && !visited[my][mx][cur.flag]) {
				pt tmp = { mx, my, cur.t + 1, cur.flag };
				q.push(tmp);
				visited[my][mx][cur.flag] = 1;
			}
			// 아직 망치 사용 x & 벽 & 아직 경험하지 않음
			if (!cur.flag && map[my][mx] == '1' && !visited[my][mx][1]) {
				pt tmp = { mx, my, cur.t + 1, 1 };
				q.push(tmp);
				visited[my][mx][1] = 1;
			}
		}
	}

	return -1;
}


int main(void) {
	input_Data();
	printf("%d\n", bfs());

	return 0;
}
