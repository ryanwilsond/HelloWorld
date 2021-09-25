// can use inline assembly, also function macros
int func() -> asm(
    mov eax, 1
); // automatically returns eax

void hlt() -> asm(hlt);

int main() {
    byte 8_bit_num = 0;
    char 8_bit_num_2 = 0;

    word 16_bit_num = 0;
    short 16_bit_num_2 = 0;

    dword 32_bit_num = 0;
    int 32_bit_num_2 = 0;

    float 32_bit_float = 0;

// WOS64_ isn't defined
%ifdef WOS64_
    double 64_bit_float = 0;

    qword 64_bit_num = 0;
    long 64_bit_num = 0;
%end

    return 0;
}
