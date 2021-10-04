# CPU Developer Details & Design

"Company" Name: EMD (Emulated Micro Devices)

CPU Model: EMP-32-2000 (EMD Micro Processor 32-bit, model 2000)

## Files

Under ./src/

| Name | Description |
|-|-|
| cpu.cpp | CPU emulator |
| engine.cpp | Window creation and handling |
| main.cpp | Entry |
| ram.cpp | Virtual RAM |

## CPU Architecture

[Instruction Index](InstructionIndex.md)

[Architecture](Architecture.md)

## Implmentation

The CPU has a main function that loops over the memory. It then has a big switch to choose what instruction to execture next. Then it executes roughly following the instruction psudo-code in the Instruction Index.

You can view this function at [src/cpu.cpp at CPU::ExecutionLoop()](./../src/cpu.cpp#L72).

Registers are just class variables, and many basic functions are functions (e.g. ReadByte(address)).

Interrupts and segments are not fully developed and are unstable (not fully tested yet).
