# ECA Developer Details

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

Read ['Usingccc.md'](Usingccc.md) for usage details. For additional command-line help you can use the --help flag when running ccc.

### Implementation Details

Read ['Design.md'](Design.md) for implementation details.

For details about the custom libraries,
