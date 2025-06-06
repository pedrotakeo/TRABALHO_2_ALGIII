#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "utils.h"

int main(int argc, char *argv[]){
    if(argc > 1 && strcmp(argv[1], "-h") == 0){
        printf("Nome: Pedro Takeo Shima \n");
        printf("GRR: GRR20240627\n");
        printf("login: pts24\n");
        printf("Nome: Beatriz Pontes Camargo\n");
        printf("GRR: GRR20242966\n");
        printf("login: bpc24\n");

        return 0;
    }
    struct hash_item map1[HASH_MAP_SIZE];
    initialize_hash_table(map1, 1, HASH_MAP_SIZE);

    struct hash_item map2[HASH_MAP_SIZE];
    initialize_hash_table(map2, 2, HASH_MAP_SIZE);

    struct hash_item print_map[2 * HASH_MAP_SIZE];
    initialize_hash_table(print_map, 0, 2 * HASH_MAP_SIZE);
    int items_inserted = 0;

    char op;
    int key;

    while ((scanf(" %c %d", &op, &key)) == 2){
        switch(op){
            case 'i':
                insert_hash(map1, map2, key, print_map, &items_inserted);
                break;
            case 'r':
                delete_hash(map1, map2, key, print_map, &items_inserted);
                break;
            default:
                
                return 0;
                break;
                
        }
    }

    print_hash(print_map, items_inserted);

    return (0);
}