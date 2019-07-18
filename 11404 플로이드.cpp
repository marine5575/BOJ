#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int N, M;	// 도시, 버스 개수
int map[101][101];	// map[from][to] = 거리

//void init() {
//
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++) {
//			if (i == j) map[i][i] = 0;
//			else map[i][j] = INF;
//		}
//	}
//}

void FW() {
	// 모든 경유지에 대해
	for (int k = 0; k < N; k++) {
		// 모든 출발점에 대해
		for (int from = 0; from < N; from++) {
			if (map[from][k] == 0) continue;	// 갈 수 없음

			// 모든 도착점에 대해
			for (int to = 0; to < N; to++) {
				if (map[k][to] == 0 || from == to) continue;	// 갈 수 없음

				// 아직 안 들렀거나, 이전게 더 값이 클 때
				if (map[from][to] == 0 || map[from][to] > map[from][k] + map[k][to])
					map[from][to] = map[from][k] + map[k][to];
			}
		}
	}
}


int main(void) {
	scanf("%d", &N);
	scanf("%d", &M);

	for (int i = 0; i < M; i++) {
		int from, to, w;

		scanf("%d %d %d", &from, &to, &w);
		from--; to--;	// 0부터 시작

		if(!map[from][to]) map[from][to] = w;	// 안 들렀으면 값으로 갱신
		else map[from][to] = min(map[from][to], w);	// 들렀으면 더 작은 값으로 갱신
	}

	FW();	// 구하기

	for (int from = 0; from < N; from++) {
		for (int to = 0; to < N; to++) {
			printf("%d ", map[from][to]);
		}
		printf("\n");
	}

	return 0;
}
