#include <stdio.h>

int main() {
    char source[] = "Hello, World! This is a test string for my_strcpy function.\n";
    char destination[101];
    
    // 使用指针实现字符串拷贝
    char *src = source;
    char *dst = destination;
    while (*src != '\0') {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';  // 添加字符串结束符
    
    printf("拷贝后的字符串: %s", destination);
    
    return 0;
}