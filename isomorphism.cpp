#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

typedef vector<vector<int>> *vvil;
typedef vector<vector<int>> vvi;
typedef vector<int> vi;

vvil tree, L;

vvi t1, t2;
vector<int> *parent;
vvi L1, L2;
vi p1, p2;

int n;

// Lexicographic sort of 2-tuples
void sort2(vector<pair<int, int> *> &a) {
    queue<pair<int, int> *> QUEUE;
    int M = 1;
    for (int i = 0; i < a.size(); ++i) {
        QUEUE.push(a[i]);
        M = max(M, a[i]->first);
        M = max(M, a[i]->second);
    }
    vector<queue<pair<int, int> * >> Q(M + 1);
    for (int j = 2; j > 0; --j) {
        while (!QUEUE.empty()) {
            pair<int, int> *A = QUEUE.front();
            QUEUE.pop();
            if (j == 1) {
                Q[A->first].push(A);
            } else {
                Q[A->second].push(A);
            }
        }
        for (int l = 0; l <= M; ++l) {
            while (!Q[l].empty()) {
                QUEUE.push(Q[l].front());
                Q[l].pop();
            }
        }
    }
    for (int i = 0; i < a.size(); ++i) {
        a[i] = QUEUE.front();
        QUEUE.pop();
    }
}

// Lexicographic sort of variety tuples
void radixSort(vector<pair<int, vector<int> > *> &a) {
    vector<pair<int, int>> B;
    B.reserve(a.size());
    int lmax = 0;
    int m = 1;
    for (int i = 0; i < a.size(); ++i) {
        vector<int> *ai = &(a[i]->second);
        lmax = max(lmax, (int) ai->size());
        for (int l = 0; l < ai->size(); ++l) {
            B.emplace_back(l + 1, (*ai)[l]);
            m = max(m, (*ai)[l]);
        }
    }
    vector<pair<int, int> *> A(B.size());
    for (int i = 0; i < B.size(); ++i) {
        A[i] = &B[i];
    }
    sort2(A);
    vector<queue<int>> NONEMPTY(lmax + 1);
    vector<queue<pair<int, vector<int>> * >> LENGTH(lmax + 1);
    for (int i = 0; i < A.size(); ++i) {
        int l = A[i]->first;
        if (NONEMPTY[l].empty() || NONEMPTY[l].back() != A[i]->second) {
            int j = A[i]->second;
            NONEMPTY[l].push(j);
        }
    }
    for (int i = 0; i < a.size(); ++i) {
        int l = a[i]->second.size();
        LENGTH[l].push(a[i]);
    }
    queue<pair<int, vector<int>> *> QUEUE;
    vector<queue<pair<int, vector<int>> * >> Q(m + 1);
    for (int l = lmax; l > 0; --l) {
        while (!LENGTH[l].empty()) {
            pair<int, vector<int>> *A0 = LENGTH[l].front();
            LENGTH[l].pop();
            int aij = (*A0).second[l - 1];
            Q[aij].push(A0);
        }
        while (!QUEUE.empty()) {
            pair<int, vector<int>> *A0 = QUEUE.front();
            QUEUE.pop();
            int aij = (*A0).second[l - 1];
            Q[aij].push(A0);
        }
        while (!NONEMPTY[l].empty()) {
            int j = NONEMPTY[l].front();
            NONEMPTY[l].pop();
            while (!Q[j].empty()) {
                QUEUE.push(Q[j].front());
                Q[j].pop();
            }
        }
    }
    while (!LENGTH[0].empty()) {
        QUEUE.push(LENGTH[0].front());
        LENGTH[0].pop();
    }
    for (int i = 0; i < a.size(); ++i) {
        a[i] = QUEUE.front();
        QUEUE.pop();
    }
}

