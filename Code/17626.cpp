/*
sol1 -> dp를 이용해서 풀 수 있다.

sol2 -> brute force algorithm을 이용해서 풀 수 있다.
주어진 수를 square의 합으로 만드는 방법을 하나하나 찾는 방법이다.
답이 1라고 가정을 하면 한 개의 for문을 돌려서 답이 1이 되는 지를 확인한다.
그리고 거기서 답을 찾지 못하면 답을 2라고 가정을 해서 답이 만들어지는 지를 확인해야 한다.
답이 2라고 가정을 하면 두 개의 for문으로 돌려서 답이 2가 되는 지를 확인하면 된다.
그 다음 3도 마찬가지이다.
문제에서 무조건 4개의 이하의 제곱 수로 모든 수를 표현이 가능하다 했으므로 
3이 아니면 답은 결국 4가 되는 것이다.
*/
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int value;
int NeededNaturalNumber[50001];

inline void InputInfo() { cin >> value; }
int GetMinNum();

int main(void) {
	fastio;
	InputInfo();
	cout << GetMinNum();

	return 0;
}

int GetMinNum() {
	int limit = (int)sqrt(value);
	fill(NeededNaturalNumber, NeededNaturalNumber + 50001, 5); // exist in <algorithm> header file
	NeededNaturalNumber[0] = 0;

	for (int i = 0; i <= value; i++) { // 합을 더할 시작점
		for (int j = 1; j <= limit; j++) { // 제곱을 시킬 수들
			int square = j * j;

			if (i + square > value)
				break;

			NeededNaturalNumber[i + square] = min(NeededNaturalNumber[i] + 1, NeededNaturalNumber[i + square]);
		}
	}
	
	return NeededNaturalNumber[value];
}