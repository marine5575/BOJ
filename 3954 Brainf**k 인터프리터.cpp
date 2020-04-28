/*********************************/
// BOJ 3954 Brainf**k 인터프리터
// 핵심: 시뮬레이션 + 스택
// 			 => 1. 들어오기만 하고 못 나간게 있으면 무한 루프
// 					2. 최대 인덱스가 sc가 아니면 루프 도는 중 
/*********************************/
#include <stdio.h>
#include <string.h>
#include <stack>
#define MAX_CODE 	4100
#define MAX_MEM		((int)1e5 + 1)
#define INF 			((int)5e7)

using namespace std;

int tc, sm, sc, si;	// 테스트 케이스 개수, 메모리 크기, 코드 길이, 입력 길이 
int memIdx, readIdx;	// 메모리 포인터, 입력 포인터 
int left[MAX_CODE], right[MAX_CODE];	// left[i] = i번 '['의 짝의 위치, right[i] = i번 ']'의 짝의 위치 
char mem[MAX_MEM];	// 메모리 
char code[MAX_CODE], input[MAX_CODE];	// 코드, 입력 파일 
stack<int> parenth;	// 괄호 짝 찾는 stack 

void input_Data(void) {
	scanf("%d %d %d", &sm, &sc, &si);
	scanf(" %s", code);
	scanf(" %s", input);
	
	memIdx = readIdx = 0;	// 초기화 
	
	for(int i = 0; i < sc; i++) {
		if(code[i] == '[') parenth.push(i);
		else if(code[i] == ']') {
			int idx = parenth.top(); parenth.pop();
			right[i] = idx;
			left[idx] = i;
		}
	}
}

int sol(void) {
	int idx = 0, maxIdx = 0;	// 코드 포인터, 최대 포인터 위치 
	char visited[MAX_CODE] = {0, };	// visited[i] = i번 괄호로 들어옴 
	
	for(int i = 0; i < INF; i++) {
		int flag = 0;	// idx를 하나 증가할까 깃발 
		
		switch(code[idx]) {
			// 메모리 포인터가 가리키는 수 -1 
			case '-': {
				mem[memIdx] = ((int)(mem[memIdx]) + 255) % 256;
				break;
			}
			// 메모리 포인터가 가리키는 수 +1
			case '+': {
				mem[memIdx] = ((int)(mem[memIdx]) + 1) % 256;
				break;
			}
			// 메모리 포인터 -1 
			case '<': {
				memIdx = (memIdx + sm - 1) % sm;
				break;
			}
			// 메모리 포인터 +1
			case '>': {
				memIdx = (memIdx + 1) % sm;
				break;
			}
			// 점프 or not 
			case '[': {
				// 가리키는 수가 0 => 짝으로 점프 
				if(!mem[memIdx]) {
					idx = left[idx];
					flag = 1;
				}
				// 점프 안함 => 걍 들어옴 
				else visited[idx] = 1;
				break;
			}
			// 점프 or not 
			case ']': {
				// 가리키는 수가 0이 아님 => 짝으로 점프 
				if(mem[memIdx]) {
					idx = right[idx];
					flag = 1;
				}
				// 점프 안함 => 걍 나감ㅂㅂ 
				else visited[right[idx]] = 0;
				break;
			}
			// 입력 포인터에 있는 것을 메모리에 쓰고 포인터 +1
			// 단, 입력 포인터가 EOF를 가리키면 255를 씀 
			case ',': {
				if(readIdx < si) mem[memIdx] = input[readIdx++];
				else mem[memIdx] = 255;
				break;
			}
		}
		
		if(!flag) idx++;
		// 최대 갔던 idx 저장 
		if(maxIdx < idx) maxIdx = idx;
		
		// 조기 종료~ 
		if(idx >= sc) break;
	}

// 1. 들어온 흔적 남아있는가? 
//	for(int i = 0; i < sc; i++) {
//		if(visited[i]) return i;
//	}
	
	return maxIdx;
}


int main(void) {
	scanf("%d", &tc);
	
	while(tc--) {
		memset(left, 0, sizeof(left));
		memset(right, 0, sizeof(right));
		memset(mem, 0, sizeof(mem));
		
		input_Data();
		int start = sol();
		
		if(start != sc) printf("Loops %d %d\n", right[start], start);
		else printf("Terminates\n");
	}
	
	return 0;
}
