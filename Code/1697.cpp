// 1. dp (1) bottom-up, (2) top-down
// 2. bfs�̿�
/*
-1�� ����, +1�� ����, x2�� ������ queue�� �־
bfs�� ������ �ϸ� �ȴ�.
*/
#include <iostream>
#include <algorithm>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

const int inf = 500000;
int finder, child;
int minTime[100005];

inline void InputInfo() { cin >> finder >> child; }
int GetTimetoFind();

int main(void) {
	fastio;
	InputInfo();
	cout << GetTimetoFind();

	return 0;
}

// min�Լ��� ����� �ϸ� stack�� minTime�迭�� ������ �ϱ� ������ stack�� ������ �ʰ��� ���ɼ��� �����Ѵ�.
// �׷��Ƿ� ũ�Ⱑ ū �迭�� ������������ ������ ���ش�.
int GetTimetoFind() {
	if (child <= finder) 
		return finder - child;

	fill(minTime, minTime + size(minTime), inf);
	for (int i = 0; i <= finder; i++)
		minTime[finder - i] = i;

	for (int i = 0; i < child; i++) {
		minTime[i + 1] = min(minTime[i] + 1, minTime[i + 1]);

		if (2 * i <= child + 1) {
			minTime[i * 2] = min(minTime[i * 2], minTime[i] + 1);
			if (i > 0)
				minTime[i * 2 - 1] = min(minTime[i * 2 - 1], minTime[i * 2] + 1);
		}
	}

	return minTime[child];
}