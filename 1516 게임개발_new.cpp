#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

vector<int> adj[501];	// 화살을 받는 노드가 쏜 애들 모아둔 것 
int cost[501];	// 노드 실행에 걸리는 최대 시간 

// 최댓값 반환 
int max(int a, int b) {
	return (a > b) ? a : b;
}

void update(int n) {
	int diff = 0;	// 최대 시간에 더해질 아이 
	
	for (auto i = adj[n].begin(); i != adj[n].end(); i++) {
		update(*i);	// 거슬러 올라감 
		diff = max(diff, cost[*i]);	// 여기까지 온 최대 시간 결정 
	}
	
	adj[n].clear();	// 이제 살펴볼 노드 없음 
	cost[n] += diff;	// 현재 노드의 최대 시간 
}


int main(void) {
	int N;	// 노드 수 
	
	scanf("%d", &N);
	
	for(int i = 0; i < N; i++) {
		int c, from;	// 값, 우선되는 노드 
		
		scanf("%d", &c);
		
		cost[i] = c;	// 각 노드 단독 실행 시간 저장 
		
		while(scanf("%d", &from) && from != -1) {
			adj[i].push_back(--from);	// 노드 별로 우선되는 노드 저장 
		}
	}
	
	for(int i = 0; i < N; i++) {
		update(i);	// 최대 시간 갱신 
		
		printf("%d\n", cost[i]);
	}
	
	return 0;
} 
