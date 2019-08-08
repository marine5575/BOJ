/*
나눗셈 연산이 오래걸린단 소리에 요즘 ( ? : ) 구문을 많이 쓰고 있는데
나머지 연산대신에 쓸 때는 >= 이어야 된다는 사실을 깜빡해서
4번이나 틀렸던 문제.
>> 나머지 연산 대신에 쓸 땐 '>=' 이어야 된다!!! << 
*/
#include <cstdio>
#define MAX 1000000000

int num[10] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1};	// 현재 자리를 이루는 0 ~ 9의 개수 || 초기화: 1자리 수 일 때 0 ~ 9의 개수 
int tmp[10];	// 이전 자리를 이뤘던 0 ~ 9의 개수 


int main(void) {
	int n;	// 원하는 총 자리수 
	scanf("%d", &n);
	int dp = 9;	// 경우의 수 
	
	// 모든 자리수에 대해서 
	for(int i = 2; n != 1 && i <= n; i++) {
		// 이전 자리수 초기화 
		for(int j = 0; j <= 9; j++) {
			tmp[j] = num[j];
		}
		
		dp = 0;	// 경우의 수 초기화 
		
		// 모든 자리에 대해서 
		for(int j = 0; j <= 9; j++) {
			// 0이 되기 위해선 전 자리가 1 
			if(j == 0) {
				num[j] = tmp[j + 1];
			}
			// 9가 되기 위해선 전 자리가 8 
			else if(j == 9) {
				num[j] = tmp[j - 1];
			}
			// 양 옆에 있는 것에서 가져 옴
			// 단, MAX를 넘으면 안되므로 확인도 함 
			else num[j] = (tmp[j - 1] + tmp[j + 1] >= MAX ? tmp[j - 1] + tmp[j + 1] - MAX : tmp[j - 1] + tmp[j + 1]);
			
			// 총 경우의 수 % MAX
			dp = dp + num[j] >= MAX ? dp + num[j] - MAX : dp + num[j];
		}
	}
	
	printf("%d\n", dp);

	return 0;
} 
