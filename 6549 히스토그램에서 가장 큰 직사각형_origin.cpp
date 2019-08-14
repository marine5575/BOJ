/*
seg tree + 이분 탐색을 활용하는 문제 
*/
#include <iostream>
#define INF 1000000001

using namespace std;
typedef long long ll;

typedef struct point {
	int idx;
	ll v = INF;
} pt;

pt tree[250001];	// seg tree
int start, n;	// 시작점, input 개수 

int query(int i, int j) {
	i += start - 1;	// 시작 
	j += start - 1;	// 끝 
	
	int min = INF, idx = - 1;	// 최솟값, 최솟값의 index 
	
	// 시작은 끝보다 작거나 같음 
	while(i <= j) {
		// '시작'이 오른쪽에 있는가? 
		if(i % 2 == 1) {
			// 최솟값 갱신 
			if(min > tree[i].v) {
				min = tree[i].v;
				idx = tree[i].idx;
			}
			i++;	// 오른쪽으로 밈 
		}
		// '끝'이 왼쪽에 있는가? 
		if(j % 2 == 0) {
			// 최솟값 갱신 
			if(min > tree[j].v) {
				min = tree[j].v;
				idx = tree[j].idx;
			}
			j--;	// 왼쪽으로 밈 
		}
		i >>= 1; j >>= 1;	// 조상을 찾아 총총... 
	}
	
	return idx;
}

ll maxArea(int s, int e) {
	int idx = query(s, e);	// 최솟값 index 
	
	// index는 0 ~ (n - 1)이므로 
	if(idx + 1 < s || idx + 1 > e) return -1;
	
	ll area = (e - s + 1) * tree[start + idx].v;	// 최솟값을 높이로 하는 직사각형 넓이 
	
	idx++;	// 1 ~ n
	
	// 왼쪽 부분 탐색 
	if(s < idx) {
		ll tmp = maxArea(s, idx - 1);
		area = area > tmp ? area : tmp;
	}
	// 오른쪽 부분 탐색 
	if(idx < e) {
		ll tmp = maxArea(idx + 1, e);
		area = area > tmp ? area : tmp;
	}
	
	return area;
}

void makeTree() {
	int tmp = start + n - 1;	// 끝부분부터 
	tmp >>= 1;	// 그의 조상 
	
	while(tmp > 0) {
		// 최솟값, 그의 index 저장 
		if(tree[tmp << 1].v < tree[(tmp << 1) + 1].v) {
			tree[tmp].v = tree[tmp << 1].v;
			tree[tmp].idx = tree[tmp << 1].idx;
		}
		else {
			tree[tmp].v = tree[(tmp << 1) + 1].v;
			tree[tmp].idx = tree[(tmp << 1) + 1].idx;
		}
		tmp--;
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	while(1) {
		cin >> n;
		
		if(n == 0) return 0;
		
		// 시작 지점 세팅 
		for(start = 1; start < n; start <<= 1);
		for(int i = 0; i < n; i++) {
			cin >> tree[start + i].v;
			tree[start + i].idx = i;
		}
		
		makeTree();
		
		cout << maxArea(1, n) << "\n";
	}
}
