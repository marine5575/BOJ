#include <iostream>
#include <cstdio>	// scanf, printf
#include <vector>	// pair, vector
#include <algorithm>	// sort

using namespace std;
typedef pair<int, int> pii;

struct fenwick {
	vector<int> tree;
	
	fenwick(int n) :tree(n+1) {};	// 생성자 
	
	void update(int i, int num) {
		// 트리 크기가 n + 1이므로 
		while (i < tree.size() - 1) {
			tree[i] += num;
			
			// i를 이진수로 표현했을 때의 마지막 1을 구하기 위해 => (i & -i) 
			i += (i & -i); 
		}
	}
	
	// 1 ~ i까지 찾음 
	int query(int i) {
		int ans = 0; 
		
		while(i) {
			ans += tree[i];
			i -= (i & -i);	//  마지막 1을 지움 
		}
		
		return ans;
	}
};

pii person[500001];	// (평소 실력, 현재 등수) 
int result[500001];	// 예상 등수 


int main(void) {
	int n;	// 선수 수 
	scanf("%d", &n);
	
	fenwick fw(n);	// 구조체 생성 
	
	for(int i = 0; i < n; i++) {
		scanf("%d", &person[i].first);
		
		person[i].second = i + 1;
	}
	
	sort(person, person + n);	// (평소 실력 기준) 내림차순으로 정렬 
	
	for(int i = 0; i < n; i++) {
		int idx = person[i].second;	// 현재 등수 
		
		result[idx] = idx - fw.query(idx - 1);	// (자신의 등수) -  (나보다 앞에 있는 실력 안 좋은 사람들 수) 
		fw.update(idx, 1);	// 이미 한 것 더하기 
	}
	
	for(int i = 1; i <= n; i++) printf("%d\n", result[i]);
	
	return 0;
}
