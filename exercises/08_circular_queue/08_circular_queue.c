#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

// 初始化队列
void init_queue(Queue *q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

// 检查队列是否为空
bool is_empty(Queue *q) {
    return q->count == 0;
}

// 检查队列是否为满
bool is_full(Queue *q) {
    return q->count == MAX_PEOPLE;
}

// 入队
void enqueue(Queue *q, People p) {
    if (is_full(q)) {
        return;
    }
    q->data[q->tail] = p;
    q->tail = (q->tail + 1) % MAX_PEOPLE;
    q->count++;
}

// 出队
People dequeue(Queue *q) {
    People p = q->data[q->head];
    q->head = (q->head + 1) % MAX_PEOPLE;
    q->count--;
    return p;
}

int main() {
    Queue q;
    int total_people = 50;
    int report_interval = 5;

    // 初始化队列
    init_queue(&q);

    // 将50个人编号入队
    for (int i = 1; i <= total_people; i++) {
        People p;
        p.id = i;
        enqueue(&q, p);
    }

    // 约瑟夫环模拟：报到report_interval的人被淘汰
    while (q.count > 1) {
        // 将前 report_interval-1 个人移到队列尾部
        for (int i = 0; i < report_interval - 1; i++) {
            People p = dequeue(&q);
            enqueue(&q, p);
        }
        // 报到 report_interval 的人被淘汰
        People eliminated = dequeue(&q);
        printf("淘汰: %d\n", eliminated.id);
    }

    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}