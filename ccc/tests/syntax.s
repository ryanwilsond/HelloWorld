.include "syntax2.s"

.start _start

struc test
    name2   dword 2
    name    dword ? ; name, type, default value
ends test

_start:
    mov eax, 1

