#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 16 LRU 缓存淘汰算法（哈希表 + 双向链表）
 *  - put(k,v)、get(k) 均为 O(1)
 *  - 容量满时淘汰最久未使用（LRU）的元素
 */

typedef struct LRUNode {
    int key;
    int value;
    struct LRUNode* prev;
    struct LRUNode* next;
} LRUNode;

typedef struct HashEntry {
    int key;
    LRUNode* node;
    struct HashEntry* next;
} HashEntry;

typedef struct {
    int capacity;
    int size;
    LRUNode* head; /* 最近使用（MRU） */
    LRUNode* tail; /* 最久未使用（LRU） */
    /* 简单链式哈希表 */
    size_t bucket_count;
    HashEntry** buckets;
} LRUCache;

static unsigned hash_int(int key) {
    unsigned ukey = (unsigned)key;
    return ukey * 2654435761u;
}

static HashEntry* hash_find(LRUCache* c, int key, HashEntry*** pprev_next) {
    size_t idx = hash_int(key) % c->bucket_count;
    HashEntry** prev_next = &c->buckets[idx];
    HashEntry* cur = c->buckets[idx];

    while (cur) {
        if (cur->key == key) {
            if (pprev_next) {
                *pprev_next = prev_next;
            }
            return cur;
        }
        prev_next = &cur->next;
        cur = cur->next;
    }

    if (pprev_next) {
        *pprev_next = prev_next;
    }
    return NULL;
}

static void list_add_to_head(LRUCache* c, LRUNode* node) {
    node->prev = NULL;
    node->next = c->head;

    if (c->head) {
        c->head->prev = node;
    }
    c->head = node;

    if (c->tail == NULL) {
        c->tail = node;
    }
}

static void list_remove(LRUCache* c, LRUNode* node) {
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        c->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        c->tail = node->prev;
    }

    node->prev = NULL;
    node->next = NULL;
}

static void list_move_to_head(LRUCache* c, LRUNode* node) {
    if (node == c->head) {
        return;
    }
    list_remove(c, node);
    list_add_to_head(c, node);
}

static LRUNode* list_pop_tail(LRUCache* c) {
    LRUNode* node = c->tail;

    if (node == NULL) {
        return NULL;
    }

    list_remove(c, node);
    return node;
}

/* LRU 接口实现 */
static LRUCache* lru_create(int capacity) {
    LRUCache* c;

    if (capacity <= 0) {
        return NULL;
    }

    c = (LRUCache*)calloc(1, sizeof(LRUCache));
    if (c == NULL) {
        return NULL;
    }

    c->capacity = capacity;
    c->bucket_count = (size_t)capacity * 2u + 1u;
    c->buckets = (HashEntry**)calloc(c->bucket_count, sizeof(HashEntry*));
    if (c->buckets == NULL) {
        free(c);
        return NULL;
    }

    return c;
}

static void lru_free(LRUCache* c) {
    size_t i;

    if (c == NULL) {
        return;
    }

    for (i = 0; i < c->bucket_count; i++) {
        HashEntry* entry = c->buckets[i];
        while (entry) {
            HashEntry* next = entry->next;
            free(entry);
            entry = next;
        }
    }

    while (c->head) {
        LRUNode* next = c->head->next;
        free(c->head);
        c->head = next;
    }

    free(c->buckets);
    free(c);
}

static int lru_get(LRUCache* c, int key, int* out_value) {
    HashEntry* entry;

    if (c == NULL) {
        return 0;
    }

    entry = hash_find(c, key, NULL);
    if (entry == NULL) {
        return 0;
    }

    list_move_to_head(c, entry->node);
    if (out_value) {
        *out_value = entry->node->value;
    }
    return 1;
}

static void lru_put(LRUCache* c, int key, int value) {
    HashEntry** prev_next;
    HashEntry* entry;

    if (c == NULL) {
        return;
    }

    entry = hash_find(c, key, &prev_next);
    if (entry) {
        entry->node->value = value;
        list_move_to_head(c, entry->node);
        return;
    }

    if (c->size >= c->capacity) {
        LRUNode* victim = list_pop_tail(c);
        if (victim) {
            HashEntry** victim_prev_next;
            HashEntry* victim_entry = hash_find(c, victim->key, &victim_prev_next);
            if (victim_entry) {
                *victim_prev_next = victim_entry->next;
                free(victim_entry);
            }
            free(victim);
            c->size--;
        }
    }

    {
        LRUNode* node = (LRUNode*)malloc(sizeof(LRUNode));
        HashEntry* new_entry;

        if (node == NULL) {
            return;
        }

        new_entry = (HashEntry*)malloc(sizeof(HashEntry));
        if (new_entry == NULL) {
            free(node);
            return;
        }

        node->key = key;
        node->value = value;
        node->prev = NULL;
        node->next = NULL;
        list_add_to_head(c, node);

        new_entry->key = key;
        new_entry->node = node;
        new_entry->next = NULL;

        *prev_next = new_entry;
        c->size++;
    }
}

/* 打印当前缓存内容（从头到尾） */
static void lru_print(LRUCache* c) {
    LRUNode* p = c->head;
    int first = 1;
    while (p) {
        if (!first) printf(", ");
        first = 0;
        printf("%d:%d", p->key, p->value);
        p = p->next;
    }
    printf("\n");
}

int main(void) {
    /* 容量 3：put(1,1), put(2,2), put(3,3), put(4,4), get(2), put(5,5) */
    LRUCache* c = lru_create(3);
    if (!c) {
        fprintf(stderr, "创建 LRU 失败\n");
        return 1;
    }

    lru_put(c, 1, 1); /* 缓存：1 */
    lru_put(c, 2, 2); /* 缓存：2,1 */
    lru_put(c, 3, 3); /* 缓存：3,2,1 (满) */
    lru_put(c, 4, 4); /* 淘汰 LRU(1)，缓存：4,3,2 */

    int val;
    if (lru_get(c, 2, &val)) {
        /* 访问 2：缓存：2,4,3 */
        (void)val; /* 演示无需使用 */
    }

    lru_put(c, 5, 5); /* 淘汰 LRU(3)，缓存：5,2,4 */

    /* 期望最终键集合：{2,4,5}，顺序无关。此处按最近->最久打印：5:5, 2:2, 4:4 */
    lru_print(c);

    lru_free(c);
    return 0;
}
