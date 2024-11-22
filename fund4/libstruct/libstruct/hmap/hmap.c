/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 16.11.2024
 */
#include <libstruct/hmap/hmap.h>

typedef struct hmap_item_t hmap_item_t;

struct hmap_item_t {
  char* key;
  void* value;
  size_t hash;
  hmap_item_t* next;
};

typedef struct {
  hmap_item_t* first;
  size_t size;
} hmap_bucket_t;

struct hmap_t {
  size_t size;
  hmap_bucket_t* buckets;
  hash_func_t hash;
  hash_error_handler_t hash_error_handler;
};

hmap_handle_t hmap_create(hmap_status_t* status) {
  error_check_pointer_and_assign(status, HMAP_OK);
  hmap_handle_t new_hmap = malloc(sizeof(struct hmap_t));
  if (!new_hmap) {
    error_check_pointer_and_assign(status, HMAP_ALLOCATION_ERROR);
    return NULL;
  }
  new_hmap->hash = string_hash;
  new_hmap->hash_error_handler = string_hash_error_handler;
  new_hmap->size = HASH_MAP_DEFAULT_SIZE;
  new_hmap->buckets = calloc(HASH_MAP_DEFAULT_SIZE, sizeof(hmap_bucket_t));
  if (!new_hmap->buckets) {
    error_check_pointer_and_assign(status, HMAP_BUCKET_ALLOCATION_ERROR);
    free(new_hmap);
    return NULL;
  }
  return new_hmap;
}
void hmap_destructor(hmap_handle_t hmap, bool with_content) {
  for (size_t i = 0; i < hmap->size; ++i) {
    hmap_bucket_t bucket = hmap->buckets[i];
    hmap_item_t* item = bucket.first;
    while (item && item->next) {
      hmap_item_t* next = item->next;
      if (item->key) {
        free(item->key);
      }
      free(item);
      if (item->value && with_content) {
        free(item->value);
      }
      item = next;
    }
  }
  free(hmap->buckets);
  free(hmap);
}

void hmap_destroy(hmap_handle_t hmap) {
  hmap_destructor(hmap, false);
}
void hmap_destroy_with_content(hmap_handle_t hmap) {
  hmap_destructor(hmap, true);
}

size_t hmap_compute_hash(hmap_handle_t hmap, const char* key,
                         hmap_status_t* status) {
  error_check_pointer_and_assign(status, HMAP_OK);
  int hash_computation_status = 0;
  size_t hash = hmap->hash(key, &hash_computation_status);
  if (hash_computation_status != 0) {
    hmap->hash_error_handler(hash_computation_status);
    error_check_pointer_and_assign(status, HMAP_HASH_COMPUTATION_ERROR);
    return -1;
  }
  return hash;
}

hmap_item_t* hmap_item_create(hmap_handle_t hmap, const char* key,
                              const void* value, hmap_status_t* status) {
  hmap_item_t* item = malloc(sizeof(hmap_item_t));
  if (!item) {
    error_check_pointer_and_assign(status, HMAP_ITEM_ALLOCATION_ERROR);
    return NULL;
  }
  if (key == NULL) {
    error_check_pointer_and_assign(status, HMAP_INVALID_KEY_ERROR);
    return NULL;
  }
  item->key = strdup(key);
  if (!item->key) {
    error_check_pointer_and_assign(status, HMAP_KEY_ALLOCATION_ERROR);
    free(item);
    return NULL;
  }
  item->value = (void*)value;
  item->next = NULL;
  item->hash = hmap_compute_hash(hmap, key, status);
  if (*status != HMAP_OK) {
    free(item->key);
    free(item);
    return NULL;
  }
  return item;
}

void hmap_bucket_add_item(hmap_bucket_t* bucket, hmap_item_t* item) {
  hmap_item_t* current = bucket->first;
  item->next = current;
  bucket->first = item;
  bucket->size++;
}

size_t hmap_compute_new_size(hmap_handle_t hmap) {
  return hmap->size * 2;
}
hmap_item_t* hmap_get_item(hmap_handle_t hmap, const char* key,
                           hmap_status_t* status) {
  error_check_pointer_and_assign(status, HMAP_OK);
  hmap_status_t hash_status;
  size_t bucket_idx = hmap_compute_hash(hmap, key, &hash_status) % hmap->size;
  if (hash_status != HMAP_OK) {
    error_check_pointer_and_assign(status, hash_status);
    return NULL;
  }
  hmap_item_t* item = hmap->buckets[bucket_idx].first;
  if (!item) {
    error_check_pointer_and_assign(status, HMAP_ITEM_NOT_FOUND_ERROR);
    return NULL;
  }
  while (item) {
    if (strcmp(key, item->key) == 0) {
      return item;
    }
    item = item->next;
  }
  error_check_pointer_and_assign(status, HMAP_ITEM_NOT_FOUND_ERROR);
  return NULL;
}

