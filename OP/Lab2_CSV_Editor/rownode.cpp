#include "rownode.h"
#include <stdlib.h>

RowNode* addNode(RowNode* tail, char** data) {
    tail->next = (RowNode*) malloc(sizeof(RowNode));
    tail->next->data = data;
    tail->next->next = NULL;

    return tail->next;
}

void removeNode(RowNode* head, RowNode* node) {
    RowNode* cur = head;
    while (cur->next != node)
        cur = cur->next;

    RowNode* connectTo = node->next;
    cur->next = connectTo;

    free(node);
}
