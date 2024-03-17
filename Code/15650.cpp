/*
ó���� for���� �̿��ؾ� �ڴٴ� ������ �����.
�ٵ� M���� ���� ������ �Ǵ� for���� ���� �޶� ���� ������ 
for���� ����� �ؼ� �ݺ��� �ϴ� �ͺ��� ��͸� �̿��ؼ� �ݺ��� ��Ų��.
*/
#include <iostream>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int N, M; // n -> �ִ� ������, m -> ������ ����
int ar[9]; // index 1���� ���� �ִ´�.

inline void InputInfo() { cin >> N >> M; }
void PrintSeq(int pos, int start);
void Solve();

int main(void) {
	fastio;
	InputInfo();
	Solve();

	return 0;
}

// �� ����Լ��� call�ϸ鼭 array�� ���� �ִ� ���̴�.
// �� ������ ��͸� �̿��ؼ� ������ ��� ��츦 ���ϴ� �Ͱ� ����.
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