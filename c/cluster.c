#include <stdio.h>
#include <stdlib.h>

typedef struct PriorityQueue{
    int *t1;
    int *t2;
    int count;
}PriorityQueue;

void InitPriorityQueue(PriorityQueue *q, int n){
    q->t1 = malloc(n * sizeof(int));
    q->t2 = malloc(n * sizeof(int));
    q->count = 0;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int Max (int a, int b) {
    return (a > b) ? 1 : 0;
}

void Insert(PriorityQueue *q, int ptr1, int ptr2, int n) {
    int i = q->count;
    q->count++;
    q->t1[i] = ptr1;
    q->t2[i] = ptr2;
    if (i < n) {
        int sum1 = q->t1[(i - 1) / 2] + q->t2[(i - 1) / 2];
        int sum2 = q->t2[i] + q->t1[i];
        while ((i > 0) && Max(sum1, sum2)) {
            swap (&(q->t1[i]), &(q->t1[(i - 1) / 2]));
            swap (&(q->t2[i]), &(q->t2[(i - 1) / 2]));
            i = (i - 1) / 2;

        }
    } else {
        while ((i > 0) && (q->t1[(i - 1) / 2] > q->t1[i])) {
            swap (&(q->t1[i]), &(q->t1[(i - 1) / 2]));
            swap (&(q->t2[i]), &(q->t2[(i - 1) / 2]));
            i = (i - 1) / 2;
        }
    }
}

int main() {
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    int b, c;
    PriorityQueue q;
    InitPriorityQueue(&q, m);
    for(int i = 0;i < n;i++){
        scanf("%d", &b);
        scanf("%d", &c);
        Insert(&q,b,c,n);
    }
    int a[n];
    for(int i = 0; i < n; i++){
        a[i] = q.t1[i] + q.t2[i];
    }
    for(int i = n; i < m; i++){
        scanf("%d", &b);
        scanf("%d", &c);
        Insert(&q, b, c, n);
    }
    int d = 0;
    for (int i = n; i < m; i++) {
        if (a[d] > q.t1[i]) {
            a[d] += q.t2[i];
            for (int j = 0; j < n - 1; j++) {
                if (a[j] > a[j + 1]) {
                    swap(&a[j], &a[j + 1]);
                }
            }
        } else
            a[d] += q.t1[i] - a[d] + q.t2[i]; {
            for (int j = 0; j < n - 1; j++) {
                if (a[j] > a[j + 1]) {
                    swap(&a[j], &a[j + 1]);
                }
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < n; i++)
        if (sum < a[i]) {
            sum = a[i];
        } else {
            sum = a[0];
        }
    printf("%d", sum);
    free(q.t1);
    free(q.t2);
    return 0;
}
