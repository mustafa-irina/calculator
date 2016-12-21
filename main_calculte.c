#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "list.h"
#include "stack.h"


void man_oper (char oper, LongNumber * ln1, LongNumber * ln2, Stack * s) {
	int z = ln1 -> sign * 2 + ln2 -> sign;
	LongNumber * ln0 = init();
	switch(oper) {
		case '+': 
			switch(z) {
				case 0:
				case 3:
					if (compareLN(ln1, ln2) >= 0) {
						push(s, sum_num(ln1, ln2));
					} else {
						push(s, sum_num(ln2, ln1));
						//printNum(ln2);
					} //puts("1");
					break;
				case 1:
				case 2:
					if (compareLN(ln1, ln2) >= 0) {
						push(s, sub_num(ln1, ln2));
					} else {
						push(s, sub_num(ln2, ln1));
						//printNum(ln2);
					}//puts("2");
					break;
				default:
					break; 
			}
		break;
		case '-':
			switch(z)
			    {
				case 0:
				    if (compareLN(ln1, ln2) >= 0){
				        push(s, sub_num(ln1, ln2));
				    } else {
				        ln2->sign = 1;
				        push(s, sub_num(ln2, ln1));
				    }
				    break;
				case 1:
				    ln2 -> sign = 0;
				    if (compareLN(ln1, ln2) >= 0) {
				        push(s, sum_num(ln1, ln2));
				    } else {
				        push(s, sum_num(ln2, ln1));
				    }
				    break;
				case 2:
				    if (compareLN(ln1, ln2) >= 0) {
				        push(s, sum_num(ln1, ln2));
				    } else {
				        ln2 -> sign = 1;
				        push(s, sum_num(ln2, ln1));
				    }
				    break;
				case 3:
				    ln2 -> sign = 0;
				    if (compareLN(ln1, ln2) >= 0){
				        push(s, sub_num(ln1, ln2));
				    } else {
				        push(s, sub_num(ln2, ln1));
				    }
				    break;
				default:
				    break;
			    }
		break;
		case '*':
			switch(z) {
				case 0:
				case 3:
					if (compareLN(ln1, ln2) >= 0) {
						ln1 -> sign = 0;
						push(s, mult_num(ln1, ln2));
					} else {
						ln2 -> sign = 0;
						push(s, mult_num(ln2, ln1));
					}
					break;
				case 1:
				case 2:
					if (compareLN(ln1, ln2) >= 0) {
						ln1 -> sign = 1;
						push(s, mult_num(ln1, ln2));
					} else {
						ln2 -> sign = 1;
						push(s, mult_num(ln2, ln1));
					}
					break;
				default:
					break;
			}
			break;
		case '/':
			if (list_len(ln2) == 1 && ln2 -> first -> value == 0){
				printf("division by zero\n");
				break;
			}
			switch(z){
				case 0:
				case 3:
					push(s, div_num(ln1, ln2));
					break;
				case 1:
				case 2:
					ln0 = div_num(ln1, ln2);
					if (compareLN(ln1, ln2) >= 0) {
						ln0 -> sign = 1;
						push(s, ln0);
					} else {
						push(s, ln0);
					}
					break;
				default:
					break;
			}
			break;
		default: 
			printf("incorrect");
			break;
	}
}


int main()
{
	LongNumber * Number1 = 0;
	LongNumber * Number2 = 0;
	char c = '\0';
	//men_oper(c, Number1, Number2);
	//sub_num(Number1, Number2);
	//sub_num(Number1, Number2);
	//printNum(Number1);
	
	Stack * stack_main = initS();

	while (1) {
		c = fgetc(stdin);
		switch (c) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				Number1 = getList(c);
				push(stack_main, Number1);
				break;
			case '=':
				if (pick(stack_main))
					printNum (pick(stack_main)) ;
				break ;
			case ' ' :
			case '\n':
				break;
			default:
				if ( c == '-' ){
					c = fgetc (stdin);
					if (c == '\n' || c == ' ' )
						c = '-';
					else{
						Number1 = getList(c) ;
						Number1 -> sign = 1;
						push (stack_main, Number1) ;
						continue;
					}
				}
				Number2 = pop(stack_main) ;
				Number1 = pop(stack_main) ;
				if (!Number1 || !Number2)
				{
					if (Number2)
						push (stack_main, Number2 ) ;
					fprintf(stderr, "empty stack\n");
					continue;
				}

				man_oper (c, Number1, Number2, stack_main);
		break ;	
		}
		
	}
		
	return 0;
}
