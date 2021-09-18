# Devoloper Details

company name = EMD (emulated micro devices)
binutil equivalient = ECA (EMD compilers and assemblers)
os name = WorldOS
cpu name = EMP-32-2000

## Files

### CPU Files

-> ./src

| Name | Description |
|-|-|
| cpu.cpp | CPU emulator |
| engine.cpp | Window creation and handling |
| main.cpp | Entry |
| ram.cpp | Virtual RAM |

### Custom Cross-Compiler Files

-> ./ccc/src

| Name | Description |
|-|-|
| asm.cpp | Assembler |
| main.cpp | Entry point and arg-parser |
| compiler.cpp | Pre-processor, compiler |
| linker.cpp | Linker |

### OS Files

-> ./OS/src

| Name | Description |
|-|-|
| main.s | Entry point |

## CPU Architecture

> [Instruction Reference](./InstructionReference.md)
