# JMP - Jump

| Opcode | Instruction | Op/En | Description |
|-|-|-|-|
| 08 | JMP *r/m8* | M | Jump absolute/near. |
| 09 | JMP *r/m16* | M | Jump absolute/near. |
| 0A | JMP *r/m32* | M | Jump absolute/near. |
| 08 | JMP *imm8* | I | Jump absolute/near. |
| 09 | JMP *imm16* | I | Jump absolute/near. |
| 0A | JMP *imm32* | I | Jump absolute/near. |
| 0B | JMP *Sreg:r/m32* | D | Jump far. |
| 0B | JMP *Sreg:imm32* | DI | Jump far. |
|

## Instruction Operand Encoding

| Op/En | Operand 1 | Operand 2 |
|-|-|-|
| M | ModRM:r/m (r) | NA |
| I | imm8/16/32 | NA |
| D | ModRM:reg (r) | ModRM:r/m (r) |
| DI | ModRM:reg (r) | imm32 |
|

## Description

Transfers program control to a different point in the instruction stream without recording return information. The destination (target) operand specifies the address of the instruction being jumped to. This operand can be an immediate value, a general-purpose register, or a memory location.

This instruction can be used to execute three different types of jumps:

- Absolute jump - A jump to a real address location.
- Near jump — A jump to an instruction within the current code segment (the segment currently pointed to by the CS register), sometimes referred to as an intrasegment jump.
- Far jump — A jump to an instruction located in a different segment than the current code segment, sometimes referred to as an intersegment jump.

## Operation

```microcode
IF near jump
    THEN
        tempIP ← GDT[CS] + SRC;
    ELSE IF far jump
        THEN
            tempIP ← GDT[SRC] + SRC;
        FI;
    ELSE
        tempIP ← SRC;
FI;

IP ← tempIP;
```

## Flags Affected

None
