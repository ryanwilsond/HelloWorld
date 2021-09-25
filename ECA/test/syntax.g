// can use inline assembly, also function macros
int func() -> asm(
    mov eax, 1
); // automatically returns eax

void hlt() -> asm(hlt);

struct 

int main() {
    byte eight_bit_num = 0;
    char eight_bit_num_2 = 0;

    word sixteen_bit_num = 0;
    short sixteen_bit_num_2 = 0;

    dword thirtytwo_bit_num = 0;
    int thirtytwo_bit_num_2 = 0;

    float thirtytwo_bit_float = 0;

// WOS64_ isn't defined
%ifdef WOS64_
    double sixtyfour_bit_float = 0;

    qword sixtyfour_bit_num = 0;
    long sixtyfour_bit_num = 0;
%end

    return 0;
}
