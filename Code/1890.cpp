#include <iostream>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using ll = long long;

int length;
int board[101][101];
ll way[101][101];

void InputInfo();
void Jumping();

int main(void) {
	fastio;
	InputInfo();
	Jumping();

	return 0;
}

void InputInfo(){
	cin >> length;

	for (int i = 1; i <= length; i++) {
		for (int j = 1; j <= length; j++) {
			int tmp;
			cin >> tmp;
			board[i][j] = tmp;
		}
	}
}

void Jumping() {
	way[1][1] = 1;

	for (int i = 1; i <= length; i++) {
		for (int j = 1; j <= length; j++) {
			if (!board[i][j])
				continue;

			if (j + board[i][j] <= length) 
				way[i][j + board[i][j]] += way[i][j];
			if (i + board[i][j] <= length)
				way[i + board[i][j]][j] += way[i][j];
		}
	}

	cout << way[length][length];
}