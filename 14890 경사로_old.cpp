/***************************/
// BOJ 14890 경사로
// << 내가 처음 푼 ver >> 
// 핵심:  경우의 수 나누기
/***************************/
#include <iostream>

using namespace std;

int n, len, ans;	// map 크기, 경사로 길이, 정답 
int map[101][101];

void rowCheck(void);
void colCheck(void);


/*********** MAIN ***********/

int main(void) {
	cin.tie(0);
	ios::sync_with_stdio(0);

	cin >> n >> len;
	
	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) {
			cin >> map[j][i];
		}
	}
	
	rowCheck();
	colCheck();
	
	cout << ans << "\n";
	
	return 0;
}


/************** FUNCTIONS ***************/

void rowCheck(void) {
	for(int j = 0; j < n; j++) {
		int pt, d_flag = 0, u_flag = 1, road = 1;	// 영점, 내려갈 때, 올라갈 때, 길인지 판단 
		 
		for(int i = 0; i < n; i++) {
			// 첫번째는 통과 
			if(i == 0) {
				pt = map[j][i];
				continue;
			}
			
			// 영점과 같은 높이 & 이전과 같은 높이 
			if(pt == map[j][i] && map[j][i] == map[j][i - 1]) {
				u_flag++;	// 올라갈 potential 
				continue;
			}
			
			// 내려갈려는 중 아니었음 & 이전과 같지 않아 => 길 아님 
			if(d_flag != 0 && map[j][i] != map[j][i - 1]) {
				road = 0;
				break;
			}
			
			// 내려가야 됨 
			if(pt > map[j][i]) {
				// 내가 너무 높아 => 길 아님 
				if(pt != map[j][i] + 1) {
					road = 0;
					break;
				}
				
				d_flag++;
				
				// 경사로 놓기 => 내려옴 
				if(d_flag == len) {
					pt = map[j][i];
					d_flag = 0;
					u_flag = 0;
				}
				// 경사로 못 놓는 맨 끝 => 길 아님 
				else if(i == n - 1){
					road = 0;
					break;
				}
			}
			// 올라가야 됨 
			else {
				// 내가 너무 낮아 or 경사로 못 놓음 => 길 아님 
				if(pt != map[j][i] - 1 || u_flag < len) {
					road = 0;
					break;
				}
				
				u_flag = 1;
				d_flag = 0;
				pt = map[j][i];
			}
		}
		
		// 길이었나? 
		if(road) ans++;
	}
}


void colCheck(void) {
	for(int i = 0; i < n; i++) {
		int pt, d_flag = 0, u_flag = 1, road = 1;	// 영점, 내려갈 때, 올라갈 때, 길인지 판단 
		 
		for(int j = 0; j < n; j++) {
			// 첫번째는 통과 
			if(j == 0) {
				pt = map[j][i];
				continue;
			}
			
			// 영점과 같은 높이 & 이전과 같은 높이 			
			if(pt == map[j][i] && map[j - 1][i] == map[j][i]) {
				u_flag++;
				continue;
			}
			
			// 내려갈려는 중 아니었음 & 이전과 같지 않아 => 길 아님
			if(d_flag != 0 && map[j][i] != map[j - 1][i]) {
				road = 0;
				break;
			}
			
			// 내려가야 됨 
			if(pt > map[j][i]) {
				// 내가 너무 높아 => 길 아님 
				if(pt != map[j][i] + 1) {
					road = 0;
					break;	
				}
				
				d_flag++;
				
				// 경사로 놓기 => 내려옴 
				if(d_flag == len) {
					pt = map[j][i];
					d_flag = 0;
					u_flag = 0;
				}
				// 경사로 못 놓는 맨 끝 => 길 아님 
				else if(j == n - 1){
					road = 0;
					break;
				}
			}
			// 올라가야 됨 
			else {
				// 내가 너무 낮아 or 경사로 못 놓음 => 길 아님 
				if(pt != map[j][i] - 1 || u_flag < len) {
					road = 0;
					break;
				}
				
				u_flag = 1;
				d_flag = 0;
				pt = map[j][i];
			}
		}
		
		// 길이었나? 
		if(road) ans++;
	}
}
