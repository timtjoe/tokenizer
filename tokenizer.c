#include <stdio.h> //for printf, scanf, getchar, etc.
#include <stdlib.h> //for malloc, free, etc.
#include <string.h> //for strlen, strcpy, etc.
#include <ctype.h> // for isdigit, isalpha, isspace, etc.
#include "headers/tokenizer.h"
#include "headers/talloc.h" // for talloc and tfree
#include "headers/linkedlist.h" // for linked list functions

Value *tokenize() {
	Value *list = makeNull();
	int charRead;

	// Loop to read all characters until EOF
	while ((charRead = getchar()) != EOF) {

		// Skip whitespace and comments
		if (isspace(charRead)) {
			continue;
		}
		else if (charRead == ';') {
			// A comment lasts until the end of the line
			while ((charRead = getchar()) != EOF && charRead != '\n');
			if (charRead == EOF) {
				break;
			}
			continue;
		}

		Value *token = NULL;
			// token = (Value *)talloc(sizeof(Value));

		// Handle different token types
		if (charRead == '(') {
			token = (Value *)talloc(sizeof(Value));
			token->type = OPEN_TYPE;
		}
		else if (charRead == ')') {
			token->type = CLOSE_TYPE;
		}
		else if (charRead == '#') {
			char nextChar = getchar();
			token = (Value *)talloc(sizeof(Value));
			if (nextChar == 't') {
				token->type = BOOL_TYPE;
				token->i = 1; // true
			}
			else if (nextChar == 'f') {
				token->type = BOOL_TYPE;
				token->i = 0; // false
			}
			else {
				// Put the character back and treat as a symbol
				ungetc(nextChar, stdin);
			}
		}

		// Check if a token was already created (e.g., parens, booleans)
		if (token) {
			list = cons(token, list);
			continue;
		}

		//Handle multi-character tokens (numbers, symbols, strings)
		char buffer[256];
		int index = 0;
		buffer[index++] = charRead;

		if (isdigit(charRead) || (charRead == '-' && isdigit(getchar()))) {
			ungetc(buffer[index - 1], stdin);
			index = 0;
			// A number
			while ((charRead = getchar()) != EOF && (isdigit(charRead) || charRead == '.')) {
				buffer[index++] = charRead;
			}
			ungetc(charRead, stdin);
			buffer[index] = '\0';

			token = (Value *)talloc(sizeof(Value));
			if (strchr(buffer, '.') != NULL) {
				token->type = DOUBLE_TYPE;
				token->d = atof(buffer);
			}
			else {
				token->type = INT_TYPE;
				token->i = atoi(buffer);
			}
		}
		else if (charRead == '"') {
			// A string
			index = 0;
			while ((charRead = getchar()) != EOF && charRead != '"' && index < 255) {
				if (charRead == '\\') {
					buffer[index++] = charRead;
					charRead = getchar();
				}
				buffer[index++] = charRead;
			}
			buffer[index] = '\0';

			token = (Value *)talloc(sizeof(Value));
			token->type = STR_TYPE;
			token->s = (char *)talloc(strlen(buffer) + 1);
			strcpy(token->s, buffer);
		}
		else {
			// A symbol
			while ((charRead = getchar()) != EOF && !isspace(charRead) && charRead != '(' && charRead != ')') {
				buffer[index++] = charRead;
			}
			ungetc(charRead, stdin);
			buffer[index] = '\0';

			token = (Value*)talloc(sizeof(Value));
			token->type = SYMBOL_TYPE;
			token->s = (char*)talloc(strlen(buffer) + 1);
			strcpy(token->s, buffer);
		}

		if (token) {
			list = cons(token, list);
		}
	}

	// Reverse the list to maintain original order
	list = reverse(list);
	return list;
}

void displayTokens(Value *list) {
	// Display the tokens in the list
	display(list);
}
