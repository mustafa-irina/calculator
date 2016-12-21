#pragma once

typedef struct LongNumber {
    NodeLong *first;
    NodeLong *last;
    int sign;
} LongNumber;

LongNumber * init();

void addFront (LongNumber * ln, int dataV);

LongNumber * getList(char c);

LongNumber *num_del (LongNumber *ln);

void printNum (LongNumber * Number);

NodeLong * addLast (LongNumber * ln, int dataV);

void remove_last (LongNumber * ln);

int list_len (LongNumber * ln);

int compareLN (LongNumber * ln1, LongNumber * ln2);

LongNumber * sum_num(LongNumber * ln1, LongNumber * ln2);

LongNumber * sub_num(LongNumber * ln1, LongNumber * ln2);

LongNumber * mult_num(LongNumber * ln1, LongNumber *ln2);

LongNumber *int_to_long(int n);

LongNumber *mult_int (LongNumber *ln1 , int n);

int getqout_num (LongNumber *ln1 , LongNumber *ln2);

LongNumber *div_num ( LongNumber *ln1 , LongNumber *ln2 );

