#include <cstdio>
#include <set>

using namespace std;

/*
트리는 노드 n개가 있다면 간선이 n-1개 존재한다는 특징이 있음 
*/


int main(void) {
	int cnt = 0;	// 테스트 케이스 번호 
	set<int> node;	// 원소에 중복 안 들어감 
	
	while(1) {
		int line = 0;	// 간선 개수 
		node.clear();	// 이전 테스트케이스 흔적 삭제 
			
		while(1) {
			int from, to;	// 출발, 도착 
			
			scanf("%d %d", &from, &to);
			
			// 해당 테스트 케이스의 종료 
			if(from == 0 && to == 0) break;
			// 모든 테스트 케이스의 끝 
			if(from == -1 && to == -1) return 0;
			
			node.insert(from); node.insert(to);	// 노드 삽입 
			line++;	// 노드 2개 사이의 간선 하나이므로 
		}
		
		cnt++;	// 1부터 시작 
		
		// 노드가 없는 것도 트리 
		if(node.size() == 0 || line + 1 == node.size()) printf("Case %d is a tree.\n", cnt);
		else printf("Case %d is not a tree.\n", cnt);
	}
	
	return 0;
}
