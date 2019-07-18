#include <iostream>
#include <cstdio>
#define INF 987654321

using namespace std;

int map[501][501];	// 값 저장
int N, M;	// 학생 수, 비교 수
int connect[501];	// 연결되어 있는 수
int ans = 0;	// 키 순서를 제대로 알 수 있는 사람 수

void FW() {
	for (int k = 0; k < N; k++) {
		for (int from = 0; from < N; from++) {
			for (int to = 0; to < N; to++) {
				if (map[from][to] > map[from][k] + map[k][to]) {
					map[from][to] = map[from][k] + map[k][to];
				}
			}
		}
	}
}


int main(void) {
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = INF;
		}
	}

	for (int i = 0; i < M; i++) {
		int from, to;

		scanf("%d %d", &from, &to);
		from--; to--;	// 0부터 시작
		
		map[from][to] = 1;
	}

	FW();

	for (int from = 0; from < N; from++) {
		for (int to = 0; to < N; to++) {
			if (map[from][to] != INF) {
				connect[from]++; connect[to]++;	// 서로 연결되어 있음

				if (connect[from] == N - 1) ans++;
				if (connect[to] == N - 1) ans++;
			}
		}
	}

	printf("%d\n", ans);

	return 0;
}
