#include <stdio.h>
#include "headers/tokenizer.h"
#include "headers/value.h"
#include "headers/linkedlist.h"
#include "headers/talloc.h"

int main() {
    Value *list = tokenize();
    displayTokens(list);
    tfree();
}
