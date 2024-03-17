#include <iostream>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using llt = long long;

llt base, mul_num, Div;

inline void InputInfo() { cin >> base >> mul_num >> Div; }
llt GetRemainder();

int main(void) {
	fastio;
	InputInfo();
	cout << GetRemainder();

	return 0;
}

llt GetRemainder() {
	llt ans = 1;

	while (mul_num) {
		if (mul_num % 2) 
			ans = (ans * base) % Div;

		mul_num /= 2;
		base = (base * base) % Div;
	}


	return ans;
}