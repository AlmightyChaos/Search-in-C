struct hash_head {
	struct hash_node *next;
};

struct hash_node {
	struct hash_node **pprev, *next;
};

struct hash_list {
	char* key;
	int value;	
	struct hash_node node;
};
