/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 24.10.2024
 */
#include <libstring/vstring.h>



struct vstring_meta_t {
  char *str;
  size_t len;
  size_t cap;
};

vstring vstring_create(char* str) {
  vstring string = malloc(sizeof(struct vstring_meta_t));
  string->cap = strlen(str);
  string_copy(str, &string->str);
}
void vstring_destroy(vstring str) {
  free(str->str);
  free(str);
}
void vstring_resize(vstring* str) {

}

