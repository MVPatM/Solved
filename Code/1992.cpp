#include <iostream>
#include <cstring>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

string ans;
int length;
bool video[64][64];

void InputInfo();
void MakeAns(int r, int c, int l);
bool isAllsame(int r, int c, int l);

int main(void) {
	fastio;
	InputInfo();
	MakeAns(0, 0, length);
	cout << ans;

	return 0;
}

void InputInfo() {
	string tmp;
	cin >> length;

	for (int i = 0; i < length; i++) {
		cin >> tmp;
		for (int j = 0; j < length; j++) 
			video[i][j] = tmp[j] - '0';
	}
}

void MakeAns(int r, int c, int l) {
	if (l == 1 || isAllsame(r, c, l)) {
		if (video[r][c] == true)
			ans += '1';
		else
			ans += '0';
		return;
	}

	ans += '(';
	MakeAns(r, c, l / 2);
	MakeAns(r, c + l / 2, l / 2);
	MakeAns(r + l / 2, c, l / 2);
	MakeAns(r + l / 2, c + l / 2, l / 2);
	ans += ')';
}

bool isAllsame(int r, int c, int l) {
	bool first = video[r][c];
	
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < l; j++) {
			if (video[r + i][c + j] != first)
				return false;
		}
	}

	return true;
}