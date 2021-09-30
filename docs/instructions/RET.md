[index](../InstructionReference.md)

# RET - Return from Procedure

| Opcode | Instruction | Op/En | Description |
|-|-|-|-|
| 02 | RET | ZO | Near return to procedure. |
| 03 | RET | ZO | Far return to procedure. |
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
IF near return
    THEN
        tempIP ← GDT[CS] + Pop();
    ELSE
        tempIP ← Pop();
FI;

IP ← tempIP;
```

## Flags Affected

None
