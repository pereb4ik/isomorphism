#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>

using namespace std;


typedef vector<vector<int>> *vvil;
typedef vector<vector<int>> vvi;
typedef vector<int> vi;

vvil children, tree, L;

vvi t1, t2;
vector<int> *parent;

int n;
// m - alphabet size

void print(pair<int, int> *p) {
    cout << p->first;
    cout << " ";
    cout << p->second;
    cout << "\n";
}

void Sort2(vector<pair<int, int> *> &a) {
    queue<pair<int, int> *> QUEUE;
    int M = 1;
    for (int i = 0; i < a.size(); ++i) {
        QUEUE.push(a[i]);
        M = max(M, a[i]->first);
        M = max(M, a[i]->second);
    }
    vector<vector<pair<int, int> * >> Q(M + 1);
    for (int j = 2; j > 0; --j) {
        for (int l = 0; l < M; ++l) {
            Q[l].clear();
        }
        while (!QUEUE.empty()) {
            pair<int, int> *A = QUEUE.front();
            QUEUE.pop();
            if (j == 1) {
                Q[A->first].push_back(A);
            } else {
                Q[A->second].push_back(A);
            }
        }
        for (int l = 0; l <= M; ++l) {
            for (int i = 0; i < Q[l].size(); ++i) {
                QUEUE.push(Q[l][i]);
            }
            Q[l].clear();
        }
    }
    for (int i = 0; i < a.size(); ++i) {
        a[i] = QUEUE.front();
        QUEUE.pop();
    }
}

void radixSort(vector<pair<int, vector<int> > *> &a) {
    /*cout << "\n";
    for (int i = 0; i < a.size(); ++i) {
        vector<int> ai = a[i]->second;
        for (int j = 0; j < ai.size(); ++j) {
            cout << ai[j];
            cout << " ";
        }
        cout << "\n";
    }
    cout << "size: ";
    cout << a.size();
    cout.flush();*/
    vector<pair<int, int> *> *A;
    vector<pair<int, int> *> B;
    vector<pair<int, int>> C;
    A = &B;
    int lmax = 0;
    int m = 1;
    for (int i = 0; i < a.size(); ++i) {
        vector<int> ai = a[i]->second;
        lmax = max(lmax, (int) ai.size());
        for (int l = 0; l < ai.size(); ++l) {
            C.push_back(make_pair(l + 1, ai[l]));
            m = max(m, ai[l]);
        }
    }
    /*cout << "kek";
    cout.flush();*/
    for (int i = 0; i < C.size(); ++i) {
        (*A).push_back(&C[i]);
    }
    m++;
    Sort2(*A);
    vector<vector<int>> NONEMPTY(lmax + 1);
    vector<vector<pair<int, vector<int>> * >> LENGTH(lmax + 1);
    for (int i = 0; i < (*A).size(); ++i) {
        int l = (*A)[i]->first;
        if (NONEMPTY[l].size() == 0 || NONEMPTY[l][NONEMPTY[l].size() - 1] != (*A)[i]->second) {
            int j = (*A)[i]->second;
            NONEMPTY[l].push_back(j);
        }
    }
    for (int i = 0; i < a.size(); ++i) {
        int l = a[i]->second.size();
        LENGTH[l].push_back(a[i]);
    }
    // sort
    deque<pair<int, vector<int>> *> QUEUE;
    vector<vector<pair<int, vector<int>> * >> Q(m + 1);
    for (int l = lmax; l > 0; --l) {
        for (int i = 0; i < LENGTH[l].size(); ++i) {
            pair<int, vector<int>> *A = LENGTH[l][i];
            int aij = (*A).second[l - 1];
            Q[aij].push_back(A);
        }
        while (!QUEUE.empty()) {
            pair<int, vector<int>> *A = QUEUE.front();
            QUEUE.pop_front();
            int aij = (*A).second[l - 1];
            Q[aij].push_back(A);
        }
        for (int i = 0; i < NONEMPTY[l].size(); ++i) {
            int j = NONEMPTY[l][i];
            for (int k = 0; k < Q[j].size(); ++k) {
                QUEUE.push_back(Q[j][k]);
            }
            Q[j].clear();
        }
    }
    for (int i = LENGTH[0].size() - 1; i > -1; --i) {
        QUEUE.push_front(LENGTH[0][i]);
    }
    for (int i = 0; i < a.size(); ++i) {
        a[i] = QUEUE.front();
        QUEUE.pop_front();
    }
}

