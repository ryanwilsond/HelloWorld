# How to use ecc

## Running the compiler & assembler

You can use ecc to compile G files and assembly language files at the same time. Files in the form of *name.g* & *name.gl* are assumed to be G files and everything else is assumed to be assembly language files.

> Note: The outputed file from ecc is a binary file which can only be run through an emulator.

To compile or assemble a file:

`$ ecc compile-options file.eas -o file.bin`

`$ ecc compile-options file.gl -o file.bin`

## Options

| name | description |
|-|-|
| --help | Stops program and displays help message. |
| -o | Send output to *file-name* instead of default *a.out*. |
| -O0 | No optimization. |
| -O1 | Optimization level 1 (default). |
| -O2 | Optimization level 2, shrinks instruction operand sizes. |
| -E | Stops after preprocess step. |
| -S | Stops after compile step. |
| -win32 | Build for win32 system. |
| -win64 | Build for win64 system. |
| -wos32 | Build for wos32 system (default). |
| -Werror | Treat all warnings as errors. |
| -w | Ignore all warnings. |
