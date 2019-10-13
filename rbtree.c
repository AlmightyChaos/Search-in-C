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

struct node *root = &nil;
struct node *queue[QUEUE_SIZE];
int front = QUEUE_SIZE - 1;
int rear = QUEUE_SIZE - 1;
bool full = false;
bool enqueue(struct node*);
bool dequeue(struct node**);

int insertNode(int, char*);
int deleteNode(int);
struct node* searchNode(int);
struct node** parentChildCheck(struct node*);
void leftRotation(struct node *);
void rightRotation(struct node *);
void insertFixUp();
void deleteFixUp();
void levelOrderTraversal();

int main(){
	insertNode(5, "faker");
	insertNode(10, "nick");
	insertNode(2, "fuick");
	insertNode(8, "fffnick");
	insertNode(12, "nickfdf");
	insertNode(4, "nic2223k");
	insertNode(1, "ni34ck");
	insertNode(13, "ytyty77");
	leftRotation(root);
	deleteNode(10);
	levelOrderTraversal();
	//printf("%s\n", searchNode(10)->data);
	//printf("%ld\n", (root->right_child));
	//printf("%ld\n", *(struct node **)((void*)root+24));
	//*(struct node**)((void*)root+24) = root;
	printf("%ld\n", *parentChildCheck(root));
	printf("%ld\n", root);
	return 0;
}
struct node** parentChildCheck(struct node* current){
	struct node* parent = NULL;
	if (current == root)
		return &root;
	parent = current->parent;
	if (parent->left_child == current)
		return &(parent->left_child);
	else
		return &(parent->right_child);
}

int insertNode(int key, char* data){
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	struct node* current = NULL;
	struct node* next_node = NULL;
	if (root == &nil)
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
	new_node->color = COLOR_RED;
	new_node->left_child = &nil;
	new_node->right_child = &nil;
	return 0;
}

int deleteNode(int key){
	struct node* del_node = searchNode(key);
	struct node* left_child = del_node->left_child;
	struct node* right_child = del_node->right_child;

	if (del_node != NULL){
		if (left_child != &nil && right_child != &nil){
			//In this situation, one can either choose to go left or right at first step.
			//We go right here.
			while(right_child->left_child != &nil)
				right_child = right_child->left_child;
			//Copy the key & data from subtitute to del_node.
			del_node->key = right_child->key;
			del_node->data = right_child->data;
			//Tree links to the leaf.
			*parentChildCheck(right_child) = right_child->right_child;
			//Leaf links back to the tree.
			right_child->right_child->parent = right_child->parent;
			//Exchange and let the substitute go to hell.
			del_node = right_child;
		}
		else if (left_child != &nil){
			*parentChildCheck(del_node) = left_child;
			left_child->parent = (del_node != root)?del_node->parent:NULL;
		}
		else if (right_child != &nil){
			*parentChildCheck(del_node) = right_child;
			right_child->parent = (del_node != root)?del_node->parent:NULL;
		}
		else{
			*parentChildCheck(del_node) = &nil;
		}

		free(del_node);

	}
	else{

		printf("The deleted node doesn't exist!\n");
		return 1;
	}

}
struct node* searchNode(int key){
	struct node* current = NULL;
	struct node* next_node = NULL;
	next_node = root;
	while(next_node != &nil){
		current = next_node;
		if (key != current->key){
			next_node = key > current->key ? current->right_child : current->left_child;
		}
		else
			return current;
	}
	return NULL;
}

void leftRotation(struct node *current){
	struct node* right_child = current->right_child;
	struct node* right_left_child = right_child->left_child;
	/*
	   if (current != root){

	   right_child->parent = current->parent;

	   if (parent->left_child == current)
	   parent->left_child = right_child;
	   else
	   parent->right_child = right_child;

	 *parentChildCheck(current) = right_child;
	 }
	 else {
	 right_child->parent = NULL;
	 root = right_child;
	 }
	 */
	right_child->parent = (current!=root)?current->parent:NULL;
	*parentChildCheck(current) = right_child;
	right_left_child->parent = current;
	right_child->left_child = current;
	current->parent = right_child;
	current->right_child = right_left_child;
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
