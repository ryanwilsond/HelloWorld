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

### ECA Files

-> ./ECA/src

| Name | Description |
|-|-|
| ccc/main.cpp | entry point |
| ccc/opts.cpp | argument parsing |
| es/assembler.cpp | assembler (and linker for now) |
| g/compiler.cpp | Pre-processor, compiler |

### OS Files

-> ./OS/src

| Name | Description |
|-|-|
| main.s | Entry point and assembly-only setup (IDT, GDT, etc.) |

## CPU Architecture

> [Instruction Reference](./docs/InstructionReference.md)

View all CPU specific documentation under 'docs/'
