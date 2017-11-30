#include "TreeLib.h"
#include <stdlib.h>


/*
 * Node functions
 */
Node::Node()
{
    this->left = this->right = NULL;
    this->value = 0;
}

Node::Node(value_type value)
{
    this->left = this->right = NULL;
    this->value = value;
}

Node::~Node()
{
    if(this->right)
        delete this->right;

    if(this->left)
        delete this->left;

    this->value = 0;
}

Node* Node::AddNodeRight(value_type value)
{
    if(!this)
    {
        printf("Pointer on Node in Node::AddNodeLeft = NULL");
        return NULL;
    }

    if(!this->right)
    {
        Node* newNode = new Node(value);
        this->right = newNode;
        return newNode;
    }
    else
    {
        this->right->AddNodeRight(value);
    }
}

Node* Node::AddNodeLeft(value_type value)
{
    if(!this)
    {
        printf("Pointer on Node in Node::AddNodeLeft = NULL");
        return NULL;
    }

    if(!this->left)
    {
        Node* newNode = new Node(value);
        this->left = newNode;
        return newNode;
    }
    else
    {
        this->left->AddNodeLeft(value);
    }
}

Node* Node::AddSort(value_type value)
{
    if(!this)
    {
        printf("Pointer on Node in Node::AddSort = NULL\n");
        return NULL;
    }

    if(this->value >= value)
    {
        if(!this->left)
        {
            Node* newNode = new Node(value);;
            this->left = newNode;
            return newNode;
        }
        this->left->AddSort(value);
    }
    else
    {
        if(!this->right)
        {
            Node* newNode = new Node(value);;
            this->right = newNode;
            return newNode;
        }
        this->right->AddSort(value);
    }
}

void Node::PrintTree()
{
    if(!this)
    {
        printf("Pointer on Node in Node::AddNodeLeft = NULL");
        return;
    }

    if(this->left)
    {
        this->left->PrintTree();
    }

    printf("%s \n" , this->value);

    if(this->right)
    {
        this->right->PrintTree();
    }

    return;
}

void Node::WriteNodeToFile(FILE* File)
{
    if(!this)
    {
        printf("Pointer on Node in Node::AddNodeLeft = NULL");
        return;
    }

    fputs(this->value , File);
    fputs("\n" , File);

    if(this->left)
    {
        fputs("{\n" , File);
        this->left->WriteNodeToFile(File);
        fputs("}\n" , File);
    }

    if(this->right)
    {
        fputs("{\n" , File);
        this->right->WriteNodeToFile(File);
        fputs("}\n" , File);
    }

    return;
}

/*
 * Tree functions
 */

Tree::Tree()
{
    this->head = NULL;
}

Tree::Tree(char* value)
{
    this->head = new Node();
    this->head->value = value;
}

Tree::~Tree()
{
    if(this->head)
        delete this->head;
}

void Tree::WriteBinTreeToFile(FILE* File)
{
    if(!File)
    {
        printf("Pointer on File in Tree::WriteBinTreeToFile + NULL\n");
        return;
    }

    fputs("{\n" , File);
    this->head->WriteNodeToFile(File);

    fputs("}\n-1\n" , File);

    return;
}
