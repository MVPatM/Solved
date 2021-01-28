/*
	�ʹ� ���� ����Լ��� �������� �ʵ��� ������ �ؾ��Ѵ�.
	���ÿ� ����Լ��� ���õ� parameter�� variable�� ������ �ؾ��ϴµ�
	������ ����������� �Ѱ谡 �ֱ� �����̴�.
*/

#include <iostream>
#include <cmath>

using namespace std;

int ar[4] = { 0, 0, 1, 0};
int ac[4] = { 0, 1, -1, 1};

long long visit = 0;
int findr, findc;

void moving_z(long long l, int r, int c);
void playing_z();

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	playing_z();
	return 0;
}

void moving_z(long long l, int r, int c) {
	if (l == 2) {
		for (int i = 0; i < 4; i++) {
			r += ar[i];
			c += ac[i];

			if ((r == findr) && (c == findc)) {
				cout << visit << "\n";
				return;
			}
			
			visit++;
		}
        
        return;
	}

	int arbr = r + l / 2;
	int arbc = c + l / 2;

	if ((findr < arbr) && (findc < arbc))
		moving_z(l / 2, r, c);
	else if ((findr < arbr) && (findc >= arbc)) {
		visit += l*l / 4;
		moving_z(l / 2, r, arbc);
	}
	else if ((findr >= arbr) && (findc < arbc)) {
		visit += l*l / 2;
		moving_z(l / 2, arbr, c);
	}
	else {
		visit += l*l * 3 / 4;
		moving_z(l / 2, arbr, arbc);
	}
}

void playing_z () {
	int n, length;
	cin >> n >> findr >> findc;
	length = (int)pow(2.0, n);

	moving_z(length, 0, 0);
}