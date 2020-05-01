/*******************/
// BOJ 1062 가르침
// 핵심: DFS (조합) & 경계 조건
// 			 => 1) 처음에 반드시 순열인지 조합인지 판단
// 					2) 경계 조건에 부합하는지 반드시 판단! 
/*******************/

// 1. 그냥 평소에 하던 완전 탐색 => 124ms
#if 0

#include <stdio.h>
#define MAX_WORD 	51
#define MAX_LEN		25

int n, k, max;	// 단어의 개수, 가르칠 문자 개수, 읽을 수 있는 최대 단어 수 
char word[MAX_WORD][MAX_LEN];
char learned[27];	// 배운 문자 

inline int char_to_Idx(char ch) {
	return ch - 'a';
}

void input_Data(void) {
	scanf("%d %d", &n, &k);
	
	for(int i = 0; i < n; i++) {
		scanf("%s", word[i]);
	}
	
	learned[char_to_Idx('a')] = learned[char_to_Idx('n')] = 1;
	learned[char_to_Idx('t')] = learned[char_to_Idx('i')] = 1;
	learned[char_to_Idx('c')] = 1;
}

int count(void) {
	// 읽을 수 있는 단어 수 세는 함수
	 
	int cnt = 0;	// 읽을 수 있는 단어 수 
	
	for(int i = 0; i < n; i++) {
		int flag = 0;	// 조기 종료 깃발 
		
		for(int j = 4; word[i][j] != 0; j++) {
			// 배운 문자가 아님 
			if(!learned[char_to_Idx(word[i][j])]) {
				flag = 1;
				break;
			}
		}
		
		// 모두 배운 문자였을 때 
		if(!flag) cnt++;
	}
	
	return cnt;
}

void dfs(int here, int cnt) {
	// 직전에 cnt개의 글자를 가르침. 이번에 idx번부터 살펴볼 차례 
	
	// k개 모두 가르침 
	if(cnt >= k) {
		int num = count();	// 이번에 읽을 수 있는 단어수
		// 최대값 갱신 
		if(max < num) max = num;
		return;
	}
	
	for(int i = here; i < 26; i++) {
		// 이미 배웠음 
		if(learned[i]) continue;
		
		learned[i] = 1;
		dfs(i + 1, cnt + 1);
		learned[i] = 0;
	}
}

int sol(void) {
	// anta, tica도 못 읽음ㅡㅡ 
	if(k < 5) return 0;
	
	dfs(1, 5);
	
	return max;
}


int main(void) {
	input_Data();
	printf("%d\n", sol());
	
	return 0;
}
#endif

// 2. 비트마스킹 이용 => 20ms
// 		(0 ~ 31bits 안쪽에서 방문 여부만 표시할 때는 비트마스킹 활용
// 		 특히 문자열에 포함된 문자 셀 때 유용)
#if 0

#include <stdio.h>
#define MAX_WORD 	51
#define MAX_LEN 	25

int n, k, maxNum;	// 단어의 개수, 가르칠 문자의 개수, 배울 수 있는 단어의 최대 개수 
int learned;	// 배운 문자 표시 (0 ~ 25bits: 'a' ~ 'z'까지의 배움 유무) 
int word[MAX_WORD];	// word에 포함된 문자 표시 
char buf[MAX_LEN];	// 임시 저장소 

inline int char_to_Idx(char ch) {
	return ch - 'a';
}

void input_Data(void) {
	scanf("%d %d", &n, &k);
	
	for(int i = 0; i < n; i++) {
		scanf("%s", buf);
		
		for(int j = 0; buf[j] != 0; j++) {
			word[i] |= (1 << char_to_Idx(buf[j]));
		}
	}
	
	learned |= (1 << char_to_Idx('a')) | (1 << char_to_Idx('n'));
	learned |= (1 << char_to_Idx('t')) | (1 << char_to_Idx('i'));
	learned |= (1 << char_to_Idx('c'));
}

inline int max(int a, int b) {
	return a > b ? a : b;
}

int count(void) {
	// 배울 수 있는 단어의 수 세는 함수
	 
	int cnt = 0;	// 배울 수 있는 단어의 수 
	
	for(int i = 0; i < n; i++) {
		// word[i]에 있는 단어를 배운 문자로 모두 표현할 수 있는가? 
		if((word[i] & ~learned) == 0) cnt++;
	}
	
	return cnt;
}

void dfs(int here, int cnt) {
	// 이번에 here부터 볼 차례, 직전에 cnt개 배웠음
	
	// 모두 배움 
	if(cnt >= k) {
		// 최대값 갱신 
		maxNum = max(maxNum, count());
		
		return;
	}
	
	for(int i = here; i < 26; i++) {
		// 이미 배움 
		if((learned >> i) & 1) continue;
		
		learned |= (1 << i);
		dfs(i + 1, cnt + 1);
		learned &= ~(1 << i);
	}
}

int sol(void) {
	// anta, tica도 못 씀;ㅅ; 
	if(k < 5) return 0;
	
	dfs(0, 5);
	
	return maxNum;
}


int main(void) {
	input_Data();
	
	printf("%d\n", sol());
	
	return 0;
}
#endif
