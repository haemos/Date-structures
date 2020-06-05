#include <stdio.h>
#include <stdlib.h>


struct TreeNode
{
	int value;
	struct TreeNode* left;
	struct TreeNode* right;
};

typedef struct TreeNode* tree;
tree createBinaryTree();
tree insert(tree node, int key);
void displayTree(tree node);
int height(tree node);
tree singleRotateWithLeft(tree node);
tree singleRotateWithRight(tree node);
tree doubleRotateWithLeft(tree node);
tree doubleRotaetWithRight(tree node);

int main(void) {
	int key;
	int high;
	tree node;
	node=createBinaryTree();
	displayTree(node);
	
	return 0;
}



void displayTree(tree node) {
	if (node == NULL)
		return;
	displayTree(node->left);
	displayTree(node->right);
	printf("%d\t", node->value);
	
}


tree createBinaryTree() {
	tree node = NULL;
	int key;
	printf("Create Binary Tree\n please enter the element,seperated by space and stop the input by Enter\n");
	while (true)
	{
		scanf_s("%d", &key);
		node = insert(node,key);
		if (getchar() == '\n') {
			return node;
		}
	}
}

tree insert(tree node, int key) {
	int leftheight,rightheight,distance;
	leftheight = rightheight = distance =0;
	if (!node) {
		node = (tree)malloc(sizeof(struct TreeNode));
		if (!node) {
			printf("Out of space!\n");
		}
		else {
			node->value = key;
			node->left = node->right = NULL;
		}
		return node;
	}
	else if (key < node->value) {
		node->left = insert(node->left, key);
		if (!node->right)
			distance = height(node->left) + 1;
		else
			distance = height(node->left) - height(node->right);
		if (distance == 2)
			if (node->left->value > key)
				node = singleRotateWithLeft(node);
			else
				node = doubleRotateWithLeft(node);
	}
	else if (key > node->value) {
		node->right = insert(node->right, key);
		if (!node->left)
			distance = height(node->right) + 1 ;
		else
			distance = height(node->right) - height(node->left);
		if(distance==2){
			if (key > node->right->value)
				node = singleRotateWithRight(node);
			else
				node = doubleRotaetWithRight(node);
		}
	}
	
	return node;
}


int height(tree node) {
	int leftheight, rightheight;
	leftheight = rightheight = 0;
	if (node->left){
		leftheight = height(node->left);
		leftheight += 1;
	}
	if (node->right) {
		rightheight = height(node->right);
		rightheight += 1;
	}


	return rightheight>leftheight?rightheight:leftheight;
}

tree singleRotateWithLeft(tree node) {
	tree k2;
	k2 = node->left;
	node->left = k2->right;
	k2->right = node;

	return k2;
}
tree singleRotateWithRight(tree node) {
	tree k2;
	k2 = node->right;
	node->right = k2->left;
	k2->left = node;
	
	return k2;
}
tree doubleRotateWithLeft(tree node) {
	node->left = singleRotateWithRight(node->left);
	return singleRotateWithLeft(node);
}
tree doubleRotaetWithRight(tree node) {
	node->right = singleRotateWithLeft(node->right);
	return singleRotateWithRight(node);
}
