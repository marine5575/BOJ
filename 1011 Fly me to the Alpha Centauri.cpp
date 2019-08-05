/*
이 문제는 거리를 1에서부터 10까지 직접 손으로 써보면 규칙이 보인다.
이런 규칙을 찾는 것은 10개까지는 규칙을 찾아보도록 
*/
#include <cstdio>

typedef long long ll;

int main(void) {
	int cs;	// 테스트 케이스 개수 
	scanf("%d", &cs);
	
	while(cs--) {
		ll x, y;	// x, y 좌표 
		scanf("%lld %lld", &x, &y);
		
		ll jump = 0, i = 1;	// 이동 횟수, 제곱수 
		
		// 거리보다 큰 제곱수 i 구하기 
		while(i * i < y - x) i++;
		
		// 거리가 (i - 1) 제곱과 같을 때 
		if((i - 1) * (i - 1) == y - x) {
			jump = 2 * (i - 1) - 1;
		}
		// (i - 1)^2 < 거리 <= 중간 지점 
		else if((i - 1) * (i - 1) + (i * i - (i - 1) * (i - 1)) / 2 >= y - x) {
			jump = 2 * i - 2;
		}
		// 중간 지점 < 거리 <= i^2 
		else jump = 2 * i - 1;
		
		printf("%lld\n", jump);
	}
	
	return 0;
} 
