#include <stdio.h>
#define MaxSize 20

int Insert(int heap[], int a,int size) {
	int lastValue = heap[size];
	int i;

	if (size == 0)
		heap[++size] = a;
	else {
		for (i = ++size; (heap[i / 2] < a) && i/2 > 0; i /= 2) {		//上潜
			heap[i] = heap[i / 2];
		}
		heap[i ] = a;
	}
	return size;
}

void display(int heap[], int size) {
	int i;
	for(i = 1; i <= size; i++)
		printf("%d\t", heap[i]);
}

void swap(int* a, int* b) {
	int c;
	c = *a;
	*a = *b;
	*b = c;
}

void percdown(int heap[], int i, int size) {
	int child, tmp, leftChild;
	leftChild = 2 * i;
	for (tmp = heap[i]; leftChild < size; i = child) {

		child = leftChild;
		if (child!=size&&heap[child] < heap[child + 1])
			child++;										//下滤
		if (tmp < heap[child])
			heap[i] = heap[child];
		else
			break;
		leftChild = 2 * child;
	}
	heap[i] = tmp;
}

void heapSort(int heap[], int size) {
	for (int i = size-1; i > 0; i--) {
		if (heap[1] > heap[size]) {
			swap(&heap[1], &heap[size--]);
			percdown(heap, 1, size);
			display(heap, size);
			printf("\n");

		}
	}
}
	
int main(void) {
	int binHeap[MaxSize] = { 0 };
	int a,size;
	size = 0;
	do{
 		scanf_s("%d", &a);
		size = Insert(binHeap, a,size);
	} while (getchar()!= '\n');

	display(binHeap, size);
	printf("\n");
	heapSort(binHeap, size);
	display(binHeap, size);
	printf("\n");
	

	return 0;
}
