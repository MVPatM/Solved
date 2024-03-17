// dfs를 이용해서 문제를 해결하면 너무많은 recursive call을 야기 하기 때문에 문제가 발생한다. 
// 그렇기 때문에 bfs를 이용해서 풀어야만 한다.

#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <utility>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
#define Empty 0
#define Wall 1

bool useBreak = false;
int row, col, minD = 0;
bool board[1001][1001];
bool isvisited[1001][1001][2];
int dc[4] = { 0, 1, 0, -1 };
int dr[4] = { 1, 0, -1, 0 };

void InputInfo();
bool isOutofBound(int r, int c);
void Init();
void Move();
void BFS();

int main(void) {
	fastio;
	InputInfo();
	Init();
	Move();

	return 0;
}

void InputInfo() {
	cin >> row >> col;

	for (int r = 1; r <= row; r++) {
		string tmp;
		cin >> tmp;

		for (int c = 0; c < col; c++)
			board[r][c + 1] = tmp[c] - '0'; // tmp[c]는 char형이기 때문에 숫자로 변환을 해야지 bool변수에 올바른 값이 들어간다.
	}
}

bool isOutofBound(int r, int c) {
	if (r < 1 || r > row || c < 1 || c > col)
		return true;

	return false;
}

void Init() {
	isvisited[1][1][0] = true;
	isvisited[1][1][1] = true;
}

void Move() {
	BFS();
	if (minD)
		cout << minD;
	else
		cout << "-1";
}

// 같은 시간에 어떤 공간에 도착을 하였을 때 벽을 부시지 않은 route가 더 유리하다.
void BFS() {
	int curR, curC, cur;
	bool curS;
	queue<pair<pair<int, int>, pair<int, bool>>> q; // coordinator, 걸린시간, 벽을 부셨는지의 유무
	q.emplace(make_pair(1, 1), make_pair(1, false));

	while (!q.empty()) {
		curR = q.front().first.first;
		curC = q.front().first.second;
		cur = q.front().second.first;
		curS = q.front().second.second;
		q.pop();

		if (curR == row && curC == col) {
			minD = cur;
			return;
		}

		for (int i = 0; i < 4; i++) {
			int nextR = curR + dr[i];
			int nextC = curC + dc[i];

			if (isOutofBound(nextR, nextC))
				continue;

			// curs == 1일 때는 curs가 0인 거의 방문 기록이 있다면 push하지 않아도 된다.
			// 왜냐하면 벽을 부시지 않고 도착한 route가 더 유리하기 때문이다.
			if (!board[nextR][nextC]) { // 다음 이동장소가 0인 경우
				if (curS && isvisited[nextR][nextC][0])
					continue;

				if (!isvisited[nextR][nextC][curS]) { // 방문을 안 한경우 queue에 push를 한다.
					isvisited[nextR][nextC][curS] = true; // curS인 상태로 그 위치에 접근을 했는지 안 하였는지를 파악을 하여야 한다.
					q.emplace(make_pair(nextR, nextC), make_pair(cur + 1, curS));
				}
			}
			else { // 다음 이동장소가 1인 경우
				if (curS) // 방문여부를 확인할 필요는 없고 단순히 break skill이 없으면 다음장소로 넘어가지를 못한다.
					continue; 

				isvisited[nextR][nextC][1] = true;
				q.emplace(make_pair(nextR, nextC), make_pair(cur + 1, true));
			}
		}
	}
}