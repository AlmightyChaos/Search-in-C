#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
struct hash_list *hash_table;

void hashInit(unsigned int bits){
	hash_table = (struct hash_list *)malloc(sizeof(struct hash_list *)*bits);
}

void hashAdd(){

}

void hashDel(){

}

void hashSearch(){

}

unsigned int stringPreHash(char* string){
	char* pos = string;
	unsigned int h = 0;
	while(*pos != '\0')
		h += (unsigned int)(*(pos++));
	return h;
		//printf("%c\n", *(pos++));
}

void hashCRC(){


}

void hashMulMethod(){


}

void chaining(){

}

void reHash(){

}

void loadFactor(){

}

void tranToRbtree(){

}

void tranToList(){

}

int main(){
	hashInit(3);
	printf("%u\n", stringPreHash("dfg"));
	return 0;
}
