#include <iostream>

using namespace std;

int map[10][10];	// 스도쿠 판 
bool row[10][10], col[10][10], square[10][10];	// row[i][j] = true: i번째 행에 숫자 j 존재, col[i][j] = true: i번째 열에 숫자 j 존재, square[i][j] = true: i번 사각형 영역에 숫자 j 존재 

// 역추적엔 역시 dfs 
void dfs(int cnt) {
	// 모든 칸을 다 봤는가? 
	if(cnt == 81) {
		// 출력 
		for(int j = 0; j < 9; j++) {
			for(int i = 0; i < 9; i++) {
				cout << map[j][i] << " ";
			}
			cout << "\n";
		}
		
		exit(0);	// 강.제.종.료. 
	}
	
	int x = cnt % 9;	// x좌표 
	int y = cnt / 9;	// y좌표 
	
	// 빈칸인가? 
	if(!map[y][x]) {
		// 모든 숫자 다 검사 
		for(int j = 1; j <= 9; j++) {
			// 같은 행, 열, 사각형에 모두 이 숫자가 존재하지 않는가? 
			if(!row[y][j] && !col[x][j] && !square[y / 3 * 3 + x / 3][j]) {
				// 방문 체크 
				map[y][x] = j;
				row[y][j] = true;
				col[x][j] = true;
				square[y / 3 * 3 + x / 3][j] = true;
				
				dfs(cnt + 1);	// 앞으로! 
				
				// 방문 해제 
				map[y][x] = 0;
				row[y][j] = false;
				col[x][j] = false;
				square[y / 3 * 3 + x / 3][j] = false;
			}
		}
	}
	else dfs(cnt + 1);	// 다음 칸 확인  
}


int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	for(int j = 0; j < 9; j++) {
		for(int i = 0; i < 9; i++) {
			cin >> map[j][i];
			
			if(map[j][i]) {
				row[j][map[j][i]] = true;
				col[i][map[j][i]] = true;
				square[j / 3 * 3 + i / 3][map[j][i]] = true;
			}
		}
	}
	
	dfs(0);
	
	return 0;
}
