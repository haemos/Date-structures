#include <stdio.h>
#include <malloc.h>
#define capacity 100


struct PriorityQueue
{
	int size ;
	int queue[capacity]; ;
};

struct PriorityQueue* insert(struct PriorityQueue* Queue,int value ) {
	int min, lastValue,i;
	min = Queue->queue[0];
	lastValue = Queue->queue[Queue->size];

	if (Queue->size == 0) {
		Queue->queue[++Queue->size] = value;
	}
	else {
		for ( i = ++Queue->size; Queue->queue[i / 2]>value;i/=2) {		//上潜
			Queue->queue[i] = Queue->queue[i / 2];
		}
		Queue->queue[i] = value;
	}
	return Queue;
}
void displayQueue(struct PriorityQueue *Queue) {
	for (int i = 1; i <= Queue->size; i++) {
		printf("%d     ", Queue->queue[i]);
	}
	printf("\n");
}

void DeleteMin(struct PriorityQueue *Queue) {
	int lastValue=Queue->queue[Queue->size--];
	int i,child;

	for (i = 1; 2*i <= Queue->size; i=child) {
		child = 2 * i;
		if (Queue->queue[child + 1] != 0 && (Queue->queue[child + 1] < Queue->queue[child]))	 //预防右边无结点同时确认方向下潜
			child++;;
				
		
		if (lastValue > Queue->queue[child]) {
			Queue->queue[i] = Queue->queue[child];		//避免在最后一层中将孩子中大的换上来了
		}
		else {
			break;		//LastValue < 和他属于一个父亲的结点 则可直接走下面赋值给父亲。
		}
		
	}
	Queue->queue[i] = lastValue;

	return;
}

int main(void) {
	int value;
	struct PriorityQueue *Queue;
	Queue = (struct PriorityQueue *)malloc(sizeof(struct PriorityQueue));
	Queue->size = 0;
	Queue->queue[0] = 0;

	for (int i = 0; i < 10; i++) {
		Queue->queue[i + 1] = 0;
		scanf_s("%d", &value);
		insert(Queue, value);
		displayQueue(Queue);
	}

	DeleteMin(Queue);
	displayQueue(Queue);
	return 0;
}
