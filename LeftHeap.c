#include <stdio.h>
#include<stdlib.h>

struct LeftHeap {
	int element;
	struct LeftHeap* left;
	struct LeftHeap* right;
	int Npl;			
};
typedef struct  LeftHeap* Lheap;


// 参考https://www.cnblogs.com/pacoson/p/5142330.html


Lheap swap(Lheap H1) {
	Lheap H2;
	H2 = H1->left;
	H1->left = H1->right;
	H1->right = H2;
	return H1;
}

Lheap merge1(Lheap H1, Lheap H2);

Lheap merge(Lheap H1,Lheap H2) {		//合并分成两函数方便交换后进行合并。
	if (H1 == NULL)return H2;
	if (H2 == NULL)return H1;
	if (H1->element < H2->element) {
		return merge1(H1, H2);					
	}
	else {
		return merge1(H2, H1);		//使根节点最小
	}
}

Lheap merge1(Lheap H1, Lheap H2) {
	if (H1->left == NULL)
		H1->left = H2;
	else {
		H1->right = merge(H1->right, H2);   //可以进行分离右节点进行合并
		if (H1->left->Npl < H1->right->Npl)
		{
			swap(H1);
		}
		H1->Npl = H1->right->Npl + 1;		//当右结点已经有了时 将绝对路径长加一。
	}
	return H1;
}

Lheap Insert(Lheap H, int element) {
	Lheap h2 = (Lheap)malloc(sizeof(struct LeftHeap));
	if (!h2)
		printf("Out of space!\n");
	else
	{
		h2->element = element;
		h2->left = h2->right = NULL;
		h2->Npl = 0;	
		H = merge(H, h2);		
	}
	return H;
}

void display(Lheap H) {
	if (H->left)display(H->left);
	printf("%d(%d)\t", H->element, H->Npl);				//先序排列
	if (H->right)display(H->right);
	
}

int main(void) {
	int a;
	Lheap H;

	H = (Lheap)malloc(sizeof(struct LeftHeap));
	H->left = H->right = NULL;
	H->Npl = 0;
	
	for (int i=0; i < 10; i++) {
		scanf_s("%d", &a);
		if (i == 0) {
			H->element = a;
		}
		else
		{
			H = Insert(H, a);
			display(H);
		}
	}
	return 0;
}
