#include <cstdio>
#include <algorithm>
#include <vector>
#define INF 987654321

using namespace std;
struct Edge {
	int x1, y1, x2, y2;	// (x1, y1)에서 (x2, y2)로 옮길 때 
	int t;	// 걸리는 시간 
};

// 좌표 옮기기 위함 
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int map[31][31];	// 지도 (0은 걸어갈 수 있는 곳, -1은 공동묘지, -2는 도착 지점 혹은 귀신 구멍) 
int dist[31][31];	// 이곳까지 오는데 걸린 최소 시간 
int w, h;	// 지도의 가로, 세로 
vector<Edge> edge;	// 연결 간선들 


int main(void) {
	while (1) {
		scanf("%d %d", &w, &h);
		
		if(w == 0 && h == 0) return 0;
		
		int g, gh;	// 공동묘지 수, 귀신 구멍 수 
		
		// 초기화 작업 
		for(int j = 0; j < h; j++) {
			for(int i = 0; i < w; i++) {
				dist[j][i] = INF;
				map[j][i] = 0;
			}
		}
		
		scanf("%d", &g);
		
		// 공동묘지 표시 
		for(int i = 0; i < g; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			
			map[y][x] = -1;
		}
		
		scanf("%d", &gh);
		
		// 귀신 구멍 표시 
		for(int i = 0; i < gh; i++) {
			int x1, y1, x2, y2, t;
			
			scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &t);
			
			map[y1][x1] = -2;
			
			edge.push_back({x1, y1, x2, y2, t});
		}
		
		map[h-1][w-1] = -2;	// 도착 지점 표시 
		
		// 모든 지점에 대해서 확인 
		for(int j = 0; j < h; j++) {
			for(int i = 0; i < w; i++) {
				// '걸어서' 갈 수 있는 곳인가? 
				if(map[j][i] == 0) {
					// 걸어서 갈 수 있는 모든 방향 
					for(int k = 0; k < 4; k++) {
						int targetX = i + dx[k];	// 이동할 x 좌표 
						int targetY = j + dy[k];	// 이동할 y 좌표 
						
						// 이동할 좌표들이 범위 안에 들어와 있는가? 
						if(targetX >= 0 && targetX < w && targetY >= 0 && targetY < h) {
							// 갈 수 없는 곳인가? 
							if(map[targetY][targetX] == -1) continue;
							
							edge.push_back({i, j, targetX, targetY, 1});	// 간선 추가 
						}
					}
				}
			}
		}
		
		dist[0][0] = 0;	// 시작지점 최소거리 
		int isUpdate = 0;	// 음의 사이클 확인용 
		
		// 전체 맵에 대해서 수행 
		for(int i = 0; i < w*h; i++) {
			isUpdate = 0;
			
			// 모든 간선에 대해서 수행 
			for(int j = 0; j < edge.size(); j++) {
				Edge e = edge[j];
				
				// 지금 서있는 곳이 아직 도착하지 않은 곳인가? 
				if(dist[e.y1][e.x1] == INF) continue;
				// 최솟값 갱신 
				if(dist[e.y2][e.x2] > dist[e.y1][e.x1] + e.t) {
					dist[e.y2][e.x2] = dist[e.y1][e.x1] + e.t;
					
					isUpdate = 1; 
				}
			}
			
			// 만약 두번째 돌았을 때 갱신되지 않았다면 음의 사이클 존재 x 
			if (isUpdate == 0) break;
		}
		
		// 음의 사이클이 존재하는가? 
		if(isUpdate) printf("Never\n");
		// 도착하지 못했는가? 
		else if(dist[h-1][w-1] == INF) printf("Impossible\n");
		else printf("%d\n", dist[h-1][w-1]);
		
		edge.clear();	// 새로운 지도를 받아올 것이므로 간선 초기화 
	}


	return 0;
}
