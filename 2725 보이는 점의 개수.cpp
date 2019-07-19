//#include <iostream>
//#include <vector>
//#include <cstdio>
//#include <cstring>
//#define MAX 1001
//
//using namespace std;
//
//int map[M][M];
//int N;
//
//
//
//int main(void) {
//	int c;
//
//	scanf("%d", &c);
//
//	map[0][0] = 1;
//	//	printf("%d\n\n", map[1][0]);
//
//	for (int x = 0; x < MAX; x++) {
//		for (int y = 0; y < MAX; y++) {
//			if (map[x][y] == 0) {
//				for (int i = 2; i * x < MAX && i * y < MAX; i++) {
//					if (map[i*x][i*y] == 1) continue;
//
//					map[i*x][i*y] = 1;
//				}
//			}
//		}
//	}
//
//	for (int i = 0; i < c; i++) {
//		scanf("%d", &N);
//
//		int cnt = 0;
//
//		for (int x = 0; x <= N; x++) {
//			for (int y = 0; y <= N; y++) {
//				if (map[x][y] == 0) cnt++;
//			}
//		}
//
//		printf("%d\n", cnt);
//	}
//
//
//	return 0;
//}


#include <stdio.h>
#include <cstdio>

using namespace std;

int ans[1001] = { 0, 2 };	// 처음에 0, 1은 따로 초기화

// 최대 공약수
int gcd(int a, int b) {
	int tmp;	// a 값 임시 저장

	while (b > 0) {
		tmp = a;
		a = b;
		b = tmp % a;
	}

	return a;
}


int main(void) {
	int c;	// 테스트 케이스 수

	scanf("%d", &c);

	// 미리 소인수 관계인 것들 세어 놓기
	for (int i = 2; i <= 1000; i++) {
		int cnt = 0;	// 소인수 관계 개수

						// 대칭이므로 반절만 봄
		for (int j = 1; j <= i; j++) {
			if (gcd(i, j) == 1) cnt++;
		}

		ans[i] = ans[i - 1] + cnt;	// 업데이트
	}


	for (int i = 0; i < c; i++) {
		int N;	// 구하고 싶은 map 크기

		scanf("%d", &N);

		printf("%d\n", ans[N] * 2 - 1);	// 대칭이라서 반절만 구했고, 원점은 제외
	}

	return 0;
}
