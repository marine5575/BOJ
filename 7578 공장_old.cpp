#include <cstdio>
#include <vector> 

using namespace std;
struct fenwick {
	vector<int> tree;	// fenwick tree
	
	fenwick(int n) :tree(n+1) {};
	
	// i 보다 위에 있는 모든 값을 합침 
	long long sum(int i) {
		long long ans = 0;	// 더하는거라 int 범위 넘칠 수도 있음 
		
		while(i < tree.size()) {
			ans += tree[i];
			i += (i & -i);	// 기어올라가기 
		}
		
		return ans;
	}
	
	// i번째보다 밑에 있는 것들 +1 해줌
	void update(int i) {
		// 홀수는 나중에 더할 때 첫번째 빼고 안 더함.
		// 그래서 밑으로 잘 저장하는 것이 필요 
		while(i) {
			tree[i]++;
			i -= (i & -i);
		}
	}
};

int arr[1000001];	// arr[x] = i : x라는 번호를 가지는 기계가 i번째에 들어옴 


int main(void) {
	int n;	// 기계 수 
	scanf("%d", &n);
	
	fenwick fw(n);	// 트리 초기화 
	
	for(int i = 1, a; i <= n; i++) {
		scanf("%d", &a);
		arr[a] = i;
	}
	
	// 내가 연결될 때, 나보다 크면서 먼저 연결된 놈들  
	long long ans = 0;	// 케이블 꼬인 숫자 
	
	for(int i = 1, a; i <= n; i++) {
		scanf("%d", &a);
		
		ans += fw.sum(arr[a]);	// 나보다 큰 것들 살펴 봄 
		fw.update(arr[a]);	// 연결되었음을 표시 
	}
	
	printf("%lld\n", ans);
	
	return 0;
}
