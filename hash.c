#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "hash.h"
#define GOLDEN_RATIO_PRIME_32 0x9e370001UL

void hashInit(struct hash_list *hash_table, unsigned int bits){
	hash_table = (struct hash_list *)malloc(sizeof(struct hash_list *)*bits);
}

void hashAdd(void *input, unsigned int bits){
	
}

void hashDel(){

}

void hashSearch(){

}

unsigned int stringPreHash(void* string){
	char* pos = (char*)string;
	unsigned int h = 0;
	while(*pos != '\0')
		h += (unsigned int)(*(pos++));
	return h;
}

unsigned int hashCRC(char* string, unsigned int bits){
	unsigned int h = 0;
	unsigned int highorder;
	char* pos = string;

	while(*pos != '\0'){
		highorder = h & 0xF8000000UL;
		h = h << 5;
		h = h ^ (highorder >> 27);
		h = h ^ (unsigned int)(*(pos++));
	}
	return h%(2<<bits);
}

unsigned int hashMulMethod(unsigned int value, unsigned int bits){
	unsigned int hash = value * GOLDEN_RATIO_PRIME_32;
	return hash >> (32 - bits);
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
	unsigned int bits = 10;
	struct hash_list *hash_table;
	hashInit(hash_table, bits);
	hashAdd((void*)3, bits);
	//hashCRC("ek", 100);
	//printf("%u\n", hashMulMethod(100, 3));
	printf("%ld\n", offsetof(struct hash_list, key));
	printf("%ld\n", (size_t) &bits);
	return 0;
}
