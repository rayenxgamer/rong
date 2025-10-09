#pragma once

#include "math/vec2.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

static inline char ascii_code_to_char(int code) {
  if (!(code <= 255 && code >= 0)){
    return '\0';
  };

  return (char)code;
}

static inline int isletterinbuffer(char letter, const char* buffer){
  assert(buffer != NULL);
  for (unsigned int i = 0; i < strlen(buffer); i++) {
    if (buffer[i] == letter) {
      return i;
    }
  }
  return 0;
}

static inline bool isletterinbuffermulti(char letter, int x, int y, const char buffer[x][y]){
  assert(buffer != NULL);
  for (unsigned int i = 0; i < x; i++) {
    for (unsigned int j = 0; j < y; j++) {
      if (buffer[i][j] == letter) {
        return true;
      }
    }
  }
  return false;
}

static inline bool isletterinbuffermulti_gi(char letter, int x, int y, const char buffer[x][y], vec2 output){
  assert(buffer != NULL);
  assert(output != NULL);

  for (unsigned int i = 0; i < x; i++) {
    for (unsigned int j = 0; j < y; j++) {
      if (buffer[i][j] == letter) {
        vec2_copy(output, (vec2){i, j});
        return true;
      }
    }
  }
  output = NULL;

  return false;
}

static inline void print_string(const char* string) {
  assert(string != NULL);
  printf("%s", string);
}

static inline void print_stringln(const char* string) {
  assert(string != NULL);
  printf("%s\n", string);
}

static inline void print_array_of_strings(size_t size, const char* string[size]){
  assert(string != NULL);
  for (uint32_t i = 0; i < size; i++) {
    printf("%s\n", string[i]);
  }
}

static inline int string_to_num(const char* string){
  int temp_num;

  for (int i = 0; i < strlen(string); i++){
    temp_num = string[i] ;
  };

  return 0;
}

static inline const char* concat_char_to_string(char character, char* string){
  size_t len = strlen(string);

  char* new_string = malloc(len + 1 + 1);

  strcpy(new_string, string);
  new_string[len] = character;
  new_string[len + 1] = '\0';

  return new_string;
}

static inline int numlen(int num) {
  if (num == 0)
    return 1;

  return floor(log10(abs(num))) + 1;
}

static inline int numlen_fast(int num) {
    if (num >= 1000000000) return 10;
    if (num >= 100000000)  return 9;
    if (num >= 10000000)   return 8;
    if (num >= 1000000)    return 7;
    if (num >= 100000)     return 6;
    if (num >= 10000)      return 5;
    if (num >= 1000)       return 4;
    if (num >= 100)        return 3;
    if (num >= 10)         return 2;
    return 1;
}

static inline char* reverse_string (char* string) {
    for (int j = 0, k = strlen(string) - 1; j < k; j++, k--) {
        char temp = string[j];
        string[j] = string[k];
        string[k] = temp;
    }
  return string;
};

static inline char* int_to_string(int num) {
    if (num == 0) {
      return "0";
    }

    int i = 0;
    char* string_copy = (char*)malloc(numlen_fast(num) + 1);
    int sign = num;

    if (num < 0)
        num = -num;

    while (num > 0) {
        string_copy[i++] = num % 10 + '0';
      	num /= 10;
    }

    if (sign < 0) {
        string_copy[i++] = '-';
    }

    string_copy[i] = '\0';

  reverse_string(string_copy);

  return string_copy;
}

static inline void assign_string(char* string_to_be_assigned, char* string_to_assign){
  string_to_be_assigned = (char*)realloc(string_to_be_assigned, strlen(string_to_assign));
  for (int i = 0; i < strlen(string_to_assign); i++) {
    string_to_be_assigned[i] = string_to_assign[i];
  }
}
