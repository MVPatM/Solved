#include <iostream>
#include <algorithm>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int stair;
int Maxscore[310];
int score[310];

void InputInfo();
void GetMax();

int main(void) {
	fastio;
	InputInfo();
	GetMax();

	return 0;
}

void InputInfo() {
	cin >> stair;

	for (int i = 1; i <= stair; i++) {
		int tmp;
		cin >> tmp;
		score[i] = tmp;
	}

	Maxscore[1] = score[1];
	Maxscore[2] = score[1] + score[2];
}

void GetMax() {
	for (int i = 3; i <= stair; i++) 
		Maxscore[i] = max(Maxscore[i - 2] + score[i], Maxscore[i - 3] + score[i] + score[i - 1]);

	cout << Maxscore[stair];
}