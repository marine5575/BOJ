/*
seg tree 크기를 좀더 적게 잡음 
*/
#include <iostream>
#define INF 1000000001

using namespace std;
typedef long long ll;

typedef struct point {
	int idx;
	ll v = INF;
} pt;

pt tree[205001];	// seg tree
int n;	// input 수 
ll maxi;	// 최댓값 

int query(int i, int j) {
	int min = INF, idx = -1;	// 최솟값, 그의 index 
	
	// 시작은 끝보다 작거나 같음 
	while(i <= j) {
		// '시작'이 오른쪽에 위치하는가? 
		if(i % 2 == 1) {
			// 최솟값 갱신 
			if(min > tree[i].v) {
				min = tree[i].v;
				idx = tree[i].idx;
			}
			i++;	// 오른쪽으로 밈 
		}
		// '끝'이 왼쪽에 위치하는가? 
		if(j % 2 == 0) {
			// 최솟값 갱신 
			if(min > tree[j].v) {
				min = tree[j].v;
				idx = tree[j].idx;
			}
			j--;	// 왼쪽으로 밈 
		}
		i >>= 1; j >>= 1;	// 조상 살피기 
	}
	
	return idx;
}

void maxArea(int s, int e) {
	int idx = query(s, e);	// 최솟값이 있는 index 
	
	ll tmp = (e - s + 1) * tree[idx].v;	// 최솟값을 높이로 하는 직사각형 
	
	// 왼쪽 살펴봄 
	if(s < idx) maxArea(s, idx - 1);
	// 오른쪽 살펴봄 
	if(idx < e) maxArea(idx + 1, e);
	
	// 최댓값 갱신 
	if(maxi < tmp) maxi = tmp;
}

void makeTree() {
	int tmp = n - 1;	// 이미 여기서 시작 
	
	while(tmp > 0) {
		// 최솟값 넣기 
		tree[tmp].v = tree[tmp << 1].v < tree[(tmp << 1) | 1].v ? tree[tmp << 1].v : tree[(tmp << 1) | 1].v;
		tree[tmp].idx = tree[tmp].v == tree[tmp << 1].v ? tree[tmp << 1].idx : tree[(tmp << 1) | 1].idx;
		tmp--;
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	while(1) {
		maxi = -1;	// 최댓값 초기화 
		cin >> n;
		
		if(n == 0) return 0;
		
		for(int i = 0; i < n; i++) {
			cin >> tree[n + i].v;
			tree[n + i].idx = n + i;
		}
		
		makeTree();
		maxArea(n, 2 * n - 1);
		
		cout << maxi << "\n";
	}
}
