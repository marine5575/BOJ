#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int dp[1001][1001];	// dp[i][j] : a는 i번째까지, b는 j번째까지 봤을 때 공통되는 문자열의 최대 길이
vector<char> ans;	// 나중에 정답 문자열 출력


int main(void) {
	string s1, s2;	// 문자열 a, b
	cin >> s1 >> s2;

	// 문자열의 모든 값에 대해 실행
	for (int i = 1; i <= s1.size(); i++) {
		for (int j = 1; j <= s2.size(); j++) {
			// 검사하는 문자열들이 같은 문자를 가지면 대각선에 있는 값보다 문자열이 1개 더 늘어나게 됨
			if (s1[i - 1] == s2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			// 위에서 오는 놈 혹은 옆에서 오는 놈 중에서 가장 긴 문자열 계승
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	int i = s1.size(), j = s2.size();	// 문자열 길이들

	// 최대 문자열의 길이가 없어질 때까지
	while (dp[i][j] != 0) {
		// 위에서 왔을 경우
		if (dp[i][j] == dp[i - 1][j]) i--;
		// 옆에서 왔을 경우
		else if (dp[i][j] == dp[i][j - 1]) j--;
		// 대각선에서 왔을 경우
		else {
			ans.push_back(s1[i - 1]);	// 같은 문자였을 것이므로
			i--; j--;
		}
	}

	printf("%d\n", dp[s1.size()][s2.size()]);

	// 뒤에서부터 뽑아냈음
	for (int k = ans.size() - 1; k >= 0; k--) printf("%c", ans[k]);
	printf("\n");

	return 0;
}
