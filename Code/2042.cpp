/*
세그먼트 트리는 무조건 index순서대로 채우는 것이 아니다.
그래서 트리의 leaf는 2의n승개의 node가 무조건 필요하다.
그러므로 대략적으로 4n의 크기가 필요하다.
*/
#include <iostream>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using LL = long long;

int n, operNum;
LL ar[1000001];
LL segTree[4000005];

// pos -> segment tree의 idx, idx -> 변경하려는 값의 위치
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
	if (from == to) { // return segTree[pos] = ar[from]으로 code를 한줄로 줄일 수 있다.
		segTree[pos] = ar[from];
		return segTree[pos];
	}

	int mid = (from + to) / 2;	
	return segTree[pos] = MakeSegment(from, mid, 2 * pos) + MakeSegment(mid + 1, to, 2 * pos + 1);
}

// segTree[pos] += d 는 tree의 조건을 만족하는 모든 노드에서 진행을 해주어야 한다.
// 그런데 tree의 마지막 node에서는 다시 재귀를 호출을 하면 안된다.
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

	// from,to 와 start,fin의 역할을 서로 착각하였다.
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
			ar[n1 - 1] = n2; // 같은 위치를 2번이상 바꾸었을 때 문제 발생 -> 꼼꼼해야함.....
			ChangeValue(0, n - 1, 1, n1 - 1, dif);
		}
		else // print sum
			cout << GetSum(0, n - 1, n1 - 1, n2 - 1, 1) << "\n";
	}
}