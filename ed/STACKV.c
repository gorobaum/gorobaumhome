#include <stdio.h>
#include <stdlib.h>
#include "ITEM.h"
#include "STACK.h"

typedef struct stack {
	Item *item;
	int TOPO;
}

void STACKdump(stack){
	int i;
	for( i = 0; i < stack.TOPO; i++) ITEMprintf(stack.item[i]);
}

int STACKempty(stack){
	return (stack.TOPO==0);
}

void STACKput(stack, item){
	stack.item[TOPO] = item;
	(stack.TOPO)++;
}

Item STACKget(stack){
	Item item;
	item = stack.item[TOPO];
	(stack.TOPO)--;
	return item;
}

stack STACKinit(int maxN){
	stack s;
	s.item = malloc(maxN*sizeof(item));
	s.TOPO = NULL;
	return s;
}
