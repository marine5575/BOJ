/*******************************/
// BOJ 2250 트리의 높이와 너비
// 핵심: DFS & 문제 파악
// 			 => 루트노드를 명시하지 않았다면 루트노드를 찾아야 됨
// 					(나가는 것만 존재하는 것이 root) 
/*******************************/
#include <stdio.h>
#include <queue>
#define MAX ((int)1e4 + 1)

using namespace std;

typedef struct pt {
	int idx, l, r;
} pt;

int n, num, maxH = 1;	// 노드의 개수, 노드의 x 좌표 위치, 최대 레벨 
int root;	// root의 번호 
int check[MAX], low[MAX], high[MAX];	// check[i] = i번의 in + out 횟수, low[i] / high[i] = 레벨 i에 존재하는 가장 작은/큰 x좌표 
pt node[MAX];

void input_Data(void) {
	scanf("%d", &n);
	
	for(int i = 0, idx, l, r; i < n; i++) {
		scanf("%d %d %d", &idx, &l, &r);
		check[idx]++;
		node[idx].l = l; node[idx].r = r;
		// 존재하면 
		if(l != -1) check[l]++;
		if(r != -1) check[r]++;
	}
}

void preorder(int idx, int h) {
	// idx번호의 node를 들리는 함수, 노드 레벨은 h임
	
	// 올 수 없는 곳 
	if(idx == -1) return;
	
	preorder(node[idx].l, h + 1);
	
	++num;
	// 최대 레벨 갱신 
	if(maxH < h) maxH = h;
	// 이 레벨의 최소 x좌표 갱신 
	if(!low[h] || low[h] > num) low[h] = num;
	// 이 레벨의 최대 x좌표 갱신 
	if(!high[h] || high[h] < num) high[h] = num;
	
	preorder(node[idx].r, h + 1);
}

void find_Root(void) {
	// root는 나가는 것만 존재하므로 1일 것임 => 유일 
	
	for(int i = 1; i <= n; i++) {
		// root 노드임 
		if(check[i] == 1) {
        root = i;
        return;
    }
	}
}

void find_Max_Width(void) {
	// 각 레벨을 보면서 가장 넓은 레벨을 찾는 함수 
	
	int w = high[1] - low[1] + 1;	// 1레벨의 넓이 
	int h = 1;	// 가장 넓은 레벨 
	
	for(int i = 2; i <= maxH; i++) {
		int comp = high[i] - low[i] + 1;
		
		// 최대값 갱신 
		if(w < comp) {
			w = comp;
			h = i;
		}
	}
	
	printf("%d %d\n", h, w);
}


int main(void) {
	input_Data();
	
	find_Root();
	
	preorder(root, 1);
	find_Max_Width();
	
	return 0;
}
