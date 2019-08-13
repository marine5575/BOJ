/*
seg tree에서는 tree의 최대 크기에 유의해야 한다.
1. input <= 50000  =>  input * 4
2. 50000 < input < 1000000  => input * 2 + 바로 밑에 반복 (ex. 220000)
3. input > 1000000  => input * 2 + 50000 
*/
#include <iostream>
#define INF 987654321

using namespace std;

int tree[220001];	// seg tree
int start, n, m;	// 시작 지점, input 개수, (a, b) 쌍 개수 

int query(int i, int j) {
	i += start - 1;	// 시작 
	j += start - 1;	// 끝 
	
	int min = INF;	// 최솟값 
	
	// 시작은 끝보다 작거나 같다 
	while(i <= j) {
		// '시작'이 오른쪽에 위치? 
		if(i % 2 == 1) {
			// 최솟값 갱신 
			if(min > tree[i]) min = tree[i];
			i++;
		}
		// '끝'이 왼쪽에 위치? 
		if(j % 2 == 0) {
			// 최솟값 갱신 
			if(min > tree[j]) min = tree[j];
			j--;
		}
		// 기어오르기 
		i >>= 1; j >>= 1;
	}
	
	return min;
}

void makeTree() {
	int tmp = start + n - 1;	// 가장 끝의 애부터 
	tmp >>= 1;	// 그 애의 조상 
	
	while(tmp > 0) {
		// 최솟값 저장 
		tree[tmp] = tree[tmp << 1] > tree[(tmp << 1) + 1] ? tree[(tmp << 1) + 1] : tree[tmp << 1];
		tmp--;
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n >> m;
	
	// tree 크기 대충 가늠 
	for(start = 1; start < n; start <<= 1);
	
	for(int i = 0; i < n; i++) {
		cin >> tree[start + i];
	}
	
	makeTree();	// 트리 만들기 
	
	int l, r;	// l ~ r번 까지 살펴봄 
	
	while(m--) {
		cin >> l >> r;
		cout << query(l, r) << "\n";
	}
	
	return 0;
}
