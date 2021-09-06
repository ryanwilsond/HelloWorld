.start _start

.data

struc GDTType
    PR      bits 1 ?    ; Present - set to 1 if a valid segment
    PRIVL   bits 2 ?    ; Privlage - kernel = 0, user = 3
    S       bits 1 ?    ; Type - code/data = 1, else 0
    EX      bits 1 ?    ; Executable - 1 if executable i.e. code segment, else 0
    RW      bits 1 ?    ; Read/Write - If a code segment 1 if readable; If a data segment 1 if writeable
    AC      bits 1 0    ; Accessed - CPU will set this to 1 when being accessed
    res     bits 1 0    ; Reserved
endstruc GDTType

struc GDTEntry
    base    dword   ?
    limit   bits 24 ?
    type    GDTType ?
endstruc GDTEntry

struc IDTType
    PR  bits 1 ?        ; Present - set to 0 for unused interrupts
    DPL bits 2 ?        ; Descriptor Privlage - what privlage the called descriptor entry should have
    S   bits 1 ?        ; Type - interrupt/trap = 0, else 1
    GT  bits 3 ?        ; Gate Type - 32-bit task gate=0, 16-bit interrupt gate=1, 16-bit trap gate=2, 32-bit interrupt gate=3, 32-bit trap gate=4
                        ; fault=5, abort=6
    res bits 1 0        ; Reserved
endstruc IDTType

struc IDTEntry
    offset      dword   ?
    selector    word    ?
    type        IDTType ?
endsrtuc IDTEntry

struc flagDesc
    res word 0          ; Reserved
    res byte 0          ; Reserved
    CF bits 1 ?         ; Carry flag
    PF bits 1 ?         ; Parity flag
    ZF bits 1 ?         ; Zero flag
    SF bits 1 ?         ; Sign flag
    TF bits 1 ?         ; Trap flag - Single step
    IF bits 1 ?         ; Interrupt enable
    IOPL bits 2 ?       ; I/O Privlage - kernel = 0, user = 3
endstruc flagDesc

.text

_start:
    ; privlage level is currently 0
    ; disabling interrupts for setup process
    xor eax, eax

    pushf
    pop al
    and al, 0b11111011
    push al
    popf

    ; setup gdt & idt
    mov cs, 0x08
    mov ds, 0x10
    mov ss, 0x18
    mov es, 0x20
    mov fs, 0x20
    mov gs, 0x20

    xor eax, eax
    xor ebx, ebx

    mov eax, gdt        ; base
    sal eax, 8          ; shift 2 bytes left
    mov ebx, gs         ; fill 2 bytes with last segment value (limit)
    add eax, ebx
    add eax, 8          ; plus 8 to account for the last segment width
    lgdt eax

    lidt idt            ; just takes a location because the idt is always 256 entries

    xor eax, eax
    ; enabling interrupts
    pushf
    pop al
    or al, 0b00000100
    push al
    popf

    ; jumping to code segment
    jmp cs:0

gdt:
    dq GDTEntry {0x00000000, 0x00000000, {0b0, 0b00, 0b0, 0b0, 0b0}}        ; base segment
    dq GDTEntry {0x00000200, 0x00000200, {0b1, 0b00, 0b1, 0b1, 0b1}}        ; code segment
    dq GDTEntry {0x00000400, 0x00000200, {0b1, 0b00, 0b1, 0b0, 0b1}}        ; data segment
    dq GDTEntry {0x00000600, 0x00000200, {0b1, 0b00, 0b0, 0b0, 0b0}}        ; stack segment
    dq GDTEntry {0x00000800, 0x00000200, {0b1, 0b00, 0b0, 0b1, 0b0}}        ; task state segment

idt:
    ; 101 = fault
    ; 100 = trap
    ; 011 = interrupt
    ; 110 = abort
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b101}}                    ; Divide-by-zero Error
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b100}}                    ; Debug
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b011}}                    ; Non-maskable Interrupt
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b100}}                    ; Breakpoint
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b100}}                    ; Overflow
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b011}}                    ; Bound-range Exceeded
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b011}}                    ; Invalid Opcode
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b011}}                    ; Device Not Available
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b110}}                    ; Double Fault
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b011}}                    ; Invalid TSS
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b011}}                    ; Segment Not Present
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b011}}                    ; Stack-Segment Fault
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b011}}                    ; General Protection Fault
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b011}}                    ; Page Fault
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b011}}                    ; Floating-Point Exception
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b011}}                    ; Alignment Check
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b110}}                    ; Machine Check
    dq IDTEntry {0x00000150, 0x0080, {0b1, 0b00, 0b011}}                    ; Virtualization Exception
    .times (32-18) dq IDTENtry {0x00000150, 0x0080, {0b0, 0b00, 0b011}}     ; res
    .times (256-32) dq IDTEntry {0x00000100, 0x0080, {0b1, 0b00, 0b011}}    ; all other interrupts go to cs:100h
