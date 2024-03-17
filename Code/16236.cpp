#include <iostream>
#include <utility>
#include <queue>
#include <cstring>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using cord = pair<int, int>; // (row, column)

int dirR[4] = { -1, 0, 0, 1 }; // up, left, right, down
int dirC[4] = { 0, -1, 1, 0 }; // up, left, right, down

cord SharkPos;
int Time, sz, sharksz = 2;
bool isvisited[20][20];
int GameBoard[20][20];
int countTime[20][20];

void InputInfo();
bool FindGame(); // game은 사냥의 대상이 되는 짐승이나 새를 의미한다.
bool isOutofBound(int r, int c);
void DoSharkGame();

int main(void) {
	fastio;
	InputInfo();
	DoSharkGame();
	cout << Time;

	return 0;
}

void InputInfo() {
	cin >> sz;

	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < sz; j++) {
			int tmp;
			cin >> tmp;
			if (tmp == 9) {
				SharkPos.first = i;
				SharkPos.second = j;
			}

			GameBoard[i][j] = tmp;
		}
	}
}

bool FindGame() { // 먹잇감을 하나 찾으면 return true
	memset(isvisited, 0, sizeof(isvisited));
	memset(countTime, 0, sizeof(countTime));

	// default set
	int tmpR = 20;
	int tmpC = 20;
	int tmpD = 1000;
	queue<cord> q;
	q.push(SharkPos);
	isvisited[SharkPos.first][SharkPos.second] = true;

	// queue가 empty인 경우가 없는 경우
	while (!q.empty()) {
		int nextR, nextC;
		int curR = q.front().first;
		int curC = q.front().second;
		q.pop();

		// 다음에 이동할 좌표를 선택을 한다.
		for (int i = 0; i < 4; i++) {
			nextR = curR + dirR[i];
			nextC = curC + dirC[i];

			if (isOutofBound(nextR, nextC) || GameBoard[nextR][nextC] > sharksz) // 물고기의 크기가 상어의 크기보다 커서 못가거나 outofbound
				continue;
			else if (GameBoard[nextR][nextC] > 0 && GameBoard[nextR][nextC] < sharksz) { // 물고기를 먹는 행위
				isvisited[nextR][nextC] = true;
				countTime[nextR][nextC] = countTime[curR][curC] + 1;

				if (tmpD > countTime[nextR][nextC]) { // 먹는 물고기의 최단 거리가 더 짧은 경우
					tmpR = nextR;
					tmpC = nextC;
					tmpD = countTime[nextR][nextC];
				}
				else if (tmpD == countTime[nextR][nextC]) { // 최단거리가 같을 때
					if (nextR < tmpR) { // 가장 위쪽에 있는 것을 선택
						tmpR = nextR;
						tmpC = nextC;
					}
					else if (nextR == tmpR && nextC < tmpC) // 높이가 같으면 가장 왼쪽에 있는 물고기를 선택
						tmpC = nextC;
				}
			}
			else if (!isvisited[nextR][nextC]) {  // 다음 탐색할 위치를 queue에 넣는 것
				q.emplace(nextR, nextC);
				isvisited[nextR][nextC] = true;
				countTime[nextR][nextC] = countTime[curR][curC] + 1;
			}
		}
	}

	// 계속 true로 나오는 경우
	if (tmpD != 1000) {
		Time += tmpD;
		GameBoard[SharkPos.first][SharkPos.second] = 0;
		SharkPos.first = tmpR;
		SharkPos.second = tmpC;
		GameBoard[SharkPos.first][SharkPos.second] = 9;
		return true;
	}

	return false;
}

bool isOutofBound(int r, int c) {
	if (r < 0 || r >= sz || c < 0 || c >= sz)
		return true;

	return false;
}

void DoSharkGame() {
	int szCount = 0;

	while (FindGame()) {
		if (++szCount == sharksz) {
			sharksz++;
			szCount = 0;
		}
	}
}