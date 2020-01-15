#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int n, mini = 123456789;
int map[21][21], visited[21];


void dfs(int player, int cnt) {
	if(cnt == n / 2) {
		vector<int> start, link;
		
		for(int i = 0; i < n; i++) {
			if(visited[i]) start.push_back(i);
			else link.push_back(i);
		}
		
		int ptStart = 0, ptLink = 0;
		for(int i = 0; i < n / 2; i++) {
			for(int j = i; j < n / 2; j++) {
				ptStart += map[start[i]][start[j]] + map[start[j]][start[i]];
				ptLink += map[link[i]][link[j]] + map[link[j]][link[i]];
			}
		}
		
		mini = mini > abs(ptStart - ptLink) ? abs(ptStart - ptLink) : mini;
		return;
	}
	
	for(int i = player + 1; i < n; i++) {
		if(visited[i]) continue;
		
		visited[i] = 1;
		dfs(i, cnt + 1);
		visited[i] = 0;
	}
}


int main(void) {
	cin >> n;
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			cin >> map[j][i];
		}
	}
	
	dfs(0, 0);
	
	cout << mini << "\n";
	
	return 0;
}
