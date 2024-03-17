/*
처음에 for문을 이용해야 겠다는 생각이 들었다.
근데 M값에 따라서 돌려야 되는 for문의 수가 달라 지기 때문에 
for문을 사용을 해서 반복을 하는 것보다 재귀를 이용해서 반복을 시킨다.
*/
#include <iostream>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int N, M; // n -> 최대 범위수, m -> 수열의 개수
int ar[9]; // index 1부터 값을 넣는다.

inline void InputInfo() { cin >> N >> M; }
void PrintSeq(int pos, int start);
void Solve();

int main(void) {
	fastio;
	InputInfo();
	Solve();

	return 0;
}

// 이 재귀함수를 call하면서 array에 값을 넣는 것이다.
// 이 문제는 재귀를 이용해서 조합의 모든 경우를 구하는 것과 같다.
void PrintSeq(int pos, int start) {
	if (pos > M) {
		for (int i = 1; i <= M; i++)
			cout << ar[i] << " ";
		cout << "\n";
		return;
	}
	
	for (int j = start; j <= (N - (M - pos)); j++) {
		ar[pos] = j;
		PrintSeq(pos + 1, j + 1);
	}
}

void Solve() {
	PrintSeq(1, 1);
}