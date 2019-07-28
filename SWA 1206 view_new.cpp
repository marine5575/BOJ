/*
최적화 전 코드. 
슬라이딩 윈도로 풀어보았다.
처음에 입력을 받을 때 바로 전전것과 전것과 비교해서 조망권을 확보할 수 있는지 관찰하고,
전전것에 대해서는 자신과 내 전것을 비교해서 최댓값과 비교하는 것이 포인트였다. 
*/
#include <cstdio>
#include <algorithm>

using namespace std;

int height[1001], isSee[1001];	// 건물 높이, 보이는가? 

int main(void) {
	// 테스트 케이스 10개 
	for(int cs = 1; cs <= 10; cs++) {
		int n, cnt = 0;	// input 개수, 조망권 확보 가능 세대 수 
		scanf("%d", &n);
		fill_n(isSee, n, 0);	// 초기화
		scanf("%d %d", &height[0], &height[1]);	// 미리 넣어놓기 
		
		for(int i = 2; i < n; i++) {
			scanf("%d", height + i);
			
			// 전전것, 전것 중 최댓값 
			int maxi = max(height[i - 2], height[i - 1]);
			// 나보다 작은것이 있을 때 조망권 확보 가능 세대수 저장 
			if(maxi < height[i]) isSee[i] = height[i] - maxi;
			
			// 나와 전것 중 최댓값 
			maxi = max(height[i - 1], height[i]);
			// 조망권이 있는가? 
			if(isSee[i - 2]) {
				// 만약 나보다 크면 조망권 없음 
				if(maxi >= height[i - 2]) isSee[i - 2] = 0;
				// 이전것보다 현재 최댓값이 큰가? 
				else if(height[i - 2] - isSee[i - 2] < maxi) isSee[i - 2] = height[i - 2] - maxi;
			}
			
			cnt += isSee[i - 2];
		}
		
		printf("#%d %d\n", cs, cnt);
	}
	
	return 0;
}
