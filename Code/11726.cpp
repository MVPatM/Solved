// overflow�� ���� ���ؼ� 10007�� ���� �������� �迭�� ������ ��Ų��.
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