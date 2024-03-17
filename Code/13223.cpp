/* using namespace std를 사용함에 따라서 end의 variable를 선언하는 것은
 모호함을 만들어 낼 수 있다.
*/
/*
<string> library에 to_string 함수는 int형 값을 string으로 바꾸어 준다.

*/
#include <iostream>
#include <cstring>
#include <string>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0)

//string now, finish;
string now, finish;
void InputInfo() { cin >> now >> finish; }
void GetTime();

int main(void) {
	fastio;
	InputInfo();
	GetTime();
}
void GetTime() {
	int now_hour, now_min, now_sec;
	int fin_hour, fin_min, fin_sec;
	int nd_hour, nd_min, nd_sec;
	int now_total, fin_total, tmp;
	string ans;

	// string의 index를 하나하나 int형값으로 바꾸어 주는 과정
	now_hour = (now[0] - '0') * 10 + (now[1] - '0');
	now_min = (now[3] - '0') * 10 + (now[4] - '0');
	now_sec = (now[6] - '0') * 10 + (now[7] - '0');
	fin_hour = (finish[0] - '0') * 10 + (finish[1] - '0');
	fin_min = (finish[3] - '0') * 10 + (finish[4] - '0');
	fin_sec = (finish[6] - '0') * 10 + (finish[7] - '0');

	now_total = now_hour * 3600 + now_min * 60 + now_sec;
	fin_total = fin_hour * 3600 + fin_min * 60 + fin_sec;
	tmp = (fin_total - now_total + 24 * 3600) % (24 * 3600);

	nd_hour = tmp / 3600;
	tmp -= nd_hour * 3600;
	nd_min = tmp / 60;
	nd_sec = tmp - nd_min * 60;
	
	// 현재시간과 투여시간이 같을 때 예외 처리
	if (nd_hour == 0 && nd_min == 0 && nd_sec == 0)
		nd_hour = 24;
	
	// make the answer
	if (nd_hour < 10)
		ans += '0';
	ans += to_string(nd_hour);
	ans += ':';

	if (nd_min < 10)
		ans += '0';
	ans += to_string(nd_min);
	ans += ':';

	if (nd_sec < 10)
		ans += '0';
	ans += to_string(nd_sec);

	cout << ans;
}