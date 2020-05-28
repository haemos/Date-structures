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

poly fill_leftnext(poly leftnext,int cofficients,int power) {
	poly fnext = (struct Polynomial*)malloc(sizeof(struct Polynomial));
	poly fnext_next = leftnext->next;
	poly flast_next = leftnext;
	fnext->coefficient = cofficients;
	fnext->power = power;

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
			else if (fnext->power == fnext_next->power) {
				fnext_next->coefficient = fnext->coefficient + fnext_next->coefficient;
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
poly free_next(poly leftnext, poly rightnext,poly other) {
	poly rnext = rightnext->next;
	poly lnext = leftnext->next;
	poly saveleft, saveright;
	while (rnext||lnext)
	{
		saveleft = lnext;
		saveright = rnext;
		if(lnext)lnext = lnext->next;
		if(rnext)rnext = rnext->next;
		if(saveright)free(saveright);
		if (saveleft)free(saveleft);
	}

	leftnext = other;
	return leftnext;
}

poly multipliacation(poly leftnext, poly rightnext) {
	poly lnext = leftnext->next;
	poly rnext = rightnext->next;
	poly other = (struct Polynomial*)malloc(sizeof(struct Polynomial));
	other->next = NULL;

	while (lnext)
	{
		while (rnext)
		{
			other->power = lnext->power + rnext->power;
			other->coefficient = lnext->coefficient * rnext->coefficient;
			other = fill_leftnext(other, other->coefficient, other->power);
			rnext = rnext->next;
		}
		lnext=lnext->next;
		rnext = rightnext->next;
	}

	leftnext = free_next(leftnext, rightnext, other);

	return leftnext;
}
void display(poly next) {
	poly next_next = next->next;
	int sign = 1;
	while (next_next) {
		if (sign == 1) {
			if (next_next->coefficient == 1) {
				printf("X^%d",next_next->power);
			}
			else{
				printf("%dX^%d", next_next->coefficient, next_next->power);
			}
			sign = 2;
			next_next = next_next->next;
			continue;
		}
		if (next_next->coefficient > 0) {
			printf("+");
		}

		if (next_next->coefficient == 1) {
			printf("X^%d", next_next->power);
		}
		else {
			printf("%dX^%d", next_next->coefficient, next_next->power);
		}
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
		printf("enter the cofficients\n");
		scanf_s("%d", &leftnext->coefficient);
		printf("enter the power\n");
		scanf_s("%d", &leftnext->power);
		head->leftnext = fill_leftnext(leftnext, leftnext->coefficient,leftnext->power);
	}
	printf("left has been finished\n");
	printf("please enter the numbers of terms in the second polynomial\n");
	scanf_s("%d", &times);
	for (int i = 0; i < times; i++) {
		printf("enter the cofficients\n");
		scanf_s("%d", &rightnext->coefficient);
		printf("enter the power\n");
		scanf_s("%d", &rightnext->power);
		head->rightnext = fill_leftnext(rightnext,rightnext->coefficient,rightnext->power);
	}
	printf("right has been finished\n");
	
	printf("The first polynomial\n");
	display(leftnext);
	printf("\n");
	printf("another polynomial\n");
	display(rightnext);
	leftnext =  multipliacation(leftnext, rightnext);
	printf("\n");
	display(leftnext);
	return 0;
}
