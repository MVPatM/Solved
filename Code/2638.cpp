#include <iostream>
#include <utility>
#include <queue>
#include <list>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using pii = pair<int, int>;

int R, C;
int dR[4] = { 0, -1, 0, 1 };
int dC[4] = { -1, 0, 1, 0 };
// board = 0, isvisited = 0: 내부 공기
// board = 0, isvisited = 1: 외부 공기
// board = 1 isvisited = 1: 곧 녹을 치즈
// board = 1 isvisited = 0: 그냥 치즈
bool board[100][100];
bool isvisited[100][100];
list<pii> Cheese;
queue<pii> MeltedCheese;

void InputInfo();
void BFS(int r, int c);
bool isOutOfBound(int r, int c);
void FindAirToConvertToOut();
void Solve();

int main(void) {
	fastio;
	InputInfo();
	Solve();

	return 0;
}

void InputInfo() {
	cin >> R >> C;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> board[i][j];

			if (board[i][j]) 
				Cheese.emplace_back(i, j);
		}
	}
}

// 외부공기를 찾는 bfs algorithm
void BFS(int r, int c) { // board == 0 and isvisted == false이면 target으로 삼는다.
	isvisited[r][c] = true;
	queue<pii> q;
	q.emplace(r, c);

	while (!q.empty()) {
		pii cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nextR = cur.first + dR[i];
			int nextC = cur.second + dC[i];

			if (isOutOfBound(nextR, nextC))
				continue;

			if (!board[nextR][nextC] && !isvisited[nextR][nextC]) {
				isvisited[nextR][nextC] = true;
				q.emplace(nextR, nextC);
			}
		}
	}
}

bool isOutOfBound(int r, int c) {
	if (r < 0 || c < 0 || r >= R || c >= C)
		return true;

	return false;
}

void FindAirToConvertToOut() {
	while (!MeltedCheese.empty()) {
		pii cur = MeltedCheese.front();
		MeltedCheese.pop();
		board[cur.first][cur.second] = 0;

		for (int i = 0; i < 4; i++) {
			int targetR = cur.first + dR[i];
			int targetC = cur.second + dC[i];

			if (isOutOfBound(targetR, targetC))
				continue;

			if (!board[targetR][targetC] && !isvisited[targetR][targetC])
				BFS(targetR, targetC);
		}
	}
}

// 치즈가 녹으면 list에서 delete를 해준다.
// delete연산이 가장 빠른 list 자료구조를 이용하였다.
void Solve() {
	int TimeToMelt = 0;
	BFS(0, 0);

	while (!Cheese.empty()) {
		for (auto iter = Cheese.begin(); iter != Cheese.end();) {
			int NumberOfWallToContactAir = 0;
			for (int i = 0; i < 4; i++) {
				int targetR = (*iter).first + dR[i];
				int targetC = (*iter).second + dC[i];

				if (isOutOfBound(targetR, targetC))
					continue;

				if (!board[targetR][targetC] && isvisited[targetR][targetC])
					NumberOfWallToContactAir++;
			}

			// erase를 하고나서 반환값을 받지 않아서 error발생
			// 그리고 erase하기 전의 iterator값을 이용해서 queue에 넣고 visit여부를 판단해야 하는데 erase이후의 값으로 하려고 해서 error발생
			if (NumberOfWallToContactAir >= 2) {
				isvisited[(*iter).first][(*iter).second] = true;
				MeltedCheese.emplace((*iter).first, (*iter).second);
				iter = Cheese.erase(iter); // list의 erase함수는 input값의 iterator가 가리키는 node를 삭제하고 그 다음 node를 가리키는 값을 return한다.
			}
			else
				iter++;
		}

		FindAirToConvertToOut();
		TimeToMelt++;
	}

	cout << TimeToMelt;
}