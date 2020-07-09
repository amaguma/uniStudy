#include <stdio.h>
#include <stdlib.h>

typedef struct Choto {
    int k, v;
} Choto;

typedef struct Queue {
    struct Choto *heap;
    int count;
} Queue;

int Max (int a, int b) {
    return (a > b) ? 1 : 0;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap1(Choto *a, Choto *b) {
    Choto tmp = *a;
    *a = *b;
    *b = tmp;
}


void InitPriorityQueue (Queue *q, int n) {
    q->heap = malloc (n * sizeof(Choto));
    q->count = 0;
}

int QueueEmpty (Queue *q) {
    return q->count == 0;
}

void Insert (Queue *q, Choto ptr) {
    int i = q->count;
    q->count = i + 1;
    q->heap[i] = ptr;
    while (i > 0  && Max(q->heap[(i - 1)/2].k, q->heap[i].k)) {
        swap1(&(q->heap[i]), &(q->heap[(i-1)/2]));
        i = (i - 1) / 2;
    }
}

void Heapify (int i, int n, Queue *p) {
    int l, r, j;
    for (;;) {
        l = 2 * i + 1,
        r = l + 1,
        j = i;
        if (l < n && Max(p->heap[i].k,p->heap[l].k))
            i = l;
        if (r < n && Max(p->heap[i].k,p->heap[r].k))
            i = r;
        if (i == j)
            break;
        swap(&(p->heap[j].k), &(p->heap[i].k));
    }
}

Choto ExtractMin(Queue *q){
    int i = 0;
    Choto ptr;
    ptr = q->heap[0];
    q->count--;
    if (q->count > 0){
        q->heap[0]=q->heap[q->count];
        Heapify(i,q->count,q);
    }
    return ptr;
}


int main  () {
    int n;
    scanf("%d", &n);
    int sum = 0;
    Queue q;
    Choto b;
    for (int i = 0; i < n; i++) {
        scanf("%d", &b.v);
        sum += b.v;
    }
    InitPriorityQueue(&q, sum);
    for (int i = 0; i < sum; i++) {
        scanf("%d", &b.k);
        Insert(&q, b);
    }
    while(!QueueEmpty(&q)) {
        printf ("%d ", ExtractMin(&q));
    }
    free(q.heap);
    return 0;
}