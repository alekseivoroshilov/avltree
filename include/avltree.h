#ifndef _AVLTREE_H
#define _AVLTREE_H

struct Node;
struct Node* insert(struct Node* node, int key);
struct Node* deleteNode(struct Node* root, int key);
int contains(struct Node *root, int key);
int preOrder(int *array, struct Node *root, int counter);
void delete_tree(struct Node *tree);

extern struct Node *root;

#endif // _AVLTREE_H