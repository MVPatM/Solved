/*
1. 최댓값 주위로 상자를 놓기 -> 말이 안됨 
why?? -> 최댓값 주위에 큰 수들이 몰려 있다는 근거가 없기 때문이다.
2. 테트로미노를 하나하나 사용해서 전체를 탐색을 하면서 큰값을 찾는 방법 (brute force algorithm)
	-> but we'll use the dfs algorithm.

*/
#include <iostream>
#include <algorithm>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

bool isvisited[500][500];
int row, col, maxValue = 0;
int mat[500][500];
int dirX[4] = { -1, 0, 1, 0 };
int dirY[4] = { 0, -1, 0, 1 };

void InputInfo();
void DoTetra();
void FindMax1(int x, int y, int sum = 0, int depth = 1);
void FindMax2(int x, int y);
inline void PrintMax() { cout << maxValue; }

int main(void) {
	fastio;
	InputInfo();
	DoTetra();
	PrintMax();

	return 0;
}

void InputInfo() {
	cin >> row >> col;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			int tmp;
			cin >> tmp;
			mat[i][j] = tmp;
		}
	}
}

void DoTetra() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			isvisited[i][j] = true;
			FindMax1(j, i);
			isvisited[i][j] = false;
			FindMax2(j, i);
		}
	}
}

void FindMax1(int x, int y, int sum, int depth) {
	if (depth == 4) {
		maxValue = max(maxValue, sum + mat[y][x]);
		return;
	}

	for (int i = 0; i < 4; i++) {
		int next_x, next_y;
		next_x = x + dirX[i];
		next_y = y + dirY[i];

		if (!(next_x < 0 || next_x >= col || next_y < 0 || next_y >= row) && !isvisited[next_y][next_x]) {//not out of bound && not visit
			isvisited[next_y][next_x] = true;
			FindMax1(next_x, next_y, sum + mat[y][x], depth + 1);
			isvisited[next_y][next_x] = false;
		}
	}
}

void FindMax2(int x, int y) {
	if (x >= 1 && x < col - 1 && y >= 1)
		maxValue = max(maxValue, mat[y][x] + mat[y - 1][x] + mat[y][x - 1] + mat[y][x + 1]);
	if (x >= 1 && x < col - 1 && y < row - 1)
		maxValue = max(maxValue, mat[y][x] + mat[y][x - 1] + mat[y][x + 1] + mat[y + 1][x]);
	if (x < col - 1 && y >= 1 && y < row - 1)
		maxValue = max(maxValue, mat[y][x] + mat[y - 1][x] + mat[y + 1][x] + mat[y][x + 1]);
	if (x >= 1 && y >= 1 && y < row - 1)
		maxValue = max(maxValue, mat[y][x] + mat[y - 1][x] + mat[y + 1][x] + mat[y][x - 1]);
}