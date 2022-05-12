#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"

#define LOADFACTOR 0.75 //Dynamic resizing factor, once it reaches
//75% of it's size, it doubles it

typedef struct item {
  int key;
  void* data; //Generic data type
} Item;

struct hash {
  int qnt, TABLE_SIZE, ITEM_SIZE;
  Item **items;
};

//If the functions returns 0 means there is an error
//if it returns 1, means success.

int keyFold(int key, int TABLE_SIZE);
int linear_probing(int pos, int i, int TABLE_SIZE);
int dynamicResize(Hash* ha);

//Create hash table based on item size
Hash* createHash(int TABLE_SIZE, int TYPE_SIZE) {
  
  Hash* ha = (Hash*) malloc(sizeof(Hash));
  
  if(ha == NULL) return NULL; //safety check

  ha->TABLE_SIZE = TABLE_SIZE;
  ha->ITEM_SIZE = TYPE_SIZE;
  ha->items = (Item**) malloc(TABLE_SIZE * sizeof(Item*));

  if(ha->items == NULL) {
    free(ha);
    return NULL;
  }

  ha->qnt = 0;
  int i;
  for(i = 0; i < TABLE_SIZE; i++) {
    ha->items[i] = NULL;
  }

  return ha;
}

//Function to free the table
void freeHash(Hash* ha) {
  if(ha == NULL) return;
  int i;
  for(i = 0; i < ha->TABLE_SIZE; i++) {
    if(ha->items[i] != NULL) {
      free(ha->items[i]->data); //Deallocates data from item in the table
      free(ha->items[i]);
    }
  }
  free(ha->items);
  free(ha);
  return;
}

//Function to insert items in the table
int insert_item_Hash(Hash* ha, int key, void *data) {
  if (ha == NULL || ha->qnt == ha->TABLE_SIZE)
    return 0;

  //Safety measures if the tables needs to resize,
  //and the dynamic resize fails, returns 0 as an error
  if(ha->qnt/(float) ha->TABLE_SIZE > LOADFACTOR && !dynamicResize(ha))
    return 0;

  int i, newPos;
  int pos = keyFold(key, ha->TABLE_SIZE);
  for(i = 0; i < ha->TABLE_SIZE; i++) {
    newPos = linear_probing(pos, i, ha->TABLE_SIZE);

    if(ha->items[newPos] == NULL) {
      Item* item = (Item*) malloc(sizeof(Item));
      if(item == NULL) return 0;
      item->key = key;
      //Allocates generic pointer from item 
      //to the table's generic item treatment.
      item->data = (void *) malloc(ha->ITEM_SIZE);

      if(item->data == NULL) {
        free(item);
        return 0;
      }

      //Copying data received from user to allocated
      //memory space in the pointer "item->data"
      memcpy(item->data, data, ha->ITEM_SIZE);
      ha->items[newPos] = item;
      ha->qnt++;
      return 1;
    }
  }
  return 0;
}

//Function to search item in the table
int search_item_Hash(Hash* ha, int key, void *data) {
  if(ha == NULL) return 0;
  int i, newPos;
  int pos = keyFold(key, ha->TABLE_SIZE);

  for(i = 0; i < ha->TABLE_SIZE; i++) {
    newPos = linear_probing(pos, i, ha->TABLE_SIZE);

    if(ha->items[newPos] == NULL)
      return 0;

    if(ha->items[newPos]->key == key) {
      memcpy(data, ha->items[newPos]->data, ha->ITEM_SIZE);
      return 1;
    }
  }
  return 0;
}


//Hashing function, you can change it if you want.
int keyFold(int key, int TABLE_SIZE) {
  int num_bits = 10;
  int p1 = key >> num_bits;
  int p2 = key & (TABLE_SIZE - 1);
  return p1 ^ p2;
}

//Linear probing method for open addressing
int linear_probing(int pos, int i, int TABLE_SIZE) {
  return ((pos + i) & 0x7FFFFFFF) % TABLE_SIZE;
}

//Function for dynamic resizing
int dynamicResize(Hash* ha) {
  if(ha == NULL) return 0;
  //Allocate item array to double it's size
  int timesTwo = ha->TABLE_SIZE * 2;
  Item** newHa = (Item**) malloc(timesTwo * sizeof(Item*));

  if(newHa == NULL) return 0;

  int i, j, pos, newPos;

  for(i = 0; i < timesTwo; i++) {
    newHa[i] = NULL;
  }

  //Passing pointers from old table to the new one
  for(i = 0; i < ha->TABLE_SIZE; i++) {
    //Search old table for items
    if(ha->items[i] != NULL) {
      //If there is items, linear probing on new table
      //with twice it's size
      pos = keyFold(ha->items[i]->key, timesTwo);
      for(j = 0; j < timesTwo; j++) {
        newPos = linear_probing(pos, j, timesTwo);
        if(newHa[newPos] == NULL) {
          //If it finds a valid position to insert the item,
          //stops linear probing
          newHa[newPos] = ha->items[i];
          break;
        }
      }
    }
  }

  //Free old item array, because there is
  //no use for it anymore
  free(ha->items);
  ha->items = newHa;
  ha->TABLE_SIZE = timesTwo;
  return 1;
}
