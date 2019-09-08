/*
지우는 과정에서 약간 생각이 짧아 많은 오류를 냈던 문제.
지울 때는 자식 노드 두 개 모두 살펴봐야 된다. 
*/
#include <iostream>
#define MAX 1000000
#define INF 987654321

using namespace std;

int heap[MAX + 2], n;	// 힙 정렬할 놈, 전체 개수 

void makeMin() {
	// 원소 하나하나씩 살펴보기 
	for(int i = 2; i <= n; i++) {
		int c = i;	// 임시 
		
		// 루트 노드가 아니면 계속 
		while(c > 1) {
			// 부모가 나보다 크면 바꿈 
			if(heap[c >> 1] > heap[c]) swap(heap[c >> 1], heap[c]);
			c >>= 1;	// 부모로 넘어감 
		}
	}
}

void deleteN(int i) {
	heap[1] = heap[i];	// 첫번째 인자와 끝 인자 바꿈 
	heap[i] = INF;	// 끝 인자 초기화 
	int idx = 1, tmp = idx;	// 내리는 놈 위치, 임시
	
	// 위치의 자식이 모두 원래 끝인자 위치보다 작거나 같을 때 
	while((idx << 1 | 1) <= i) {
		// min heap의 성질 만족 
		if(heap[idx] < heap[idx << 1] && heap[idx] < heap[idx << 1 | 1]) break;
		
		// 왼쪽 자식이 나보다 작을 때 
		if(heap[idx] > heap[idx << 1]) tmp = idx << 1;
		// 오른쪽 자식이 나보다 작을 때 && 오른쪽 자식이 왼쪽 자식보다 작을 때 
		if(heap[idx] > heap[idx << 1 | 1] && heap[tmp] > heap[idx << 1 | 1]) tmp = idx << 1 | 1;
		
		// 바꿔줌 
		swap(heap[idx], heap[tmp]);
		idx = tmp;
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n;
	
//	fill_n(heap, n + 1, INF);
	
	for(int i = 1; i <= n; i++) {
		cin >> heap[i];
	}
	
	makeMin();
	
	for(int i = n; i > 0; i--) {
		cout << heap[1] << "\n";
		// root가 아닐 때 
		if(i > 1) deleteN(i);
	}
	
	return 0;
}
