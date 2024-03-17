#include <iostream>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0)

int length;
int paper[2187][2187];
int Count[3];

void InputInfo();
void GetPaperNumber(int lg, int x, int y);
void PrintAnswer() { cout << Count[0] << "\n" << Count[1] << "\n" << Count[2]; }

int main(void) {
	fastio;
	InputInfo();
	GetPaperNumber(length, 0, 0);
	PrintAnswer();

	return 0;
}

void InputInfo() {
	cin >> length;

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			int tmp;
			cin >> tmp;
			paper[i][j] = tmp;
		}
	}
}

// lg가 1이 되면 무조건 return이 된다.
void GetPaperNumber(int lg, int x, int y) {
	bool issame = true;
	int v = paper[x][y];

	for (int i = 0; i < lg; i++) {
		for (int j = 0; j < lg; j++) {
			if (paper[x + i][y + j] != v) {
				issame = false;
				break;
			}
		}

		if (!issame)
			break;
	}

	if (issame) {
		Count[v + 1] += 1;
		return;
	}
	else {
		lg /= 3;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) 
				GetPaperNumber(lg, x + i * lg, y + j * lg);
		}
	}
}