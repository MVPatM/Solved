// 1. dp (1) bottom-up, (2) top-down
// 2. bfs이용
/*
-1한 지점, +1한 지점, x2한 지점을 queue에 넣어서
bfs를 진행을 하면 된다.
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

// min함수를 사용을 하면 stack에 minTime배열을 저장을 하기 때문에 stack의 범위를 초과할 가능성이 존재한다.
// 그러므로 크기가 큰 배열은 전역범위에서 설정을 해준다.
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