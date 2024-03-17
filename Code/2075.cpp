#include <iostream>
#include <queue>;

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int num;
priority_queue<int, vector<int>, greater<int>> cont;

void InputInfo();
int GetValue() { return cont.top(); }

int main(void) {
	fastio;
	InputInfo();
	cout << GetValue();

	return 0;
}

void InputInfo() {
	cin >> num;
	
	for (int i = 0; i < num * num; i++) {
		int tmp;
		cin >> tmp;

		if (cont.size() <= num || tmp > cont.top())
			cont.push(tmp);
	}
}