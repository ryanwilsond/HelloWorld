/* Tests for nsvector */
// #define NSTD_USE_STD_OVERLAY
#include <nsvector>

// additional headers
#include <stdio.h>

int main() {
    vector<int> myvector = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i=10; i<=21; i++) {
        myvector.append(i);
    }

    for (int elem : myvector) {
        printf("%i, ", elem);
    } printf("\n");

    myvector.pop();

    for (int elem : myvector) {
        printf("%i, ", elem);
    } printf("\n");

    myvector.insert(-2, 17);

    for (int elem : myvector) {
        printf("%i, ", elem);
    } printf("\n");

    printf("done\n");

    return 0;
}
