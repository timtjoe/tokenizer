#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "headers/talloc.h"

// Node structure for linked list to track allocated pointers.
typedef struct PointerNode {
	// The allocated pointer.
	void* pointer;
	// Pointer to the next node in the list.
	struct PointerNode *next;
} PointerNode; // Define the structure for a node in the linked list.

// Head of the linked list of allocated pointers.
static PointerNode *allocatedPointers = NULL;

void *talloc(size_t size) {
	// Allocate memory of requested size.
	void *newPointer = malloc(size);
	if (newPointer == NULL) {
		fprintf(stderr, "Fatal error: Memory allocation failed in talloc. \n");
		texit(1);
	}

	// Create a new node to track the allocated pointer.
	PointerNode *newNode = malloc(sizeof(PointerNode));
	if (newNode == NULL)
	{
		// Free the previously allocated memory and exit.
		free(newPointer);
		fprintf(stderr, "Fatal error: Memory  allocation failed for talloc's internal list.\n");
		texit(1);
	}

	// Store allocated pointer in node.
	newNode->pointer = newPointer;
	// Insert at the head of the list.
	newNode->next = allocatedPointers;
	// Update head to new node.
	allocatedPointers = newNode;
	// Return allocated memory to caller.
	return newPointer;
};


void tfree() {
	// Current node we are freeing.
	PointerNode *current = allocatedPointers;
	// Temporary pointer to hold next node while we free current node.
	PointerNode *temp;

	while (current != NULL) {
		temp = current->next;
		//Free the allocated memory and the node itself.
		free(current->pointer);
		// Free the node tracking the pointer.
		free(current);
		// Move to next node.
		current = temp;
	}
	// All pointers are freed, set head to NULL.
	allocatedPointers = NULL;
}

void texit(int status) {
	tfree();
	exit(status);
}