/*
   2의 n승을 곱하거나 2의 n승을 나눌 때에는 bit연산자 ('<<' or '>>')를 이용해서 구할 수 있다.
   그러나 n이 매우 클 때 bit연산자를 이용하면 원하는 결과를 얻을 수 없다.
   Hardware가 명령어를 몇 bit까지 지원을 하는 지에 따라서 다르다.
*/

#include <iostream>
#include <cmath>

using namespace std;

void hanoi(int n, int from, int to);
void play_hanoi();

int main(void) {
	play_hanoi();
	return 0;
}

void hanoi(int n, int from, int to) {
	if (n == 0)
		return;

	int pos = 6 - from - to;
	hanoi(n - 1, from, pos);

	cout << from << " " << to << '\n';
	
	hanoi(n - 1, pos, to);
	
}

void play_hanoi() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	cout << (1 << n) - 1 << "\n";

	hanoi(n, 1, 3);
}