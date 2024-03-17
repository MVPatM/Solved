#include <iostream>
#include <string>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

string in;

inline void InputInfo() { cin >> in; }
int GetMinNum();

int main(void) {
	fastio;
	InputInfo();
	cout << GetMinNum();

	return 0;
}

int GetMinNum() {
	string tmp;
	int op, ans = 0;
	bool isminus = false;

	for (int i = 0; i < in.length(); i++) {
		if (in[i] == '+') {
			op = stoi(tmp);
			tmp = "";
			if (isminus)
				ans -= op;
			else
				ans += op;
		}
		else if (in[i] == '-') {
			op = stoi(tmp);
			tmp = "";
			if (isminus)
				ans -= op;
			else
				ans += op;
			isminus = true;
		}
		else 
			tmp += in[i];
	}

	op = stoi(tmp);
	if (isminus)
		ans -= op;
	else
		ans += op;

	return ans;
}