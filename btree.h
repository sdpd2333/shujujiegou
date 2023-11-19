#ifndef BTREE_H
#define BTREE_H

#include "rqueue.h"

struct TreeNode {
	int data;
	TreeNode* left;
	TreeNode* right;
};

class BinaryTree {
	public:
	BinaryTree();
	~BinaryTree();
	
	void insert(int element);
	void levelOrderTraversal();
	BinaryTree* arrayToBinaryTree(int* arr, int size);
	int getWidth();
	// Add more functions as required ...
	
	private:
	TreeNode* root;
	
	void destroyTree(TreeNode* node);
	TreeNode* insert(int element, TreeNode* node);
	void levelOrderTraversal(TreeNode* root);
	int getWidth(TreeNode* node, int level);
	int getHeight(TreeNode* node);
};

#endif // BTREE_H