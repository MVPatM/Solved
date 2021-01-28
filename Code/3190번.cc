/* 
   몇몇 규칙에 따라서 값이 계속 반복 되는 경우 
   array과 %연산을 이용해서 값을 반복 시켜준다.
   코드가 어떤 조건이 변하는 경계점에서 프로그램이 잘 작동을 하는지 확인해야 한다.
*/

#include <iostream>
#include <deque>
#include <queue>
#include <utility>

using namespace std;

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int board_size, apple_num, time = 1;
	int going_dir = 1;// 0: north, 1:right, 2:south, 3:left
	
	cin >> board_size;
	cin >> apple_num;

	int direct_change;

	deque<pair<int, int>> snake; // front: head, back: tail
	queue<pair<int, char>> direction;

	int** board = new int*[board_size + 1]; // snake > 2, apple > 1, empty > 0  + [행][열]

	// array initialization
	for (int i = 0; i < (board_size + 1); i++) {
		board[i] = new int[board_size + 1];
	}
	for (int i = 0; i < (board_size + 1); i++) {
		for (int j = 0; j < (board_size + 1); j++) {
			board[i][j] = 0;
		}
	}

	for (int i = 0; i < apple_num; i++) {
		int AppleX, AppleY;
		cin >> AppleX >> AppleY;
		board[AppleX][AppleY] = 1;
	}

	cin >> direct_change;

	for (int i = 0; i < direct_change; i++) {
		int time;
		char d;

		cin >> time >> d;

		direction.push(make_pair(time, d));
	}

	snake.push_front(make_pair(1, 1));
	board[1][1] = 2;

	while (1) {
		int nx, ny;
		nx = snake.front().first + dx[going_dir];
		ny = snake.front().second + dy[going_dir];

		if ((nx < 1 || ny < 1 || nx > board_size || ny > board_size) || board[nx][ny] == 2)
			break;

		if (board[nx][ny] == 1) // eat apple
			snake.push_front(make_pair(nx, ny));
		else {// don't eat apple
			snake.push_front(make_pair(nx, ny));
			board[snake.back().first][snake.back().second] = 0;
			snake.pop_back();
		}
        
        board[nx][ny] = 2;

		if (!direction.empty() && (direction.front().first == time)) {
			if (direction.front().second == 'D')
				going_dir = (going_dir + 1) % 4;
			else if (direction.front().second == 'L')
				going_dir = (3 + going_dir) % 4;
			direction.pop();
		}

		time++;
	}

	for (int i = 0; i < (board_size + 1); i++) {
		delete[] board[i];
	}

	delete board;

	cout << time << "\n";

	return 0;
}