// g++ -o tree 
// ./tree

#include <iostream>

typedef struct Node_T {
	Node_T* left;
	int val;
	Node_T* right;
} Node;

void bfs(Node* node) {
	Node* q[100];
	int qhead = 0;
  	int	qend = 0;

	if (node != NULL) {
		q[qend++] = node;

	}
	while (qhead != qend) {
		// pop one out
		Node* n = q[qhead++];  
		std::cout << n->val; 
		// push children in
		if (n->left) 
			q[qend++] = n->left;
		if (n->right)
			q[qend++] = n->right;
	}
}

int height(Node* node) {
	if (node == NULL) {
		return 0;
	}
	int left = height(node->left);
	int right = height(node->right);
	if (left>right) 
		return left+1;
	else 
		return right+1;
}

void postfix(Node* node) {
	if (node==NULL) {
		return;
	}
	postfix(node->left);
	postfix(node->right);
	std::cout << node->val;
}

void prefix(Node* node) {
	if (node == NULL) {
		return;
	}
	std::cout << node->val;
	prefix(node->left);
	prefix(node->right);
}

void infix(Node* node) {
	if (node==0) {
		return ;
	}
	infix(node->left);
	std::cout << node->val;
	infix(node->right);
}

Node* insert(Node* node, int val) { 
	if (node == 0) {
		return new Node{0, val, 0};
	}
	if (val < node->val) 
		node->left = insert(node->left, val);
	else 
		node->right = insert(node->right, val);
	return node;
}

Node* buildBST(int* a, int n) {
	Node *node = 0;
	for (int i=0; i<n; i++) {
		node = insert(node, a[i]);
	}
	return node;
}

void visit(Node**);

void freeTree(Node** node) {
	if (*node==0) {
		return ;
	}
	freeTree(&((*node)->left));
	freeTree(&((*node)->right));
	visit(node);
}

void visit(Node** node) {
	std::cout << "node " << (*node)->val << " freed" << std::endl;
	free(*node);
	*node = 0;
}

int main() {
	int a[] = {7,4,6,8,5,3,2,1,0};
	int n = sizeof(a)/sizeof(int);
	Node* node = buildBST(a, n);
	std::cout << "bfs: ";  bfs(node); std::cout << std::endl; // 748362510
	std::cout << "infix: ";  infix(node); std::cout << std::endl;  // 012345678 
	std::cout << "prefix: "; prefix(node); std::cout << std::endl; // 743210658
	std::cout << "postfix: "; postfix(node); std::cout << std::endl; // 012356487
	std::cout << "height: "<< height(node) << std::endl;  // 6
	freeTree(&node);
	std::cout << "bfs: ";  bfs(node); std::cout << std::endl; // empty
	return 1;
}
/*
bfs: 748362510
infix: 012345678
prefix: 743210658
postfix: 012356487
height: 6
node 0 freed
node 1 freed
node 2 freed
node 3 freed
node 5 freed
node 6 freed
node 4 freed
node 8 freed
node 7 freed
bfs: 
*/
