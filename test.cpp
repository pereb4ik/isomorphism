#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

int m = 10;


void print(pair<int, int> *p) {
    cout << p->first;
    cout << " ";
    cout << p->second;
    cout << "\n";
    cout.flush();
}

void Sort2(vector<pair<int, int> *> &a) {
    queue<pair<int, int> *> QUEUE;
    vector<vector<pair<int, int> * >> Q(m + 2);
    for (int i = 0; i < a.size(); ++i) {
        QUEUE.push(a[i]);
        print(a[i]);
    }
    for (int j = 2; j > 0; --j) {
        for (int l = 0; l < m; ++l) {
            Q[l].clear();
        }
        while (!QUEUE.empty()) {
            pair<int, int> *A = QUEUE.front();
            QUEUE.pop();
            if (j == 1) {
                Q[A->first].push_back(A);
                print(A);
            } else {
                Q[A->second].push_back(A);
                print(A);
            }
        }
        for (int l = 0; l <= m; ++l) {
            for (int i = 0; i < Q[l].size(); ++i) {
                QUEUE.push(Q[l][i]);
            }
            Q[l].clear();
        }
        cout << "\n";
    }
    for (int i = 0; i < a.size(); ++i) {
        a[i] = QUEUE.front();
        QUEUE.pop();
    }
}

void radixSort(vector<vector<int> *> &a) {
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i]->size(); ++j) {
            cout << (*a[i])[j];
            cout << " ";
        }
        cout << "\n";
    }
    vector<pair<int, int> *> *A;
    vector<pair<int, int> *> B;
    vector<pair<int, int>> C;
    A = &B;
    int lmax = 0;
    m = 1;
    for (int i = 0; i < a.size(); ++i) {
        lmax = max(lmax, (int) a[i]->size());
        for (int l = 0; l < a[i]->size(); ++l) {
            C.push_back(make_pair(l + 1, (*a[i])[l]));
            m = max(m, (*a[i])[l]);
        }
    }
    for (int i = 0; i < C.size(); ++i) {
        (*A).push_back(&C[i]);
    }
    m++;
    Sort2(*A);
    /*for (int i = 0; i < (*A).size(); ++i) {
        print((*A)[i]);
    }*/

    vector<vector<int>> NONEMPTY(lmax + 1);
    vector<vector<vector<int> * >> LENGTH(lmax + 1);
    for (int i = 0; i < (*A).size(); ++i) {
        int l = (*A)[i]->first;
        if (NONEMPTY[l].size() == 0 || NONEMPTY[l][NONEMPTY[l].size() - 1] != (*A)[i]->second) {
            int j = (*A)[i]->second;
            NONEMPTY[l].push_back(j);
            /*cout << "l: ";
            cout << l;
            cout << " ";
            cout << j;
            cout << "\n";
    */
        }
    }
    /*cout << "asd";
    cout << a.size();
    cout << "\n";
    */
    for (int i = 0; i < a.size(); ++i) {
        int l = a[i]->size();
        /*cout << l;
        cout << " ";
        cout << a[i]->back();
        cout << "\n";*/
        LENGTH[l].push_back(a[i]);
    }
    // sort
    deque<vector<int> *> QUEUE;
    vector<vector<vector<int> * >> Q(m + 1);
    for (int l = lmax; l > 0; --l) {
        for (int i = 0; i < LENGTH[l].size(); ++i) {
            vector<int> *A = LENGTH[l][i];
            /*cout << "asd";
            for (int j = 0; j < A->size(); ++j) {
                cout << (*A)[j];
                cout << " ";
            }
            cout << "\n";
            */
            int aij = (*A)[l - 1];
            /*cout << "aij";
            cout << aij;
            cout << "\n";*/
            Q[aij].push_back(A);
        }
        while (!QUEUE.empty()) {
            vector<int> *A = QUEUE.front();
            QUEUE.pop_front();
            int aij = (*A)[l - 1];
            /*cout << "aij";
            cout << aij;
            cout << "\n";*/
            Q[aij].push_back(A);
        }
        for (int i = 0; i < NONEMPTY[l].size(); ++i) {
            int j = NONEMPTY[l][i];
            for (int k = 0; k < Q[j].size(); ++k) {
                QUEUE.push_back(Q[j][k]);
                /*cout << Q[j][k]->back();
                cout << " b";*/
            }
            Q[j].clear();
        }
    }
    for (int i = LENGTH[0].size() - 1; i > -1; --i) {
        QUEUE.push_front(LENGTH[0][i]);
    }
    cout << "size";
    cout << QUEUE.size();

    for (int i = 0; i < a.size() && !QUEUE.empty(); ++i) {
        a[i] = QUEUE.front();
        QUEUE.pop_front();
    }
}


int main() {
    /*vector<vector<int> *> A(4);
    vector<vector<int>> B(A.size());
    for (int i = 0; i < A.size(); ++i) {
        A[i] = &B[i];
    }
    *//*A[2]->push_back(1);
    A[2]->push_back(1);
    A[2]->push_back(6);

    A[1]->push_back(2);
    A[1]->push_back(3);

    A[0]->push_back(0);

    A[3]->push_back(0);
    A[3]->push_back(2);*//*
    A[0]->push_back(0);
    A[0]->push_back(0);

    radixSort(A);
    cout << "\n";
    for (int i = 0; i < A.size(); ++i) {
        vector<int> b = *(A[i]);
        for (int j = 0; j < b.size(); ++j) {
            cout << b[j];
            cout << " ";
        }
        cout << "\n";
    }*/
    vector<pair<int, int> *> a(4);
    vector<pair<int, int>> b(4);
    b[0] = make_pair(1, 0);
    b[1] = make_pair(2, 1);
    b[2] = make_pair(3, 0);
    b[3] = make_pair(4, 0);
    for (int i = 0; i < a.size(); ++i) {
        a[i] = &b[i];
    }
    Sort2(a);
    return 0;
}