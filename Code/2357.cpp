#include <iostream>
#include <algorithm>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
#define Inf 1000000005

int n, operNum;
int ar[100000];
int maxSegtree[400001];
int minSegtree[400001];

void InputInfo();
int MakeMinSegtree(int from, int to, int pos);
int MakeMaxSegtree(int from, int to, int pos);
int GetMin();
int GetMax();
void Solve();

int main(void) {
	fastio;
	InputInfo();
	Solve();

	return 0;
}

void InputInfo() {
	cin >> n >> operNum;

	for (int i = 0; i < n; i++)
		cin >> ar[i];
}

int MakeMinSegtree(int from, int to, int pos) {
	if (from == to) {
		minSegtree[pos] = ar[from];
		return minSegtree[pos];
	}

	int mid = (from + to) / 2;
	return minSegtree[pos] = min(MakeMinSegtree(from, mid, pos * 2), MakeMinSegtree(mid + 1, to, pos * 2 + 1));
}

int MakeMaxSegtree(int from, int to, int pos) {
	if (from == to) {
		maxSegtree[pos] = ar[from];
		return maxSegtree[pos];
	}

	int mid = (from + to) / 2;
	return maxSegtree[pos] = max(MakeMaxSegtree(from, mid, pos * 2), MakeMaxSegtree(mid + 1, to, pos * 2 + 1));
}

int GetMin(int from, int to, int start, int fin, int pos) {
	if (fin < from || to < start)
		return Inf;
	
	if (start <= from && to <= fin)
		return minSegtree[pos];

	int mid = (from + to) / 2;
	return min(GetMin(from, mid, start, fin, pos * 2), GetMin(mid + 1, to, start, fin, pos * 2 + 1));
}

int GetMax(int from, int to, int start, int fin, int pos) {
	if (fin < from || to < start)
		return 0;

	if (start <= from && to <= fin)
		return maxSegtree[pos];

	int mid = (from + to) / 2;
	return max(GetMax(from, mid, start, fin, pos * 2), GetMax(mid + 1, to, start, fin, pos * 2 + 1));
}

void Solve() {
	MakeMaxSegtree(0, n - 1, 1);
	MakeMinSegtree(0, n - 1, 1);

	for (int i = 0; i < operNum; i++) {
		int s, f;
		cin >> s >> f;
		cout << GetMin(0, n - 1, s - 1, f - 1, 1) << " " << GetMax(0, n - 1, s - 1, f - 1, 1) << "\n";
	}
}