bool equals(vi a, vi b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

vi findCenter() {
    int N = n;
    vi a;
    vi deg(n);
    for (int v = 0; v < n; v++) {
        deg[v] = (*tree)[v].size();
        if (deg[v] <= 1) {
            a.push_back(v);
            --N;
        }
    }
    while (N > 0) {
        vi na;
        for (int v : a) {
            for (int u : (*tree)[v]) {
                if (--deg[u] == 1) {
                    na.push_back(u);
                    --N;
                }
            }
        }
        a = na;
    }
    return a;
}

int dfs(int v, int depth) {
    (*L)[depth].push_back(v);
    int h = 0;
    for (int u : (*tree)[v]) {
        if (u != (*parent)[v]) {
            (*parent)[u] = v;
            h = max(h, dfs(u, depth + 1));
        }
    }
    return h + 1;
}

// Realization of Aho, Hopcroft and Ullman algorithm
bool rootedTreeIsomorphism(int r1, int r2) {
    //list of vert on levels
    L1.assign(n, vector<int>());
    L2.assign(n, vector<int>());

    p1.assign(n, -1);
    p2.assign(n, -1);

    tree = &t1;
    L = &L1;
    parent = &p1;
    int h1 = dfs(r1, 0);

    tree = &t2;
    L = &L2;
    parent = &p2;
    int h2 = dfs(r2, 0);

    if (h1 != h2) {
        return false;
    }

    int h = h1;
    vi label1(n);
    vi label2(n);
    if (L1[h - 1].size() != L2[h - 1].size()) {
        return false;
    }
    for (int v : L1[h - 1]) {
        label1[v] = 0;
    }
    for (int v : L2[h - 1]) {
        label2[v] = 0;
    }
    vi m1(n);
    vi m2(n);
    for (int hi = h - 2; hi >= 0; hi--) {
        if (L1[hi].size() != L2[hi].size()) {
            return false;
        }

        int lsize = L1[hi].size();
        vector<pair<int, vector<int> > *> tuples1(lsize);
        vector<pair<int, vector<int> > *> tuples2(lsize);
        vector<pair<int, vector<int> >> ts1(lsize);
        vector<pair<int, vector<int> >> ts2(lsize);

        for (int i = 0; i < lsize; ++i) {
            tuples1[i] = &ts1[i];
            tuples2[i] = &ts2[i];
        }

        for (int i = 0; i < lsize; ++i) {
            tuples1[i]->first = L1[hi][i];
            m1[tuples1[i]->first] = i;
            tuples2[i]->first = L2[hi][i];
            m2[tuples2[i]->first] = i;
        }
        for (int i = 0; i < L1[hi + 1].size(); i++) {
            int v = L1[hi + 1][i];
            int j = m1[p1[v]];
            tuples1[j]->second.push_back(label1[v]);
        }
        for (int i = 0; i < L2[hi + 1].size(); i++) {
            int v = L2[hi + 1][i];
            int j = m2[p2[v]];
            tuples2[j]->second.push_back(label2[v]);
        }

        radixSort(tuples1);
        radixSort(tuples2);

        for (int i = 0; i < lsize; ++i) {
            if (!equals(tuples1[i]->second, tuples2[i]->second)) {
                return false;
            }
        }

        for (int i = 0, j = 0; i < lsize; i++) {
            if (i > 0 && !equals(tuples1[i]->second, tuples1[i - 1]->second)) {
                j++;
            }
            label1[tuples1[i]->first] = j;
        }
        for (int i = 0, j = 0; i < lsize; i++) {
            if (i > 0 && !equals(tuples2[i]->second, tuples2[i - 1]->second)) {
                j++;
            }
            label2[tuples2[i]->first] = j;
        }
        for (int i = 0; i < lsize; ++i) {
            int v = tuples1[i]->first;
            int u = tuples2[i]->first;
            L1[hi][i] = v;
            L2[hi][i] = u;
            if (label1[v] != label2[u]) {
                return false;
            }
        }
    }

    return true;
}

bool treeIsomorphism() {
    tree = &t1;
    vector<int> c1 = findCenter();
    tree = &t2;
    vector<int> c2 = findCenter();
    if (c1.size() == c2.size()) {
        if (rootedTreeIsomorphism(c1[0], c2[0])) {
            return true;
        } else {
            if (c1.size() > 1) {
                return rootedTreeIsomorphism(c1[1], c2[0]);
            }
        }
    }
    return false;
}

int main() {
    scanf("%d", &n);

    t1.resize(n, vector<int>());
    t2.resize(n, vector<int>());

    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        scanf("%d", &v);
        scanf("%d", &u);
        v--;
        u--;
        t1[v].push_back(u);
        t1[u].push_back(v);
    }

    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        scanf("%d", &v);
        scanf("%d", &u);
        v--;
        u--;
        t2[v].push_back(u);
        t2[u].push_back(v);
    }
    bool res = treeIsomorphism();
    printf("%d\n", res);
    return 0;
}