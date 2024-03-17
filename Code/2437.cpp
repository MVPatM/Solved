#include <iostream>
#include <queue>

using namespace std;
#define fastio ios_base::sync_with_stdio(0),cin.tie(0);
priority_queue<int, vector<int>, greater<int>> weigh;

void InputInfo();
void GetMinweigh();

int main(void) {
	fastio;
	InputInfo();
	GetMinweigh();

	return 0;
}

void InputInfo() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int tmp;
		cin >> tmp;
		weigh.push(tmp);
	}
}

void GetMinweigh() {
	int mx = 0;

	while (!weigh.empty()) {
		if (mx + 1 < weigh.top())
			break;

		mx += weigh.top();
		weigh.pop();
	}

	cout << ++mx;
}