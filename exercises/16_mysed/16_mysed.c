#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    const char* p = cmd + 2;
    const char* delimiter = strchr(p, '/');
    if (delimiter == NULL) {
        return -1;
    }
    
    size_t old_len = delimiter - p;
    size_t new_len = strlen(delimiter + 1) - 1;
    
    *old_str = (char*)malloc(old_len + 1);
    if (*old_str == NULL) {
        return -1;
    }
    strncpy(*old_str, p, old_len);
    (*old_str)[old_len] = '\0';
    
    *new_str = (char*)malloc(new_len + 1);
    if (*new_str == NULL) {
        free(*old_str);
        *old_str = NULL;
        return -1;
    }
    strncpy(*new_str, delimiter + 1, new_len);
    (*new_str)[new_len] = '\0';

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    char* pos = strstr(str, old);
    if (pos == NULL) {
        return;
    }
    
    size_t old_len = strlen(old);
    size_t new_len = strlen(new);
    size_t suffix_len = strlen(pos + old_len);
    
    memmove(pos + new_len, pos + old_len, suffix_len + 1);
    memcpy(pos, new, new_len);
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
