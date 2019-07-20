#include <iostream>
#include <cstring>	// memset 
#include <cstdio>	// scanf, printf
#include <vector>	// vector, pair
#include <algorithm>	// sort
#define MAX 20000001	// 실력 최대 값 

using namespace std;
typedef pair<int, int> pii;

int n;	// 선수 수 
vector<pii> person;	// 사람들 
int ans[500001];	// 예상 순위 

struct ath {
	int idxT[MAX];	// 인덱스 트리 
	int size;	// leaf node 개수 
	
	// 초기화 
	void init() {
		memset(idxT, 0, sizeof(idxT));
		for(size = 1; size < n; size <<= 1);
	}
	
	void update(int i) {
		i |= size;	// 실질적으로 i + size 
		idxT[i] = 1;	// 들렀음 
		
		// 부모 노드들도 다 갱신 
		while(i >>= 1) idxT[i] = idxT[i << 1] + idxT[i << 1 | 1];
	}
	
	int query(int from, int to) {
		from |= size;
		to |= size;
		int Lvalue = 0, Rvalue = 0;	// 왼쪽, 오른쪽에서 조사한 값 
		
		// 절대식: from은 to보다 왼쪽에 있음 
		while(from <= to) {
			// 애매하게 합칠 수 없는 곳에 있는 경우 갱신
			 
			// from이 홀수 
			if(from & 1) Lvalue += idxT[from++];
			// to가 짝수 
			if(!(to & 1)) Rvalue += idxT[to--];
			
			from >>= 1;	to >>= 1;	// 부모 노드로 올라감 
		}
		
		return Lvalue + Rvalue;
	}
} ath;


int main(void) {
	scanf("%d", &n);
	
	person.resize(n);
	ath.init();
	
	for(int i = 0; i < n; i++) {
		int tmp;
		
		scanf("%d", &tmp);
		
		person[i] = {tmp, i + 1};
	}
	
	sort(person.begin(), person.end());	// 평소 실력 기준으로 오름차순 정렬 
	
	// person의 다다를 때까지 꺼냄 
	for(auto &i : person) {
		int idx = i.second;
		
		ans[idx] = idx - ath.query(1, idx - 1);	// (현재 순위) - (내 앞에 있는 실력 없는 놈들) 
		ath.update(idx);	// 이미 들림 체크 
	}
	
	for(int i = 1; i <= n; i++) {
		printf("%d\n", ans[i]);
	}
	
	return 0;
}
