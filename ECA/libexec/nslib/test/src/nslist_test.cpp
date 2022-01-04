/* Tests for nslist */
#include <nslist>

// additional headers
#include <stdio.h>

int main() {
    list<int> mylist = {1, 2, 3, 4};
    mylist.insert(4, 1);
    int * myarray = (int*)mylist.to_array();

    for (int i=0; i<mylist.count(); i++) {
        printf("%i, ", myarray[i]);
    } printf("\n");

    printf("done\n");

    return 0;
}
