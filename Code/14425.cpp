#include <iostream>
#include <set>
#include <string>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

set<string> Set;
int check_num;
void InputInfo();
void FindSame();

int main(void) {
	fastio;
	InputInfo();
	FindSame();

	return 0;
}

void InputInfo() {
	int s;
	cin >> s >> check_num;

	for (int i = 0; i < s; i++) {
		string tmp;
		cin >> tmp;
		Set.insert(tmp);
	}
}

void FindSame() {
	int count = 0;

	for (int i = 0; i < check_num; i++) {
		string tmp;
		cin >> tmp;

		if (Set.find(tmp) != Set.end())
			count++;
	}

	cout << count;
}