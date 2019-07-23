#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int map[1001][1001];	// map[i][j] : (i, j)를 우측 끝으로 하는 가장 큰 정사각형의 square_root


int main(void) {
	int n, m, max = 0;	// 줄 개수, 칸 개수, 최대값 저장
	string s;	// 문자열로 들어옴

	scanf("%d %d", &n, &m);

	// 맨 끝에 있는 1들도 계산해야 되기 때문에 (1, 1)부터 시작
	for (int i = 1; i <= n; i++) {
		cin >> s;

		for (int j = 1; j <= m; j++) {
			map[i][j] = s[j - 1] - '0';	// '문자'로 받아왔기 때문에 정수로 변환
		}
	}

	// map은 실질적으로 (1, 1)부터 시작
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			// 애초에 point가 1이어야 정사각형을 이룰 수 있음
			if (map[i][j] == 1) {
				// 주위 정사각형 root의 최소값 + 1
				// 그림 그려보면 쉬운 납득 가능
				map[i][j] = min(min(map[i - 1][j - 1], map[i - 1][j]), map[i][j - 1]) + 1;

				// 최대값 갱신
				if (map[i][j] > max) max = map[i][j];
			}
		}
	}

	printf("%d\n", max * max);	// root였기 때문에 제곱


	return 0;
}
