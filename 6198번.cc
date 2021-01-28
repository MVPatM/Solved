/* 
   ���� ������ ��������
   int�� ������ -2��32�¿��� 2�� 32�� �̸������� ���� ǥ���� �����ϴ�.
   ��� ���� ���߿� �� ������ �ʰ��ϴ� ���� �ִٸ� �� ū ������ ǥ���ϴ� �ڷ����� �̿��ؾ��Ѵ�.
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