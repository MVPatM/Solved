/*
문제에 따라서 값을 container에 따로 저장할 필요가 있는지 없는지를 판단해서
container 사용여부를 따진다.
ver1: iteration을 사용하였고 선택받지 않은 node를 0, 지금 turn에 선택받은 node를 1, 전에 선택받아진 node를 2라고 정의한다.
      같은 team인지 발견을 하는 과정에서 일단 stack에 node를 넣고 state를 1로 설정을 한다. 이 때 stack 에 넣는 node의 state가 
	  2 이거나 1이면은 stack에 넣지 않는다.
	  만약 마지막 node의 state가 2이면 stack에 있는 원소를 pop하면서 state를 2로 변경해주고 count를 해준다.
	  마지막 node의 state가 1이면 stack에 있는 원소를 pop하면서 같은 값이 어디에 있는지를 찾는다.
	  찾기 전까지는 count를 해주지 않고 찾고 난 뒤부터 count를 해준다
	  team을 가지지 못하는 node를 count를 해준다.
ver2: team이 되려면 circular구조를 가져야만 한다.
	  cycle을 가지지 않는 다는 것은 직선구조로 되어 있다는 의미이다.
	  직선구조의 시작점은 들어오는 edge가 존재하지 않고 node로 부터 나가는 edge만 존재한다
	  그리고 순환구조는 시작점이 존재하지 않는다.
	  직선구조의 모든 시작점에서 탐색을 시작하면 모든 점을 모두 search가 가능하다.
ver3: team을 가지는 node를 count를 해주고 student수에서 빼준다.
      recursive fuction을 사용을 하면 for문과 stack등의 자료구조를 이용하는 효과를 낼 수 있다.
	  for문을 사용을 하지 않음으로서 다른 자료구조를 이용하지 않아도 된다.
*/
#include <iostream>
#include <cstring>

using namespace std;

#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int studentpriority[100001];
bool isvisited[100001];
int ans;

void Do_Project();
void PrintNoteamstudent();
void inputarray(int s);
int findteam(int n);
void Initiate(int s);

int main(void) {
	fastio;
	Do_Project();

	return 0;
}

void Do_Project() {
	int testcase;
	cin >> testcase;

	while (testcase--) {
		PrintNoteamstudent();
	}
}

void PrintNoteamstudent() {
	int student, count = 0;

	cin >> student;
	Initiate(student);
	inputarray(student);

	for (int i = 1; i <= student; i++) {
		ans = 0;
		if (!isvisited[i])
			findteam(i);
		count += ans;
	}

	cout << count << "\n";
}

void inputarray(int s) {
	for (int i = 1; i <= s; i++) {
		int tmp;
		cin >> tmp;
		studentpriority[i] = tmp;
	}
}

int findteam(int n) { // change the code
	if (isvisited[n])
		return n;

	isvisited[n] = true;
	int rp = findteam(studentpriority[n]);
	ans++;

	if (n == rp)
		ans = 0;
	return rp;
}

void Initiate(int s) {
	ans = 0;
	s++;
	memset(isvisited, 0, s * sizeof(bool));
}