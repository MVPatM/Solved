/*
cost�� ����� ��κ� Ŭ ���� ��츦 ����� ���� �ʾҴ�.
INF�� ���� ũ�� �������� �ʾƼ� ������ �߻��Ͽ���.
*/

#include <iostream>
#include <algorithm>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
const int INF = 150000000;

int cost[101][101];
int length;

void Initialize();
void InputInfo();
void floyd();
void PrintResult();

int main(void) {
	fastio;
	InputInfo();
	floyd();
	PrintResult();
	return 0;
}

void Initialize() {
	for (int i = 1; i <= length; i++) {
		for (int j = 1; j <= length; j++)
			cost[i][j] = INF;
	}
}

void InputInfo() {
	int bus;
	cin >> length >> bus;
	Initialize();

	for (int i = 0; i < bus; i++) {
		int s, d, c;
		cin >> s >> d >> c;
		cost[s][d] = min(cost[s][d], c);
	}
}


void floyd() {
	for (int i = 1; i <= length; i++) {
		for (int j = 1; j <= length; j++) {
			for (int k = 1; k <= length; k++) 
				cost[j][k] = min(cost[j][i] + cost[i][k], cost[j][k]);
		}
	}
}

void PrintResult() {
	for (int i = 1; i <= length; i++) {
		for (int j = 1; j <= length; j++) {
			if (cost[i][j] == INF || i == j)
				cout << 0 << " ";
			else
				cout << cost[i][j] << " ";
		}
		cout << "\n";
	}

}