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

// 첫번째 줄의 값을 초기화하는데는 문제가 없다
void InputInfo() {
	cin >> line;

	// 첫번째 줄 값을 input
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
	// 이전의 dp값에서 최댓값과 최솟값을 구한후 input값을 더해서 다음 값을 계산을 하는 code
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

	// ver2 dp에 저장된 이전의 결과값을 이용을 해야 하는데 
	// 연산을 하다보면 이 값이 변할 수 있기 때문에 tmp배열에 예전 dp값을 저장한 후에 새롭게 dp에 들어갈 값을 계산해 주었다.
	/*
	for (int i = 1; i < line; i++) {
		// tmp array에 dp에 저장되었던 값을 이동시킨다. 
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