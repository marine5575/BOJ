/*
최적화를 시키려고 했지만, c++에서는 아까 코드가 최선인 것 같다.
이 코드를 이용했을 때 메모리는 4kb 줄어들었지만, 실행 시간이 5ms 증가했다.
그냥 예전 코드를 이용하도록 하자.
어차피 아이디어는 똑같다. 
*/
#include <cstdio>
#include <iostream>	// fill_n
#define INF 987654321

int height[1001];	// 높이 저장 

int main(void) {
	// 테스트 케이스 10개 
	for(int cs = 1; cs <= 10; cs++) {
		int n, ans = 0;	// input 개수, 정답 
		scanf("%d", &n);
		std::fill_n(height, n, 0);	// 초기화 
		
		for(int i = 0; i < n; i++) {
			scanf("%d", height + i);
		}
		
		for(int i = 2; i < n; i++) {
			int min = INF;	// 최솟값 저장 
			
			// height[i]보다 큰 것이 범위 (+-)2 안에 들어 있는가? 
			if(height[i] < height[i - 1] || height[i] < height[i - 2] || height[i] < height[i + 1] || height[i] < height[i + 2]) {
				min = 0;
			}
			// 범위 안에 height[i]보다 작은 것들만 존재 
			else {
				int m1 = height[i] - height[i - 1];
				int m2 = height[i] - height[i - 2];
				int m3 = height[i] - height[i + 1];
				int m4 = height[i] - height[i + 2];
				
				// 최솟값으로 갱신 
				if(min > m1) min = m1;
				if(min > m2) min = m2;
				if(min > m3) min = m3;
				if(min > m4) min = m4;
			}
			
			ans += min;	// 더함 
		}
		
		printf("#%d %d\n", cs, ans);
	}
	
	return 0;
}
