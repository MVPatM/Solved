// overflow를 막기 위해서 10007로 나눈 나머지를 배열에 저장을 시킨다.
#include <iostream>

using namespace std;
using ll = long long;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

ll ways[1001];

void tiling();

int main(void) {
	fastio;
	tiling();

	return 0;
}

void tiling() {
	int n;
	cin >> n;

	ways[1] = 1;
	ways[2] = 2;

	for (int i = 3; i <= n; i++) 
		ways[i] = ways[i - 1] + ways[i - 2];

	cout << ways[n];
}