#include <iostream>
#include <algorithm>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int line;
int maxDp[3], minDp[3];

void InputInfo();
void GetValue();
void PrintAnswer();

int main(void) {
	fastio;
	InputInfo();
	GetValue();
	PrintAnswer();

	return 0;
}

// ù��° ���� ���� �ʱ�ȭ�ϴµ��� ������ ����
void InputInfo() {
	cin >> line;

	// ù��° �� ���� input
	for (int i = 0; i < 3; i++) {
		int tmp;
		cin >> tmp;
		maxDp[i] = tmp;
		minDp[i] = tmp;
	}
}

void GetValue() {
	int maxtmp[3], mintmp[3]; // use in ver2
	int input[3]; // use in ver1

	// ver1
	// ������ dp������ �ִ񰪰� �ּڰ��� ������ input���� ���ؼ� ���� ���� ����� �ϴ� code
	for (int i = 1; i < line; i++) {
		for (int j = 0; j < 3; j++) 
			cin >> input[j];
		
		maxDp[0] = max(maxDp[0], maxDp[1]);
		maxDp[2] = max(maxDp[1], maxDp[2]);
		maxDp[1] = max(maxDp[0], maxDp[2]);

		minDp[0] = min(minDp[0], minDp[1]);
		minDp[2] = min(minDp[1], minDp[2]);
		minDp[1] = min(minDp[0], minDp[2]);

		for (int j = 0; j < 3; j++) {
			maxDp[j] += input[j];
			minDp[j] += input[j];
		}
	}

	// ver2 dp�� ����� ������ ������� �̿��� �ؾ� �ϴµ� 
	// ������ �ϴٺ��� �� ���� ���� �� �ֱ� ������ tmp�迭�� ���� dp���� ������ �Ŀ� ���Ӱ� dp�� �� ���� ����� �־���.
	/*
	for (int i = 1; i < line; i++) {
		// tmp array�� dp�� ����Ǿ��� ���� �̵���Ų��. 
		for (int j = 0; j < 3; j++) {
			maxtmp[j] = maxDp[j];
			mintmp[j] = minDp[j];
		}

		// renew the first index value
		int tmp;
		cin >> tmp;
		maxDp[0] = max(maxtmp[0] + tmp, maxtmp[1] + tmp);
		minDp[0] = min(mintmp[0] + tmp, mintmp[1] + tmp);

		// second index value
		// 
		cin >> tmp;
		maxDp[1] = max(maxtmp[0] + tmp, maxtmp[1] + tmp);
		maxDp[1] = max(maxDp[1], maxtmp[2] + tmp);
		minDp[1] = min(mintmp[0] + tmp, mintmp[1] + tmp);
		minDp[1] = min(minDp[1], mintmp[2] + tmp);

		// third index value
		cin >> tmp;
		maxDp[2] = max(maxtmp[1] + tmp, maxtmp[2] + tmp);
		minDp[2] = min(mintmp[1] + tmp, mintmp[2] + tmp);
	}
	*/
}

void PrintAnswer() {
	// print max value
	int ans = maxDp[0];
	for (int i = 1; i < 3; i++)
		ans = max(ans, maxDp[i]);
	cout << ans << " ";

	// print min value
	ans = minDp[0];
	for (int i = 1; i < 3; i++)
		ans = min(ans, minDp[i]);
	cout << ans;
}