/*
seg tree에서는 tree의 최대 크기에 유의해야 한다.
=> 배열 크기 = input * 4 
*/
#include <stdio.h>
#define INF 1000000001

int tree[400001];	// seg tree
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
	scanf("%d %d", &n, &m);
	
	// tree 크기 대충 가늠 
	for(start = 1; start < n; start <<= 1);
	
	for(int i = 0; i < n; i++) {
		scanf("%d", &tree[start + i]);
	}
	
	makeTree();	// 트리 만들기 
	
	int l, r;	// l ~ r번 까지 살펴봄 
	
	while(m--) {
		scanf("%d %d", &l, &r);
		printf("%d\n", query(l, r));
	}
	
	return 0;
}
