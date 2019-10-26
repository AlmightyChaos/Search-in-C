#ifndef _RBTREE_H_
#define _RBTREE_H_
#define COLOR_RED 'r'
#define COLOR_BLACK 'b'
#define QUEUE_SIZE 1024
typedef enum{
	false = 0,
	true = 1
} bool;

struct node{
	char color;
	int key;
	char* data;
	struct node *left_child, *right_child, *parent;	
};

bool enqueue(struct node*);
bool dequeue(struct node**);
int insertNode(int, char*);
int deleteNode(int);
struct node* searchNode(int);
struct node** parentChildCheck(struct node*);
void leftRotation(struct node *);
void rightRotation(struct node *);
void insertFixUp(struct node*);
void deleteFixUp(struct node*);
void levelOrderTraversal();
#endif
