#include <iostream>

using namespace std;

int n, maxi = -1000000001, mini = 1000000001;	// input 개수, 최대값, 최소값 
int input[12], op[4];	// input 배열, op[0 or 1 or 2 or 3] = (plus or minus or mul or div) 개수 

void dfs(int cnt, int sum) {
	// 모든 연산자를 다 사용함 
	if(cnt == n) {
		// 최대, 최소 갱신 
		maxi = maxi < sum ? sum : maxi;
		mini = mini > sum ? sum : mini;
	}
	
	// plus > 0 
	if(op[0]) {
		op[0]--;	// 방문 체크 
		dfs(cnt + 1, sum + input[cnt]);	// 다음 것 방문, sum 갱신 
		op[0]++;	// 방문 해제 
	}
	// minus > 0
	if(op[1]) {
		op[1]--;	// 방문 체크 
		dfs(cnt + 1, sum - input[cnt]); // 다음 것 방문, sum 갱신 
		op[1]++;	// 방문 해제 
	}
	// mul > 0
	if(op[2]) {
		op[2]--;	// 방문 체크 
		dfs(cnt + 1, sum * input[cnt]);	// 다음 것 방문, sum 갱신 
		op[2]++;	// 방문 해제 
	}
	// div > 0
	if(op[3]) {
		op[3]--;	// 방문 체크 
		dfs(cnt + 1, sum / input[cnt]);	// 다음 것 방문, sum 갱신 
		op[3]++;	// 방문 해제 
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) {
		cin >> input[i];
	}
	for(int i = 0; i < 4; i++) {
		cin >> op[i];
	}
	
	dfs(1, input[0]);
	
	cout << maxi << "\n" << mini << "\n";
	
	return 0;
}
