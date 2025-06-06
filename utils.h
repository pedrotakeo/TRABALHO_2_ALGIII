#ifndef __UTILS_H__
#define __UTILS_H__

#define HASH_MAP_SIZE 11
#define AVAILABLE 0
#define NOT_AVAILABLE 1

struct hash_item{
    int key;
    int state;
    int tabela; //p impressao
};

int hash_tabela1(int k);

int hash_tabela2(int k);

void initialize_hash_table(struct hash_item map[], int num_tabela, int amt);

void insert_hash(struct hash_item t1[], struct hash_item t2[],int key, struct hash_item ordered[], int *items_inserted);

void delete_hash(struct hash_item t1[], struct hash_item t2[],int key, struct hash_item ordered[], int *items_inserted);

void print_hash(struct hash_item ordered[], int items_inserted);


#endif