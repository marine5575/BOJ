#include <stdio.h>
#include <stdlib.h>
#define MAX 35

typedef struct pt {
	int x, y, dir;
} pt;

int r, c;	// 유럽의 세로, 가로
int dx[] = { 1, 0, -1, 0 };	// right, down, left, up
int dy[] = { 0, 1, 0, -1 };
char map[MAX][MAX];
// out[i][0~3 or 4] = i번 가스관이 (연결되어 있는지 or 모양)
char out[8][5] = { {0, 1, 0, 1, '|'}, {1, 0, 1, 0, '-'}, {1, 1, 1, 1, '+'}, {1, 1, 0, 0, '1'},
							{1, 0, 0, 1, '2'}, {0, 0, 1, 1, '3'}, {0, 1, 1, 0, '4'} };
pt start;	// 시작 위치, 나가는 방향

void input_Data(void) {
	scanf("%d %d", &r, &c);

	int flag = 0;	// 모스크바 찾았는지 표시 깃발

	for (int j = 0; j < r; j++) {
		scanf("%s", map[j]);

		// 이미 모스크바 찾음
		if (flag) continue;

		for (int i = 0; i < c; i++) {
			// 모스크바 아님;
			if (map[j][i] != 'M') continue;

			pt tmp = { i, j, -1 };
			start = tmp;
			flag = 1;
			break;
		}
	}
}

void init(void) {
	// 모스크바 근처에 있는 가스관을 찾는 함수

	for (int i = 0; i < 4; i++) {
		int mx = start.x + dx[i];
		int my = start.y + dy[i];

		// 범위 확인
		if (mx < 0 || mx >= c || my < 0 || my >= r) continue;
		// 자그레브임 or 빈 칸임
		if (map[my][mx] == 'Z' || map[my][mx] == '.') continue;

		start.dir = i;
		break;
	}
}

inline int pipeToIdx(char c) {
	switch (c) {
	case '|': return 0;
	case '-': return 1;
	case '+': return 2;
	case '1': return 3;
	case '2': return 4;
	case '3': return 5;
	case '4': return 6;
	}
	return -1;
}

void found(int x, int y) {
	// (x, y)칸이 발견한 빈칸이었을 때, 가스관을 배치하는 함수

	char connected[4] = { 0, };	// 각 방향으로 나갈 수 있는지 확인하는 함수

	for (int i = 0; i < 4; i++) {
		int mx = x + dx[i];
		int my = y + dy[i];

		// 범위 확인 & 빈칸임
		if (mx < 0 || mx >= c || my < 0 || my >= r || map[my][mx] == '.') continue;
		
		int idx = pipeToIdx(map[my][mx]);	// 파이프 index
		// 들어갈 수 없는 파이프임
		if (!out[idx][i ^ 2]) continue;

		connected[i] = 1;
	}

	// 모든 모양에 대해서 일치하는지 살펴봄
	for (int i = 0; i < 7; i++) {
		int flag = 0;	// 불일치 확인 깃발

		for (int j = 0; j < 4; j++) {
			// 같음 => 통과
			if (out[i][j] == connected[j]) continue;

			flag = 1;
			break;
		}

		// 일치했음
		if (!flag) {
			printf("%d %d %c\n", y + 1, x + 1, out[i][4]);
			exit(0);
		}
	}
}

void dfs(int x, int y, int dir) {
	// 직전에 (x, y)에 들렸고, dir 방향으로 나감

	// 빈칸임
	if (map[y][x] == '.') {
		found(x, y);
		return;
	}

	int mx = x + dx[dir];
	int my = y + dy[dir];
	int idx = pipeToIdx(map[my][mx]);	// 다음 위치의 파이프 index
	int newDir = dir;	// 새로운 방향

	// 빈칸일 경우는 제외
	while (idx != -1) {
		// 다시 되돌아가는 것은 x & 나갈 수 있음
		if (newDir != (dir ^ 2) && out[idx][newDir] == 1) break;

		newDir = (newDir + 1) % 4;
		// 한 바퀴 다 돌았음
		if (newDir == dir) break;
	}

	dfs(mx, my, newDir);
}

void sol(void) {
	init();
	dfs(start.x, start.y, start.dir);
}


int main(void) {
	input_Data();
	sol();

	return 0;
}
