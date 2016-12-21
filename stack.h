#pragma once

typedef struct NodeStack {
    LongNumber * value;
    struct NodeStack *next;
    struct NodeStack *prev;
} NodeStack;

typedef struct Stack {
    NodeStack *last;
} Stack;

NodeStack* nodeInit (LongNumber * dataV);

NodeStack * del_node_stack (NodeStack * node);

Stack * initS();

void push (Stack * ln, LongNumber * dataV);

LongNumber * pop (Stack * ln);

LongNumber * pick (Stack * ln);


