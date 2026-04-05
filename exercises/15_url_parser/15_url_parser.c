#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;

    const char* query_start = strchr(url, '?');
    if (query_start == NULL) {
        goto exit;
    }
    query_start++;

    char query_buf[1024];
    strncpy(query_buf, query_start, sizeof(query_buf) - 1);
    query_buf[sizeof(query_buf) - 1] = '\0';

    char* param = strtok(query_buf, "&");
    while (param != NULL) {
        char* equal_pos = strchr(param, '=');
        if (equal_pos != NULL) {
            *equal_pos = '\0';
            char* key = param;
            char* value = equal_pos + 1;
            printf("key = %s, value = %s\n", key, value);
        }
        param = strtok(NULL, "&");
    }

exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}