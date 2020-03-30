#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>
#define MAX 101

using namespace std;

typedef struct st {
	int num, cnt;
} st;

int r, c, k;	// map[r][c]에 k가 들어있는지 확인 
int row = 3, col = 3;	// 현재 최대 행 개수, 열 개수
int map[MAX][MAX];

bool compare(st& a, st& b) {
	// 1. 등장횟수 기준으로 오름차순
	// 2. 같으면 숫자 크기 기준으로 오름차순 
	
	if(a.cnt < b.cnt) return true;
	else if(a.cnt == b.cnt) {
		if(a.num < b.num) return true;
		else return false;
	}
	else return false;
}

void rowSort(void) {
	// 각 행을 정렬 
	
	int copied[MAX][MAX] = {0, };	// 결과 저장 
	int maxCol = -1;	// 이번 회차의 최대 열 개수 
	
	// 각 행에 대해서 실행 
	for(int j = 0; j < row; j++) {
		int count[MAX] = {0, };	// 숫자 등장 횟수 저장 
		int max = -1;	// 이번 행의 최고 숫자 
		
		for(int i = 0; i < col; i++) {
			// 0이면 통과 
			if(!map[j][i]) continue;
			
			count[map[j][i]]++;
			
			// 최대값 갱신 
			if(max < map[j][i]) max = map[j][i];
		}
		
		vector<st> vec;	// 있는 숫자들 넣을 곳 
		
		for(int i = 1; i <= max; i++) {
			// 비어있으면 통과 
			if(!count[i]) continue;
			
			st tmp = {i, count[i]};
			vec.push_back(tmp);
		}
		
		sort(vec.begin(), vec.end(), compare);	// 등장횟수 기준으로 오름차순 
		
		int idx = 0;	// 집어넣을 곳을 가리킴 
		
		for(int i = 0; i < vec.size(); i++) {
			copied[j][idx++] = vec[i].num;
			copied[j][idx++] = vec[i].cnt;
		}
		
		// 최대값 갱신 
		if(maxCol < idx) maxCol = idx;
	}
	
	// 원상태 복귀 
	col = maxCol;
	memcpy(map, copied, sizeof(copied));
}

void colSort(void) {
	// 각 열을 정렬 
	
	int copied[MAX][MAX] = {0, };
	int maxRow = -1;	// 이번 회차의 최대 행의 수 
	
	// 각 열에 대해서 정렬 
	for(int i = 0; i < col; i++) {
		int count[MAX] = {0, };
		int max = -1;
		
		for(int j = 0; j < row; j++) {
			if(!map[j][i]) continue;
			
			count[map[j][i]]++;
			
			if(max < map[j][i]) max = map[j][i];
		}
		
		vector<st> vec;
		
		for(int j = 1; j <= max; j++) {
			if(!count[j]) continue;
			
			st tmp = {j, count[j]};
			vec.push_back(tmp);
		}
		
		sort(vec.begin(), vec.end(), compare);
		
		int idx = 0;
		
		for(int j = 0; j < vec.size() && idx < MAX; j++) {
			copied[idx++][i] = vec[j].num;
			copied[idx++][i] = vec[j].cnt;
		}
		
		if(maxRow < idx) maxRow = idx;
	}
	
	row = maxRow;
	memcpy(map, copied, sizeof(copied));
}

void find(void) {
	int cnt = 0;	// cnt회차까지 진행됨 
	
	while(1) {
		// 이미 찾음 
		if(map[r][c] == k) {
			printf("%d\n", cnt);
			break;
		}
		// 100번 넘었음 
		if(cnt > 100) {
			printf("-1\n");
			break;
		}
		
		if(row >= col) rowSort();
		else colSort();
		
		cnt++;
	}
}


int main(void) {
	scanf("%d %d %d", &r, &c, &k);
	r--; c--;
	
	for(int j = 0; j < 3; j++) {
		for(int i = 0; i < 3; i++) {
			scanf("%d", &map[j][i]);
		}
	}
	
	find();
	
	return 0;
} 
