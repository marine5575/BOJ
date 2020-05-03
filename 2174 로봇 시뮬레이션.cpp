/****************************/
// BOJ 2174 로봇 시뮬레이션
// 핵심: 시뮬레이션 + 중간에 끊기 (exit(0)) 
/****************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#define MAX 102

using namespace std;

typedef struct pt {
	int x, y, dir;
} pt;
typedef struct od {
	int idx;
	char select;
	int loop;
} od;

int c, r, n, m;	// 지도의 가로, 세로, 로봇의 개수, 명령의 개수 
int map[MAX][MAX];	// map[j][i] = (i, j)에 있는 로봇의 번호 
int dx[] = {0, -1, 0, 1};	// down, left, up, right
int dy[] = {1, 0, -1, 0};
pt robot[MAX]; 
vector<od> order;

inline int char_to_Dir(char c) {
	if(c == 'N') return 0;
	else if(c == 'W') return 1;
	else if(c == 'E') return 3;
	else return 2;
}

void input_Data(void) {
	scanf("%d %d %d %d", &c, &r, &n, &m);
	
	for(int i = 1, x, y; i <= n; i++) {
		char c;
		
		scanf("%d %d %c", &x, &y, &c);
		
		pt tmp = {x, y, char_to_Dir(c)};
		robot[i] = tmp;
		
		map[y][x] = i;
	}
	
	for(int i = 0, num, loop; i < m; i++) {
		char c;
		
		scanf("%d %c %d", &num, &c, &loop);
		od tmp = {num, c, loop};
		order.push_back(tmp);
	}
}

void move_Robot(int idx) {
	// order[idx].idx 번 로봇을 loop만큼 dir 방향으로 전진하는 함수 
	
	int loop = order[idx].loop, num = order[idx].idx;	// 반복 횟수, 움직일 로봇 번호 
	int dir = robot[num].dir;	// 로봇의 방향 
	int x = robot[num].x, y = robot[num].y;	// 로봇의 현재 위치 
	
	for(int i = 0; i < loop; i++) {
		int mx = x + dx[dir];
		int my = y + dy[dir];
		
		// 범위 확인 
		if(mx <= 0 || mx > c || my <= 0 || my > r) {
			printf("Robot %d crashes into the wall\n", num);
			exit(0);
		}
		// 충돌함 
		if(map[my][mx]) {
			printf("Robot %d crashes into robot %d\n", num, map[my][mx]);
			exit(0);
		}
		
		map[y][x] = 0;
		map[my][mx] = num;
		
		pt tmp = {mx, my, dir};
		robot[num] = tmp;
		x = mx; y = my;
	}
}

void turn_Robot(int idx, int flag) {
	// flag(0: 왼쪽으로 90도 / 1: 오른쪽으로 90도)일 때 로봇을 돌리는 함수 
	
	int num = order[idx].idx, loop = order[idx].loop % 4;	// 움직일 로봇 번호, 반복 횟수 
	
	// 왼쪽으로 90도 
	if(!flag) robot[num].dir = (robot[num].dir + loop) % 4;
	// 오른쪽으로 90도 
	else robot[num].dir = (robot[num].dir + 3 * loop) % 4;
}

void sol(void) {
	for(int i = 0; i < m; i++) {
		// 전진일 때 
		if(order[i].select == 'F') move_Robot(i);
		// 왼쪽으로 90도 
		else if(order[i].select == 'L') turn_Robot(i, 0);
		// 오른쪽으로 90도 
		else turn_Robot(i, 1);
	}
}


int main(void) {
	input_Data();
	sol();
	
	printf("OK\n");
	
	return 0;
}
