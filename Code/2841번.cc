/*
  cin �� cout�� �ӵ��� c�� ����� �ӵ����� ������.
  �׷��� ios::sync_with_stdio(0) �� cin.tie(0)�Լ��� ���ؼ� ����� �ӵ��� ����ų �� �ִ�.
  endl�� '\n' ���� ó���ӵ��� ������.
  (����) -> �迭�� �׻� index�� ������ 0���� �����Ѵٴ� ���� �� �����ؾ� �Ѵ�.
*/

#include <iostream>
#include <stack>

using namespace std;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
	int itr, fret;
	int count = 0;
	stack<int> frets[7]; // ���� �ٸ��� ������ ��� �ִ� fret�� �����Ѵ�.

	cin >> itr >> fret;

	for (int i = 0; i < itr; i++) {
		int line, num;
		cin >> line >> num;
        
		if (frets[line].empty()) {
			frets[line].push(num);
			count += 1;
		}
		else {
			while (!frets[line].empty() && frets[line].top() > num) {
				();frets[line].pop
				count += 1;
			}

			if (frets[line].empty() || frets[line].top() < num) {
				frets[line].push(num);
				count += 1;
			}
		}
	}

	cout << count << "\n";

	return 0;
}