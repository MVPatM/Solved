#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int arr[1000];
int dp[1000];
int pointer[1000]; // index�� ����Ű�� array�̴�.
int len;

void InputInfo();
void Solve();

int main(void) {
	fastio;
	InputInfo();
	Solve();

	return 0;
}

void InputInfo() {
	cin >> len;

	for (int i = 0; i < len; i++)
		cin >> arr[i];
}

void Solve() {
	int maxvalue = 1, maxidx = 0, i;
	fill(dp, dp + len, 1);
	for (i = 0; i < len; i++)
		pointer[i] = i;

	for (i = 0; i < len; i++) {
		for (int j = 0; j < i; j++) {
			/* �̷� ������ �ڵ��� �ϸ� ���� ���� ������ ����ϰ� �ȴ�.
			if (arr[j] < arr[i]) { 
				num++;
			}
			*/
			if (arr[j] < arr[i]) { // ���� ��� ������ dp�� �̿��ؾ� �Ѵ�.
				//dp[i] = max(dp[i], dp[j] + 1);�ϳ��� �˻��� �ϸ鼭 �ڱ� �ڽ��� ���� ū�� �ƴϸ� index j�ǰ��� ������ ��ų ������ �ľ�

				if (dp[j] + 1 > dp[i]) {
					dp[i] = dp[j] + 1;
					pointer[i] = j;
				}
			}
		}
		
		if (dp[i] > maxvalue) {
			maxvalue = dp[i];
			maxidx = i;
		}
	}

	cout << maxvalue << "\n";

	// ���� 14002�� �߰� ����
	vector<int> tmp;
	for (i = maxidx; i != pointer[i]; i = pointer[i])
		tmp.push_back(arr[i]);
	tmp.push_back(arr[i]);
	// reverse�Լ��� �̿��ؼ� index�� ���ؼ� ������ �ϴ� ���� �ƴ϶� back�Լ��� �̿��ؼ� �ڿ��� ���� ������ �� �� �ִ�.
	reverse(tmp.begin(), tmp.end());

	for (i = 0; i < tmp.size(); i++)
		cout << tmp[i] << " ";

	/*
	* version 2
	for (i = 0; i < tmp.size(); i++) {
		cout << tmp.back();
		tmp.pop_back();
	}
	*/
}