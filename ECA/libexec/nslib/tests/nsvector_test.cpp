// Tests for nsvector
#include <nsvector>

// additional headers
#include <stdio.h>

int main() {
    vector<int> myvector = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i=10; i<=21; i++) {
        myvector.append(i);
    }

    myvector.pop();
    myvector.insert(17, -2);

    for (int i=0; i<myvector.size(); i++) {
        printf("%i, ", myvector[i]);
    } printf("\n");

    return 0;
}