// a >= b
bool compare(pair<int, vi> a, pair<int, vi> b) {
    vi A = a.second;
    vi B = b.second;
    if (A.size() > B.size()) {
        return true;
    }
    if (B.size() > A.size()) {
        return false;
    }
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] > B[i]) {
            return true;
        }
        if (B[i] > A[i]) {
            return false;
        }
    }
    return true;
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
            (*children)[v].push_back(u);
            h = max(h, dfs(u, depth + 1));
        }
    }
    return h + 1;
}

bool rootedTreeIsomorphism(int r1, int r2) {
    //list of vert on levels
    vvi L1(n);
    vvi L2(n);

    vi p1(n);
    vi p2(n);
    p1.assign(n, -1);
    p2.assign(n, -1);

    vvi c1(n);
    vvi c2(n);

    tree = &t1;
    L = &L1;
    parent = &p1;
    children = &c1;
    int h1 = dfs(r1, 0);

    tree = &t2;
    L = &L2;
    parent = &p2;
    children = &c2;
    int h2 = dfs(r2, 0);

    if (h1 != h2) {
        return false;
    }
    /*cout << "\n";
    for (int i = 0; i < n; ++i) {
        cout << p1[i];
        cout << " ";
    }
    cout << "<-parents1\n";


    cout << "\n";
    for (int i = 0; i < n; ++i) {
        cout << p2[i];
        cout << " ";
    }
    cout << "<-parents2\n";
*/
    int h = h1;
    vi label1(n);
    vi label2(n);

    for (int v : L1[h - 1]) {
        label1[v] = 0;
        /*cout << "v: ";
        cout << v;
        cout << " ";
        cout << "0\n";*/
    }
    for (int v : L2[h - 1]) {
        label2[v] = 0;
        /*cout << "v: ";
        cout << v;
        cout << " ";
        cout << "0\n";*/
    }
    if (L1[h - 1].size() != L2[h - 1].size()) {
        return false;
    }
    vi m1(n);
    vi m2(n);
    for (int hi = h - 2; hi >= 0; hi--) {
        if (L1[hi].size() != L2[hi].size()) {
            return false;
        }

        vector<pair<int, vector<int> > *> tuples1(L1[hi].size());
        vector<pair<int, vector<int> > *> tuples2(L2[hi].size());
        vector<pair<int, vector<int> >> tt1(L1[hi].size());
        vector<pair<int, vector<int> >> tt2(L2[hi].size());

        for (int i = 0; i < L1[hi].size(); ++i) {
            tuples1[i] = &tt1[i];
            tuples2[i] = &tt2[i];
        }

        for (int i = 0; i < L1[hi].size(); ++i) {
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
        //sort(tuples1.begin(), tuples1.end(), compare);
        //sort(tuples2.begin(), tuples2.end(), compare);

        for (int i = 0, j = 0; i < L1[hi].size(); i++) {
            if (i > 0 && !equals(tuples1[i]->second, tuples1[i - 1]->second)) {
                j++;
            }
            label1[tuples1[i]->first] = j;
            /*cout << "v1: ";
            cout << tuples1[i]->first;
            cout << " ";
            cout << j;
            cout << "\n";*/
        }
        for (int i = 0, j = 0; i < L2[hi].size(); i++) {
            if (i > 0 && !equals(tuples2[i]->second, tuples2[i - 1]->second)) {
                j++;
            }
            label2[tuples2[i]->first] = j;
            /*cout << "v2: ";
            cout << tuples2[i]->first;
            cout << " ";
            cout << j;
            cout << "\n";*/
        }
        for (int i = 0; i < L1[hi].size(); ++i) {
            int v = tuples1[i]->first;
            int u = tuples2[i]->first;
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
    cin >> n;

    t1.assign(n, vector<int>());
    t2.assign(n, vector<int>());

    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v;
        cin >> u;
        v--;
        u--;
        t1[v].push_back(u);
        t1[u].push_back(v);
    }

    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v;
        cin >> u;
        v--;
        u--;
        t2[v].push_back(u);
        t2[u].push_back(v);
    }
    bool res = treeIsomorphism();
    cout << res << endl;
    return 0;
}