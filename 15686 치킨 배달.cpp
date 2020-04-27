/************************/
// BOJ 15686 치킨배달 
// 핵심: 브루트 포스 => 닥치고 다 찾아보기 
/************************/
#include <stdio.h>
#include <vector>
#define MAX_TOWN 	21
#define MAX_CHICK 14
#define INF				((int)1e9 + 1)

using namespace std;

typedef struct pt {
	int x, y;
} pt;

int n, m, minDist = INF;	// 도시 크기, 폐업 면한 치킨집 수, 최소 거리 
int map[MAX_TOWN][MAX_TOWN];
char open[MAX_CHICK];
vector<pt> homePos, chickPos;	// 집의 위치, 치킨집 위치 

void input_Data(void) {
	scanf("%d %d", &n, &m);
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			scanf("%d", &map[j][i]);
			
			pt tmp = {i, j};
			if(map[j][i] == 1) homePos.push_back(tmp);
			else if(map[j][i] == 2) chickPos.push_back(tmp);
		}
	}
}

inline int min(int a, int b) {
	return a < b ? a : b;
}

inline int abs(int a) {
	return a < 0 ? -a : a;
}

inline int cal_Dist(pt a, pt b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

void cal_All_Dist(void) {
	// 각 집의 최소 치킨 거리를 더해서 예전에 구했던 값과 비교 
	
	int sum = 0;	// 치킨거리 합 
	
	for(int i = 0; i < homePos.size(); i++) {
		int dist = INF, num = 0;	// 최소 치킨거리, 들린 치킨집 수 
		
		for(int j = 0; j < chickPos.size(); j++) {
			// 열린 치킨집은 다 들렀음 
			if(num == m) break;
			// 닫혀있음 
			if(!open[j]) continue;
			
			// 최소값 갱신 
			dist = min(dist, cal_Dist(homePos[i], chickPos[j]));
			num++;
		}
		
		sum += dist;
	}
	
	// 최소값 갱신 
	if(minDist > sum) minDist = sum;
}

void dfs(int here, int cnt) {
	// 이번에 here부터 열 치킨집을 살펴볼 것임 
	// 직전까지 cnt개의 치킨집을 열었음
	
	// 최대로 열었음 
	if(cnt >= m) {
		cal_All_Dist();
		return;
	}
	
	for(int i = here; i < chickPos.size(); i++) {
		// 이미 열려있음 
		if(open[i]) continue;
		
		open[i] = 1;
		
		dfs(i + 1, cnt + 1);
		
		open[i] = 0;
	}
}


int main(void) {
	input_Data();
	dfs(0, 0);
	printf("%d\n", minDist);
	
	return 0;
}
