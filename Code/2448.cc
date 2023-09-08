#include <iostream>

using namespace std;

char map[3072][6144];

void draw_star(int height, int x, int y); //x and y are starting point of the box
void drawing();

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	drawing();
	
	return 0;
}

void draw_star(int height, int x, int y) {
	if (height == 3) {
		map[x][y + 2] = '*';
		map[x + 1][y + 1] = '*';
		map[x + 1][y + 3] = '*';
		for (int i = 0; i < 5; i++)
			map[x + 2][y + i] = '*';
		return; 
	}
	
	int half = height / 2;

	draw_star(half, x, y + half);
	draw_star(half, x + half, y);
	draw_star(half, x + half, y + height);
}

void drawing() {
	int line;
	cin >> line;

	draw_star(line, 0, 0);

	for (int i = 0; i < line; i++) {
		for (int j = 0; j < 2 * line; j++) {
			if (map[i][j] == '*')
				cout << "*";
			else
				cout << " ";
		}
		cout << "\n";
	}
}