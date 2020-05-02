/******************************/
// <<< 투포인터 개념을 처음 봄 >>>
//	BOJ 2842 집배원 한상덕
// 핵심: DFS / BFS + 투 포인터
//			 => 범위를 구하는 것은 같은 위치에서 출발해서
//					될 때까지 e++, 그 후에는 안 될 때까지 s++ 하는 것을 반복
/******************************/
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#define MAX 60
#define INF ((int)1e6 + 1)

using namespace std;

typedef struct pt {
	int x, y;
} pt;

int n, kNum, maxH;	// 마을 크기, 집의 개수, 꼭 가야하는 곳의 가장 높은 고도
int height[MAX][MAX];	// 고도
int dx[] = { 1, 1, 0, -1, -1, -1, 0, 1 };	// 오른쪽부터 시계 방향
int dy[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
char map[MAX][MAX];
pt start;	// 우체국 위치
vector<int> cand;	// 고도 set

void input_Data(void) {
	scanf("%d", &n);

	for (int j = 0; j < n; j++) {
		scanf("%s", map[j]);

		for (int i = 0; i < n; i++) {
			// 우체국일 때
			if (map[j][i] == 'P') {
				pt tmp = { i, j };
				start = tmp;
			}
			// 집일 때
			else if (map[j][i] == 'K') {
				kNum++;
			}
		}
	}
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &height[j][i]);
			cand.push_back(height[j][i]);

			// 집이나 우체국일 때 => 꼭 가야하는 곳의 가장 높은 고도 저장
			if (map[j][i] == 'P' || map[j][i] == 'K') {
				if (maxH < height[j][i]) maxH = height[j][i];
			}
		}
	}
}

inline int check(int x, int y, int s, int e) {
	// 갈 수 있는 곳이면 1 반환, 아니면 0 반환

	return s <= height[y][x] && height[y][x] <= e;
}

int bfs(int s, int e) {
	// start부터 갈 수 있는 모든 곳(s ~ e 사이 고도)을 가는 함수. 만난 집의 개수 반환

	// 우체국도 못가는 곳이면 바로 반환
	if (!check(start.x, start.y, s, e)) return 0;

	int cnt = 0;	// 갈 수 있는 집의 개수
	char visited[MAX][MAX] = { 0, };
	queue<pt> q;
	q.push(start);
	visited[start.y][start.x] = 1;

	while (!q.empty()) {
		pt cur = q.front(); q.pop();	// 현재 위치

		for (int i = 0; i < 8; i++) {
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];

			// 범위 확인 & 이미 들린 곳
			if (mx < 0 || mx >= n || my < 0 || my >= n || visited[my][mx]) continue;
			// 갈 수 없는 곳
			if (!check(mx, my, s, e)) continue;

			// 집 도착
			if (map[my][mx] == 'K') cnt++;

			pt tmp = { mx, my };
			q.push(tmp);
			visited[my][mx] = 1;
		}
	}

	return cnt;
}

int find_Max_Idx(void) {
	// 최고 고도를 가진 곳의 idx를 반환

	int idx = 0;	// 최고 고도를 가진 곳의 idx

	for (int i = 0; i < cand.size(); i++) {
		// 최고 고도인 곳
		if (maxH == cand[i]) idx = i;
	}

	return idx;
}

int sol(void) {
	sort(cand.begin(), cand.end());
	cand.erase(unique(cand.begin(), cand.end()), cand.end());

	int s = 0, e = find_Max_Idx(), fatigue = 0;	// 최소 높이, 최고 높이, 가장 작은 피로도

	while (s <= e && e < cand.size()) {
		int num = bfs(cand[s], cand[e]);	// 만난 집의 개수

		// 모든 집을 다 돌았음 => 갈 수 있음
		if (num >= kNum) {
			// 피로도 최소값 갱신
			if (!fatigue || fatigue > cand[e] - cand[s]) fatigue = cand[e] - cand[s];
			s++;
		}
		// 갈 수 없음
		else e++;
	}

	return fatigue;
}


int main(void) {
	input_Data();

	printf("%d\n", sol());

	return 0;
}
