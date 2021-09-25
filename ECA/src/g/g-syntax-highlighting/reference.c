#define func __asm__("movl $1, eax")

#define hlt __asm__("hlt")

int main() {
    char eight_bit_num = 0;
    short sixteen_bit_num = 0;
    int thirtytwo_bit_num = 0;
    float thirtytwo_bit_float = 0;

#ifdef _WIN64
    long sixtyfour_bit_num = 0;
    double sixtyfour_bit_float = 0;
#endif

    return 0;
}
