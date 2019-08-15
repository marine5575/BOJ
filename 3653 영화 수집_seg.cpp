/*
seg tree로 풀어보았다.
seg tree는 빠르고 다 좋아.
근데 segmentation fault가 너무 싫다. (런타임 에러) 
그냥 2 * n - 1에 끝낼 수 있는 놈을 연습하자. 
*/
#include <iostream>

using namespace std;

int tree[800001];	// seg tree
int arr[100002];	// arr[x] = i : x는 i에 들어있음 
int n, m, start;	// 비디오 수, 꺼내 볼 수, 시작 지점 

void update(int i, int diff) {
	i += start;	// 처음 세팅 
	
	while(i) {
		tree[i] += diff;
		i >>= 1;
	}
}

int query(int i, int j) {
	i += start;	// 시작 
	j += start;	// 끝 
	
	int sum = 0;	// 합 
	
	while(i <= j) {
		if(i % 2 == 1) sum += tree[i++];
		if(j % 2 == 0) sum += tree[j--];
		i >>= 1; j >>= 1;
	}
	
	return sum;
}

void makeTree() {
	int i = start + n + m - 1;	// 여기서부터 
	i >>= 1;	// 그의 조상 
	
	while(i > 0) {
		tree[i] = tree[i << 1] + tree[i << 1 | 1];
		i--;
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	int cs;	// 테스트 케이스 
	cin >> cs;
	
	while(cs--) {
		cin >> n >> m;
		int idx = m - 1;	// 꽂을 곳
		// 초기화 
		fill_n(tree, 4 * (n + m), 0);
		fill_n(arr, n + 1, 0);
		
		// 시작 지점 세팅 
		for(start = 1; start < n + m; start <<= 1);
		for(int i = 0; i < n; i++) {
			tree[i + m + start] = 1;
			arr[i + 1] = i + m;
		}
		
		makeTree();
		
		for(int i = 0, x; i < m; i++) {
			cin >> x;
			cout << query(0, arr[x] - 1) << " ";
			update(arr[x], -1);
			update(idx, 1);
			arr[x] = idx--;
		}
		
		cout << "\n";
	}
	
	return 0;
} 
