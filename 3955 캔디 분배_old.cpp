#include <iostream>
#include <cstdio>
#include <vector>
#define MAX 1000000000

using namespace std;

int gcd(int a, int b) {
	int tmp;	// 임시 저장 
	
	// 공약수는 0보다 큼 
	while (b > 0) {
		tmp = a;
		a = b;
		b = tmp % a;	// a%b = r일 때 a, b의 최대 공약수는 b, r의 최대 공약수와 같음 
	}
	
	return a;
}

int ext_gcd(int a, int b) {
	int quo, rem, y, y1 = 0, y2 = 1;	// 몫, 나머지, 결과 저장, 처음 시작  
	int tmp = a;	// 나중에 결과가 음수이면 더해주기 위함 
	
	// c * x + k * y = 1에서 k쪽에만 관심 있음 
	while(rem != 1) {
		quo = a / b;
		rem = a % b;
		y = y1 - y2 * quo;
		y1 = y2;
		y2 = y;
		a = b;
		b = rem;
	}
	
	while(y < 0) y += tmp;
	
	return y;
}


int main(void) {
	int t, result;	// 테스트 케이스 개수, 결과 값 

	scanf("%d\n", &t);

	for (int i = 0; i < t; i++) {
		int k, c;	// 손님 명 수, 주머니 속 캔디 개수 

		scanf("%d %d", &k, &c);

		int tmp = gcd(k, c);	// 최대 공약수 

		// 서로소인가? 
		if (tmp != 1) {
			printf("IMPOSSIBLE\n");
			continue;
		}
		// 사탕이 한 개밖에 없나? 
		if (c == 1) {
			if (k + 1 > MAX) {
				printf("IMPOSSIBLE\n");
			}
			else printf("%d\n", k + 1);
			continue;
		}
		// 사람이 한 명 밖에 없나? 
		if (k == 1) {
			printf("1\n");
			continue;
		}
		
		result = ext_gcd(k, c);	// 최소 주머니 개수 
		
		// 1e9 이상은 가질 수 없으므로 
		if(result > MAX) {
			printf("IMPOSSIBLE\n");
			continue;
		}
		
		printf("%d\n", result);
	}

	return 0;
}
