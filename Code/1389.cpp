#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
#define fastio ios_base::sync_with_stdio(0),cin.tie(0);

const int INF = 1000;
int mat[101][101];
int user, rlt;
bool isvisited[101];
int bacan[101];

void InputInfo();
void FW();
int GetMinBacan();
void BFS(int f);
int GetMinBacan2();

int main(void) {
	fastio;
	InputInfo();
	cout << GetMinBacan2();

	return 0;
}

void InputInfo() {
	cin >> user >> rlt;
	fill(&mat[0][0], &mat[user][user + 1], INF);

	for (int i = 0; i < rlt; i++) {
		int tmp1, tmp2;
		cin >> tmp1 >> tmp2;
		mat[tmp1][tmp2] = 1;
		mat[tmp2][tmp1] = 1;
	}
	
	for (int i = 1; i <= user; i++)
		mat[i][i] = 0;
}

void FW() {
	for (int i = 1; i <= user; i++) {
		for (int j = 1; j <= user; j++) { // matrix에 대한 것
			for (int k = 1; k <= user; k++) //경유지에 대한 것
				mat[j][k] = min(mat[j][k], mat[j][i] + mat[i][k]);
		}
	}
}

int GetMinBacan() {
	int m = 10000;
	int minuser = 0;

	for (int i = 1; i <= user; i++) {
		int tmp = 0;
		for (int j = 1; j <= user; j++)
			tmp += mat[i][j];
		if (m > tmp) {
			m = tmp;
			minuser = i;
		}
	}

	return minuser;
}

void BFS(int f) {
	queue<int> q;
	q.push(f);
	isvisited[f] = true;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int i = 1; i <= user; i++) {
			if (mat[cur][i] == 1 && !isvisited[i]) {
				q.push(i);
				isvisited[i] = true;
				bacan[i] = bacan[cur] + 1;
			}
		}
	}
}

int GetMinBacan2() {
	int minuser = 0;
	int minsum = 10000;

	for (int i = 1; i <= user; i++) { // bfs의 시작점 
		int tmpSum = 0;
		BFS(i);
		for (int j = 1; j <= user; j++) 
			tmpSum += bacan[j];

		if (minsum > tmpSum) {
			minuser = i;
			minsum = tmpSum;
		}

		memset(isvisited, 0, sizeof(isvisited));
		memset(bacan, 0, sizeof(bacan));
	}

	return minuser;
}