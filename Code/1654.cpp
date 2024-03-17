/*
 가장 길이가 긴 막대를 binary search를 해주어서 문제를 해결한다.
 int를 사용을 하면 overflow가 발생하기 때문에 long long자료형을 사용을 해주어야 한다.
 만약 maxlen이 1이면 mid값이 0으로 설정이 되기 때문에 divisionbyzero error가 발생을 한다.
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