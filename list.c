#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "list.h"
#include "stack.h"

LongNumber * init() {
	LongNumber * ln = (LongNumber*)malloc(sizeof(LongNumber));
	ln -> first = 0;
	ln -> last = 0;
	ln -> sign = 0;
	return ln;
}

void addFront (LongNumber * ln, int dataV) {
   NodeLong* p = NLInit(dataV);
   if (!ln -> first) {
        ln -> first = p;
	ln -> last = p;
        return;
   }
   ln -> first -> prev = p;
   p -> next = ln -> first;
   ln -> first = p;
}

LongNumber * getList(char c) {
	LongNumber *ln = init();
	addFront(ln, c - 48);
	while ((c = fgetc(stdin)) != '\n') {
		if (c == '-') {
			ln -> sign = 1;
		} else {
			addFront(ln, c - 48);
		}
	}
	return ln;
}

LongNumber *num_del (LongNumber *ln)
 {
	NodeLong *curr = ln -> first;
	while (curr) {
		if (curr -> next) {
			curr = curr -> next;
			curr -> prev = del_node (curr -> prev);
		} else
			curr = del_node (curr);
	}
	free (ln);
	ln = 0;

	return ln;
 }

void printNum (LongNumber * Number) {
	NodeLong * p = Number -> last;
	if (Number -> sign != 0) {
		printf("%c", '-');
	}
	while (p) {
		printf("%d", p -> value);
		p = p -> prev;
	}
	puts("");
}

NodeLong * addLast (LongNumber * ln, int dataV) {
	NodeLong * p = NLInit(dataV);
	if (!ln -> first) {
		ln -> first = p;
		ln -> last = p;
		return p;
	}
	ln -> last -> next = p;
   	p -> prev = ln -> last;
   	ln -> last = p;
	return p;
}

void remove_last (LongNumber * ln) {
	ln -> last = ln -> last -> prev;
	del_node(ln -> last -> next);
	ln -> last -> next = 0;
}

int list_len (LongNumber * ln) {
	int len = 0;
	NodeLong * curr = ln -> first;
	while (curr) {
		len++;
		curr = curr -> next;
	}
	return len;
}

int compareLN (LongNumber * ln1, LongNumber * ln2) {
	int delta = list_len (ln1) - list_len (ln2) ;
	if (delta)
		return delta;
	NodeLong * curr1 = ln1 -> last;
	NodeLong * curr2 = ln2 -> last;
	while (curr1 && curr2) {
		if ((curr1 -> value - curr2 -> value) && !delta)
		{
			delta = curr1 -> value - curr2 -> value;
			return delta ;
		}
		curr1 = curr1 -> prev;
		curr2 = curr2 -> prev;
	}


	return delta ;
 }


LongNumber * sum_num(LongNumber * ln1, LongNumber * ln2) {
	NodeLong * curr1 = ln1 -> first;
	NodeLong * curr2 = ln2 -> first;
	int add = 0;
	while (curr2) {
		curr1 -> value += add;
		curr1 -> value += curr2 -> value;
		add = curr1 -> value /10;
		curr1 -> value = curr1 -> value % 10;
		curr1 = curr1 -> next;
		curr2 = curr2 -> next;
	}
	if (add) {
		if (!curr1) {
			addLast(ln1, add);
		}
                else {
			while ((add)&&(curr1)) {
				curr1 -> value += add;
				add = curr1 -> value /10;
				curr1 -> value = curr1 -> value % 10;
				curr1 = curr1 -> next;
			}
			if (!curr1) {
				addLast(ln1, add);
			}
		}
	}
	if (ln1 -> last -> value == 0) {
		remove_last(ln1);
	}
	return ln1;
}

