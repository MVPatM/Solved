/*
 ���� ���̰� �� ���븦 binary search�� ���־ ������ �ذ��Ѵ�.
 int�� ����� �ϸ� overflow�� �߻��ϱ� ������ long long�ڷ����� ����� ���־�� �Ѵ�.
 ���� maxlen�� 1�̸� mid���� 0���� ������ �Ǳ� ������ divisionbyzero error�� �߻��� �Ѵ�.
*/
#include <iostream>
#include <algorithm>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using ll = long long;

ll lan[10000];
int have, need;
ll maxlen = 0;

void InputInfo();
int GetPieceNum(int s);
void CutLan();

int main(void) {
	fastio;
	InputInfo();
	CutLan();

	return 0;
}

void InputInfo() {
	cin >> have >> need;

	for (int i = 0; i < have; i++) {
		ll tmp;
		cin >> tmp;
		lan[i] = tmp;
		maxlen = max(maxlen, tmp);
	}
}

int GetPieceNum(int s) {
	int cnt = 0;

	for (int i = 0; i < have; i++) 
		cnt += (lan[i] / s);
	
	return cnt;
}

void CutLan() {
	ll from = 0, to = maxlen, mid;
	int piece = 0;

	while (from < to) {
		mid = (from + to) / 2;

		if (mid == 0) // exception handling when maxlen = 1
			mid = 1;
		piece = GetPieceNum(mid);

		if (piece < need) 
			to = mid;
		else  
			from = mid + 1;
	}

	piece = GetPieceNum(from);
	if (piece < need)
		cout << from - 1;
	else
		cout << from;
}