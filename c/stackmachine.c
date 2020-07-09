#include <stdio.h>
#include <stdlib.h>



struct Stack {
    int *data, cap, top;

};

void InitStack(struct Stack *s, int n) {
    s->data = malloc(n * sizeof(int));
    s->cap = n;
    s->top = 0;
}


void Push(struct Stack *s, int x) {

    if (s->top == s->cap) {
        int n = 2 * s->cap;
        s->data = realloc(s->data, n * sizeof(int));
        s->cap *= 2;
    }

    s->data[s->top] = x;
    s->top++;
}

int  Pop(struct Stack *s) {
    s->top--;
    return s->data[s->top];
}


void ADD (struct Stack *s) {
    int a = Pop(s);
    int b = Pop(s);
    Push(s,a+b);
}

void SUB (struct Stack *s) {
    int a = Pop(s);
    int b = Pop(s);
    Push(s, a - b);
}

void MUL (struct Stack *s) {
    int a = Pop(s);
    int b = Pop(s);
    Push(s, a * b);
}

void DIV (struct Stack *s) {
    int a = Pop(s);
    int b = Pop(s);
    Push(s, a / b);
}

void MAX (struct Stack *s) {
    int a = Pop(s);
    int b = Pop(s);
    int max = a;
    if (a < b) max = b;
    Push(s, max);
}

void MIN (struct Stack *s) {
    int a = Pop(s);
    int b = Pop(s);
    int min = a;
    if (a > b) min = b;
    Push(s, min);
}

void NEG (struct Stack *s) {
    int a = Pop(s);
    Push(s, -a);
}

void DUP (struct Stack *s) {
    int a = Pop(s);
    Push(s, a);
    Push(s, a);
}

void SWAP (struct Stack *s) {
    int a = Pop(s);
    int b = Pop(s);
    Push(s, a);
    Push(s, b);
}

int main() {
    int n, a;
    scanf ("%d", &n);
    struct Stack s;
    InitStack(&s, n);
    char q[5];
    for (int i = 0; i < n; i++) {
        scanf ("%s", q);
        switch (q[0]) {

            case 'C':
                scanf("%d", &a);
                Push(&s, a);
                break;

            case 'A':
                ADD(&s);
                break;

            case 'S':
                if (q[1] == 'U') SUB(&s);
                else SWAP(&s);
                break;

            case 'M':
                if (q[1] == 'U') MUL(&s);
                else {
                    if (q[1] == 'A') MAX(&s);
                    else MIN(&s);
                }
                break;

            case 'D':
                if (q[1] == 'I') DIV(&s);
                else DUP(&s);
                break;

            case 'N':
                NEG(&s);
        }
    }
    a = Pop(&s);
    printf ("%d", a);
    free(s.data);
    return 0;
}



