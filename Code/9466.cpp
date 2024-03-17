/*
������ ���� ���� container�� ���� ������ �ʿ䰡 �ִ��� �������� �Ǵ��ؼ�
container ��뿩�θ� ������.
ver1: iteration�� ����Ͽ��� ���ù��� ���� node�� 0, ���� turn�� ���ù��� node�� 1, ���� ���ù޾��� node�� 2��� �����Ѵ�.
      ���� team���� �߰��� �ϴ� �������� �ϴ� stack�� node�� �ְ� state�� 1�� ������ �Ѵ�. �� �� stack �� �ִ� node�� state�� 
	  2 �̰ų� 1�̸��� stack�� ���� �ʴ´�.
	  ���� ������ node�� state�� 2�̸� stack�� �ִ� ���Ҹ� pop�ϸ鼭 state�� 2�� �������ְ� count�� ���ش�.
	  ������ node�� state�� 1�̸� stack�� �ִ� ���Ҹ� pop�ϸ鼭 ���� ���� ��� �ִ����� ã�´�.
	  ã�� �������� count�� ������ �ʰ� ã�� �� �ں��� count�� ���ش�
	  team�� ������ ���ϴ� node�� count�� ���ش�.
ver2: team�� �Ƿ��� circular������ �����߸� �Ѵ�.
	  cycle�� ������ �ʴ� �ٴ� ���� ���������� �Ǿ� �ִٴ� �ǹ��̴�.
	  ���������� �������� ������ edge�� �������� �ʰ� node�� ���� ������ edge�� �����Ѵ�
	  �׸��� ��ȯ������ �������� �������� �ʴ´�.
	  ���������� ��� ���������� Ž���� �����ϸ� ��� ���� ��� search�� �����ϴ�.
ver3: team�� ������ node�� count�� ���ְ� student������ ���ش�.
      recursive fuction�� ����� �ϸ� for���� stack���� �ڷᱸ���� �̿��ϴ� ȿ���� �� �� �ִ�.
	  for���� ����� ���� �������μ� �ٸ� �ڷᱸ���� �̿����� �ʾƵ� �ȴ�.
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