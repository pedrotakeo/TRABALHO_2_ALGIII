#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"

int hash_tabela1(int k){  // função de hash para a tabela 1
    return k % HASH_MAP_SIZE;
}

int hash_tabela2(int k){  // função de hash para a tabela 2
    float item = k * 0.9;
    float hash_result = (item - floor(item)); 
    hash_result = HASH_MAP_SIZE * hash_result;

    return floor(hash_result);
}

//===============================================================AUX FUNCTIONS

void initialize_item(struct hash_item *item, int num_tabela){ //inicializa itens da hash map;
    item->key = 0;
    item->state = AVAILABLE;
    item->tabela = num_tabela;
}

void insert_ordered_array(struct hash_item map[], int key, int tabela, int *items_inserted){
    struct hash_item insert;
    insert.key = key;
    insert.state = NOT_AVAILABLE;
    insert.tabela = tabela;
    
    if(items_inserted == 0){
        map[0] = insert;
        (*items_inserted)++;
        return;
    }

    if(map[(*items_inserted) - 1].key <= insert.key){
        map[(*items_inserted)] = insert;
        (*items_inserted)++;
        return;
    }

    if(insert.key < map[0].key){
        for(int j = (*items_inserted); j > 0; j--){
            map[j] = map[j - 1];
        }
        map[0] = insert;
        (*items_inserted)++;
        return;
    }

    int i = 0;
    for(i = 0; i < (*items_inserted); i++){
        if (insert.key < map[i].key){
            break;
        }
    }

    for(int j = (*items_inserted); j > i ; j--){
        map[j] = map[j - 1];
    }
    map[i] = insert;
    (*items_inserted)++;
    return;


}


void change_ordered_array_state(struct hash_item map[], int key, int estado, int tabela, int items_inserted){
    for (int i = 0; i < items_inserted; i++){
        if(map[i].key == key){
            map[i].state = estado;
            map[i].tabela = tabela;
            break;
        }
    }
    return;
}


//===============================================================
void initialize_hash_table(struct hash_item map[], int num_tabela, int amt){ //inicializa hash map
    for(int i = 0; i < amt; i++){  //inicializa itens do mapa
        initialize_item(&map[i], num_tabela); 
    }
}

void insert_hash(struct hash_item t1[], struct hash_item t2[],int key, struct hash_item ordered[], int *items_inserted){
    int hash_pos = hash_tabela1(key);

    if(hash_pos > HASH_MAP_SIZE){ //segurança
        return;
    }

    if(t1[hash_pos].state == AVAILABLE){
        t1[hash_pos].key = key;
        t1[hash_pos].state = NOT_AVAILABLE;
        insert_ordered_array(ordered, t1[hash_pos].key, 1, items_inserted);
    }
    else{
        int key_save = t1[hash_pos].key;
        t1[hash_pos].key = key;
        insert_ordered_array(ordered, t1[hash_pos].key, 1, items_inserted);

        hash_pos = hash_tabela2(key_save);

        if(hash_pos > HASH_MAP_SIZE){//segurança
            return;
        }
        t2[hash_pos].key = key_save;
        change_ordered_array_state(ordered, key_save, NOT_AVAILABLE, 2, *items_inserted);
    }

    return;
}

void delete_hash(struct hash_item t1[], struct hash_item t2[],int key, struct hash_item ordered[], int *items_inserted){
    int hash_pos = hash_tabela2(key);

    if(t2[hash_pos].key == key){
        int key_save = t2[hash_pos].key;
        t2[hash_pos].key = 0;
        t2[hash_pos].state = AVAILABLE;
        change_ordered_array_state(ordered, key_save, AVAILABLE, 0, *items_inserted);
        return;
    }

    hash_pos = hash_tabela1(key);
    if(t1[hash_pos].key == key){
        t1[hash_pos].state = AVAILABLE;
        change_ordered_array_state(ordered, t1[hash_pos].key, AVAILABLE, 0, *items_inserted);
        return;
    }

    return;
}

void print_hash(struct hash_item ordered[], int items_inserted){
    for (int i = 0; i < items_inserted; i++){
        if(ordered[i].state == NOT_AVAILABLE){
            int pos;
            if(ordered[i].tabela == 1){
                pos = hash_tabela1(ordered[i].key);
            }
            else{
                pos = hash_tabela2(ordered[i].key);
            }
            printf("%d,T%d,%d\n", ordered[i].key, ordered[i].tabela, pos);
        }
    }
}