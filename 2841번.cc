/*
  cin 과 cout의 속도는 c의 입출력 속도보다 느리다.
  그래서 ios::sync_with_stdio(0) 과 cin.tie(0)함수를 통해서 입출력 속도를 향상시킬 수 있다.
  endl은 '\n' 보다 처리속도가 느리다.
  (주의) -> 배열은 항상 index의 시작은 0에서 시작한다는 점을 꼭 인지해야 한다.
*/

#include <iostream>
#include <stack>

using namespace std;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
	int itr, fret;
	int count = 0;
	stack<int> frets[7]; // 현재 줄마다 손으로 잡고 있는 fret을 저장한다.

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