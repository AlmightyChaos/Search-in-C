#include "rbtree.h"
int main(void){
	insertNode(5, "faker");
	insertNode(10, "nick");
	insertNode(2, "fuick");
	insertNode(8, "fffnick");
	insertNode(12, "nickfdf");
	insertNode(4, "nic2223k");
	insertNode(1, "ni34ck");
	insertNode(13, "ytyty77");
	insertNode(7, "ytydsfs");
	insertNode(15, "yt535sfs");
	insertNode(14, "ytyty43");
	deleteNode(13);
	levelOrderTraversal();
	/*printf("%s\n", searchNode(10)->data);
	printf("%ld\n", (root->right_child));
	printf("%ld\n", *(struct node **)((void*)root+24));
	*(struct node**)((void*)root+24) = root;
	printf("%ld\n", *parentChildCheck(root));
	printf("%ld\n", root);*/
	return 0;
}
