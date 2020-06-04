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
tree deleteElement(tree node,int key);
int findMin(tree node);
int findMax(tree ndoe);

int main(void) {
	int key;
	tree node;
	node=createBinaryTree();
	displayTree(node);
	
	printf("\nplease enter you want to delete element\n");
	scanf_s("%d", &key);
	deleteElement(node,key);
	displayTree(node);
	return 0;
}


tree deleteElement(tree node,int key) {
	tree savenode;
	if (key > node->value)
		node->right=deleteElement(node->right, key);
	else if (key < node->value)
		node->left=deleteElement(node->left, key);
	else if (node->value==key)
		{
		if ((node->left && node->right)||(!node->left && node->right)) {
			node->value = findMin(node->right);
			node->right = deleteElement(node->right, findMin(node->right));
			}
		else if (node->left && !node->right) {
			node->value = findMax(node->left);
			node->left = deleteElement(node->left, findMax(node->left));
		}
		else {
			savenode = node;
			node = node->left;
			free(savenode);
			return node;
		}
		}
	return node;
}

int findMin(tree node) {
	int key ;
	key = node->value;
	while (node) {
		if (node->value < key)
			key = node->value;
		node = node->left;
	}
	return key;
}
int findMax(tree node) {
	int key;
	key = node->value;
	while (node) {
		if (node->value > key)
			key = node->value;
		node = node->right;
	}
	return key;
}

void displayTree(tree node) {
	if (node == NULL)
		return;
	displayTree(node->left);
	displayTree(node->right);
	printf("%d", node->value);
	
}
tree insert(tree node, int key) {
	tree newnode = NULL;
	if (!node) {
		node = (tree )malloc(sizeof(struct TreeNode));		
		node->value = key;
		node->left = node->right = NULL;
		return node;
	}
	else {
		if (key > node->value) {
			node->right = insert(node->right, key);
		}
		else if(key < node->value){
			node ->left = insert(node->left, key);
		}			
	}

	return node;
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
