#include <cstdio>
#include <set>

using namespace std;

/*
Ʈ���� ��� n���� �ִٸ� ������ n-1�� �����Ѵٴ� Ư¡�� ���� 
*/


int main(void) {
	int cnt = 0;	// �׽�Ʈ ���̽� ��ȣ 
	set<int> node;	// ���ҿ� �ߺ� �� �� 
	
	while(1) {
		int line = 0;	// ���� ���� 
		node.clear();	// ���� �׽�Ʈ���̽� ���� ���� 
			
		while(1) {
			int from, to;	// ���, ���� 
			
			scanf("%d %d", &from, &to);
			
			// �ش� �׽�Ʈ ���̽��� ���� 
			if(from == 0 && to == 0) break;
			// ��� �׽�Ʈ ���̽��� �� 
			if(from == -1 && to == -1) return 0;
			
			node.insert(from); node.insert(to);	// ��� ���� 
			line++;	// ��� 2�� ������ ���� �ϳ��̹Ƿ� 
		}
		
		cnt++;	// 1���� ���� 
		
		// ��尡 ���� �͵� Ʈ�� 
		if(node.size() == 0 || line + 1 == node.size()) printf("Case %d is a tree.\n", cnt);
		else printf("Case %d is not a tree.\n", cnt);
	}
	
	return 0;
}
