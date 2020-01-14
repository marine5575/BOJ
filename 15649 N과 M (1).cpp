#include <iostream>

using namespace std;

int n, m;	// 1부터 N까지 자연수 중에서 중복 없이 M개를 고른 수열
int arr[10], visited[9];	// arr[i] = 고른 m개 중에 i번째 수, visited[j] = 숫자 j의 방문 여부

void dfs(int cnt) {
	// m개를 다 골랐는가? 
	if(cnt == m) {
		// 고른 m개 출력 
		for(int i = 0; i < m; i++) cout << arr[i] << " ";
		cout << "\n";
		
		return;
	}
	
	for(int i = 1; i <= n; i++) {
		// 이미 방문했다면 통과 
		if(visited[i]) continue;
		
		visited[i] = 1;	// 방문 체크 
		arr[cnt] = i;	// cnt번째의 수는 i 
		dfs(cnt + 1);	// 다음 수를 찾아 떠남 
		visited[i] = 0;	// 방문 해제 
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n >> m;
	
	dfs(0);
	
	return 0;
}
