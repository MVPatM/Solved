#include <iostream>
#include <algorithm>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int seqLen;
int seq[1000];
int upDP[1000];
int downDP[1000];

void InputInfo();
void Solve();

int main(void) {
	fastio;
	InputInfo();
	Solve();

	return 0;
}

void InputInfo() {
	cin >> seqLen;

	for (int i = 0; i < seqLen; i++)
		cin >> seq[i];
}

// 2번의 dp algorithm을 사용해서 구한다.
/*
현재 지정하고 있는 위치의 값이 부분 수열의 최댓값이라고 가정을 하였을 때
그 때 부분 수열의 최대 길이를 구하는 것이다.
*/
void Solve() {
	int i, j, ans = 0;
	fill(upDP, upDP + seqLen, 1);
	fill(downDP, downDP + seqLen, 1);

	for (i = 1; i < seqLen; i++) {
		for (j = 0; j < i; j++) {
			if (seq[i] > seq[j]) 
				upDP[i] = max(upDP[i], upDP[j] + 1);
		}
	}

	for (i = seqLen - 2; i >= 0; i--) {
		for (j = seqLen - 1; j > i; j--) {
			if (seq[i] > seq[j])
				downDP[i] = max(downDP[i], downDP[j] + 1);
		}
	}

	for (i = 0; i < seqLen; i++)
		ans = max(ans, upDP[i] + downDP[i] - 1);

	cout << ans;
}