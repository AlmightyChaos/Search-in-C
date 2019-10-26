#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

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
void insertFixUp(struct node* current){
	struct node* uncle = NULL;

	while(current->parent->color == COLOR_RED){

		if (current->parent == current->parent->parent->left_child){
			uncle = current->parent->right_child;

			if (uncle->color == COLOR_RED){
				current->parent->color = COLOR_BLACK;
				uncle->color = COLOR_BLACK;
				current->parent->parent->color = COLOR_RED;
				current = current->parent->parent;
			}
			else{
				if(current == current->parent->right_child){
					current = current->parent;
					leftRotation(current);
				}
				current->parent->color = COLOR_BLACK;
				current->parent->parent->color = COLOR_RED;
				rightRotation(current->parent->parent);
			}
		}
		else{
			uncle = current->parent->parent->left_child;
			if (uncle->color == COLOR_RED){
				current->parent->color = COLOR_BLACK;
				uncle->color = COLOR_BLACK;
				current->parent->parent->color = COLOR_RED;
				current = current->parent->parent;
			}
			else{
				if (current == current->parent->left_child){
					current = current->parent;
					rightRotation(current);
				}
				current->parent->color = COLOR_BLACK;
				current->parent->parent->color = COLOR_RED;
				leftRotation(current->parent->parent);
			}
		}

	}	
	root->color = COLOR_BLACK;
}

void deleteFixUp(struct node* current){
	struct node* sibling = NULL;
	while(current != root && current->color != COLOR_RED){
		if (current == current->parent->left_child){
			sibling = current->parent->right_child;
			if (sibling->color == COLOR_RED){
				sibling->color = COLOR_BLACK;
				current->parent->color = COLOR_RED;
				leftRotation(current->parent);
				sibling = current->parent->right_child;
			}
			if (sibling->right_child->color == COLOR_BLACK && sibling->left_child->color == COLOR_BLACK){
				sibling->color = COLOR_RED;
				current = current->parent;
			}
			else{
				if(sibling->left_child->color == COLOR_RED){
					sibling->left_child->color = COLOR_BLACK;
					sibling->color = COLOR_RED;
					rightRotation(sibling);
					sibling = current->parent->right_child;
				}
				sibling->color = current->parent->color;
				current->parent->color = COLOR_BLACK;
				sibling->right_child->color = COLOR_BLACK;
				leftRotation(current->parent);
				current = root;
			}
		}


		else{
			sibling = current->parent->left_child;
			if (sibling->color == COLOR_RED){
				sibling->color = COLOR_BLACK;
				current->parent->color = COLOR_RED;
				rightRotation(current->parent);
				sibling = current->parent->left_child;
			}
			if (sibling->right_child->color == COLOR_BLACK && sibling->left_child->color == COLOR_BLACK){
				sibling->color = COLOR_RED;
				current = current->parent;
			}
			else{
				if(sibling->right_child->color == COLOR_RED){
					sibling->right_child->color = COLOR_BLACK;
					sibling->color = COLOR_RED;
					leftRotation(sibling);
					sibling = current->parent->left_child;
				}
				sibling->color = current->parent->color;
				current->parent->color = COLOR_BLACK;
				sibling->left_child->color = COLOR_BLACK;
				rightRotation(current->parent);
				current = root;
			}
		}
	}
	current->color = COLOR_BLACK;
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
	if (root == &nil){
		root = new_node;
		new_node->parent = &nil;
	}
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

	new_node->color = COLOR_RED;
	new_node->key = key;
	new_node->data = data;
	new_node->left_child = &nil;
	new_node->right_child = &nil;
	insertFixUp(new_node);
	return 0;
}

int deleteNode(int key){
	struct node* del_node = searchNode(key);
	struct node* current = NULL;
	struct node* substitute = NULL;
	struct node* left_child = del_node->left_child;
	struct node* right_child = del_node->right_child;

	if (del_node != NULL){
		if (left_child != &nil && right_child != &nil){
			/*In this situation, one can either choose to go left or right at first step.
			We go right here.*/
			current = right_child;
			/*Then we go left to find the best*/
			while(current->left_child != &nil)
				current = current->left_child;
			/*Copy the key & data from subtitute to del_node.*/
			del_node->key = current->key;
			del_node->data = current->data;
			/*Renew the left_child & right_child*/
			left_child = current->left_child;
			right_child = current->right_child;
			/*Move the del_node to current.*/
			del_node = current;
		}
		if (left_child != &nil){ /*Only have left_child.*/
			*parentChildCheck(del_node) = left_child;
			left_child->parent = del_node->parent;
			substitute = left_child;
		}
		else{/*Including only have right_child & have no child.*/
			*parentChildCheck(del_node) = right_child;
			right_child->parent = del_node->parent;
			substitute = right_child;
		}

		if (del_node->color == COLOR_BLACK)
			deleteFixUp(substitute);

		free(del_node);
	}
	else{

		printf("The deleted node doesn't exist!\n");
		return 1;
	}
	return 0;
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
	right_child->parent = current->parent;
	*parentChildCheck(current) = right_child;
	right_left_child->parent = current;
	right_child->left_child = current;
	current->parent = right_child;
	current->right_child = right_left_child;
}

void rightRotation(struct node *current){
	struct node* left_child = current->left_child;
	struct node* left_right_child = left_child->right_child;

	left_child->parent = current->parent;
	*parentChildCheck(current) = left_child;
	left_right_child->parent = current;
	left_child->right_child = current;
	current->parent = left_child;
	current->left_child = left_right_child;
}

void levelOrderTraversal(){
	struct node *current = NULL;
	enqueue(root);
	while(dequeue(&current)){
		printf("(%d)%s:%c", current->key, current->data, current->color);
		if (current->parent != NULL)
			printf("-%d\n", current->parent->key);
		else
			printf("\n");
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
