#include <iostream>
#include <cmath>	// abs 함수 

using namespace std;

int n, cnt = 0, row[16];	// input, 경우의 수, row[i] = a : (a, i)에 queen 위치함 

void nQueen(int y) {
	// 마지막 줄까지 다 찾음 
	if(y == n) {
		cnt++;
		return;
	}
	
	// x좌표 유랑 
	for(int r = 0; r < n; r++) {
		int flag = 1;	// 쓸만한 값은 1, 아니면 0 
		
		// 이전 queen을 살펴보기 
		for(int j = 0; j < y; j++) {
			// 같은 열에 존재하거나(x좌표 동일) 대각선에 위치 
			if(row[j] == r || y - j == abs(row[j] - r)) {
				flag = 0;
				break;
			}
		}
		
		// 쓸만한 값인가? 
		if(flag) {
			row[y] = r;
			nQueen(y + 1);	// 다음 queen을 배치하자 
		}
	}
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n;
	
	nQueen(0);
	
	cout << cnt << "\n";
	
	return 0;
}
