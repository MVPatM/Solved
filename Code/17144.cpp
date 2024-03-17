#include <iostream>
#include <cstring>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int AirCleaner[2]; // 항상 열의 위치는 0으로 고정되어 있다.
int roomRow, roomCol, total_time;
int room[50][50];
int var[50][50];
int dR[4] = { -1, 0, 1, 0 };
int dC[4] = { 0, 1, 0, -1 };

void InputInfo();
bool isOutofbound(int r, int c);
void Init();
void SpreadDust();
void OperateAirCleaner();
int GetTotalDust();
void Solve();

int main(void) {
	fastio;
	InputInfo();
	Solve();

	return 0;
}

void InputInfo() {
	cin >> roomRow >> roomCol >> total_time;
	
	for (int i = 0; i < roomRow; i++) {
		for (int j = 0; j < roomCol; j++) {
			cin >> room[i][j];
		}
	}

	// find the position of aircleaner 
	for (int i = 0; i < roomRow; i++) {
		if (room[i][0] == -1) {
			AirCleaner[0] = i;
			AirCleaner[1] = i + 1;
			break;
		}
	}
}

bool isOutofbound(int r, int c) {
	if (r < 0 || r >= roomRow || c < 0 || c >= roomCol)
		return true;

	return false;
}

void Init() {
	for (int i = 0; i < roomRow; i++) 
		memset(var[i], 0, sizeof(int) * roomCol);
}

void SpreadDust() {
	for (int r = 0; r < roomRow; r++) {
		for (int c = 0; c < roomCol; c++) {
			if (room[r][c] > 4) {
				for (int k = 0; k < 4; k++) {
					int nextR = r + dR[k];
					int nextC = c + dC[k];
					if (!isOutofbound(nextR, nextC) && room[nextR][nextC] != -1) { // 공기청정기가 있는 위치에 먼지가 퍼지지 않는다.
						int v = room[r][c] / 5;
						var[r][c] -= v;
						var[nextR][nextC] += v;
					}
				}
			}
		}
	}

	// update 하면서 var값을 초기화 하여도 된다.
	for (int r = 0; r < roomRow; r++) {
		for (int c = 0; c < roomCol; c++)
			room[r][c] += var[r][c];
			// var[r][c] = 0;
	}
}

void OperateAirCleaner() {
	int curR = AirCleaner[0] - 2;
	int	curC = 0;
	int dir = 0;

	while (room[curR][curC] != -1) { // 위 순환
		room[curR - dR[dir]][curC - dC[dir]] = room[curR][curC];

		if (isOutofbound(curR + dR[dir], curC + dC[dir]) || (curR + dR[dir] > AirCleaner[0]))
			dir++;

		curR += dR[dir];
		curC += dC[dir];
	}

	curR = AirCleaner[1] + 2;
	curC = 0;
	dir = 2;

	while (room[curR][curC] != -1) { // 아래 순환
		room[curR - dR[dir]][curC - dC[dir]] = room[curR][curC];

		if (isOutofbound(curR + dR[dir], curC + dC[dir]) || (curR + dR[dir] < AirCleaner[1]))
			dir = (dir + 3) % 4;

		curR += dR[dir];
		curC += dC[dir];
	}
	
	room[AirCleaner[0]][1] = 0;
	room[AirCleaner[1]][1] = 0;
}

int GetTotalDust() {
	int total_amount = 0;
	for (int r = 0; r < roomRow; r++) {
		for (int c = 0; c < roomCol; c++) {
			if (room[r][c] > 0)
				total_amount += room[r][c];
		}
	}

	return total_amount;
}

void Solve() {
	for (int i = 0; i < total_time; i++) {
		Init(); // 시간이 흐를때 마다 var배열의 값을 초기화 시켜주어야 한다.
		SpreadDust();
		OperateAirCleaner();
	}

	cout << GetTotalDust();
}