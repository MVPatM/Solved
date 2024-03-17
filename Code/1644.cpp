/*
다수의 소수를 찾는 방법은 에라토스 테네스의 체이다.
*/

#include <iostream>
#include <vector>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int n, cnt = 0;
bool isNotPrime[4000001];
vector<int> PrimeNumber;

void InputInfo() { cin >> n; }
void FindPrime();
void PrimeSum();

int main(void) {
	fastio;
	InputInfo();
	FindPrime();
	PrimeSum();

	return 0;
}

void FindPrime() {
	for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) {
			for (int j = 2; j * i <= n; j++) 
				isNotPrime[i * j] = true;
			PrimeNumber.push_back(i);
		}
	}
}

void PrimeSum() {
	bool isend = false;

	for (int start = 0, add = 0; start < PrimeNumber.size(); start++, add = 0) {
		for (int end = start; end < PrimeNumber.size(); end++) {
			if (add < n) 
				add += PrimeNumber[end];
			else 
				break;
		}

		if (add == n)
			cnt++;
	}

	cout << cnt;
}