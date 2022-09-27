/* 
잘못된 알고리즘을 이용을 해서 문제를 풀려고 해서 문제가 발생하였다.
단순히 자기 위치에서 윗부분과 왼쪽부분이 비어있으면 새롭게 만들어진 배추 무리라고 생각을 하였다.
2가지 숫자로 어떤 변수를 표현을 할 때 bool자료형을 이용을 하면 된다.
*/
/*
ver은 백준에 제출한 시간 순서대로 부여를 한 것이다..
ver1: ver2보다 더 많은 recursive call을 해서 더 많은 overhead가 발생을 할 수 있다.
      dfs에 들어온 자기 위치 정보에 따라서 return을 할 수 있다.
ver2: 미리 미래의 위치 정보를 조사를 해서 옳지 않은 위치는 아예 recursive call을 하지 않아서
      더 적은 recursive call읋 하게 된다.
ver3: array의 크기를 가로,세로 각각 2씩 늘려 주어서 outofarrayindex의 exception을 막아 주었다.
*/
#include <iostream>

using namespace std;

int width, length;

bool field[50][50]; //[세로] [가로] , True(1) -> Cabbage, False(0) -> Empty
bool isvisited[50][50];

int dx[] = {-1, 0 , 1 , 0 };
int dy[] = { 0, -1, 0 , 1 };

void Do_Test();
void InputCabbagePos(int n);
void dfs(int y, int x);
int CalWorm();
void CleanField();
void printfield();

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	Do_Test();

	return 0;
}

void Do_Test() {
	int testcase, num;

	cin >> testcase;

	while (testcase--) {
		cin >> width >> length >> num;
		InputCabbagePos(num);
		printfield();
		cout << CalWorm() << "\n";
		CleanField();
	}
}

void InputCabbagePos(int n) {
	while (n--) {
		int x, y;
		cin >> x >> y;
		field[y][x] = true;
	}
}

// recursive or iteration을 사용을 할 때는 의도하지 않은 무한 loop를 조심해야 한다.
// 무한loop를 돌면 아무 출력없이 program이 종료가 된다.
// dfs를 하면 같은 배추 group인데 visit배추와 unvisit배추로 나눌 수 없다. visit 배추가 되면 무조건 상하좌우로 dfs를 하기 때문이다.
void dfs(int y, int x) {
	if (!field[y][x] || isvisited[y][x])
		return;

	isvisited[y][x] = true;

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && nx < width
			&& ny >= 0 && ny < length)
			dfs(ny, nx);
	}
}

int CalWorm() {
	int worm = 0;

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			if (field[i][j] && !isvisited[i][j]) {
				worm++;
				dfs(i, j);
			}
		}
	}

	return worm;
}

void CleanField() {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			field[i][j] = false;
			isvisited[i][j] = false;
		}
	}
}

void printfield() {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++)
			cout << field[i][j] << " ";

		cout << "\n";
	}
}