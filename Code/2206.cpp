// dfs�� �̿��ؼ� ������ �ذ��ϸ� �ʹ����� recursive call�� �߱� �ϱ� ������ ������ �߻��Ѵ�. 
// �׷��� ������ bfs�� �̿��ؼ� Ǯ��߸� �Ѵ�.

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
			board[r][c + 1] = tmp[c] - '0'; // tmp[c]�� char���̱� ������ ���ڷ� ��ȯ�� �ؾ��� bool������ �ùٸ� ���� ����.
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

// ���� �ð��� � ������ ������ �Ͽ��� �� ���� �ν��� ���� route�� �� �����ϴ�.
void BFS() {
	int curR, curC, cur;
	bool curS;
	queue<pair<pair<int, int>, pair<int, bool>>> q; // coordinator, �ɸ��ð�, ���� �μ̴����� ����
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

			// curs == 1�� ���� curs�� 0�� ���� �湮 ����� �ִٸ� push���� �ʾƵ� �ȴ�.
			// �ֳ��ϸ� ���� �ν��� �ʰ� ������ route�� �� �����ϱ� �����̴�.
			if (!board[nextR][nextC]) { // ���� �̵���Ұ� 0�� ���
				if (curS && isvisited[nextR][nextC][0])
					continue;

				if (!isvisited[nextR][nextC][curS]) { // �湮�� �� �Ѱ�� queue�� push�� �Ѵ�.
					isvisited[nextR][nextC][curS] = true; // curS�� ���·� �� ��ġ�� ������ �ߴ��� �� �Ͽ������� �ľ��� �Ͽ��� �Ѵ�.
					q.emplace(make_pair(nextR, nextC), make_pair(cur + 1, curS));
				}
			}
			else { // ���� �̵���Ұ� 1�� ���
				if (curS) // �湮���θ� Ȯ���� �ʿ�� ���� �ܼ��� break skill�� ������ ������ҷ� �Ѿ���� ���Ѵ�.
					continue; 

				isvisited[nextR][nextC][1] = true;
				q.emplace(make_pair(nextR, nextC), make_pair(cur + 1, true));
			}
		}
	}
}