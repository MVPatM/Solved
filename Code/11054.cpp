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

// 2���� dp algorithm�� ����ؼ� ���Ѵ�.
/*
���� �����ϰ� �ִ� ��ġ�� ���� �κ� ������ �ִ��̶�� ������ �Ͽ��� ��
�� �� �κ� ������ �ִ� ���̸� ���ϴ� ���̴�.
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