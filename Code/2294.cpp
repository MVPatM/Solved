#include <iostream>
#include <algorithm>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int kind, value;
int coin[101];
int coinnum[10001];

void InputInfo();
void Coin();

int main(void) {
	fastio;
	InputInfo();
	Coin();

	return 0;
}

void InputInfo() {
	cin >> kind >> value;
	fill(coinnum, coinnum + size(coinnum), 15000);

	for (int i = 1; i <= kind; i++) {
		int tmp;
		cin >> tmp;
		coin[i] = tmp;
	}
}

void Coin() {
	coinnum[0] = 0;

	for (int i = 0; i <= value; i++) {
		for (int j = 1; j <= kind; j++) 
			if (i + coin[j] <= value)
				coinnum[i + coin[j]] = min(coinnum[i + coin[j]], coinnum[i] + 1);
	}

	if (coinnum[value] == 15000)
		cout << "-1";
	else
		cout << coinnum[value];
}