#include <iostream>
#include <cstring>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int dirR[4] = {0, -1, 0, 1};
int dirC[4] = {-1, 0, 1, 0};

int n;
bool isvisited[100][100];
string screen[100];

void InputInfo();
bool isOutOfBound(int r, int c);
int GetSectionNum(bool isColorBlind);
void DFS(int r, int c, char color, bool isColorBlind);

int main(void) {
	fastio;
	InputInfo();
	cout << GetSectionNum(false) << " " << GetSectionNum(true);

	return 0;
}

void InputInfo() {
	cin >> n;

	for (int i = 0; i < n; i++) {
		string tmp;
		cin >> tmp;
		screen[i] = tmp;
	}
}

bool isOutOfBound(int r, int c) {
	if (r < 0 || r >= n || c < 0 || c >= n)
		return true;

	return false;
}

int GetSectionNum(bool isColorBlind) {
	int cnt = 0;
	memset(isvisited, 0, sizeof(isvisited));
	
	if (isColorBlind) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (!isvisited[i][j]) { // 이 if문의 통과가 계속 발생한다...
					cnt++;
					DFS(i, j, screen[i][j], true);
				}
			}
		}
	}
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (!isvisited[i][j]) {
					cnt++;
					DFS(i, j, screen[i][j], false);
				}
			}
		}
	}

	return cnt;
}

void DFS(int r, int c, char color, bool isColorBlind) {
	if (isColorBlind) {
		if (color == 'B') {
			if (color != screen[r][c])
				return;
		}
		else {
			if (screen[r][c] == 'B')
				return;
		}
	}
	else {
		if (screen[r][c] != color)
			return;
	}

	isvisited[r][c] = true;
	int nextR, nextC;

	for (int k = 0; k < 4; k++) {
		nextR = r + dirR[k];
		nextC = c + dirC[k];

		if (!isOutOfBound(nextR, nextC) && !isvisited[nextR][nextC])
			DFS(nextR, nextC, color, isColorBlind);
	}
}