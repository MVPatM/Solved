#include <iostream>
#include <cstring>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);
using llt = long long;

int arr_length;
llt mul_num;
int ar[5][5];
int mulAr[5][5];
int ans[5][5];

void InputInfo();
void ArrMult();
void GetRemainder();

int main(void) {
	fastio;
	InputInfo();
	GetRemainder();
	for (int i = 0; i < arr_length; i++) {
		for (int j = 0; j < arr_length; j++)
			cout << ans[i][j] << " ";
		cout << "\n";
	}


	return 0;
}

void InputInfo() {
	cin >> arr_length >> mul_num;
	for (int i = 0; i < arr_length; i++) {
		for (int j = 0; j < arr_length; j++) {
			int tmp;
			cin >> tmp;
			ar[i][j] = tmp;
			mulAr[i][j] = tmp;
		}
	}
}

void ArrMult() {
	int tmp[5][5];
	int i, j, k;

	memset(tmp, 0, sizeof(tmp));
	for (i = 0; i < arr_length; i++) {
		for (j = 0; j < arr_length; j++) {
			for (k = 0; k < arr_length; k++) 
				tmp[i][j] += (mulAr[i][k] * mulAr[k][j]);
		}
	}

	for (i = 0; i < arr_length; i++) {
		for (j = 0; j < arr_length; j++)
			mulAr[i][j] = tmp[i][j] % 1000;
	}
}


void GetRemainder() {
	int tmp[5][5];
	int i, j, k;

	for (int i = 0; i < arr_length; i++)
		ans[i][i] = 1;

	while (mul_num) {
		// tmp의 matrix는 while문이 반복이 되면 계속 initialize를 시켜주어야 한다.
		memset(tmp, 0, sizeof(tmp));
		if (mul_num % 2) {
			for (i = 0; i < arr_length; i++) {
				for (j = 0; j < arr_length; j++) {
					for (k = 0; k < arr_length; k++) 
						tmp[i][j] += (ans[i][k] * mulAr[k][j]);
				}
			}

			for (i = 0; i < arr_length; i++) {
				for (j = 0; j < arr_length; j++)
					ans[i][j] = tmp[i][j] % 1000;
			}
		}

		ArrMult();
		mul_num /= 2;
	}
}