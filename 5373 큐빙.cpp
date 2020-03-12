/********************/
// BOJ 5373 큐빙
// 핵심: 문제 잘 읽고, 그대로 코드로 구현
/********************/
#include <stdio.h>
#include <string.h>

int n;	// 큐브를 돌린 횟수 
char cube[6][3][3];	// cube[위, 아래, 앞, 뒤, 왼, 오]의 상태 
char colors[] = {'w', 'y', 'r', 'o', 'g', 'b'};
enum dir {u, d, f, b, l, r};	// 0, 1, 2, 3, 4, 5

void init_Cube(void) {
	// 큐브를 처음 상태로 돌리는 함수 
	
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 3; j++) {
			for(int k = 0; k < 3; k++) {
				cube[i][j][k] = colors[i];
			}
		}
	}
}

void turn_Side(char order) {
	// order 면과 붙어있는 4면을 시계방향으로 돌리는 함수 
	
	char tmp[3];	// 임시 저장 
	
	switch(order) {
		case 'U': {
			for(int i = 0; i < 3; i++) {
				tmp[i] = cube[r][i][0];
			}
			for(int i = 0; i < 3; i++) {
				cube[r][i][0] = cube[b][2][i];
			}
			for(int i = 0; i < 3; i++) {
				cube[b][2][i] = cube[l][2 - i][2];
			}
			for(int i = 0; i < 3; i++) {
				cube[l][i][2] = cube[f][0][i];
			}
			for(int i = 0; i < 3; i++) {
				cube[f][0][i] = tmp[2 - i];
			}
			break;
		}
		case 'D': {
			for(int i = 0; i < 3; i++) {
				tmp[i] = cube[l][i][0];
			}
			for(int i = 0; i < 3; i++) {
				cube[l][i][0] = cube[b][0][2 - i];
			}
			for(int i = 0; i < 3; i++) {
				cube[b][0][i] = cube[r][i][2];
			}
			for(int i = 0; i < 3; i++) {
				cube[r][i][2] = cube[f][2][2 - i];
			}
			for(int i = 0; i < 3; i++) {
				cube[f][2][i] = tmp[i];
			}
			break;
		}
		case 'L': {
			for(int i = 0; i < 3; i++) {
				tmp[i] = cube[b][i][0];
			}
			for(int i = 0; i < 3; i++) {
				cube[b][i][0] = cube[d][i][0];
			}
			for(int i = 0; i < 3; i++) {
				cube[d][i][0] = cube[f][i][0];
			}
			for(int i = 0; i < 3; i++) {
				cube[f][i][0] = cube[u][i][0];
			}
			for(int i = 0; i < 3; i++) {
				cube[u][i][0] = tmp[i];
			}
			break;
		}
		case 'R': {
			for(int i = 0; i < 3; i++) {
				tmp[i] = cube[f][i][2];
			}
			for(int i = 0; i < 3; i++) {
				cube[f][i][2] = cube[d][i][2];
			}
			for(int i = 0; i < 3; i++) {
				cube[d][i][2] = cube[b][i][2];
			}
			for(int i = 0; i < 3; i++) {
				cube[b][i][2] = cube[u][i][2];
			}
			for(int i = 0; i < 3; i++) {
				cube[u][i][2] = tmp[i];
			}
			break;
		}
		case 'F': {
			for(int i = 0; i < 3; i++) {
				tmp[i] = cube[l][2][i];
			}
			for(int i = 0; i < 3; i++) {
				cube[l][2][i] = cube[d][0][2 - i];
			}
			for(int i = 0; i < 3; i++) {
				cube[d][0][i] = cube[r][2][2 - i];
			}
			for(int i = 0; i < 3; i++) {
				cube[r][2][i] = cube[u][2][i];
			}
			for(int i = 0; i < 3; i++) {
				cube[u][2][i] = tmp[i];
			}
			break;
		}
		case 'B': {
			for(int i = 0; i < 3; i++) {
				tmp[i] = cube[r][0][i];
			}
			for(int i = 0; i < 3; i++) {
				cube[r][0][i] = cube[d][2][2 - i];
			}
			for(int i = 0; i < 3; i++) {
				cube[d][2][i] = cube[l][0][2 - i];
			}
			for(int i = 0; i < 3; i++) {
				cube[l][0][i] = cube[u][0][i];
			}
			for(int i = 0; i < 3; i++) {
				cube[u][0][i] = tmp[i];
			}
			break;
		}
	}
}

void turn_Fore(char order) {
	// order면을 시계 방향으로 90도 회전시키는 함수 
	
	char tmp[3][3];	// 원본 
	int now;	// 현재 order면의 숫자 
	
	switch(order) {
		case 'U': {
			now = u;
			break;
		}
		case 'D': {
			now = d;
			break;
		}
		case 'F': {
			now = f;
			break;
		}
		case 'B': {
			now = b;
			break;
		}
		case 'L': {
			now = l;
			break;
		}
		case 'R': {
			now = r;
			break;
		}
	}
	
	memcpy(tmp, cube[now], sizeof(cube[now]));	// 복사 
	
	for(int j = 0; j < 3; j++) {
		for(int i = 0; i < 3; i++) {
			cube[now][i][2 - j] = tmp[j][i];
		}
	}
}


int main(void) {
	int tc;	// test case 개수 
	scanf("%d", &tc);
	
	while(tc--) {
		init_Cube();	// 초기화 
		
		scanf("%d", &n);
		
		char order[3];	// 명령 => 기준면 & 회전 방향(+: 시계, -: 반시계) 
		
		for(int i = 0; i < n; i++) {
			scanf(" %s", order);
			
			// 반시계 방향 == 시계 방향 3번
			for(int j = 0; j < 3; j++) {
				turn_Side(order[0]);
				turn_Fore(order[0]);
				 
				// 시계 방향일 때 
				if(order[1] == '+') break;
			}
		}
		
		for(int j = 0; j < 3; j++) {
			for(int i = 0; i < 3; i++) {
				printf("%c", cube[u][j][i]);
			}
			printf("\n");
		}
	}
	
	return 0;
}
