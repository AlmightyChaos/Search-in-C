#include <stdio.h>
#include <stdlib.h>
#define COLOR_RED 'r'
#define COLOR_BLACK 'b'
#define QUEUE_SIZE 10

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

struct node nil={
	.color = COLOR_BLACK,
	.left_child = NULL,
	.right_child = NULL,
	.parent = NULL
};

struct node *root = NULL;
struct node *queue[QUEUE_SIZE];
int front = QUEUE_SIZE - 1;
int rear = QUEUE_SIZE - 1;
bool full = false;
bool enqueue(struct node*);
bool dequeue(struct node**);

int insertNode(int, char*);
int deleteNode();
void leftRotation(struct node *);
void rightRotation(struct node *);
void insertFixUp();
void deleteFixUp();
void levelOrderTraversal();

int main(){
	insertNode(5, "faker");
	insertNode(10, "nick");
	levelOrderTraversal();
	return 0;
}

int insertNode(int key, char* data){
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	struct node* current = NULL;
	struct node* next_node = NULL;
	if (root == NULL)
		root = new_node;
	else{
		next_node = root;
		while(next_node != &nil){
			current = next_node;
			if (key != current->key){
				next_node = key > current->key ? current->right_child : current->left_child;
			}
			else{
				printf("The inserted key already exists!\n");
				return 1;
			}
		}
		new_node->parent = current;
		if (key > current->key) 
			current->right_child = new_node;
		else
			current->left_child = new_node;
	}
	new_node->key = key;
	new_node->data = data;
	new_node->left_child = &nil;
	new_node->right_child = &nil;
	nil.parent = new_node;
	return 0;
}

void leftRotation(struct node *current){
	struct node* right_child = current->right_child;
	struct node* right_left_child = right_child->left_child;
	struct node* parent = current->parent;
	struct node* pars_child = NULL;
	if (current != root){
		right_child->parent = parent;
		pars_child = parent->left_child == current?parent->left_child:parent->right_child;
		pars_child = right_child;
	}
	else {
		right_child->parent = NULL;
		root = right_child;
	}
	right_left_child->parent = current;
	right_left_child = current;
	parent = right_child;
	right_child = right_left_child;
}

void rightRotation(struct node *current){

}

void levelOrderTraversal(){
	struct node *current = NULL;
	enqueue(root);
	while(dequeue(&current)){
		printf("(%d):%s\n", current->key, current->data);
		if (current->left_child != &nil)
			enqueue(current->left_child);
		if (current->right_child != &nil)
			enqueue(current->right_child);
	}
}
bool enqueue(struct node* value) {
	if (full)
		return false;
	else{
		if (++rear == QUEUE_SIZE)
			rear = 0;
		queue[rear] = value;
		if (front == rear)
			full = true;
		return true;
	}
}
bool dequeue(struct node** value) {
	if (front == rear && !full)
		return false;
	else{
		if (++front == QUEUE_SIZE)
			front = 0;
		*value = queue[front];
		full = false;
		return true;
	}
}
