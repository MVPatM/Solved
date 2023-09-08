/* 
   변수 범위를 조심하자
   int형 변수는 -2의32승에서 2의 32승 미만까지의 수만 표현이 가능하다.
   계산 과정 도중에 이 범위를 초과하는 것이 있다면 더 큰 범위를 표현하는 자료형을 이용해야한다.
*/

#include <iostream>
#include <stack>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int building_num;;
    long long observable = 0;
	stack<int> height;
	cin >> building_num;

	for (int i = 0; i < building_num; i++) {
		int h;
		cin >> h;

		if (height.empty()) // For the first case
			height.push(h);
		else {
			while (!height.empty() && (height.top() <= h)){
				height.pop();
            }
            
            // the number of building that can see other buildings 
			observable += height.size();
			height.push(h);
		}
	}
	
	cout << observable;

	return 0;
}