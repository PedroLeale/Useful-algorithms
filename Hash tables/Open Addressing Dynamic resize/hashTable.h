
typedef struct hash Hash;
Hash* createHash(int TABLE_SIZE, int TAMANHO_TIPO);
void freeHash(Hash* ha);
int insert_item_Hash(Hash* ha, int chave, void *dados);
int search_item_Hash(Hash* ha, int chave, void *dados);