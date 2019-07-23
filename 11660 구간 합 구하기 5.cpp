#include <cstdio>

using namespace std;
typedef long long ll;

ll arr[1025][1025];	// 계산 값 저장
ll mem[1025][1025];	// 원래 값 저장


int main(void) {
	int n, m, i1, j1, i2, j2;	// 표의 크기, 구해야 하는 횟수, (i1, j1), (i2, j2)

	scanf("%d %d", &n, &m);

	// 줄 번호
	for (int i = 0; i < n; i++) {
		// 칸 번호
		for (int j = 0; j < n; j++) {
			scanf("%d", &arr[i][j]);
			mem[i][j] = arr[i][j];	// 미리 저장

			// 시작점일 경우
			if (i == 0 && j == 0) continue;

			// 첫째 줄
			if (i == 0) arr[i][j] += arr[i][j - 1];
			// 첫째 칸들
			else if (j == 0) arr[i][j] += arr[i - 1][j];
			// 그 외
			else {
				arr[i][j] += arr[i - 1][j] + arr[i][j - 1] - arr[i - 1][j - 1];	// 겹치는 범위 빼줌
			}
		}
	}

	for (int i = 0; i < m; i++) {
		scanf("%d %d %d %d", &i1, &j1, &i2, &j2);
		i1--; j1--; i2--; j2--;	// (0, 0)부터 시작

		// 만약 같은 점 2개 줄 경우
		if (i1 == i2 && j1 == j2) {
			printf("%lld\n", mem[i1][j1]);
			continue;
		}

		// (i2, j2) - (i2, j1 - 1) - (i1 - 1, j2) + (i1 - 1, j1 - 1)
		// 겹치는 범위 더해줌
		ll sum = arr[i2][j2] - arr[i2][j1 - 1] - arr[i1 - 1][j2] + arr[i1 - 1][j1 - 1];

		printf("%lld\n", sum);
	}


	return 0;
}
