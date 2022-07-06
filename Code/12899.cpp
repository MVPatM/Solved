#include <iostream>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

const int lim = 2000000;
int segTree[8000001]; // index 1���� ����

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
		// ���� ������ subtree�� �̵��� �ϸ� ������ tree�� �������δ� value���� ���� subtree���� �� ����°�� ã�ƾ� �Ѵ�. 
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