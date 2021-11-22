/* less formal test file */

#include <stdio.h>


    inline long long ceil(long double _Float)
    {
    long long _Floor = (long long)_Float;

    if (_Floor == _Float)
        {
        return _Floor;
        }

    return _Floor + 1;
    }

int main() {
    float num = 3.0;
    float num2 = 3.1;
    float num3 = 3.9;

    printf("%i, %i, %i\n", ceil(num), ceil(num2), ceil(num3));

    return 0;
}
