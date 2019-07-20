#include <iostream>
#include <cstdio>	// scanf, printf
#include <vector>	// pair, vector
#include <algorithm>	// sort

using namespace std;
typedef pair<int, int> pii;

struct fenwick {
	vector<int> tree;
	
	fenwick(int n) :tree(n+1) {};	// ������ 
	
	void update(int i, int num) {
		// Ʈ�� ũ�Ⱑ n + 1�̹Ƿ� 
		while (i < tree.size() - 1) {
			tree[i] += num;
			
			// i�� �������� ǥ������ ���� ������ 1�� ���ϱ� ���� => (i & -i) 
			i += (i & -i); 
		}
	}
	
	// 1 ~ i���� ã�� 
	int query(int i) {
		int ans = 0; 
		
		while(i) {
			ans += tree[i];
			i -= (i & -i);	//  ������ 1�� ���� 
		}
		
		return ans;
	}
};

pii person[500001];	// (��� �Ƿ�, ���� ���) 
int result[500001];	// ���� ��� 


int main(void) {
	int n;	// ���� �� 
	scanf("%d", &n);
	
	fenwick fw(n);	// ����ü ���� 
	
	for(int i = 0; i < n; i++) {
		scanf("%d", &person[i].first);
		
		person[i].second = i + 1;
	}
	
	sort(person, person + n);	// (��� �Ƿ� ����) ������������ ���� 
	
	for(int i = 0; i < n; i++) {
		int idx = person[i].second;	// ���� ��� 
		
		result[idx] = idx - fw.query(idx - 1);	// (�ڽ��� ���) -  (������ �տ� �ִ� �Ƿ� �� ���� ����� ��) 
		fw.update(idx, 1);	// �̹� �� �� ���ϱ� 
	}
	
	for(int i = 1; i <= n; i++) printf("%d\n", result[i]);
	
	return 0;
}
