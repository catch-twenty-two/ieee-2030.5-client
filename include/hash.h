#pragma once

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup hash Hash

    Provides a dynamically sized hash table implementation based upon sparse
    groups. Sparse groups are arrays of elements that use a single bit to
    indicate occupancy. Only the elements of the array that are occupied are
    stored, this results in a compact representation of a hash table at the
    cost of some extra processing to perform the insertion.
    @{
*/

typedef struct _HashTable HashTable;

/** @brief Allocate a HashTable.
    @param size is the initial size of the HashTable
*/
HashTable *hash_new (int size);

/** @brief Free a HashTable.
    @param ht is a pointer to a HashTable
*/
void hash_free (HashTable *ht);

/** @brief Put the data item into the HashTable. 
    @param ht is a pointer to a HashTable
    @param data is pointer to the data item
*/
void hash_put (HashTable *ht, void *data);

/** @brief Delete the hash entry that matches the key.
    @param ht is a pointer to a HashTable
    @param key is a pointer to a hash key
    @returns the hash entry associated with the key
*/
void *hash_delete (HashTable *ht, void *key);

/** @brief Get the data item that matches the key.
    @param ht is a pointer to a HashTable
    @param key is a pointer to a hash key
    @returns the hash entry associated with the key
*/
void *hash_get (HashTable *ht, void *key);

/** @brief Allocate a new HashTable with entries hashed by character strings.
    @param size is the initial size of the HashTable
    @param get_key is a user supplied function to get the key from a hash entry
    @returns a new HashTable
*/
HashTable *new_string_hash (int size, void *(*get_key) (void *data));

/** @brief Allocate a new HashTable with entries hashed by 64-bit integers.
    @param size is the initial size of the HashTable
    @param get_key is a user supplied function to get the key from a hash entry
    @returns a new HashTable
*/
HashTable *new_int64_hash (int size, void *(*get_key) (void *data));

/** @brief Create a global hash table with functions to initialize the
    HashTable, find, insert, and delete entries from the HashTable.
*/
#define global_hash(name, kind, size) \
  HashTable *name##_hash = NULL;		   \
  void *find_##name (void *key) {		   \
    return hash_get (name##_hash, key);	   \
  }						   \
  void insert_##name (void *data) {		   \
    hash_put (name##_hash, data);		   \
  }						   \
  void *delete_##name (void *key) {		   \
    return hash_delete (name##_hash, key);	   \
  }						   \
  void name##_init () {					\
    name##_hash = new_##kind##_hash (size, name##_key);	\
  }

typedef struct {
  void *g, *ht; int i;
} HashPointer;

void *hash_next (HashPointer *p);

void *hash_iterate (HashPointer *p, HashTable *ht);

void hash_erase (HashPointer *p);

#define foreach_h(h, hp, ht)					\
  for (h = hash_iterate (hp, ht); h != NULL; h = hash_next (hp))

/** @} */

