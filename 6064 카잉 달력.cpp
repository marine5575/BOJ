/*
최소공배수를 이용하는 문제 
*/
#include <cstdio>

// 최대 공약수 
int gcd(int a, int b) {
	while(b != 0) {
		int r = a % b;
		a = b;
		b = r;
	}
	
	return a;
}

// 최소 공배수 
int lcm(int a, int b) {
	return a * b / gcd(a, b);
}


int main(void) {
	int cs;	// 테스트 케이스 개수 
	scanf("%d", &cs);
	
	while(cs--) {
		int M, N, x, y;	// <M:N> : 카잉 달력의 마지막 해, <x:y> : 구하고 싶은 해 
		scanf("%d %d %d %d", &M, &N, &x, &y);
		
		// 나머지 연산 쓰기 위한 세팅 
		if(x == M) x = 0;
		if(y == N) y = 0;
		
		int ans = -1, max = lcm(M, N), tmp;	// 정답, 마지막 해의 순서, 임시 저장 
		
		// 큰 것을 기준으로 계산하는 것이 좀 더 빠름 
		if(M > N) {
			tmp = x;	// x부터 시작 
			
			// 마지막 해는 넘지 않아야 됨 
			while(tmp <= max) {
				// 정답인가? 
				if(tmp % N == y) {
					ans = tmp;
					break;
				}
				
				tmp += M;
			}
		}
		else {
			tmp = y;	// y부터 시작 
			
			// 마지막 해는 넘지 않아야 됨 
			while(tmp <= max) {
				// 정답인가? 
				if(tmp % M == x) {
					ans = tmp;
					break;
				}
				
				tmp += N;
			}
		}
		
		printf("%d\n", ans);
	}
	
	return 0;
} 
