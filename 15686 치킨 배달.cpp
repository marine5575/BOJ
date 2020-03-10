/************************/
// BOJ 15686 치킨배달 
// 핵심: 브루트 포스 => 닥치고 다 찾아보기 
/************************/
#include <stdio.h>
#define INF 1000000001

typedef struct st {
	int x, y;
} pt;

int n, m;	// 지도 크기, 열 수 있는 최대 치킨집 수 
int chickMax, homeMax, ans = INF;	// 현재 치킨집 개수, 현재 집 개수, 최소 치킨거리 
pt chickArr[14], homeArr[101];	// 치킨집 위치, 집 위치 
int visited[14];	// 치킨집 열었는지 확인 

int cal_Chick_Dist(pt a, pt b) {
	int dx = a.x - b.x < 0 ? b.x - a.x : a.x - b.x;
	int dy = a.y - b.y < 0 ? b.y - a.y : a.y - b.y;
	
	return dx + dy;
}

int min(int a, int b) {
	return a < b ? a : b;
}

void open_Chick(int last, int cnt) {
	// chickArr[last]에 치킨집을 열었을 때
	// 치킨 거리 계산 후 최소 길이 갱신
	// cnt = last 열었을 때 열려있는 총 치킨집 수 
	
	// 치킨 거리 계산할 필요 없는 경우 
	if(last == chickMax || cnt > m) return;
	
	visited[last] = 1;	// 방문 체크 
	
	int sum = 0;	// 현재 전체 최소 치킨 거리 
	
	for(int i = 0; i < homeMax; i++) {
		int dist = INF, num = 0;	// 현재 집에서 최소 치킨거리, 확인한 열려있는 치킨집 수 
		
		for(int j = 0; j < chickMax; j++) {
			// 열려있는 모든 치킨집 다 확인함 
			if(num == cnt) break;
			// 닫혀있음 
			if(!visited[j]) continue;
			
			// 최소값 갱신 
			dist = min(dist, cal_Chick_Dist(homeArr[i], chickArr[j]));
			num++;	// 열린 치킨집 + 1 
		}
		
		sum += dist;
	}
	
	// 최소값 갱신 
	if(ans > sum) ans = sum;
	
	open_Chick(last + 1, cnt + 1);	// 다음 치킨집 열기 (last가 열려있는 상태) 
	visited[last] = 0;	// 방문 해제 
	open_Chick(last + 1, cnt);	// 다음 치킨집 열기 (last가 닫혀있는 상태) 
}

int main(void) {
	scanf("%d %d", &n, &m);
	
	for(int j = 0, tmp; j < n; j++) {
		for(int i = 0; i < n; i++) {
			scanf("%d", &tmp);
			
			// 집일 때 
			if(tmp == 1) {
				homeArr[homeMax].x = i;
				homeArr[homeMax++].y = j;
			}
			// 치킨집일 때 
			else if(tmp == 2) {
				chickArr[chickMax].x = i;
				chickArr[chickMax++].y = j;
			}
		}
	}
	
	open_Chick(0, 1);
	
	printf("%d\n", ans);
	
	return 0;
}
