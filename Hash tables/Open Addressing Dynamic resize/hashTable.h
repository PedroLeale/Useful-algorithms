
typedef struct hash Hash;
Hash* createHash(int TABLE_SIZE, int TYPE_SIZE);
void freeHash(Hash* ha);
int insert_item_Hash(Hash* ha, int key, void *data);
int search_item_Hash(Hash* ha, int key, void *data);