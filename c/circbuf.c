#include <stdio.h>
#include <stdlib.h>


struct Queue {
    int *data, count, head, tail, cap;

};

void InitQueue(struct Queue *q, int n) {
    q->data = malloc(n * sizeof(int));
    q->cap = n;
    q->count = 0;
    q->head = 0;
    q->tail = 0;
}

int QueueEmpty (struct Queue *q) {
    return q->count == 0;
}

void Enqueue (struct Queue *q, int x) {
    if (q->count == q->cap) {
        int n = 2 * q->cap;
        q->data = realloc(q->data, n * sizeof(int));
        q->cap *= 2;
    }
    q->data[q->tail] = x;
    q->tail++;
    if (q->tail == q->cap) {
        q->tail = 0;
    }
    q->count++;
}

int Dequeue (struct Queue *q) {
    int x = q->data[q->head];
    q->head++;
    if (q->head == q->cap) {
        q->head = 0;
    }
    q->count--;
    return x;
}

int main() {
    int n, a, x;
    scanf("%d", &n);
    struct Queue q;
    InitQueue(&q, n);
    char s[5];
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        if (s[0] == 'D') {
            x = Dequeue(&q);
            printf("%d\n", x);
        } else {
            if (s[1] == 'N') {
                scanf("%d", &a);
                Enqueue(&q, a);
            } else {
                x = QueueEmpty(&q);
                if (x) printf("true\n");
                else printf("false\n");
            }
        }
    }
    free(q.data);
    return 0;
}



