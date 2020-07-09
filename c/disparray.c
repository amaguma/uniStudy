#include <stdio.h>
#include <stdlib.h>
typedef struct elem elem;
struct elem{
    int k;
    int v;
    elem* next;
};
elem* Init(int k,int v){
    elem *x = malloc(sizeof(elem));
    x->k = k;
    x->v = v;
    x->next = NULL;
    return x;
}

elem* Push(elem *x, elem *y){
    y->next = x;
    return y;
}
elem * Search(elem *x , int k){
    elem *y = x;
    while(!(x == NULL || x->k == k)){
        x = x->next;
    }
    return x;
}


int Lookup(elem **t, int m, int k){
    elem *p = Search(t[k % m ],k);
    if(NULL == p)return 0;
    return p->v;
}

void Freeelem(elem *t){
    elem *x = t;
    while(NULL != t){
        t = t->next;
        free(x);
        x = t;
    }
}


int main(){
    int n,m,k,v;
    scanf("%d", &n);
    scanf("%d", &m);
    elem **t=calloc(m,sizeof(elem*));
    for(int i = 0 ; i < n ; i++){
        char str[10];
        scanf("%s", str);
        if(!(str[1] == 'S')){
            scanf("%d", &k);
            printf("%d\n", Lookup(t,m,k));
        }
        else{
            scanf("%d %d", &k,&v);
            t[k % m] = Push(t[k % m],Init(k,v));
        }
    }
    int i=0;
    while(i<m){
        Freeelem(t[i]);
        i++;
    }
    free(t);
    return 0;
}
