#ifndef TREE_TREELIB_H
#define TREE_TREELIB_H

#include <stdio.h>


typedef char* value_type;

class Node
{
public:
    Node* right;
    Node* left;
    value_type value;

    Node();
    Node(value_type);
    ~Node();

    Node* AddNodeRight(value_type);
    Node* AddNodeLeft(value_type);

    Node* AddSort(value_type);

    void PrintTree();
    void WriteNodeToFile(FILE*);
};

class Tree
{
public:
    Node* head;

    Tree();
    Tree(char *);
    ~Tree();

    void WriteBinTreeToFile(FILE*);
};

#endif //TREE_TREELIB_H
