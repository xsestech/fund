/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 04.11.2024
 */
#include <libtask/task1/task1.h>

/**
 * Bitwise increment
 * We xor every bit with mask to invert it until we reach 0
 * @param number input number
 * @return incremented number
 */
uint64_t bitwise_increment(uint64_t number) {
  uint64_t mask = 1;
  while (number & mask) {
    number ^= mask;
    mask <<= 1;
  }
  number ^= mask;
  return number;
}
/**
 * Bitwise decrement
 * We xor every bit with mask to invert it until we reach 1
 * @param number input number
 * @return decremented number
 */
uint64_t bitwise_decrement(uint64_t number) {
  uint64_t mask = 1;
  while (!(number & mask)) {
    number ^= mask;
    mask <<= 1;
  }
  number ^= mask;
  return number;
}

size_t log_2_pow_r(uint64_t number, uint8_t r) {
  uint64_t result = 0;
  while (number != 0) {
    number >>= r;
    result = bitwise_increment(result);
  }
  return bitwise_increment(result);
}
uint64_t bitabs(int64_t number) {
  uint64_t mask = number >> 63;
  return (number ^ mask) + (~mask + 1);
}

char* convert_to_base_two(int64_t number, uint8_t r, task1_status_t* status) {
  error_check_pointer_and_assign((int*)status, TASK1_OK);
  if (r < 1 || r > 5) {
    error_check_pointer_and_assign((int*)status, TASK1_INVALID_BASE_ERROR);
    return NULL;
  }
  size_t number_len =
      bitwise_increment(bitwise_increment(log_2_pow_r(llabs(number), r)));
  char* result = malloc(number_len);
  if (!result) {
    error_check_pointer_and_assign((int*)status, TASK1_ALLOCATION_ERROR);
    return NULL;
  }

  /* As we are in base 2^r, we can convert it by getting the last r bits and
  * then shifting them to the left to r bits */
  const uint8_t mask = bitwise_decrement(1 << r);
  const char* alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  size_t pos = 0;
  uint64_t abs_number = bitabs(number);
  while (abs_number) {
    result[pos] = alphabet[abs_number & mask];
    pos = bitwise_increment(pos);
    abs_number >>= r;
  }
  if (number < 0) {
    result[pos] = '-';
    pos = bitwise_increment(pos);
  }
  result[pos] = 0;

  // Leading zeros
  while (pos > 0 && result[bitwise_decrement(pos)] == '0') {
    pos = bitwise_decrement(pos);
  }
  result[pos] = 0;
  pos = bitwise_decrement(pos);
  size_t left = 0;
  size_t right = pos;
  while (left < right) {
    char tmp = result[left];
    result[left] = result[right];
    result[right] = tmp;
    left = bitwise_increment(left);
    right = bitwise_decrement(right);
  }
  return result;
}