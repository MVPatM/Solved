#include <iostream>
#include <queue>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using Ltime = pair<int, int>;

vector<Ltime> cont;
void InputInfo();
void Sorting() { sort(cont.begin(), cont.end()); }
void lecture();

int main(void) {
	fastio;
	InputInfo();
	Sorting();
	lecture();

	return 0;
}

void InputInfo() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int tmp1, tmp2;
		cin >> tmp1 >> tmp2;
		cont.emplace_back(tmp1, tmp2);
	}
}

void lecture() {
	int room = 1;
	priority_queue<int, vector<int>, greater<int>> pq;
	pq.push(cont[0].second);

	for (int i = 1; i < cont.size(); i++) {
		if (cont[i].first < pq.top()) {
			pq.push(cont[i].second);
			room++;
		}
		else {
			pq.pop();
			pq.push(cont[i].second);
		}
	}

	cout << room;
}