/******************/
// BOJ 17779 게리맨더링 2
// 핵심: 문제 파악 
/******************/
#include <stdio.h>
#define MAX 21
#define INF 987654321

int n, ans = INF;	// 재현시 크기, 인구 차이 최솟값 
int map[MAX][MAX];

int check(int x, int y, int d1, int d2) {
	// (x, y)를 가장 윗꼭지점으로 해서
	// 사각형을 그릴 수 있다면 1 반환, 아니면 0 반환
	
	// 4개의 꼭지점이 모두 지도에 있어야 됨 
	if(x + d2 < 0 || x + d2 >= n || y + d2 < 0 || y + d2 >= n) return 0;
	if(x - d1 < 0 || x - d1 >= n || y + d1 < 0 || y + d1 >= n) return 0;
	if(x - d1 + d2 < 0 || x - d1 + d2 >= n || y + d1 + d2 < 0 || y + d1 + d2 >= n) return 0;
	
	return 1;
}

void paint(int x, int y, int d1, int d2) {
	// 1, 2, 3, 4 구역을 색칠하면서 합을 구하고
	// 최대 선거구와 최소 선거구의 차이를 구하는 함수 
	
	int group[MAX][MAX] = {0, };	// 선거구 
	int maxSum = 0, minSum = INF, sum = 0;	// 최다 선거구, 최소 선거구, 인구 합 
	
	// 1번 구역
	int lim = x;
	for(int j = 0; j < y + d1; j++) {
		if(j >= y) lim--;
		
		for(int i = 0; i <= lim; i++) {
			group[j][i] = 1;
			sum += map[j][i];
		}
	}
	
	if(maxSum < sum) maxSum = sum;
	if(minSum > sum) minSum = sum;
	
	// 2번 구역
	sum = 0;
	lim = x + 1;
	for(int j = 0; j <= y + d2; j++) {
		if(j > y) lim++;
		
		for(int i = lim; i < n; i++) {
			group[j][i] = 2;
			sum += map[j][i];
		}
	}
	
	if(maxSum < sum) maxSum = sum;
	if(minSum > sum) minSum = sum;
	
	// 3번 구역
	sum = 0;
	lim = x - d1;
	for(int j = y + d1; j < n; j++) {
		for(int i = 0; i < lim; i++) {
			group[j][i] = 3;
			sum += map[j][i];
		}
		
		if(j < y + d1 + d2) lim++;
	}
	
	if(maxSum < sum) maxSum = sum;
	if(minSum > sum) minSum = sum;
	
	// 4번 구역
	sum = 0;
	lim = x + d2;
	for(int j = y + d2 + 1; j < n; j++) {
		for(int i = lim; i < n; i++) {
			group[j][i] = 4;
			sum += map[j][i];
		}
		
		if(j <= y + d1 + d2) lim--;
	}
	
	if(maxSum < sum) maxSum = sum;
	if(minSum > sum) minSum = sum;
	
	// 5번 구역
	sum = 0;
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			// 다른 선거구면 통과 
			if(group[j][i]) continue;
			
			sum += map[j][i];
		}
	}
	
	if(maxSum < sum) maxSum = sum;
	if(minSum > sum) minSum = sum;
	
	// 최소값 갱신 
	if(ans > maxSum - minSum) ans = maxSum - minSum;
}


int main(void) {
	scanf("%d", &n);
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			scanf("%d", &map[j][i]);
		}
	}
	
	// 모든 꼭지점 다 봄 
	for(int y = 0; y < n; y++) {
		for(int x = 0; x < n; x++) {
			// 모든 길이 다 해봄 
			for(int d1 = 1; d1 < n; d1++) {
				int d2;
				for(d2 = 1; d2 < n; d2++) {
					// 이 이후는 모두 불가능 
					if(!check(x, y, d1, d2)) break;
					
					paint(x, y, d1, d2);
				}
				
				// 이 이후는 모두 불가능 
				if(d2 == 1) break;
			}
		}
	}
	
	printf("%d\n", ans);
	
	return 0;
} 
