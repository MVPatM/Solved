/*
새로운 tree를 만들어 줄 필요가 없고
left tree를 먼저 분할 시켜주면서 root를 출력 시켜주면 preorder를 출력시키는 것과 같다.
*/
#include <iostream>

using namespace std;
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

int vertex_num;
int inorder[100000];
int postorder[100000];
int inorderidx[100001];
int tree[100001][2]; // 0:left child, 1: right child, 그리고 array의 값이 0이면 child가 존재하지 않는 것이다.

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

void MakeTree(int in_from, int in_to, int post_from, int post_to) { // root값을 굳이 parameter값으로 보낼 필요가 있을까?? 라는 거죵...
	if (in_from == in_to) // left subtree와 right subtree가 모두 존재하지 않는 경우
		return;

	int i, j; // i = rootidx, j = 
	int root = postorder[post_to];
	// 이 for문에서는 예외 조건이 없다.
	for (i = in_from; i <= in_to; i++) { // inorder에서 현재 root index찾기 
		if (inorder[i] == root) 
			break;
	}

	// left subtree의 node의 개수는 inorder에서나 postorder에서나 같다.
	// right subtree도 left subtree와 마찬가지로 node의 개수는 inorder나 postorder나 같다.
	int left_root = 0, right_root = 0;
	if (i == in_to) { // left subtree만 존재하는 경우
		j = post_to;
		left_root = postorder[j - 1];
	}
	else if (i == in_from) { // right subtree만 존재하는 경우
		j = post_from;
		right_root = postorder[post_to - 1];
	}
	else { // left subtree와 right subtree가 모두 존재하는 경우
		for (j = post_from; j < post_to; j++) { // postorder에서 다음 재귀함수에서 사용할 root 찾기
			if (postorder[j] == inorder[i + 1]) {
				left_root = postorder[j - 1];
				right_root = postorder[post_to - 1]; 
				break;
			}
		}
	}

	tree[root][0] = left_root;
	tree[root][1] = right_root;

	// left subtree가 존재하면 recursion function call
	if (left_root)
		MakeTree(in_from, i - 1, post_from, j - 1);
	
	// right subtree가 존재하면 recursion function call
	if (right_root)
		MakeTree(i + 1, in_to, j, post_to - 1);
}

void MakeTreeVer2(int in_from, int in_to, int post_from, int post_to) {
	if (in_from > in_to || post_from > post_to)
		return;

	// for문을 돌려서 postorder의 마지막 값이 inorder의 어떤 index에 존재하는 지를 찾는 것이 아니라
	// 또 다른 database인 inorder에 저장된 값이 inorder에서 어떤 index에 존재하는 지를 나타내주는 db를 새로 만들어서 for문을 돌리지 않도록 해준다.
	int rootidx = inorderidx[postorder[post_to]];
	int leftsize = rootidx - in_from;
	int rightsize = in_to - rootidx;
	cout << inorder[rootidx] << " ";
	
	MakeTreeVer2(in_from, rootidx - 1, post_from, post_from + leftsize - 1);
	MakeTreeVer2(rootidx + 1, in_to, post_to - rightsize, post_to - 1);
}

void MakeTreeVer3(int in_from, int in_to, int post_from, int post_to) {
	// for문을 돌려서 postorder의 마지막 값이 inorder의 어떤 index에 존재하는 지를 찾는 것이 아니라
	// 또 다른 database인 inorder에 저장된 값이 inorder에서 어떤 index에 존재하는 지를 나타내주는 db를 새로 만들어서 for문을 돌리지 않도록 해준다.
	int rootidx = inorderidx[postorder[post_to]];
	int leftsize = rootidx - in_from;
	int rightsize = in_to - rootidx;
	cout << inorder[rootidx] << " ";

	// left와 right를 순서를 바꾸게 되면 preorder로 출력이 안되기 때문에 순서를 바꾸면 안된다.
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