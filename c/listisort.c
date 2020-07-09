#include <stdio.h>
#include <stdlib.h>

typedef struct Element {
    struct Element *prev,*next;
    int v;
}Element;

void InitDoubleLinkedList (Element *l) {
    l->v= -1000000;
    l->prev = l;
    l->next = l;
}

int Delete(Element *x) {
    Element *y, *z;
    int a = x->v;
    y = x->prev;
    z = x->next;
    y->next = z;
    z->prev = y;
    free(x);
    return a;
}

void InsertAfter (Element *x, int a, Element *y) {
    Element *z;
    z = x->next;
    y->v = a;
    y->prev=x;
    y->next = z;
    x->next->prev = y;
    x->next = y;
}


void insert (Element *x, int a) {
    Element *y = malloc(sizeof(Element));
    InsertAfter(x,a,y);
    while((y->next->v) > (y->v)) {
        int tmp = y->v;
        y->v = y->next->v;
        y->next->v = tmp;
        y=y->next;
    }
}

int main() {
    int n, i = 0;
    scanf("%d", &n);
    Element x;
    InitDoubleLinkedList(&x);
    while (i < n) {
        scanf ("%d", &x.v);
        insert(&x, x.v);
        i++;
    }
    i = 0;
    while ( i < n) {
        printf("%d ", Delete(x.prev));
        i++;
    }
        return 0;
}