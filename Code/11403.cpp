#include <iostream>
#include <algorithm>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int n;
bool isPath[100][100];

void InputInfo();
void FindPath();
void PrintResult();

int main(void) {
	fastio;
	InputInfo();
	FindPath();
	PrintResult();

	return 0;
}

void InputInfo() {
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int tmp;
			cin >> tmp;
			isPath[i][j] = tmp;
		}
	}

}

void FindPath() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) 
				isPath[j][k] = max(isPath[j][k], isPath[j][i] && isPath[i][k]);
		}
	}
}

void PrintResult() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << isPath[i][j] << " ";
		cout << "\n";
	}
}