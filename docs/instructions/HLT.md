[index](../InstructionReference.md)

# HLT - Halt

| Opcode | Instruction | Op/En | Description |
|-|-|-|-|
| 01 | HLT | ZO | Halt. |
|

## Instruction Operand Encoding

| Op/En | Operand 1 | Operand 2 |
|-|-|-|
| ZO | NA | NA |
|

## Description

Stops instruction execution and places the processorin a HALT state. An enabled interrupt (including NMI), a debug exception, the INIT# signal, or the RESET# signal will resume execution.

## Operation

```microcode
Enter Halt state;
```

## Flags Affected

None
