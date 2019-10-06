#include <stdio.h>

struct node{
	int color;
	int key;
	char* data;
	struct node *left_child;
	struct node *right_child;
	struct node *parent;	
};

void insertNode();
void deleteNode();
void leftRotation();
void rightRotation();
void insertAdjustment();
void deleteAdjustment();

int main(){


	return 0;
}
