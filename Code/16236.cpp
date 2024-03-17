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
bool FindGame(); // game�� ����� ����� �Ǵ� �����̳� ���� �ǹ��Ѵ�.
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

bool FindGame() { // ���հ��� �ϳ� ã���� return true
	memset(isvisited, 0, sizeof(isvisited));
	memset(countTime, 0, sizeof(countTime));

	// default set
	int tmpR = 20;
	int tmpC = 20;
	int tmpD = 1000;
	queue<cord> q;
	q.push(SharkPos);
	isvisited[SharkPos.first][SharkPos.second] = true;

	// queue�� empty�� ��찡 ���� ���
	while (!q.empty()) {
		int nextR, nextC;
		int curR = q.front().first;
		int curC = q.front().second;
		q.pop();

		// ������ �̵��� ��ǥ�� ������ �Ѵ�.
		for (int i = 0; i < 4; i++) {
			nextR = curR + dirR[i];
			nextC = curC + dirC[i];

			if (isOutofBound(nextR, nextC) || GameBoard[nextR][nextC] > sharksz) // ������� ũ�Ⱑ ����� ũ�⺸�� Ŀ�� �����ų� outofbound
				continue;
			else if (GameBoard[nextR][nextC] > 0 && GameBoard[nextR][nextC] < sharksz) { // ����⸦ �Դ� ����
				isvisited[nextR][nextC] = true;
				countTime[nextR][nextC] = countTime[curR][curC] + 1;

				if (tmpD > countTime[nextR][nextC]) { // �Դ� ������� �ִ� �Ÿ��� �� ª�� ���
					tmpR = nextR;
					tmpC = nextC;
					tmpD = countTime[nextR][nextC];
				}
				else if (tmpD == countTime[nextR][nextC]) { // �ִܰŸ��� ���� ��
					if (nextR < tmpR) { // ���� ���ʿ� �ִ� ���� ����
						tmpR = nextR;
						tmpC = nextC;
					}
					else if (nextR == tmpR && nextC < tmpC) // ���̰� ������ ���� ���ʿ� �ִ� ����⸦ ����
						tmpC = nextC;
				}
			}
			else if (!isvisited[nextR][nextC]) {  // ���� Ž���� ��ġ�� queue�� �ִ� ��
				q.emplace(nextR, nextC);
				isvisited[nextR][nextC] = true;
				countTime[nextR][nextC] = countTime[curR][curC] + 1;
			}
		}
	}

	// ��� true�� ������ ���
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