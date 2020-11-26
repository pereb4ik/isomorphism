#include <stdlib.h>

typedef struct STnode *link;

typedef int *Item;

typedef char *Key;

static Item NULLItem = (int *) 0;

struct STnode {
    Item item;
    link next;
};

static link head, z;
static int N;

int eq(Item a, Item b) {
    return 0;
}

static link NEW(Item item, link next) {
    link x = malloc(sizeof *x);
    x->item = item;
    x->next = next;
    return x;
}

int STcount() {
    return N;
}

Item searchR(link t, Key v) {
    if (t == z) {
        return NULLItem;
    }
    if (eq(t->item, v)) {
        return 0;
    }
}


Key key(Item item) {
    return NULL;
}

int hash(Key v, int M) {
    return 0;
}

static link *heads, z;

static int N, M;

void STinit(int max) {
    N = 0;
    M = max / 5;
    heads = malloc(M * sizeof(link));
    z = NEW(NULLItem, NULL);
    for (int i = 0; i < M; ++i) {
        heads[i] = z;
    }
}

Item STSearch(Key v) {
    return searchR(heads[hash(v, M)], v);
}

void STinsert(Item item) {
    int i = hash(key(item), M);
    heads[i] = NEW(item, heads[i]);
    N++;
}


int main() {

    return 0;
}