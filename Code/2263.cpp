/*
���ο� tree�� ����� �� �ʿ䰡 ����
left tree�� ���� ���� �����ָ鼭 root�� ��� �����ָ� preorder�� ��½�Ű�� �Ͱ� ����.
*/
#include <iostream>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int vertex_num;
int inorder[100000];
int postorder[100000];
int inorderidx[100001];
int tree[100001][2]; // 0:left child, 1: right child, �׸��� array�� ���� 0�̸� child�� �������� �ʴ� ���̴�.

void InputInfo();
void InputInfoVer2();
void MakeTree(int in_to, int in_from, int post_to, int post_from);
void MakeTreeVer2(int in_to, int in_from, int post_to, int post_from);
void ShowPreOrder(int n);
void Solve();

int main(void) {
	fastio;
	InputInfo();
	Solve();

	return 0;
}

void InputInfo() {
	int i;
	cin >> vertex_num;

	for (i = 0; i < vertex_num; i++)
		cin >> inorder[i];
	
	for (i = 0; i < vertex_num; i++)
		cin >> postorder[i];
}

void InputInfoVer2() {
	int i;
	cin >> vertex_num;

	for (i = 0; i < vertex_num; i++) {
		cin >> inorder[i];
		inorderidx[inorder[i]] = i;
	}

	for (i = 0; i < vertex_num; i++)
		cin >> postorder[i];
}

void MakeTree(int in_from, int in_to, int post_from, int post_to) { // root���� ���� parameter������ ���� �ʿ䰡 ������?? ��� ����...
	if (in_from == in_to) // left subtree�� right subtree�� ��� �������� �ʴ� ���
		return;

	int i, j; // i = rootidx, j = 
	int root = postorder[post_to];
	// �� for�������� ���� ������ ����.
	for (i = in_from; i <= in_to; i++) { // inorder���� ���� root indexã�� 
		if (inorder[i] == root) 
			break;
	}

	// left subtree�� node�� ������ inorder������ postorder������ ����.
	// right subtree�� left subtree�� ���������� node�� ������ inorder�� postorder�� ����.
	int left_root = 0, right_root = 0;
	if (i == in_to) { // left subtree�� �����ϴ� ���
		j = post_to;
		left_root = postorder[j - 1];
	}
	else if (i == in_from) { // right subtree�� �����ϴ� ���
		j = post_from;
		right_root = postorder[post_to - 1];
	}
	else { // left subtree�� right subtree�� ��� �����ϴ� ���
		for (j = post_from; j < post_to; j++) { // postorder���� ���� ����Լ����� ����� root ã��
			if (postorder[j] == inorder[i + 1]) {
				left_root = postorder[j - 1];
				right_root = postorder[post_to - 1]; 
				break;
			}
		}
	}

	tree[root][0] = left_root;
	tree[root][1] = right_root;

	// left subtree�� �����ϸ� recursion function call
	if (left_root)
		MakeTree(in_from, i - 1, post_from, j - 1);
	
	// right subtree�� �����ϸ� recursion function call
	if (right_root)
		MakeTree(i + 1, in_to, j, post_to - 1);
}

void MakeTreeVer2(int in_from, int in_to, int post_from, int post_to) {
	if (in_from > in_to || post_from > post_to)
		return;

	// for���� ������ postorder�� ������ ���� inorder�� � index�� �����ϴ� ���� ã�� ���� �ƴ϶�
	// �� �ٸ� database�� inorder�� ����� ���� inorder���� � index�� �����ϴ� ���� ��Ÿ���ִ� db�� ���� ���� for���� ������ �ʵ��� ���ش�.
	int rootidx = inorderidx[postorder[post_to]];
	int leftsize = rootidx - in_from;
	int rightsize = in_to - rootidx;
	cout << inorder[rootidx] << " ";
	
	MakeTreeVer2(in_from, rootidx - 1, post_from, post_from + leftsize - 1);
	MakeTreeVer2(rootidx + 1, in_to, post_to - rightsize, post_to - 1);
}

void MakeTreeVer3(int in_from, int in_to, int post_from, int post_to) {
	// for���� ������ postorder�� ������ ���� inorder�� � index�� �����ϴ� ���� ã�� ���� �ƴ϶�
	// �� �ٸ� database�� inorder�� ����� ���� inorder���� � index�� �����ϴ� ���� ��Ÿ���ִ� db�� ���� ���� for���� ������ �ʵ��� ���ش�.
	int rootidx = inorderidx[postorder[post_to]];
	int leftsize = rootidx - in_from;
	int rightsize = in_to - rootidx;
	cout << inorder[rootidx] << " ";

	// left�� right�� ������ �ٲٰ� �Ǹ� preorder�� ����� �ȵǱ� ������ ������ �ٲٸ� �ȵȴ�.
	if (leftsize)
		MakeTreeVer3(in_from, rootidx - 1, post_from, post_from + leftsize - 1);
	if (rightsize)
		MakeTreeVer3(rootidx + 1, in_to, post_to - rightsize, post_to - 1);
}

void ShowPreOrder(int n) {
	if (!n)
		return;

	cout << n << " ";
	ShowPreOrder(tree[n][0]);
	ShowPreOrder(tree[n][1]);
}

void Solve() { 
	int tree_root = postorder[vertex_num - 1];
	MakeTree(0, vertex_num - 1, 0, vertex_num - 1);
	ShowPreOrder(tree_root);
}