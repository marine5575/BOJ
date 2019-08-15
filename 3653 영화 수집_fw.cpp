/*
Fenwick Tree로 풀었다.
구간 합을 구하는 문제는 fenwick이 훨씬 나은 듯 하다.
공간도 적게 쓰고... 
일단 key point는 n + m 짜리 tree를 만들어서
다 보면 위로 올려놓는 것이었다. 
*/
#include <iostream>

using namespace std;

int arr[100001];	// arr[x] = i : x값을 가지는 것은 tree[i]에 위치하고 있음 
int tree[200001];	// fw tree 
int n, m;	// 비디오 수, 돌려볼 수 

void update(int i, int diff) {
	while(i <= n + m) {
		tree[i] += diff;
		i += (i & -i);
	}
}

int query(int i) {
	int sum = 0;
	
	while(i) {
		sum += tree[i];
		i -= (i & -i);
	}
	
	return sum;
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	int cs;	// 테스트 케이스 
	cin >> cs;
	
	while(cs--) {
		cin >> n >> m;
		int idx = m;	// 이번에 올려 놓을 위치
		// 초기화 
		fill_n(tree, n + m + 1, 0);
		fill_n(arr, n, 0);
		
		// 미리 넣어놓기 
		for(int i = 1; i <= n; i++) {
			update(i + m, 1);
			arr[i] = i + m;
		}
		
		for(int i = 1, x; i <= m; i++) {
			cin >> x;
			// 나보다 앞에 있는 것들 찾기 
			cout << query(arr[x] - 1) << " ";
			update(arr[x], -1);	// 그 위치에서 빼기 
			update(idx, 1);	// 꽂아넣기 
			arr[x] = idx--;	// 갱신 
		}
		
		cout << "\n";
	}
	
	return 0;
} 
