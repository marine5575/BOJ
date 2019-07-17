#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

vector<int> adj[501];	// ȭ���� �޴� ��尡 �� �ֵ� ��Ƶ� �� 
int cost[501];	// ��� ���࿡ �ɸ��� �ִ� �ð� 

// �ִ� ��ȯ 
int max(int a, int b) {
	return (a > b) ? a : b;
}

void update(int n) {
	int diff = 0;	// �ִ� �ð��� ������ ���� 
	
	for (auto i = adj[n].begin(); i != adj[n].end(); i++) {
		update(*i);	// �Ž��� �ö� 
		diff = max(diff, cost[*i]);	// ������� �� �ִ� �ð� ���� 
	}
	
	adj[n].clear();	// ���� ���캼 ��� ���� 
	cost[n] += diff;	// ���� ����� �ִ� �ð� 
}


int main(void) {
	int N;	// ��� �� 
	
	scanf("%d", &N);
	
	for(int i = 0; i < N; i++) {
		int c, from;	// ��, �켱�Ǵ� ��� 
		
		scanf("%d", &c);
		
		cost[i] = c;	// �� ��� �ܵ� ���� �ð� ���� 
		
		while(scanf("%d", &from) && from != -1) {
			adj[i].push_back(--from);	// ��� ���� �켱�Ǵ� ��� ���� 
		}
	}
	
	for(int i = 0; i < N; i++) {
		update(i);	// �ִ� �ð� ���� 
		
		printf("%d\n", cost[i]);
	}
	
	return 0;
} 
