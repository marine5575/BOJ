/****************/
// BOJ 17822 원판 돌리기
// 핵심: 시뮬레이션 / BFS / DFS
/****************/

// 1. BFS 방법 
#if 0

#include <stdio.h>
#include <string.h>
#include <queue>
#define MAX 51

using namespace std;

typedef struct pt {
	int idx, num;
} pt;

int n, m, t;	// 원판 개수, 원판 당 적힌 정수 개수, 회전 횟수 
int sum, totNum;	// 모든 수의 합, 정수의 총 개수 
int plate[MAX][MAX];
int dx[] = {1, 0, -1, 0};	// right, down, left, up
int dy[] = {0, 1, 0, -1};

void turn_Clock(int x, int dir, int k) {
	// x의 배수인 접시를 dir(0: 시계/ 1: 반시계) 방향으로 k번 돌림
	
	int cnt;	// 실제로는 cnt번 돌리는 것과 동일 
	
	// 시계 방향 
	if(!dir) cnt = k % m;
	// 반시계 방향 
	else cnt = ((m - 1) * k) % m;
	
	for(int i = 1; x * i <= n; i++) {
		int num = x * i - 1;	// 이번 접시 번호 
		
		// 시계 방향으로 cnt칸 돌림 
		for(int p = 0; p < cnt; p++) {
			int tmp = plate[num][m - 1];
		
			for(int j = m - 2; j >= 0; j--) {
				plate[num][j + 1] = plate[num][j];
			}
			plate[num][0] = tmp;
		}
	}
}

int bfs(void) {
	int flag = 0;	// 움직였나 파악
	int visited[MAX][MAX] = {0, };	// 들렀는지 파악
	int copied[MAX][MAX];	// 변화된 것을 기록
	memcpy(copied, plate, sizeof(plate));
	
	queue<pt> q;
	pt init = {0, 0};
	q.push(init);
	visited[0][0] = 1;
	
	while(!q.empty()) {
		pt cur = q.front();
		q.pop();
		
		for(int i = 0; i < 4; i++) {
			int mx = cur.idx + dx[i];
			int my = cur.num + dy[i];
			
			// 범위 벗어나면 다시 돌려놓기 
			if(mx < 0) mx = m - 1;
			else if(mx >= m) mx = 0;
			
			// 범위 확인 & 들렀는지 확인 
			if(my < 0 || my >= n || visited[my][mx]) continue;
			// 지워진 것이라면 이후 볼 필요 x 
			if(plate[cur.num][cur.idx] == -1) break;
			// 인접한 것과 동일한 값이 아니면 통과 
			if(plate[my][mx] != plate[cur.num][cur.idx]) continue;
			
			// 방문 체크
			visited[my][mx] = 1; 
			copied[cur.num][cur.idx] = copied[my][mx] = -1;
			flag = 1;
			pt tmp = {mx, my};
			q.push(tmp);
		}
		
		// 나 다음 것 중 방문하지 않은 것을 하나 넣기 
		int start = cur.idx + 1, breakFlag = 0;
		for(int j = cur.num; j < n; j++) {
			for(int i = start; i < m; i++) {
				// 이미 방문함 or 방문할 필요 없는 곳 
				if(visited[j][i] || plate[j][i] == -1) continue;
			
				pt tmp = {i, j};
				q.push(tmp);
				breakFlag = 1;
				break;
			}
			if(breakFlag) break;
			
			start = 0;
		}
	}
	memcpy(plate, copied, sizeof(copied));
	
	// 인접한 수가 하나 이상 있음 
	if(flag) return 1;
	// 없음 
	else return 0;
}

void cal_Sum(void) {
	// 전체 합과 정수의 총 개수를 구함 
	
	sum = totNum = 0;
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			if(plate[j][i] == -1) continue;
			
			sum += plate[j][i];
			totNum++;
		}
	}
}

void classify(void) {
	double avg = sum / (double)totNum;	// 평균 
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			// 없는 칸 
			if(plate[j][i] == -1) continue;
			
			// 평균보다 큼 
			if(plate[j][i] > avg) {
				plate[j][i]--;
				sum--;
			}
			// 평균보다 작음 
			else if(plate[j][i] < avg) {
				plate[j][i]++;
				sum++;
			}
		}
	}
}


