/*********************/
// <<< old >>>
// BOJ 16235 나무 재테크
// 핵심: 문제 파악 
/*********************/
#include <stdio.h>
#include <vector>
#include <algorithm>
#define MAX 11

using namespace std;

int n, m, k;	// map 크기, 나무 개수, 놔둘 햇수 
int soil[MAX][MAX], energy[MAX][MAX];	// 토양, 겨울에 추가되는 양분 
int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};	// right부터 시계 방향 
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
vector<int> map[MAX][MAX];

void spring_and_Summer(void) {
	// 봄: 어린 순으로 이전 나이만큼 양분 섭취 => 나이 + 1 
	// 여름: (죽은 나무의 나이 / 2) -> 양분
	
	// 나이 오름차순 
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			sort(map[j][i].begin(), map[j][i].end());
		}
	}
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			// 없으면 pass 
			if(map[j][i].size() == 0) continue;
			
			vector<int> tmp;
			int sum = 0;	// 죽은 나무에서 나온 양분 
			
			for(int k = 0; k < map[j][i].size(); k++) {
				// 양분 모자람 
				if(soil[j][i] < map[j][i][k]) {
					sum += map[j][i][k] / 2;
					m--;
				}
				// 양분 충분 
				else {
					soil[j][i] -= map[j][i][k];
					tmp.push_back(map[j][i][k] + 1);
				}
			}
			
			soil[j][i] += sum;
			map[j][i].clear();
			map[j][i].assign(tmp.begin(), tmp.end());
		}
	}
}

void autumn(void) {
	// 나이 5의 배수인 것 번식 => 사방팔방으로 나이가 1인 나무 생김!
	
	vector<int> spread[MAX][MAX];
	
	for(int y = 0; y < n; y++) {
		for(int x = 0; x < n; x++) {
			// 없으면 통과 
			if(map[y][x].size() == 0) continue;
			
			for(int i = 0; i < 8; i++) {
				int mx = x + dx[i];
				int my = y + dy[i];
				
				// 범위 체크 
				if(mx < 0 || mx >= n || my < 0 || my >= n) continue;
				
				// 5의 배수만 번식 
				for(int j = 0; j < map[y][x].size(); j++) {
					if(map[y][x][j] % 5) continue;
					
					spread[my][mx].push_back(map[y][x][j]);
					m++;
				}
			}
		}
	}
	
	// 묘목 심기 
	for(int y = 0; y < n; y++) {
		for(int x = 0; x < n; x++) {
			if(spread[y][x].size() == 0) continue;
			
			for(int i = 0; i < spread[y][x].size(); i++) {
				map[y][x].push_back(1);
			}
		}
	}
}

void winter(void) {
	// energy에 있는 만큼 soil에 양분 추가
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			soil[j][i] += energy[j][i];
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
	for(int i = 0, x, y, t; i < m; i++) {
		scanf("%d %d %d", &y, &x, &t);
		
		map[y - 1][x - 1].push_back(t);
	}
	
	for(int i = 0; i < k; i++) {
		spring_and_Summer();
		autumn();
		winter();
	}
	
	printf("%d\n", m);
	
	return 0;
} 
