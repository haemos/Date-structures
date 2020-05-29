#include <stdio.h>
#include <stdlib.h>

struct Stack
{
	char element;
	struct Stack* next;
};
typedef struct Stack* stack;
int k=0;
stack push(stack head, char c) {
	stack point = (stack)malloc(sizeof(struct Stack));
	point->element = c;
	point->next = head->next;
	head->next = point;
	k+=1;
	return head;
}

stack pop(stack head) {
	stack point = head->next;

	head->next = point->next;
	if(point->element!='('&&point->element!=')')printf("%c", point->element);
	k-=1;
	free(point);
	return head;
}
stack check_stack(stack head){
	int sign,flag;
	stack point = head->next;
	stack point_next=point->next;
	sign=(int)point->element;
	flag=(int)point_next->element;
	
	if (sign == 43 || sign == 45) {
		sign = 1;
	}
	else if (sign == 42 || sign == 47) {
		sign = 2;
	}
	
	if (flag == 43 || flag == 45) {
		flag = 1;
	}
	else if (flag == 42 || flag == 47) {
		flag = 2;
	}
	
	if(flag == sign)pop(head);
	return head;
}

stack transform(stack head, char a) {
	int sign = (int)a;
	int flag;

	stack next=head->next;
	
	if (sign == 43 || sign == 45) {
		sign = 1;
	}
	else if (sign == 42 || sign == 47) {
		sign = 2;
	}

	if (sign >= 48 && sign <= 57) {
		printf("%c", a);
	}
	else {
		if (head->next == NULL) {
			head = push(head, a);
			return head;
		}
		else {
			flag = (int)(next->element);		//+43 -45 40( 41) 42* 47/
			if (sign==2&&(flag==43||flag==45)) {
				push(head,a);
				return head;
			}else if(sign==40||flag==40){
				push(head,a);
				return head;	
			}else if(sign==41){
				while(next->element!='('){
					next=next->next;
					head = pop(head);
				}
				head = pop(head);
				return head;
			}else if(sign==2||sign==1){
				head = pop(head	);
				head = push(head, a);
				if(k>=2){
					head = check_stack(head);
				}
				return head;
			}

		}
	}
	return head;
}

int main(void) {
	char string[40];
	char c;
	int i = 0;

	stack head_stack = (stack)malloc(sizeof(struct Stack));
	head_stack->next = NULL;

	printf("enter the expression\n");
	scanf("%s",string);

	while ((c = string[i]) != '\0') {
		head_stack = transform(head_stack, c);
		i++;
	}
	while (head_stack->next)
	{
		pop(head_stack);
	}


	return 0;
}
