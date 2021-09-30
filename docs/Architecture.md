# EMP-32-2000 Architecture

## Memory Organization

This CPU has 32-bit memory addressing. By default it is using a flat memory model.
The global descriptor table starts with an inital NULL entry, then each segment follows.
To load the GDT you call 'lgdt' with a 4 byte value containing info about where the first GDT entry is, and how long the GDT is.

Example:

```asssembly
mov eax, gdt ; start of gdt
sal eax, 8   ; shift over 2 bytes
add eax, 0x8 ; number of entries (1 in this example) * 8 (entry length)
lgdt eax
```

Segments are defined as follows:

```assembly
struc GDTEntryInfo
    PR      bits 1 ?    ; Present - set to 1 if valid segment
    PRIVL   bits 2 ?    ; Privlage - kernel = 0, user = 3
    S       bits 1 ?    ; Type - code/data = 1, else 0
    EX      bits 1 ?    ; Executable - 1 if code segment, else 0
    RW      bits 1 ?    ; Read/Write - If a code segment 1 means readable; If data segment 1 means writable
    AC      bits 1 0    ; Accessed - CPU will automatically set this to 1 when being accessed
    res     bits 1 0
ends GDTEntryInfo

struc GDTEntry
    base    dword        ?  ; Start location of segment
    limit   bits 24      ?  ; Size of segment
    type    GDTEntryInfo ?  ; Info about segment
ends GDTEntry
```

Each segment is 8 bytes.

Whens segmentation is enabled instructions with pointer operands use segment addressing `jmp seg:address`. If not segment is given, it defaults to near segment (current segment).

## Interrupts

The Interrupt Descriptor Table has entries similar to the GDT. When an interrupt is triggered through the CPUs I/O pins, it looks up the interrupt on the IDT and goes to the given address. Before the IDT is setup interrupts aren't handled. You can load the IDT with `lidt [DWORD PTR]idt` because there is always 256 entries for the IDT.

Each IDT entry are defined as follows:

```assembly
struc IDTEntryInfo
    PR  bits 1 ?    ; Present - set to 0 for unused interrupts
    DPL bits 2 ?    ; Descriptor Privlage - what privlage the interrupt handling segment needs
    S   bits 1 ?    ; Type - interrupt/trap = 0, else 1
    GT  bits 3 ?    ; Gate Type = 32-bit task gate=0, 16-bit interrupt gate=1, 16-bit trap gate=2, 32-bit interrupt gate=3, 32-bit trap gate=4, fault=5, abort=6
    res bits 1 0
ends IDTEntryInfo

struc IDTEntry
    offset   dword   ?  ; near address to jump to in segment
    selector word    ?  ; segment
    type     IDTType ?  ; Info about interrupt
    res      byte    0
ends IDTEntry
```

Each IDT entry is 8 bytes.

## Registers

**General Purpose Registers:**

| name | code | use |
|-|-|-|
| eax | 000 | |
| ebx | 001 | |
| ecx | 010 | |
| edx | 011 | |
| esp | 100 | stack pointer (bottom) |
| eip | 101 | instruction pointer |
| ebp | 110 | base index |
| edp | 111 | destination index |

**Status Registers:**

| name | code | use |
|-|-|-|
| cs | 000 | code segment |
| ds | 001 | data segment |
| ss | 010 | stack segment |
| es | 011 | extra segment |
| fs | 100 | extra segment |
| gs | 101 | extra segment |
| | 110 | res |
| | 111 | res |

Last two status register are reserved for extra data (debug)

### EFLAGS

The EFLAGS register is a 4 byte register with info about the current environment.

Not safe to depend on these flags having a specific value on startup.

| bit | name | meaning |
|-|-|-|
| 0 | CF   : Carry Flag | Arithmetic resulted in carry (1) |
| 1 | ZF   : Zero Flag | Arithmetic resulted in zero (1) |
| 2 | SF   : Sign Flag | Arithmetic resulted in negative (1) |
| 3 | TF   : Trap Flag | Manually set on in source code to enable single-stepping (1) |
| 4 | OF   : Overflow Flag | Arithmetic resulted in overflow (1) |
| 5 | IF   : Interrupt Enable | Interrupts get processed (1) |
| 6-7 | IOPL : I/O Privilege Level | Kernel=0, User=3 |

## Instruction Encoding

**General form:**

| Opcode | ModRM | Operand 1 | Operand 2 |
|-|-|-|-|
| 1 byte | 0 or 1 byte | 0, 1, 2, or 4 bytes | 0, 1, 2, or 4 bytes |

Most instructions follow this form.

**ModRM:**

| Mode | Register 1 | Register 2 |
|-|-|-|
| 2 bits | 3 bits (see register codes) | 3 bits |

The mode can be:

- SIB (Scaled Indexing)
- REGREG
- REGDISP
- DISPREG
- REG
- DISP
- IMM
- REGIMM
- DISPIMM

Different instructions use different groupings of these mode (at most four).
