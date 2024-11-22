/**
 * @file
 * @brief Header file for hash map functions
 * @details This file contains the declarations for the hash map functions and related status codes.
 * It provides a way to create, destroy, insert, retrieve, and remove key-value pairs in a hash map.
 * The status of the hash map operations is also provided through an enumeration.
 * 
 * @date 16.11.2024
 */
#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <liberrors/errors.h>
#include <libstring/hash.h>

#ifndef HASH_MAP_DEFAULT_SIZE
#define HASH_MAP_DEFAULT_SIZE 8
#endif

/**
 * @enum hmap_status_t
 * @brief Status codes for hash map operations
 * @details This enumeration defines the possible status codes that can be returned by the hash map functions.
 */
typedef enum {
  HMAP_OK, /**< Operation was successful */
  HMAP_ALLOCATION_ERROR, /**< Memory allocation error occurred */
  HMAP_ITEM_ALLOCATION_ERROR, /**< Item memory allocation error occurred */
  HMAP_INVALID_KEY_ERROR, /**< Invalid key error */
  HMAP_KEY_ALLOCATION_ERROR, /**< Key memory allocation error occurred */
  HMAP_BUCKET_ALLOCATION_ERROR, /**< Bucket memory allocation error occurred */
  HMAP_HASH_COMPUTATION_ERROR, /**< Hash computation error occurred */
  HMAP_ITEM_NOT_FOUND_ERROR /**< Item not found error */
} hmap_status_t;

/**
 * @typedef hmap_handle_t
 * @brief Handle for the hash map
 * @details This typedef defines a handle for the hash map, which is a pointer to the hash map structure.
 */
typedef struct hmap_t* hmap_handle_t;

/**
 * @typedef hash_func_t
 * @brief Function pointer type for hash functions
 * @details This typedef defines a function pointer type for hash functions that take a string key and return a hash value.
 * @param key The string key to hash
 * @param status Pointer to an integer to store the status of the hash function
 * @return The hash value of the key
 */
typedef size_t (*hash_func_t)(const char* key, int* status);

/**
 * @typedef hash_error_handler_t
 * @brief Function pointer type for hash error handlers
 * @details This typedef defines a function pointer type for error handlers that handle errors during hashing.
 * @param error The error code to handle
 */
typedef void (*hash_error_handler_t)(int error);

/**
 * @brief Create a hash map
 * @details Allocates and initializes a new hash map.
 * @param status Pointer to a status variable to store the status of the operation
 * @return Handle to the created hash map
 */
hmap_handle_t hmap_create(hmap_status_t* status);

/**
 * @brief Destroy a hash map
 * @details Frees the memory allocated for the hash map.
 * @param hmap Handle to the hash map to destroy
 */
void hmap_destroy(hmap_handle_t hmap);

/**
 * @brief Destroy a hash map with its content
 * @details Frees the memory allocated for the hash map and its key-value pairs.
 * @param hmap Handle to the hash map to destroy
 */
void hmap_destroy_with_content(hmap_handle_t hmap);

/**
 * @brief Insert a key-value pair into the hash map
 * @details Inserts a key-value pair into the hash map. If the key already exists, its value is updated.
 * @param hmap Handle to the hash map
 * @param key The key to insert
 * @param value The value to associate with the key
 * @return Status code of the operation
 */
hmap_status_t hmap_insert(hmap_handle_t hmap, const char* key, const void* value);


/**
 * @brief Retrieve a value from the hash map
 * @details Retrieves the value associated with the given key from the hash map.
 * @param hmap Handle to the hash map
 * @param key The key to retrieve the value for
 * @param status Pointer to a status variable to store the status of the operation
 * @return The value associated with the key, or NULL if the key is not found
 */
void* hmap_get(hmap_handle_t hmap, const char* key, hmap_status_t* status);

/**
 * @brief Remove a key-value pair from the hash map
 * @details Removes the key-value pair associated with the given key from the hash map.
 * @param hmap Handle to the hash map
 * @param key The key to remove
 * @return Status code of the operation
 */
hmap_status_t hmap_remove(hmap_handle_t hmap, const char* key);

#endif  //HASH_MAP_H
