/* 1. input을 받는대로 data를 재가공 시킨다.
   2. input을 받은후 그 다음 data를 하나하나 검색을 하면서 찾는다.
*/
#include <iostream>
#include <utility>
#include <algorithm>
#include <climits>

using namespace std;
 
// 여러가지 명령어를 define을 할 때에는 쉼표를 통해서 명령어를 구분을 해준다.
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

using pos = pair<int, int>;

int Msize, Btarget = INT_MAX;
int matrix[301][301];
pos TargetPos;

void Do_LEN();
void InputMatrix();
int FindTarget();
bool isExoticPair(int t);

int main(void) {
	fastio;
	Do_LEN();

	return 0;
}

void Do_LEN() {
	int target;
	InputMatrix();

	do {
		target = FindTarget();
	} while (!isExoticPair(target) && target != 0);

	if (target == 0)
		cout << "-1\n";
	else
		cout << target << "\n";

}

// input to matrix
void InputMatrix() {
	cin >> Msize;

	for (int i = 1; i <= Msize; i++) {
		for (int j = 1; j <= Msize; j++)
			cin >> matrix[i][j];
	}
}

// FInd Target and update the information about Btarget and Targetpos
int FindTarget() {
	int m = 0;

	for (int i = 1; i <= Msize; i++) {
		for (int j = 1; j <= Msize; j++) {
			if (matrix[i][j] > m && matrix[i][j] < Btarget) {
				m = matrix[i][j];
				TargetPos.first = i;
				TargetPos.second = j;
			}
		}
	}

	Btarget = m;
	return m;
}

// check to have exotic pair about target
bool isExoticPair(int t) {
	int count = 0;

	for (int i = TargetPos.first; i <= Msize; i++) {
		for (int j = TargetPos.second; j <= Msize; j++) {
			if (count++ != 0 && matrix[i][j] == t)
				return true;
		}
	}

	return false;
}