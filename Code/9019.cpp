#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

// 방문하지 않으면 시작점을 제외하고 모든 곳은 size = 0
string order[10000];

void DoDSLR();
inline int OrderD(int n) { return (2 * n) % 10000; }
inline int OrderS(int n) { return n ? n - 1 : 9999; }
int OrderL(int n);
int OrderR(int n);

int main(void) {
	fastio;
	DoDSLR();

	return 0;
}

void DoDSLR() {
	int TestCase;
	cin >> TestCase;

	for (int i = 0; i < TestCase; i++) {
		int InitValue, FinalValue;
		cin >> InitValue >> FinalValue;

		queue<int> q;
		q.push(InitValue);
		fill(order, order + 10000, "");

		while (!q.empty()) {
			int next;
			int cur = q.front();
			q.pop();

			next = OrderD(cur);
			if (next != InitValue && (order[next].size() == 0 || order[next].size() > order[cur].size() + 1)) {
				q.push(next);
				order[next] = order[cur] + 'D';
			}

			next = OrderS(cur);
			if (next != InitValue && (order[next].size() == 0 || order[next].size() > order[cur].size() + 1)) {
				q.push(next);
				order[next] = order[cur] + 'S';
			}

			next = OrderL(cur);
			if (next != InitValue && (order[next].size() == 0 || order[next].size() > order[cur].size() + 1)) {
				q.push(next);
				order[next] = order[cur] + 'L';
			}

			next = OrderR(cur);
			if (next != InitValue && (order[next].size() == 0 || order[next].size() > order[cur].size() + 1)) {
				q.push(next);
				order[next] = order[cur] + 'R';
			}
		}

		cout << order[FinalValue] << "\n";
	}
}

int OrderL(int n) {
	int n4 = n / 1000;
	n %= 1000;
	int n3 = n / 100;
	n %= 100;
	int n2 = n / 10;
	n %= 10;
	int n1 = n;

	return 1000 * n3 + 100 * n2 + 10 * n1 + n4;
}

int OrderR(int n) {
	int n4 = n / 1000;
	n %= 1000;
	int n3 = n / 100;
	n %= 100;
	int n2 = n / 10;
	n %= 10;
	int n1 = n;

	return 1000 * n1 + 100 * n4 + 10 * n3 + n2;
}