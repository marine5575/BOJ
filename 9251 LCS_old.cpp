/*
공간을 좀 많이 잡아먹는 알고리즘 
*/
#include <iostream>
#include <string>

using namespace std;

int dp[1002][1002];	// dp[i][j] = A : s2의 i번째, s1의 j번째까지 도달했을 때의 최장 수열 길이 


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	string s1, s2;
	cin >> s1 >> s2;
	
	// s2의 모든 원소 확인 
	for(int i = 1; i <= s2.size(); i++) {
		// s1의 모든 원소 확인 
		for(int j = 1; j <= s1.size(); j++) {
			// 글자가 일치하는가?
			// 대각선에 있는 값 + 1 
			if(s1[j - 1] == s2[i - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
			// 일치하지 않는 경우
			// 더 큰 값 저장 
			else {
				dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
			}
		}
	}
	
	cout << dp[s2.size()][s1.size()] << "\n";
	
	return 0;
}
