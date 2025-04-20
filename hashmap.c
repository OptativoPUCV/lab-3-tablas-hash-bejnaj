#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1; 
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    // sacas el valor para indexar
    long lugarHash = hash(key, map->capacity);

    // iteracion para buscar donde ubicarlo considerando colisiones
    while (map->buckets[lugarHash] != NULL && map->buckets[lugarHash]->key != NULL) {
        if (map->buckets[lugarHash]->key == key) {
            // si existe actualizar valor
            map->buckets[lugarHash]->value = value;
            return;
        }
        lugarHash = (lugarHash + 1) % map->capacity;
    }
    map->buckets[lugarHash] = createPair(key, value);
    map->size++;
    map->current = lugarHash;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    // crear map
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    map->buckets = (Pair **)calloc(capacity, sizeof(Pair *));
    if (map->buckets == NULL) {
        free(map); // Liberar memoria si falla la asignación de buckets
        return NULL;
    }

    // Inicializar las variables del mapa
    map->size = 0;
    map->capacity = capacity;
    map->current = -1; // Índice actual inicializado a -1

    return map;
    return NULL;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
