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
// board = 0, isvisited = 0: ���� ����
// board = 0, isvisited = 1: �ܺ� ����
// board = 1 isvisited = 1: �� ���� ġ��
// board = 1 isvisited = 0: �׳� ġ��
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

// �ܺΰ��⸦ ã�� bfs algorithm
void BFS(int r, int c) { // board == 0 and isvisted == false�̸� target���� ��´�.
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

// ġ� ������ list���� delete�� ���ش�.
// delete������ ���� ���� list �ڷᱸ���� �̿��Ͽ���.
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

			// erase�� �ϰ��� ��ȯ���� ���� �ʾƼ� error�߻�
			// �׸��� erase�ϱ� ���� iterator���� �̿��ؼ� queue�� �ְ� visit���θ� �Ǵ��ؾ� �ϴµ� erase������ ������ �Ϸ��� �ؼ� error�߻�
			if (NumberOfWallToContactAir >= 2) {
				isvisited[(*iter).first][(*iter).second] = true;
				MeltedCheese.emplace((*iter).first, (*iter).second);
				iter = Cheese.erase(iter); // list�� erase�Լ��� input���� iterator�� ����Ű�� node�� �����ϰ� �� ���� node�� ����Ű�� ���� return�Ѵ�.
			}
			else
				iter++;
		}

		FindAirToConvertToOut();
		TimeToMelt++;
	}

	cout << TimeToMelt;
}