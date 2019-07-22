#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

double prob[51];	// 각각의 경우의 수 저장


int main(void) {
	int m, sum = 0, k, input;	// 색깔 종류, 총 개수 중간 값, 고를 개수, 중간 저장
	vector<int> n;	// 색깔별 개수
	double ans = 0.0;	// 정답

	scanf("%d", &m);

	for (int i = 0; i < m; i++) {
		scanf("%d", &input);
		n.push_back(input);
		sum += input;
	}

	scanf("%d", &k);

	// 색깔 종류 대로
	for (int i = 0; i < m; i++) {
		// 해당 색깔은 고를 개수 이상 있는가?
		if (n[i] >= k) {
			prob[i] = 1.0;

			// 해당 색깔 내에서 모두 고를 확률
			for (int j = 0; j < k; j++) prob[i] *= (double)(n[i] - j) / (sum - j);
		}

		ans += prob[i];	// 색깔별로 확률 더함
	}

	printf("%.15lf\n", ans);

	return 0;
}
