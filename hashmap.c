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
    map->current = lugarHash;
    map->buckets[lugarHash] = createPair(key, value);
    map->size++;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)

    // creamos copia de los datos actuales
    Pair **antiguosDatos = map->buckets;
    long capacidadOriginal = map->capacity;

    // duplicamos capacidad
    map->capacity *= 2;

    // guardamos memoria para los buckets desde 0, con la nueva capacidad
    map->buckets = (Pair **)calloc(map->capacity, sizeof(Pair *));
    map->size = 0;

    for (long i = 0; i < capacidadOriginal; i++) {
        if (antiguosDatos[i] != NULL && antiguosDatos[i]->key != NULL) {
            insertMap(map, antiguosDatos[i]->key, antiguosDatos[i]->value);
        }
    }
}


HashMap * createMap(long capacity) {
    // crear map
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    // expandir sus pares
    map->buckets = (Pair **)calloc(capacity, sizeof(Pair *));

    // iniciar por defecto sus valores
    map->size = 0;
    map->capacity = capacity;
    map->current = -1;

    return map;
}

void eraseMap(HashMap * map,  char * key) {
    long index = hash(key, map->capacity);
    while (map->buckets[index] != NULL) { 
        if (is_equal(map->buckets[index]->key, key)) {
            map->buckets[index]->key = NULL;
            map->size--;
            return;
        }
        index = (index + 1) % map->capacity;
    }
}

Pair * searchMap(HashMap * map,  char * key) {   
    long index = hash(key, map->capacity);
    while (map->buckets[index] != NULL){
        if (is_equal(map->buckets[index]->key, key)){
            return map->buckets[index];
        }
        index = (index + 1) % map->capacity;
    }
    map->current = -1;
    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
