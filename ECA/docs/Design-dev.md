# ECA Developer Details & Design

Toolchain Name: ECA (EMD Compilers and Assemblers)
CCC: Custom Compiler Collection

## CCC

### Files

Under 'src/'

| Name | Description |
|-|-|
| ccc/main.cpp | entry point |
| ccc/opts.cpp | argument parsing |
| es/assembler.cpp | assembler (and linker for now) |
| g/compiler.cpp | Pre-processor, compiler |

### Features/Usage

To compiler and assemble G and EMP-32 Assembly, you can use ccc.

Read ['Usingccc.md'](Usingccc.md) for command-line argument descriptions.

### Implementation Details
