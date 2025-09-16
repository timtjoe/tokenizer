#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "headers/linkedlist.h"
#include "headers/talloc.h"

Value *makeNull() {
	// Create a new NULL_TYPE value node.
	Value *nullNode = (Value *)talloc(sizeof(Value));
	// Ensure memory allocation was successful.
	assert(nullNode != NULL);
	// Set the type to NULL_TYPE.
	nullNode->type = NULL_TYPE;
	return nullNode;
}

Value *cons(Value *car, Value *cdr) {
	// Create a new CONS_TYPE value node.
	assert(cdr->type == NULL_TYPE || cdr->type == CONS_TYPE);
	// Ensure memory allocation was successful.
	Value *consNode = (Value *)talloc(sizeof(Value));
	assert(consNode != NULL);
	// Set the type to CONS_TYPE and assign car and cdr.
	consNode->type = CONS_TYPE;
	consNode->c.car = car;
	consNode->c.cdr = cdr;
	return consNode;
}

void display(Value *list) {
	// Iterate through the list and print each element based on its type.
	Value *current = list;

	while (current->type != NULL_TYPE) {
		Value* token = current->c.car;

		switch (token->type) {
			case OPEN_TYPE:
				printf("(:open\n");
				break;
			case CLOSE_TYPE:
				printf(":close)\n");
				break;	
			case SYMBOL_TYPE:
				printf(":%s:symbol\n", token->s);
				break;
			case STR_TYPE:
				printf("\"%s\":string\n", token->s);
				break;
			case INT_TYPE:
				printf("%d:integer\n", token->i);
				break;
			case DOUBLE_TYPE:
				printf("%f:double\n", token->d);
				break;
			case PTR_TYPE:
				printf("%p:pointer\n", token->p);
				break;
			case BOOL_TYPE:
				if (token->i) {
					printf("#t:boolean\n");
				} else {
					printf("#f:boolean\n");
				}
				break;
			case CONS_TYPE:
				printf("Error: Unexpected CONS_TYPE in display.\n");
				break;
			default:
				printf("Error: Unknown type in display.\n");
				break;
		}
		// Move to the next node in the list.
		current = current->c.cdr;
	}
}

Value *reverse(Value* list) {
	// Create a new list that is the reverse of the one that is passed in.
	Value *reversedList = makeNull();
	Value *current = list;
	while (current->type != NULL_TYPE) {
		// Prepend current car to the new reversed list.
		reversedList = cons(current->c.car, reversedList);
		current = current->c.cdr;
	}
	return reversedList;
}

Value *car(Value* list) {
	// Get the car value of the list.
	assert(list != NULL);
	assert(list->type == CONS_TYPE);
	return list->c.car;
}

Value *cdr(Value* list) {
	// Get the cdr value of the list.
	assert(list != NULL);
	assert(list->type == CONS_TYPE);
	return list->c.cdr;
}

bool isNull(Value* value) {
	// Check if the value is of NULL_TYPE.
	assert(value != NULL);
	return value->type == NULL_TYPE;
}

int length(Value *value) {
	// Measure length of the list.
	assert(value != NULL);
	int len = 0;
	Value *current = value;
	while (current->type != NULL_TYPE) {
		// Increment length for each CONS_TYPE node.
		len++;
		current = current->c.cdr;
	}
	return len;
}

