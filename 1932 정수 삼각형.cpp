#include <cstdio>
#include <algorithm>

using namespace std;

int arr[501][501];	// 최댓값 저장 배열


int main(void) {
	int n;	// 삼각형 크기

	scanf("%d", &n);

	// 줄 번호
	for (int i = 0; i < n; i++) {
		// 칸 번호
		for (int j = 0; j < i + 1; j++) {
			scanf("%d", &arr[i][j]);

			// 초기 상태면 스킵
			if (i == 0 && j == 0) continue;

			// 맨 처음 칸이면 위에거 그대로 더함
			if (j == 0) arr[i][j] += arr[i - 1][j];
			// 맨 마지막 칸이어도 위에거 그대로 더함
			else if (j == i) arr[i][j] += arr[i - 1][j - 1];
			else {
				arr[i][j] += max(arr[i - 1][j], arr[i - 1][j - 1]);	// 위에것 중 더 큰 것 더함
			}
		}
	}

	int max = 0;	// 최댓값 저장

	for (int i = 0; i < n; i++) {
		// 더 큰 값 찾을 때마다 갱신
		if (arr[n - 1][i] > max) max = arr[n - 1][i];
	}

	printf("%d\n", max);


	return 0;
}
