#include "btree.h"
#include <iostream>
#include <queue>

BinaryTree::BinaryTree() {
	root = nullptr;
}

BinaryTree::~BinaryTree() {
	destroyTree(root);
}

void BinaryTree::destroyTree(TreeNode* node) {
	if (node != nullptr) {
		destroyTree(node->left);
		destroyTree(node->right);
		delete node;
	}
}

TreeNode* BinaryTree::insert(int element, TreeNode* node) {
if (node == nullptr) {
	node = new TreeNode;
	node->data = element;
	node->left = node->right = nullptr;
} else if (element < node->data) {
	node->left = insert(element, node->left);
} else if (element > node->data) {
	node->right = insert(element, node->right);
}
	return node;
}

void BinaryTree::insert(int element) {
	root = insert(element, root);
}

void BinaryTree::levelOrderTraversal(TreeNode* node) {
	if (node == nullptr)
		return;
	
	std::queue<TreeNode*> q;
	q.push(node);
	
	while (!q.empty()) {
	TreeNode* current = q.front();
	q.pop();
	
	std::cout << current->data << " ";
	
	if (current->left != nullptr)
	  q.push(current->left);
	if (current->right != nullptr)
	  q.push(current->right); 
	}
}

void BinaryTree::levelOrderTraversal() {
	levelOrderTraversal(root);
	std::cout << std::endl;
}
BinaryTree* BinaryTree::arrayToBinaryTree(int* arr, int size) {
BinaryTree* tree = new BinaryTree();
for (int i = 0; i < size; i++) {
	tree->insert(arr[i]);
}
	return tree;
}

int BinaryTree::getWidth(TreeNode* node, int level) {
	if (node == NULL)
		return 0;
	if (level == 1)
		return 1;
	else if (level > 1)
		return getWidth(node->left, level-1) + getWidth(node->right, level-1);
	return 0;
}

int BinaryTree::getWidth() {
int maxWidth = 0;
int width;
int height = getHeight(root);

for (int i = 1; i <= height; i++) {
	width = getWidth(root, i);
	if (width > maxWidth)
		maxWidth = width;
}

	return maxWidth;
}

int BinaryTree::getHeight(TreeNode* node) {
if (node == nullptr)
return 0;
else {
	int lHeight = getHeight(node->left);
	int rHeight = getHeight(node->right);
	
	if (lHeight > rHeight)
	  return(lHeight + 1);
	else 
	  return(rHeight + 1);
}
}