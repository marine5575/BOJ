#include <cstdio>
#define div 100000

using namespace std;

int map[101][101][2][2];	// map[i][j][0 or 1][0 or 1] : (i, j) 위치에 (북 or 동) 방향으로 (1번 or 두 번 이상) 움직여서 들어온 상태


int main(void) {
	int w, h;

	scanf("%d %d", &w, &h);

	for (int i = 1; i < w; i++) map[i][0][0][0] = 1;
	for (int i = 1; i < h; i++) map[0][i][1][0] = 1;

	for (int x = 1; x < w; x++) {
		for (int y = 1; y < h; y++) {
			map[x][y][0][0] = (map[x - 1][y][0][0] + map[x - 1][y][0][1]) % div;
			map[x][y][0][1] = map[x - 1][y][1][0];
			map[x][y][1][0] = (map[x][y - 1][1][0] + map[x][y - 1][1][1]) % div;
			map[x][y][1][1] = map[x][y - 1][0][0];
		}
	}

	int ans = map[w - 1][h - 1][0][0] + map[w - 1][h - 1][0][1] + map[w - 1][h - 1][1][0] + map[w - 1][h - 1][1][1];

	printf("%d\n", ans % div);

	return 0;
}
