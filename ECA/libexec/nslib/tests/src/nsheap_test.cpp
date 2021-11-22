/* Tests for nsheap */
#define NS_DEBUG
#include <xnsmem0>

// additional headers
#include <stdio.h>

using nstd::nsmalloc;
using nstd::nsfree;

int * test(const long long size) {
    printf("mallocing\n");
    int * intarr = (int *)nsmalloc(sizeof(int) * size);
    printf("setting\n");

    for (int i=0; i<size; i++) {
        intarr[i] = i*2;
    }

    printf("printing\n");
    for (int i=0; i<size; i++) {
        printf("%i, ", intarr[i]);
    } printf("\n");

    return intarr;
}

int main() {

    int * intarr = test(5);
    nsfree(intarr);

    intarr = test(10);
    nsfree(intarr);

    printf("done\n");

    return 0;
}
