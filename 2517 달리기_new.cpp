#include <iostream>
#include <cstring>	// memset 
#include <cstdio>	// scanf, printf
#include <vector>	// vector, pair
#include <algorithm>	// sort
#define MAX 20000001	// �Ƿ� �ִ� �� 

using namespace std;
typedef pair<int, int> pii;

int n;	// ���� �� 
vector<pii> person;	// ����� 
int ans[500001];	// ���� ���� 

struct ath {
	int idxT[MAX];	// �ε��� Ʈ�� 
	int size;	// leaf node ���� 
	
	// �ʱ�ȭ 
	void init() {
		memset(idxT, 0, sizeof(idxT));
		for(size = 1; size < n; size <<= 1);
	}
	
	void update(int i) {
		i |= size;	// ���������� i + size 
		idxT[i] = 1;	// �鷶�� 
		
		// �θ� ���鵵 �� ���� 
		while(i >>= 1) idxT[i] = idxT[i << 1] + idxT[i << 1 | 1];
	}
	
	int query(int from, int to) {
		from |= size;
		to |= size;
		int Lvalue = 0, Rvalue = 0;	// ����, �����ʿ��� ������ �� 
		
		// �����: from�� to���� ���ʿ� ���� 
		while(from <= to) {
			// �ָ��ϰ� ��ĥ �� ���� ���� �ִ� ��� ����
			 
			// from�� Ȧ�� 
			if(from & 1) Lvalue += idxT[from++];
			// to�� ¦�� 
			if(!(to & 1)) Rvalue += idxT[to--];
			
			from >>= 1;	to >>= 1;	// �θ� ���� �ö� 
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
	
	sort(person.begin(), person.end());	// ��� �Ƿ� �������� �������� ���� 
	
	// person�� �ٴٸ� ������ ���� 
	for(auto &i : person) {
		int idx = i.second;
		
		ans[idx] = idx - ath.query(1, idx - 1);	// (���� ����) - (�� �տ� �ִ� �Ƿ� ���� ���) 
		ath.update(idx);	// �̹� �鸲 üũ 
	}
	
	for(int i = 1; i <= n; i++) {
		printf("%d\n", ans[i]);
	}
	
	return 0;
}
