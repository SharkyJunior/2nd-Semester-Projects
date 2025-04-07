#ifndef ROWNODE_H
#define ROWNODE_H

#include <stdlib.h>

struct RowNode {
    RowNode* next;
    char** data;
};

RowNode* addNode(RowNode* head, char** data);
void removeNode(RowNode* head, RowNode* node);


#endif // ROWNODE_H
