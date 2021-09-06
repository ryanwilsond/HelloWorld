# MOV - Move

| Opcode | Instruction | Op/En | Description |
|-|-|-|-|
| 04 | MOV *r/m8,r8* | MR | Move *r8* to *r/m8*. |
| 05 | MOV *r/m16,r16* | MR | Move *r16* to *r/m16*. |
| 06 | MOV *r/m32,r32* | MR | Move *r32* to *r/m32*. |
| 04 | MOV *r8,r/m8* | RM | Move *r/m8* to *r8*. |
| 05 | MOV *r16,r/m16* | RM | Move *r/m16* to *r16*. |
| 06 | MOV *r32,r/m32* | RM | Move *r/m32* to *r32*. |
| 07 | MOV *Sreg,r32* | RM | Move *r32* to *Sreg*. |
| 07 | MOV *r32,Sreg* | RM | Move *Sreg* to *r32*. |
| 81 | MOV *r/m8,imm8* | MI | Move *imm8* to *r/m8*. |
| 81 | MOV *r/m16,imm16* | MI | Move *imm16* to *r/m16*. |
| 81 | MOV *r/m32,imm32* | MI | Move *imm32* to *r/m32*. |
|

## Instruction Operand Encoding

| Op/En | Operand 1 | Operand 2 |
|-|-|-|
| MR | ModRM:r/m (w) | ModRM:reg (r) |
| RM | ModRM:reg (w) | ModRM:r/m (r) |
| MI | ModRM:r/m (w) | imm8/16/32 |
|

## Description

Copies the second operand (source operand) to the first operand (destination operand). The source operand can be an immediate value, general-purpose register, segment register, or memory location; the destination register can be a general-purpose register, segment register, or memory location. Both operands must be the same size, which can be a byte, word, or double-word.

## Operation

```microcode
DEST ← SRC;
```

## Flags Affected

None
