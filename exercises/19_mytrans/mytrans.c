// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
  char *start = str;
  while (*start && isspace((unsigned char)*start)) {
    start++;
  }
  if (*start == '\0') {
    *str = '\0';
    return;
  }
  char *end = start + strlen(start) - 1;
  while (end > start && isspace((unsigned char)*end)) {
    end--;
  }
  *(end + 1) = '\0';
  if (start != str) {
    memmove(str, start, end - start + 2);
  }
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};

  while (fgets(line, sizeof(line), file) != NULL) {
    trim(line);
    if (line[0] == '#' && line[1] != '\0') {
      strncpy(current_word, line + 1, sizeof(current_word) - 1);
      current_word[sizeof(current_word) - 1] = '\0';
    } else if (strncmp(line, "Trans:", 6) == 0) {
      char *translation = line + 6;
      trim(translation);
      if (current_word[0] != '\0' && translation[0] != '\0') {
        hash_table_insert(table, current_word, translation);
        (*dict_count)++;
      }
      current_word[0] = '\0';
    }
  }

  fclose(file);
  return 0;
}
