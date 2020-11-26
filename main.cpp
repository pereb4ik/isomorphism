#include <iostream>

using namespace std;

struct NodeT {
    // x - key
    // y - priority
    int x, y;
    NodeT *l;
    NodeT *r;
};

typedef NodeT *Node;

Node makeNode(int x, int y) {
    NodeT *t = (NodeT *) malloc(sizeof(NodeT));
    t->x = x;
    t->y = y;
    return t;
}

Node root;

pair<Node, Node> split(Node t, int k) {
    if (t == NULL) {
        return make_pair((Node) NULL, (Node) NULL);
    }
    if (k < t->x) {
        pair<Node, Node> L = split(t->l, k);
        t->l = L.second;
        L.second = t;
        return L;
    } else {
        pair<Node, Node> R = split(t->r, k);
        t->r = R.first;
        R.first = t;
        return R;
    }
}

Node merge(Node a, Node b) {
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;
    if (a->y < b->y) {
        b->l = merge(a, b->l);
        return b;
    } else {
        a->r = merge(a->r, b);
        return a;
    }
}

void add(Node v) {
    pair<Node, Node> n = split(root, v->x);
    root = merge(merge(n.first, v), n.second);
}

void remove(int k) {
    pair<Node, Node> n = split(root, k - 1);
    n.second = split(n.second, k).second;
    root = merge(n.first, n.second);
}

void print(Node v) {
    if (v != NULL) {
        cout << v->x;
        cout << " ";
        cout << v->y;
        cout << "\n";
        print(v->l);
        print(v->r);
    }
}

pair<pair<int, int>, bool> check(Node v) {
    if (v != NULL) {
        bool good = true;
        // min and max x in subtree of v
        pair<int, int> X = make_pair(v->x, v->x);
        if (v->l != NULL) {
            good = good && (v->l->y < v->y);
            pair<pair<int, int>, bool> L = check(v->l);
            good = good && L.second;
            good = good && L.first.second < v->x;
            X.first = min(X.first, L.first.first);
            X.second = max(X.second, L.first.second);
        }
        if (v->r != NULL) {
            good = good && (v->r->y < v->y);
            pair<pair<int, int>, bool> R = check(v->r);
            good = good && R.second;
            good = good && R.first.first > v->x;
            X.first = min(X.first, R.first.first);
            X.second = max(X.second, R.first.second);
        }
        return make_pair(X, good);
    }
}

int main() {
    srand(1234);
    int n = 1000;
    Node arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = makeNode(rand(), rand());
        add(arr[i]);
        cout << (check(arr[i]).second ? "good" : "bad");
        cout << "\n";
    }
    cout << "Start deleting\n";
    for (int i = n - 1; i > -1; --i) {
        //cout << arr[i]->x;
        //cout << " :x\n";
        //print(root);
        remove(arr[i]->x);
        cout << (check(arr[i]).second ? "good" : "bad");
        cout << "\n";
        free(arr[i]);
    }
    return 0;
}