LongNumber * sub_num(LongNumber * ln1, LongNumber * ln2) {
	NodeLong * curr1 = ln1 -> first;
	NodeLong * curr2 = ln2 -> first;
	int add = 0;
	while (curr2) {
		curr1 -> value += add;
		add = 0;
		curr1 -> value -= curr2 -> value;
		if (curr1 -> value < 0) {
			add = -1;
			curr1 -> value += 10;
		}
	curr1 = curr1 -> next;
	curr2 = curr2 -> next;
	}
	while (add && curr1) {
		curr1 -> value += add;
		add = 0;
		if (curr1 -> value < 0) {
			add = -1;
			curr1 -> value += 10;
		}
		curr1 = curr1 -> next;
	}
	while ((!ln1 -> last -> value) && (ln1 -> last != ln1 -> first)) {
		remove_last(ln1);
	}
	return ln1;
}

LongNumber * mult_num(LongNumber * ln1, LongNumber *ln2) {
	LongNumber * res = init();
	NodeLong * curr2 = ln2 -> first;
	NodeLong * curr_res = res -> first;
	res -> sign = ln1 -> sign;
	while (curr2)
	{
		if (!curr_res) {
			curr_res = addLast(res, 0);
		}
		NodeLong *curr_st = curr_res;
		NodeLong *curr1 = ln1 -> first;

		while (curr1)
		{
			int d = curr2 -> value * curr1 -> value;

			if (!curr_st){
				curr_st = addLast(res, 0);
			}
			curr_st -> value += d;



			if (curr_st -> value / 10)
			{
				if (!curr_st -> next) {
					curr_st -> next = addLast(res, 0);
				}
				curr_st -> next -> value += curr_st -> value / 10;
			}
			curr_st -> value %= 10;
			curr1 = curr1 -> next;
			curr_st = curr_st -> next;

		}
		curr_res = curr_res -> next;
		curr2 = curr2 -> next;
	}

	if (res -> last -> value > 9)
	{
		addLast(res , res -> last -> value / 10);
		res -> last -> prev -> value %= 10;
	}
	curr_res = res -> last;
	while (!curr_res -> value && res -> first != res -> last)
	{
		curr_res = curr_res -> prev;
		remove_last(res);
	}
	return res;
 }

LongNumber *int_to_long(int n){
	LongNumber *ln = init();
	addLast(ln, n % 10);
	n /= 10;
	while (n > 0){
		addLast(ln, n % 10) ;
		n /= 10;
	}
	return ln;
 }

LongNumber *mult_int (LongNumber *ln1 , int n){
	LongNumber *ln2 = int_to_long(n);
	LongNumber *res = mult_num (ln1, ln2);
	ln2 = num_del(ln2);
	return res ;
 }

int getqout_num (LongNumber *ln1 , LongNumber *ln2){
	int qout;
	for (qout = 0; qout < 10 ; qout ++ )
	{
		if ( ( compareLN ( mult_int ( ln2 , qout ) , ln1 ) <= 0 ) && ( compareLN ( mult_int ( ln2 , qout + 1 ) , ln1 ) > 0 ) )
			return qout ;
	}
	return 1 ;
}

 LongNumber *div_num ( LongNumber *ln1 , LongNumber *ln2 ) {
	LongNumber *res = init ( ) ;
	if ( compareLN ( ln1 , ln2 ) < 0 )
	{
		addLast (res , 0) ;
		return res ;
	}

	LongNumber *subRes = init ( ) ;
	addFront ( subRes , ln1 -> last -> value) ;

	NodeLong *ln1_curr = ln1 -> last ;

	while ( compareLN ( subRes , ln2 ) < 0 ){
		ln1_curr = ln1_curr -> prev ;
		addFront ( subRes , ln1_curr -> value) ;
	}
	do	{
		int qout = getqout_num ( subRes , ln2 ) ;
		addFront ( res , qout ) ;

		subRes = sub_num ( subRes , mult_int ( ln2 , qout ) ) ;
		ln1_curr = ln1_curr -> prev ;
		if ( ln1_curr ){
			addFront ( subRes , ln1_curr -> value) ;

		}
	} while ( ln1_curr ) ;

	subRes = num_del ( subRes ) ;
	return res ;
 }
