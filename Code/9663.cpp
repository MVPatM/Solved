#include <iostream>
#include <cstdlib>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int queen_num;
int cnt = 0;
int pos[15];
bool isused[15];

void InputInfo() { cin >> queen_num; }
void DoNqueen();
void Nqueen(int n, int p);
bool ispossible(int n, int p);

int main(void) {
	fastio;
	InputInfo();
	DoNqueen();
	cout << cnt;

	return 0;
}

void DoNqueen() {

	for (int i = 1; i <= queen_num; i++) {
		Nqueen(1, i);
	}
}

void Nqueen(int n, int p) {
	isused[p] = true;
	pos[n] = p;

	if (n == queen_num) {
		cnt++;
	}
	else {
		for (int i = 1; i <= queen_num; i++) {
			if (ispossible(n + 1, i) && !isused[i])
				Nqueen(n + 1, i);
		}
	}

	isused[p] = false;
}

bool ispossible(int n, int p) {
	for (int i = 1; i < n; i++) {
		if ((n - i) == abs(p - pos[i]))
			return false;
	}

	return true;
}