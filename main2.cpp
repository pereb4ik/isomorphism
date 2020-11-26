#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

#define ll long long

ll gcd(ll a, ll b) {
    if(b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

double max(double a) {
    return a;
}

template<class P, class... T>
auto max(P x, T... y) {
    double m = max(y...);
    if (m > x) {
        return m;
    } else {
        return x;
    }
}

/*double (*sum(double (*f)(double, double)))(double) {
    double (*g)(double) = [](double x) {
        double sum = 0.0;
        for (int i = 0; i < 100; ++i) {
            //sum += f(x, 1.0 * i);
        }
        return sum / 100;
    };
    //return g;
}*/


double fold(double (*f)(double, double), double *A, int n) {
    double val = f(A[n - 2], A[n - 1]);
    for (int i = n - 3; i > -1; --i) {
        val = f(A[i], val);
    }
    return val;
}

vector<vector<void>> reverse(vector<vector<void>> A) {
    vector<vector<void>> B;
    for (int i = 1; i < A.size(); ++i) {
        B.push_back(A[i]);
    }
    if (A.size() > 0) {
        B.push_back(A[0]);
    }
    return B;
}


int main() {
    srand(1);
    double A[100];
    for (int i = 0; i < 100; ++i) {
        double a = (double) rand() / ((double) RAND_MAX + 1);
        a = a * 1.5 + 0.5;
        A[i] = a;
    }
    cout << fold([](double a, double b) {
        return a + b;
    }, A, 100);
    cout << "\n";
    cout << fold([](double a, double b) {
        return a * b;
    }, A, 100);
    return 0;
}
