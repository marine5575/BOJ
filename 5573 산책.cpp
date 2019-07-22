#include <cstdio>

using namespace std;

int map[1001][1001];	// 상태
int count[1001][1001];	// 몇 번 상태가 바뀌는가

/*
map[i][j] = map[i-1][j] + map[i][j-1]이므로 greedy하게 풀 수 없음
greedy하게 풀게 되면 안쪽 노드가 업데이트 되어 있지 않아서 오류가 생김
*/


int main(void) {
	int h, w, n;

	scanf("%d %d %d", &h, &w, &n);	// 높이, 넓이, 찾는 순서

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			scanf("%d", &map[y][x]);
		}
	}

	count[0][0] += n - 1;	// n번째 경로 이전에 n-1번 들렀음

	// 모든 노드에 대해서 수행
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			// 아직 한 번도 들리지 않은 경우
			if (count[y][x] == 0) continue;

			// 이전 경로에서 들렀던 반절만큼 다음 경로로 감
			count[y + 1][x] += count[y][x] / 2;
			count[y][x + 1] += count[y][x] / 2;

			// 홀수번 들렀는가?
			if (count[y][x] % 2) {
				// 오른쪽으로 가는 상태인가? 아닌가?
				if (map[y][x] == 1) count[y][x + 1]++;
				else count[y + 1][x]++;
			}

			// 상태 업데이트
			map[y][x] = (map[y][x] + count[y][x]) % 2; 
		}
	}

	int x = 0, y = 0;

	// 마지막 경로를 따라가봄
	while (x < w && y < h) {
		if (map[y][x] == 1) x++;
		else y++;
	}

	printf("%d %d\n", y + 1, x + 1);

	return 0;
}
