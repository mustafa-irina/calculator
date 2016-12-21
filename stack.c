#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "list.h"
#include "stack.h"

NodeStack* nodeInit (LongNumber * dataV) {
    NodeStack * p = (NodeStack*)malloc(sizeof(NodeStack));
    p -> value = dataV;
    p -> next = 0;
    p -> prev = 0;
    return p;
}

NodeStack * del_node_stack (NodeStack * node) {
	free(node);
	node = 0;
	return node;
}

Stack * initS() {
	Stack * ln = (Stack*)malloc(sizeof(Stack));
	ln -> last = 0;
	return ln;
}

void push (Stack * ln, LongNumber * dataV) {
   NodeStack* p = nodeInit(dataV);
   if (!ln -> last) {
	ln -> last = p;
        return;
   }
   ln -> last -> next = p;
   p -> prev = ln -> last;
   ln -> last = p;
}

LongNumber * pop (Stack * ln) {
	LongNumber * p = ln -> last -> value;
	if (ln -> last -> prev)
	{	
		ln -> last = ln -> last -> prev;
		del_node_stack(ln -> last -> next);
	}
	return p;

}

LongNumber * pick (Stack * ln) {
	LongNumber * p = ln -> last -> value;
	return p;
}
