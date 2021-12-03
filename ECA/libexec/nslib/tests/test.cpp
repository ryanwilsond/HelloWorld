/* less formal test file */

#include <stdio.h>
#include <nsstring>
#include <nsvector>

int main() {
    vector<int> myvec = {1, 2, 3, 4};
    
    for (int i=0; i<20; i++) {
        myvec.append(i);
    }

    myvec.assign(5, 22);

    for (int i : myvec) {
        printf("%i, ", i);
    } printf("\n");

    vector<string> myvecs = {string("Hi"), string("Hello"), string("Howdy"), string("testing")};
    
    for (int i=0; i<20; i++) {
        myvecs.append(string("testing_"));
    }

    myvecs.assign(5, string("Test"));

    for (string i : myvecs) {
        printf("%s, ", i);
    } printf("\n");

    return 0;
}
