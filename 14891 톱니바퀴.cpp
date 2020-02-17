/********************/
// BOJ 14891 톱니바퀴
// 핵심: 재귀 & shift 연산 
/********************/

#include <stdio.h>

char gear[4];	// 톱니바퀴 (0: N극 / 1: S극) 
int k;	// 회전 횟수

void turn(int from, int num, int dir) {
	int left = -2, right = -2;	// 왼쪽, 오른쪽 톱니바퀴 회전 방향 (-1: anti-clockwise / 1: clockwise / 0: 움직이지 x) 
	
	// 맨 왼쪽 or 왼쪽에서 옴 
	if(num == 1 || from == -1) left = 0;
	// 맨 오른쪽 or 오른쪽에서 옴 
	if(num == 4 || from == 1) right = 0;
	
	// 아직 왼쪽 정해지지 않음 
 	if(left == -2) {
 		// 서로 다른 극일 때 
		if(((gear[num - 1] >> 1) & 1) ^ ((gear[num - 2] >> 5) & 1)) {
			left = -dir;
		}
		// 같은 극일 때 
		else left = 0;
	}
	// 아직 오른쪽 정해지지 않음 
	if(right == -2) {
		// 서로 다른 극 
		if(((gear[num - 1] >> 5) & 1) ^ ((gear[num] >> 1) & 1)) {
			right = -dir;
		}
		// 같은 극 
		else right = 0;
	}
	
	// 시계 방향 회전 => right shift (>>) 
	if(dir == -1) {
		char tmp = (gear[num - 1] >> 7) & 1;
		gear[num - 1] <<= 1;
		
		// 없어진 값이 1일 때 => set
		if(tmp == 1) gear[num - 1] |= tmp;
		// 0일 때 => clear 
		else gear[num - 1] &= ~1;
	}
	// 반시계 방향 회전 => left shift (<<) 
	else {
		char tmp = gear[num - 1] & 1;
		gear[num - 1] >>= 1;
		
		// 없어진 값이 1일 때 => set 
		if(tmp == 1) gear[num - 1] |= (tmp << 7);
		// 0일 때 => clear 
		else gear[num - 1] &= ~(1 << 7);
	}
	
	// 돌려야 될 때
	if(left != 0) turn(1, num - 1, left);
	if(right != 0) turn(-1, num + 1, right);
}


int cal_Score(void) {
	int sum = 0, mul = 1;	// 점수, weight 
	
	for(int i = 0; i < 4; i++) {
		sum += (gear[i] >> 7) & 1 * mul;
		mul *= 2;
	}
	
	return sum;
}


int main(void) {
	for(int i = 0; i < 4; i++) {
		char c;
		
		for(int j = 0; j < 8; j++) {
			scanf("%c", &c);
			if(j != 0) gear[i] <<= 1;
			gear[i] |= c - '0';
		}
		scanf("%*c");
	}
	
	scanf("%d", &k);
	
	for(int i = 0; i < k; i++) {
		int num, dir;
		scanf("%d %d", &num, &dir);
		
		turn(0, num, dir);
	}
	
	printf("%d\n", cal_Score());
	
	return 0;
}
