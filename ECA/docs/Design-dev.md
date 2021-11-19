# ECA Developer Details & Design

Toolchain Name: ECA (EMD Compilers and Assemblers)
ECC: ECA Compiler Collection

**File extensions:**

| ext | description |
|-|-|
| \*.g, *.gl | G Language |
| \*.eas (\*.asm, *.s) | EMP-32-2000 Assembly Language |
| *.gh | G Language header file |
| *.ein | EAS include (header) file |

## ECC

### Files

Under 'src/ecc'

| Name | Description |
|-|-|
| main.cpp | entry point |
| opts.cpp | argument parsing |
| es/assembler.cpp | assembler & linker |
| g/compiler.cpp | preprocessor & compiler |

### Features/Usage

To compiler and assemble G and EMP-32 Assembly, you can use ecc.

Read ['Usingecc.md'](Usingecc.md) for command-line argument descriptions.

### Implementation Details

The program parsed the command-line arguments and sends the input files to the compiler first, then assembler (according to the file extensions). Currently the linker is built into the assembler. Then it writes this binary data to an outfile.

Details on the assembler and compiler details are absent because they themselves have not been implemented (yet).
