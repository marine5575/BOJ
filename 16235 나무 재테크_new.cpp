/*********************/
// <<< new >>>
// BOJ 16235 나무 재테크
// 핵심: simulation
// 			 => 정렬을 사용하지 않고 {나이, 그루 수}형식의 vector를 사용
// 			 --- 주의: (나이 / 2)를 먼저하고 개수 곱해야 되는 것 ---
/*********************/
#include <stdio.h>
#include <vector>
#define MAX 11

using namespace std;

typedef struct st {
	int age, cnt;
} tree;

int n, m, k;	// map 크기, 나무 개수, k년 후에 검사할 것임 
int energy[MAX][MAX], soil[MAX][MAX];	// 겨울에 추가하는 양분들, 양분 저장된 땅 
int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};	// right부터 시계 방향 
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
vector<tree> map[MAX][MAX];	// 나무가 저장되어 있는 땅 

void spring_Summer_and_Winter(void) {
	// 봄: 자신의 나이만큼 양분을 먹음(나이 오름차순) -> 나이 + 1
	// 		 양분 모자람 -> 죽음
	// 여름: 죽은 나무가 양분으로 변함 (나이 / 2)
	// 겨울: 로봇이 energy 추가 
	
	for(int y = 0; y < n; y++) {
		for(int x = 0; x < n; x++) {
			int sum = 0;	// 죽은 나무에서 나온 양분 
			
			for(int i = map[y][x].size() - 1; i >= 0; i--) {
				int age = map[y][x][i].age;	// 현재 나무의 나이 
				int num = map[y][x][i].cnt;	// 동 나이대의 그루 수 
				
				// num 에게 다 양분 주는 것 x 
				if(soil[y][x] < age * num) {
					int alive = soil[y][x] / age;	// 살아남은 나무 
					
					m -= (num - alive);	// 죽은 나무 뺌 
					sum += (num - alive) * (age / 2);	// 양분 추출 
					
					// 다 죽었을 때 
					if(!alive) {
						map[y][x].erase(map[y][x].begin() + i);
						continue;
					}
					
					// 몇 그루 살았을 때 
					soil[y][x] -= alive * age;
					map[y][x][i].cnt = alive;
				}
				// 모두에게 양분 주는 거 ok 
				else soil[y][x] -= num * age;
				 
				map[y][x][i].age++;	// 봄: 나이 + 1 
			}
			
			soil[y][x] += (sum + energy[y][x]);	// 여름 + 겨울 
		}
	}
}

void autumn(void) {
	// 가을: 나이가 (5의 배수)인 것들이 사방팔방으로 번식
	// 			 (애기 나무들(나이 = 1) 생김) 
	
	for(int y = 0; y < n; y++) {
		for(int x = 0; x < n; x++) {
			// 나무가 없음 => 통과 
			if(map[y][x].size() == 0) continue;
			
			for(int i = 0; i < map[y][x].size(); i++) {
				// 나이가 5의 배수인가? 
				if(map[y][x][i].age % 5 != 0) continue;
				
				for(int j = 0; j < 8; j++) {
					int mx = x + dx[j];
					int my = y + dy[j];
					
					// 범위 확인 
					if(mx < 0 || mx >= n || my < 0 || my >= n) continue;
					
					m += map[y][x][i].cnt;	// 나무 추가 
					
					// 원래 땅에 나무가 있었음 & 최소 나이가 1임 
					if(map[my][mx].size() != 0 && map[my][mx].back().age == 1) {
						map[my][mx].back().cnt += map[y][x][i].cnt;
					}
					// 원래 땅에 나무가 없었음 or 나이가 1인 나무 없음 
					else {
						tree tmp = {1, map[y][x][i].cnt};
						map[my][mx].push_back(tmp);
					}
				}
			}
			
		}
	}
}


int main(void) {
	scanf("%d %d %d", &n, &m, &k);
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			scanf("%d", &energy[j][i]);
			soil[j][i] = 5;
		}
	}
	for(int i = 0, x, y, age; i < m; i++) {
		scanf("%d %d %d", &y, &x, &age);
		
		tree tmp = {age, 1};
		map[y - 1][x - 1].push_back(tmp);
	}
	
	for(int i = 0; i < k; i++) {
		spring_Summer_and_Winter();
		autumn();
	}
	
	printf("%d\n", m);
	
	return 0;
} 
