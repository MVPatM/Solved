#include <iostream>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

const int lim = 2000000;
int segTree[8000001]; // index 1부터 시작

void InsertValue(int start, int end, int idx, int value);
int DeleteValue(int start, int end, int index, int value);
void Solve();

int main(void) {
	fastio;
	Solve();

	return 0;
}

void InsertValue(int start, int end, int idx, int value) {
	if (value < start || end < value)
		return;

	segTree[idx]++;

	if (start == end)
		return;
	
	int mid = (start + end) / 2;
	InsertValue(start, mid, 2 * idx, value);
	InsertValue(mid + 1, end, 2 * idx + 1, value);
}

int DeleteValue(int start, int end, int index, int value) {
	segTree[index]--;

	if (start == end)
		return start;

	int mid = (start + end) / 2;

	if (segTree[2 * index] >= value)
		return DeleteValue(start, mid, 2 * index, value);
	else {
		// 만약 오른쪽 subtree로 이동을 하면 오른쪽 tree를 기준으로는 value에서 왼쪽 subtree값을 뺀 값번째를 찾아야 한다. 
		value -= segTree[2 * index];
		return DeleteValue(mid + 1, end, 2 * index + 1, value);
	}
}

void Solve() {
	int query;
	cin >> query;

	for (int i = 0; i < query; i++) {
		int kind, v;
		cin >> kind >> v;

		if (kind == 1)
			InsertValue(1, lim, 1, v);
		else
			cout << DeleteValue(1, lim, 1, v) << "\n";
	}
}