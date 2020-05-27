//Write a program to solve the multiplication of two polynomials and only can use one linked list.
#include <stdio.h>
#include <stdlib.h>

struct Polynomial {
	int coefficient;
	int power;
	struct Polynomial* next;
};

struct Polynomial_head{
	struct Polynomial* leftnext;
	struct Polynomial* rightnext;
};
typedef Polynomial* poly;

poly fill_leftnext(poly leftnext) {
	poly fnext = (struct Polynomial*)malloc(sizeof(struct Polynomial));
	poly fnext_next = leftnext->next;
	poly flast_next = leftnext;
	printf("enter the cofficients\n");
	scanf_s("%d", &fnext->coefficient);
	printf("enter the power\n");
	scanf_s("%d", &fnext->power);

	if (!fnext_next){
		fnext->next = leftnext->next;
		leftnext->next = fnext;
	}else {
		while (fnext_next){
			if (fnext->power>fnext_next->power)
			{
				fnext->next = fnext_next;
				flast_next->next = fnext;
				return leftnext;
			}
			if(!fnext_next->next){
				fnext->next = fnext_next->next;
				fnext_next->next = fnext;
				return leftnext;
			}
			fnext_next = fnext_next->next;
			flast_next = flast_next->next;
		}
	}
	return leftnext;
}

void display(poly next) {
	poly next_next = next->next;
	while (next_next) {
		if (next_next->coefficient > 0) {
			printf("+");
		}
		else {
			printf("-");
		}
		printf("%dX^%d", next_next->coefficient, next_next->power);
		next_next = next_next->next;
	}
}

int main(void) {
	int times;
	poly leftnext,rightnext;
	struct Polynomial_head* head = (struct Polynomial_head *)malloc(sizeof(struct Polynomial_head));
	leftnext = (struct Polynomial*)malloc(sizeof(struct Polynomial));
	rightnext = (struct Polynomial*)malloc(sizeof(struct Polynomial));
	head->leftnext = leftnext;
	head->rightnext = rightnext;
	leftnext->next = rightnext->next = NULL;
	
	printf("please enter the numbers of terms in the first polynomial\n");
	scanf_s("%d", &times);
	for (int i = 0; i < times; i++) {
		head->leftnext = fill_leftnext(leftnext);
	}
	printf("left has been finished\n");
	printf("please enter the numbers of terms in the second polynomial\n");
	scanf_s("%d", &times);
	for (int i = 0; i < times; i++) {
		head->rightnext = fill_leftnext(rightnext);
	}
	printf("right has been finished\n");
	
	printf("The first polynomial\n");
	display(leftnext);
	printf("\n");
	printf("another polynomial\n");

	display(rightnext);
	return 0;
}
