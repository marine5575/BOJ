#include <iostream>

using namespace std;

int n, m;	// 1부터 N까지 자연수 중에서 중복 없이 M개를 고른 수열
char arr[15];	// 문자열 

void dfs(int cnt) {
	// m개를 다 골랐는가? 
	if(cnt == m) {
		// 고른 m개 출력 
        arr[cnt * 2 - 1] = '\n';
        cout << arr;
		return;
	}
	
	for(int i = 1; i <= n; i++) {
		arr[cnt * 2] = i + '0';	// 문자이므로 '0'을 더해줌 
        arr[cnt * 2 + 1] = ' ';	// 띄어서 출력해야됨 
		dfs(cnt + 1);	// 다음 수를 찾아 떠남
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n >> m;
	
	dfs(0);
	
	return 0;
}
