#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "list.h"
#include "stack.h"

NodeLong* NLInit (int dataV) {
    NodeLong* p = (NodeLong*)malloc(sizeof(NodeLong));
    p -> value = dataV;
    p -> next = 0;
    p -> prev = 0;
    return p;
}

NodeLong * del_node (NodeLong * node) {
	free(node);
	node = 0;
	return node;
}