int main(void) {
	scanf("%d %d %d", &n, &m, &t);
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			scanf("%d", &plate[j][i]);
		}
	}
	
	for(int i = 0, x, dir, k; i < t; i++) {
		scanf("%d %d %d", &x, &dir, &k);
		turn_Clock(x, dir, k);
		
		// 하나도 인접한게 없을 때 
		if(!bfs()) {
			cal_Sum(); 
			classify();
		}
	}
	
	cal_Sum();
	printf("%d\n", sum);
	
	return 0;
}
#endif

// 2. 시뮬레이션 
#if 0

#include <stdio.h>
#include <string.h>
#define MAX 51

int n, m, t;	// 원판 개수, 원판에 있는 정수 개수, 회전 횟수 
int sum, totNum;	// 전체 합, 총 정수의 개수 
int plate[MAX][MAX];

void turn_Clock(int x, int dir, int k) {
	// x의 배수인 원판을 dir(0: 시계 / 1: 반시계) 방향으로 k번 돌림
	
	int cnt;	// 실제로 돌리는 횟수 
	
	// 시계 방향 
	if(!dir) cnt = k % m;
	// 반시계 방향 1번 == 시계 방향으로 (m - 1)번 돌린 것 
	else cnt = ((m - 1) * k) % m;
	
	for(int i = 1; x * i <= n; i++) {
		int num = x * i - 1;	// 돌릴 원판 
		
		// cnt번 시계 방향으로 돌림
		for(int j = 0; j < cnt; j++) {
			int tmp = plate[num][m - 1];
			
			for(int p = m - 2; p >= 0; p--) {
				plate[num][p + 1] = plate[num][p];
			}
			plate[num][0] = tmp;
		}
	}
}

void cal_Sum(void) {
	// 전체 합을 구하는 함수
	
	sum = totNum = 0;
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			// 지워진 곳은 통과 
			if(!plate[j][i]) continue;
			
			sum += plate[j][i];
			totNum++;
		}
	} 
}

void classify(void) {
	// 평균을 기준으로 큰 것은 -1, 작은 것은 +1 하는 함수
	
	cal_Sum();
	
	double avg = sum / (double)totNum;	// 평균 
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			// 지워진 곳은 통과 
			if(!plate[j][i]) continue;
			
			// 평균보다 큼 
			if(plate[j][i] < avg) plate[j][i]++;
			// 평균보다 작음 
			else if(plate[j][i] > avg) plate[j][i]--;
		}
	}
}

void check(void) {
	// 인접한 것은 없애고, 인접한 것이 존재하지 않을 경우
	// 평균을 기준으로 나누는 함수 호출
	// 모두다 살펴보기 떄문에 오른쪽과 왼쪽 중 하나만 선택해도 ok 
	
	int flag = 0;	// 인접한 것이 존재하면 1, 아니면 0 
	int copied[MAX][MAX];	// 변경을 기록할 곳 
	memcpy(copied, plate, sizeof(plate));
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < m; i++) {
			// 비어있으면 통과 
			if(!plate[j][i]) continue;
			
			int nextIdx = i + 1 < m ? i + 1 : 0;	// 살펴볼 오른쪽 
			
			// 오른쪽과 자신이 같음 
			if(plate[j][i] == plate[j][nextIdx]) {
				copied[j][i] = copied[j][nextIdx] = 0;	// 지움 
				flag = 1;
			}
			// 위쪽과 내가 같음 
			if(j != n - 1 && plate[j][i] == plate[j + 1][i]) {
				copied[j][i] = copied[j + 1][i] = 0;	// 지움 
				flag = 1;
			}
		}
	}
	
	memcpy(plate, copied, sizeof(copied));
	
	// 인접한게 하나도 없었을 때 
	if(!flag) classify();
}


int main(void) {
	scanf("%d %d %d", &n, &m, &t);
	
	for(int j = 0; j < n; j++) {
		for(int i = 0 ; i < m; i++) {
			scanf("%d", &plate[j][i]);
		}
	}
	for(int i = 0, x, dir, k; i < t; i++) {
		scanf("%d %d %d", &x, &dir, &k);
		turn_Clock(x, dir, k);
		check();
	}
	
	cal_Sum();
	
	printf("%d\n", sum);
	
	return 0;
}
#endif
