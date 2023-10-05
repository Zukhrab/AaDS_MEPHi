//
//  tree.h
//  BlackRedTree
//
//  Created by Зухраб Асаханов on 15.09.2023.
//

#ifndef tree_h
#define tree_h

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int key;
    char* info;
    struct node *par;
    struct node *left;
    struct node *right;
    int color;
} Node;

int getInt(int* a);
char* getStr(void);

Node* newNode(int key, char* info, Node* par);
int isLeaf(Node *n);
Node* leftRotate(Node* node);
Node* rightRotate(Node* node);
void checkNode(Node* node);
Node* insertNode(int key, char* sstr, Node** root);
void checkForCase2(Node* toDelete, int delete, int fromDirection, Node** root);
void deleteNode(int key, Node** root);
void printInorder(Node* root, int level);
void checkBlack(Node* temp, int c);
void printMaxElement(Node* root);
Node* findNode(int key, Node** root);

#endif /* tree_h */
