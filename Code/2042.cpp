/*
���׸�Ʈ Ʈ���� ������ index������� ä��� ���� �ƴϴ�.
�׷��� Ʈ���� leaf�� 2��n�°��� node�� ������ �ʿ��ϴ�.
�׷��Ƿ� �뷫������ 4n�� ũ�Ⱑ �ʿ��ϴ�.
*/
#include <iostream>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using LL = long long;

int n, operNum;
LL ar[1000001];
LL segTree[4000005];

// pos -> segment tree�� idx, idx -> �����Ϸ��� ���� ��ġ
void InputInfo();
LL MakeSegment(int from, int to, int pos);
void ChangeValue(int from, int to, int pos, int idx, LL d);
LL GetSum(int from, int to, int start, int fin, int pos);
void Solve();

int main(void) {
	fastio;
	InputInfo();
	Solve();
	return 0;
}

void InputInfo() {
	LL tmp;
	cin >> n >> operNum >> tmp;
	operNum += tmp;

	for (int i = 0; i < n; i++)
		cin >> ar[i];
}

LL MakeSegment(int from, int to, int pos) {
	if (from == to) { // return segTree[pos] = ar[from]���� code�� ���ٷ� ���� �� �ִ�.
		segTree[pos] = ar[from];
		return segTree[pos];
	}

	int mid = (from + to) / 2;	
	return segTree[pos] = MakeSegment(from, mid, 2 * pos) + MakeSegment(mid + 1, to, 2 * pos + 1);
}

// segTree[pos] += d �� tree�� ������ �����ϴ� ��� ��忡�� ������ ���־�� �Ѵ�.
// �׷��� tree�� ������ node������ �ٽ� ��͸� ȣ���� �ϸ� �ȵȴ�.
void ChangeValue(int from, int to, int pos, int idx, LL d) {
	if (idx < from || to < idx)
		return;
	
	if (from == to && from == idx) {
		segTree[pos] += d;
		return;
	}

	int mid = (from + to) / 2;
	segTree[pos] += d;
	ChangeValue(from, mid, 2 * pos, idx, d);
	ChangeValue(mid + 1, to, 2 * pos + 1, idx, d);

	/*
	segTree[pos] += d;
	if (from != to) {
		int mid = (from + to) / 2;
		ChangeValue(from, mid, 2 * pos, idx, d);
		ChangeValue(mid + 1, to, 2 * pos + 1, idx, d);
	}
	*/
}

LL GetSum(int from, int to, int start, int fin, int pos) {
	if (fin < from || to < start)
		return 0;

	// from,to �� start,fin�� ������ ���� �����Ͽ���.
	if (start <= from && to <= fin)
		return segTree[pos];

	int mid = (from + to) / 2;
	return GetSum(from, mid, start, fin, pos * 2) + GetSum(mid + 1, to, start, fin, pos * 2 + 1);
}

void Solve() {
	MakeSegment(0, n - 1, 1);

	for (int i = 0; i < operNum; i++) {
		int kind, n1;
		LL n2;
		cin >> kind >> n1 >> n2;

		if (kind == 1) { // change the value
			LL dif = n2 - ar[n1 - 1];
			ar[n1 - 1] = n2; // ���� ��ġ�� 2���̻� �ٲپ��� �� ���� �߻� -> �Ĳ��ؾ���.....
			ChangeValue(0, n - 1, 1, n1 - 1, dif);
		}
		else // print sum
			cout << GetSum(0, n - 1, n1 - 1, n2 - 1, 1) << "\n";
	}
}