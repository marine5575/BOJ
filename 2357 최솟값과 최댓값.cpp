/*
하나의 트리에 최솟값, 최댓값을 다 저장해서 들고 다니면 된다.
이때 또 런타임 에러가 뜨게 되는데, 어느 부분에서 잘못 참조하는지 아직 모르겠다.
>> 최댓값이 1e9이면 987654321은 쓸 수 없음에 유의! << 
*/
#include <iostream>
#define INF 1000000001

using namespace std;

struct sort {
	int min = INF, max = 0;
};

sort tree[250001];	// seg tree
int start, n, m;	// 실질적 시작 지점, input 개수, 비교 수 

sort query(int i, int j) {
	sort tmp;	// 임시 저장 
	
	i += start - 1;	// 시작 
	j += start - 1;	// 끝 
	
	// 시작은 끝보다 작거나 같다 
	while(i <= j) {
		// '시작'이 오른쪽인가? 
		if(i % 2 == 1) {
			// 최솟값, 최댓값 갱신 
			if(tmp.min > tree[i].min) tmp.min = tree[i].min;
			if(tmp.max < tree[i].max) tmp.max = tree[i].max;
			i++;	// 오른쪽으로 한칸 
		}
		// '끝'이 오른쪽인가? 
		if(j % 2 == 0) {
			// 최솟값, 최댓값 갱신 
			if(tmp.min > tree[j].min) tmp.min = tree[j].min;
			if(tmp.max < tree[j].max) tmp.max = tree[j].max;
			j--;	// 왼쪽으로 한칸 
		}
		i >>= 1; j >>= 1;	// 조상 둘러보기 
	}
	
	return tmp;
}

void makeTree() {
	int tmp = start + n - 1;	// 끝에서부터 시작 
	tmp >>= 1;	// 그의 조상님 
	
	while(tmp > 0) {
		// 최솟값, 최댓값 
		tree[tmp].min = tree[tmp << 1].min < tree[(tmp << 1) + 1].min ? tree[tmp << 1].min : tree[(tmp << 1) + 1].min;
		tree[tmp].max = tree[tmp << 1].max < tree[(tmp << 1) + 1].max ? tree[(tmp << 1) + 1].max : tree[tmp << 1].max;
		tmp--;
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n >> m;
	
	for(start = 1; start < n; start <<= 1);
	for(int i = 0; i < n; i++) {
		cin >> tree[start + i].min;
		tree[start + i].max = tree[start + i].min;
	}
	
	// ☆☆☆☆☆seg tree 만들기☆☆☆☆☆ 
	makeTree();
	
	int i, j;
	
	while(m--) {
		cin >> i >> j;
		sort tmp = query(i, j);	// 찾기
		cout << tmp.min << " " << tmp.max << "\n";
	}
	
	return 0;
}
