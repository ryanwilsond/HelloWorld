[index](../InstructionReference.md)

# LGDT - Load Global Descriptor Table Register

| Opcode | Instruction | Op/En | Description |
|-|-|-|-|
| 02 | LGDT *imm32* | I | Load *imm32* into GDTR |
|

## Instruction Operand Encoding

| Op/En | Operand 1 | Operand 2 |
|-|-|-|
| I | imm32 | NA |
|

## Description

Loads the value in the source operand into the global descriptor table register (GDTR). The source operand specifies the location to the first   GDT entry.

The LGDT instruction is used only in operating-system software; it is not used in application programs.

## Operation

```microcode
Enable Paging;

GDTR ← SRC;
```

## Flags Affected

None
