#pragma once

typedef struct NodeLong {
    int value;
    struct NodeLong *next;
    struct NodeLong *prev;
    } NodeLong;

NodeLong* NLInit (int dataV);

NodeLong * del_node (NodeLong * node);