hmap_status_t hmap_insert_item(hmap_handle_t hmap, hmap_item_t* item) {
  hmap_item_t* existing_item = hmap_get_item(hmap, item->key, NULL);
  if (!existing_item) {
    const size_t idx = item->hash % hmap->size;
    hmap_bucket_add_item(&hmap->buckets[idx], item);
  } else {
    existing_item->value = item->value;
    free(item);
  }
  return HMAP_OK;
}

hmap_status_t hmap_check_chain_sizes_and_evacuate(hmap_handle_t hmap) {
  size_t new_size = hmap_compute_new_size(hmap);
  size_t old_size = hmap->size;
  hmap->size = new_size;
  hmap_bucket_t* old_buckets = hmap->buckets;
  hmap->buckets = calloc(new_size, sizeof(hmap_bucket_t));
  if (!hmap->buckets) {
    return HMAP_BUCKET_ALLOCATION_ERROR;
  }
  for (size_t i = 0; i < old_size; ++i) {
    hmap_item_t* item = old_buckets[i].first;
    while (item) {
      hmap_item_t* next = item->next;
      hmap_status_t status = hmap_insert_item(hmap, item);
      if (status != HMAP_OK) {
        return status;
      }
      item = next;
    }
  }
  free(old_buckets);
  return HMAP_OK;
}

bool hmap_is_rebuild_needed(hmap_handle_t hmap) {
  size_t max_size = 0;
  size_t min_size = SIZE_MAX;
  for (int i = 0; i < hmap->size; ++i) {
    if (hmap->buckets[i].size > max_size) {
      max_size = hmap->buckets[i].size;
    }
    if (hmap->buckets[i].size < min_size) {
      min_size = hmap->buckets[i].size;
    }
  }
  if (max_size == 0 || min_size == 0) {
    return false;
  }
  if (max_size > 2 * min_size) {
    return true;
  }
  return false;
}

hmap_status_t hmap_insert(hmap_handle_t hmap, const char* key,
                          const void* value) {
  hmap_status_t status;
  hmap_item_t* item = hmap_item_create(hmap, key, value, &status);
  if (status != HMAP_OK) {
    return status;
  }
  hmap_insert_item(hmap, item);

  if (hmap_is_rebuild_needed(hmap)) {
    hmap_check_chain_sizes_and_evacuate(hmap);
  }
  return HMAP_OK;
}

void* hmap_get(hmap_handle_t hmap, const char* key, hmap_status_t* status) {
  hmap_item_t* item = hmap_get_item(hmap, key, status);
  if (!item) {
    return NULL;
  }
  return item->value;
}

hmap_status_t hmap_remove(hmap_handle_t hmap, const char* key) {
  hmap_status_t status;
  hmap_item_t* item = hmap_get_item(hmap, key, &status);
  if (!item) {
    return status;
  }
  size_t bucket_idx = item->hash % hmap->size;
  hmap_item_t* current = hmap->buckets[bucket_idx].first;
  if (item == hmap->buckets[bucket_idx].first) {
    hmap->buckets[bucket_idx].first = item->next;
  }
  while (current->next != item && current->next) {
    current = current->next;
  }
  current->next = item->next;

  free(item);
  hmap->buckets[bucket_idx].size--;
  return HMAP_OK;
}
void hmap_error_handler(hmap_status_t status) {
  error_print("HMAP Error: ");
  switch (status) {
    case HMAP_OK:
      break;
    case HMAP_ALLOCATION_ERROR:
      error_print("Failed to allocate memory for hmap structure");
      break;
    case HMAP_HASH_COMPUTATION_ERROR:
      error_print("Failed hash computation");
      break;
    case HMAP_KEY_ALLOCATION_ERROR:
      error_print("Failed to allocate memory for key");
      break;
    case HMAP_ITEM_ALLOCATION_ERROR:
      error_print("Failed to allocate memory for item");
      break;
    case HMAP_INVALID_KEY_ERROR:
      error_print("NULL key was provided");
      break;
    case HMAP_ITEM_NOT_FOUND_ERROR:
      error_print("Item for this key was not found");
      break;
    case HMAP_BUCKET_ALLOCATION_ERROR:
      error_print("Can't allocate memory for hmap buckets");
      break;
    default:
      error_print("Unkown error");
      break;
  }
}