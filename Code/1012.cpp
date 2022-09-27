/* 
�߸��� �˰����� �̿��� �ؼ� ������ Ǯ���� �ؼ� ������ �߻��Ͽ���.
�ܼ��� �ڱ� ��ġ���� ���κа� ���ʺκ��� ��������� ���Ӱ� ������� ���� ������� ������ �Ͽ���.
2���� ���ڷ� � ������ ǥ���� �� �� bool�ڷ����� �̿��� �ϸ� �ȴ�.
*/
/*
ver�� ���ؿ� ������ �ð� ������� �ο��� �� ���̴�..
ver1: ver2���� �� ���� recursive call�� �ؼ� �� ���� overhead�� �߻��� �� �� �ִ�.
      dfs�� ���� �ڱ� ��ġ ������ ���� return�� �� �� �ִ�.
ver2: �̸� �̷��� ��ġ ������ ���縦 �ؼ� ���� ���� ��ġ�� �ƿ� recursive call�� ���� �ʾƼ�
      �� ���� recursive call�� �ϰ� �ȴ�.
ver3: array�� ũ�⸦ ����,���� ���� 2�� �÷� �־ outofarrayindex�� exception�� ���� �־���.
*/
#include <iostream>

using namespace std;

int width, length;

bool field[50][50]; //[����] [����] , True(1) -> Cabbage, False(0) -> Empty
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

// recursive or iteration�� ����� �� ���� �ǵ����� ���� ���� loop�� �����ؾ� �Ѵ�.
// ����loop�� ���� �ƹ� ��¾��� program�� ���ᰡ �ȴ�.
// dfs�� �ϸ� ���� ���� group�ε� visit���߿� unvisit���߷� ���� �� ����. visit ���߰� �Ǹ� ������ �����¿�� dfs�� �ϱ� �����̴�.
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