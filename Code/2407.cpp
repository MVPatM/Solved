#include <iostream>
#include <cstring>
#include <algorithm> // reverse함수는 algorithm 헤더파일에 존재한다.

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

string dp[101][101];
int N, R;

inline void InputInfo() { cin >> N >> R; }
void Init();
string Comb(int n, int r);
string StringSum(string str1, string str2);

int main(void) {
	fastio;
	InputInfo();
	Init();
	cout << Comb(N, R);

	return 0;
}

// N과 R이 5이상이여도 4c1은 사용되어질 수 있기 때문에 1부터 모두 push를 해주어야 한다.
void Init() {
	for (int n = 1; n <= N; n++) {
		string tmp;
		int tmpN = n;
		
		while (tmpN) {
			tmp.push_back((tmpN % 10) + '0'); // 한자리 int형정수를 char형으로 변환시키는 code
			tmpN /= 10;
		}
	
		reverse(tmp.begin(), tmp.end());
		dp[n][1] = tmp;
		dp[n][n - 1] = tmp;
		dp[n][0] = "1";
		dp[n][n] = "1";
	}
}

// 파스칼 삼각형을 이용한 재귀 함수를 이용해서 답을 구하려고 한다.
// 이 때 중복되어지는 값은 dp를 이용하여서 계산이 중복되지 않도록 한다.
string Comb(int n, int r) {
	if (dp[n][r] != "")
		return dp[n][r];

	dp[n][r] = StringSum(Comb(n - 1, r - 1), Comb(n - 1, r));
	dp[n][n - r] = dp[n][r];
	return dp[n][r];
}

// long long 자료형으로 정수의 길이가 한계가 있으면 string을 이용해서 계산을 진행하여야 한다.
string StringSum(string str1, string str2) {
	string ans = "";
	int sum = 0;

	// while문 앞에도 empty를 묻는 것을 붙이고 
	// if 문에서도 empty의 유무를 묻기 때문에 중복된 물음이라고 생각을 해서 안좋은 code라고 생각을 하였다.
	// 중복되게 물었다고 하여서 편견을 가지지 말자
	while (!str1.empty() || !str2.empty() || sum) {
		if (!str1.empty()) {
			sum += (str1.back() - '0');
			str1.pop_back();
		}

		if (!str2.empty()) {
			sum += (str2.back() - '0');
			str2.pop_back();
		}

		ans.push_back((sum % 10) + '0'); // 한자리 int형정수를 char형으로 변환을 시키는 방법
		sum /= 10;
	}

	reverse(ans.begin(), ans.end());
	return ans;
}