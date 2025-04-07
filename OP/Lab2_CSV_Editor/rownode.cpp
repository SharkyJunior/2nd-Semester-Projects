#include "rownode.h"
#include <stdlib.h>

RowNode* addNode(RowNode* head, char** data) {
    RowNode* cur = head;
    while (cur->next != NULL)
        cur = cur->next;

    cur->next = (RowNode*) malloc(sizeof(RowNode));
    cur->next->data = data;
    cur->next->next = NULL;

    return cur->next;
}

void removeNode(RowNode* head, RowNode* node) {
    RowNode* cur = head;
    while (cur->next != node)
        cur = cur->next;

    RowNode* connectTo = node->next;
    cur->next = connectTo;

    free(node->data);
    free(node);
}
