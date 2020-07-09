#include <stdio.h>
#include <stdlib.h>


struct Elem {
    int max, elem;
};
struct Stack {
    struct Elem *data;
    int cap, top1, top2;
};

int max (int a, int b) {
    int max = a;
    if (a < b) {
        max = b;
    }
    return max;
}


void InitDoubleStack(struct Stack *s, int n) {
    s->data = malloc(n * sizeof(struct Elem));
    s->cap = n;
    s->top1 = 0;
    s->top2 = n - 1;
}

int StackEmpty1(struct Stack *s) {
    return s->top1 <= 0;
}

int StackEmpty2(struct Stack *s) {
    return s->top2 == (s->cap - 1);
}

void Push1 (struct Stack *s, int x) {
//    if (s->top2 < s->top1) {
//        int n = 2 * s->cap;
//        s->data = realloc(s->data, n * sizeof(int));
//        s->c0ap *= 2;
//    }
    if (StackEmpty1(s))
        s->data[s->top1].max = x;
    else {
        s->data[s->top1].max = max(x, s->data[s->top1 - 1].max);
    }

    s->data[s->top1].elem = x;
    s->top1++;
}

void Push2 (struct Stack *s, int x) {
//    if (s->top2 < s->top1) {
//        int n = 2 * s->cap;
//        s->data = realloc(s->data, n * sizeof(int));
//        s->cap *= 2;
//    }
    if (StackEmpty2(s))
        s->data[s->top2].max = x;
    else {
        s->data[s->top2].max = max(x, s->data[s->top2 + 1].max);
    }

    s->data[s->top2].elem = x;
    s->top2--;
}

struct Elem Pop1 (struct Stack *s) {
    s->top1--;
    return s->data[s->top1];
}

struct Elem Pop2(struct Stack *s) {
    s->top2++;
    return s->data[s->top2];
}

void InitQueueOnStack (struct Stack *s, int n) {
    InitDoubleStack(s, n);
}

int QueueEmpty (struct Stack *s) {
    return StackEmpty1(s) && StackEmpty2(s);
}

void Enqueue (struct Stack *s, int x) {
    Push1 (s, x);
    //printf("%d", s->data[s->top1 - 1].elem);
}

int Dequeue (struct Stack *s) {
    if (StackEmpty2(s)) {
        while (!(StackEmpty1(s))) {

            //printf("kek\n");
            Push2(s, Pop1(s).elem);
        }
    }
    return Pop2(s).elem;
}

int Maximum (struct Stack *s) {
    if (StackEmpty1(s))
        return s->data[s->top2 + 1].max;
    else {
        if (StackEmpty2(s))
            return s->data[s->top1 - 1].max;
        else {
            return max(s->data[s->top1 - 1].max, s->data[s->top2 + 1].max);
        }
    }
}

int main() {
    int n, a;
    scanf("%d", &n);
    struct Stack s;
    InitQueueOnStack(&s, 100000);
    char q[6];
    for (int i = 0; i < n; i++) {
        scanf("%s", q);
        switch (q[0]) {

            case 'E':
                if (q[1] == 'N') {
                    scanf("%d", &a);
                    Enqueue(&s, a);
                } else {
                    a = QueueEmpty(&s);
                    if (a) printf("true\n");
                    else printf("false\n");
                }
                break;

            case 'D':
                a = Dequeue(&s);
                printf("%d\n", a);
                break;

            case 'M':
                a = Maximum(&s);
                printf("%d\n", a);
                break;

        }
    }
    free(s.data);
    return 0;
}