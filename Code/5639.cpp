/*
tree�� �������ʰ� preorder��ȸ�� ���ؼ� �ٷ� postorder��ȸ�� ���� �� �ִ�.
preorder�� postorder�� �Ʒ����� ���� �ö���鼭 ����� �ϴ� �����̰�
inorder�� ������ �Ʒ��� �������鼭 ����� �ϴ� �����̴�.
�׷��� preorder�� postorder�� bottom-up��İ� �����ϰ�
inorder�� top-down��İ� �����ϴ�.
*/
#include <iostream>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int tree[1000001][2];
int preorder[10001];
int root, sz = 0;

void InputInfo();
void InputInfo2();
void MakeTree(int n);
void ShowPostorder(int n);
void ShowPostorderver2(int start, int end);
void Solve();
void Solve2();

int main(void) {
	fastio;
	InputInfo2();
	Solve2();
}

void InputInfo() {
	int tmp;
	cin >> root;
	
	while (cin >> tmp) {
		if (tmp == EOF)
			break;
		MakeTree(tmp);
	}
}

void InputInfo2() {
	int tmp, i = 0;

	while (cin >> tmp) {
		if (tmp == EOF)
			break;
		sz++;
		preorder[i++] = tmp;
	}
}

void MakeTree(int n) {
	int cur = root;

	while (1) {
		if (cur > n) { // left child
			if (tree[cur][0] == 0) {
				tree[cur][0] = n;
				break;
			}
			else
				cur = tree[cur][0];
		}
		else if (cur < n) { // right child
			if (tree[cur][1] == 0) {
				tree[cur][1] = n;
				break;
			}
			else
				cur = tree[cur][1];
		}
	}
}

void ShowPostorder(int n) {
	if (!n)
		return;

	ShowPostorder(tree[n][0]);
	ShowPostorder(tree[n][1]);
	cout << n << "\n";
}

void Solve() {
	ShowPostorder(root);
}

void ShowPostorderver2(int start, int end) {
	if (start > end)
		return;
	
	int left_end = end;
	int sub_root = preorder[start];

	for (int i = start + 1; i <= end; i++) {
		if (sub_root < preorder[i]) {
			left_end = i - 1;
			break;
		}
	}

	ShowPostorderver2(start + 1, left_end);
	ShowPostorderver2(left_end + 1, end);
	cout << sub_root << "\n";
}

void Solve2() {
	ShowPostorderver2(0, sz - 1);
}