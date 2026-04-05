#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

typedef struct {
    int row;
    int col;
} Position;

typedef struct {
    Position *data;
    int front;
    int rear;
    int capacity;
} Queue;

void queue_init(Queue *q, int capacity) {
    q->data = (Position *)malloc(sizeof(Position) * capacity);
    q->front = 0;
    q->rear = 0;
    q->capacity = capacity;
}

int queue_is_empty(Queue *q) {
    return q->front == q->rear;
}

void queue_push(Queue *q, Position p) {
    if ((q->rear + 1) % q->capacity != q->front) {
        q->data[q->rear] = p;
        q->rear = (q->rear + 1) % q->capacity;
    }
}

Position queue_pop(Queue *q) {
    Position p = {-1, -1};
    if (!queue_is_empty(q)) {
        p = q->data[q->front];
        q->front = (q->front + 1) % q->capacity;
    }
    return p;
}

void queue_free(Queue *q) {
    free(q->data);
}

int is_valid(int row, int col, int visited[MAX_ROW][MAX_COL]) {
    return row >= 0 && row < MAX_ROW && 
           col >= 0 && col < MAX_COL && 
           maze[row][col] == 0 && 
           !visited[row][col];
}

int main(void)
{
    int visited[MAX_ROW][MAX_COL];
    memset(visited, 0, sizeof(visited));
    
    int parent_row[MAX_ROW][MAX_COL];
    int parent_col[MAX_ROW][MAX_COL];
    memset(parent_row, -1, sizeof(parent_row));
    memset(parent_col, -1, sizeof(parent_col));
    
    Queue queue;
    queue_init(&queue, MAX_ROW * MAX_COL);
    
    Position start = {0, 0};
    Position end = {MAX_ROW - 1, MAX_COL - 1};
    
    queue_push(&queue, start);
    visited[start.row][start.col] = 1;
    
    int found = 0;
    int directions[4][2] = {{0, 1}, {-1, 0}, {1, 0}, {0, -1}};
    
    while (!queue_is_empty(&queue)) {
        Position current = queue_pop(&queue);
        
        if (current.row == end.row && current.col == end.col) {
            found = 1;
            break;
        }
        
        for (int i = 0; i < 4; i++) {
            int new_row = current.row + directions[i][0];
            int new_col = current.col + directions[i][1];
            
            if (is_valid(new_row, new_col, visited)) {
                visited[new_row][new_col] = 1;
                parent_row[new_row][new_col] = current.row;
                parent_col[new_row][new_col] = current.col;
                Position next = {new_row, new_col};
                queue_push(&queue, next);
            }
        }
    }
    
    if (found) {
        Position path[MAX_ROW * MAX_COL];
        int path_count = 0;
        
        Position cur = end;
        while (cur.row != -1 && cur.col != -1) {
            path[path_count++] = cur;
            int pr = parent_row[cur.row][cur.col];
            int pc = parent_col[cur.row][cur.col];
            cur.row = pr;
            cur.col = pc;
        }
        
        for (int i = 0; i < path_count; i++) {
            printf("(%d, %d)\n", path[i].row, path[i].col);
        }
    } else {
        printf("No path!\n");
    }
    
    queue_free(&queue);

	return 0;
}