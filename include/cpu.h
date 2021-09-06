#ifndef CPU_H
#define CPU_H

#include "ram.h"
#include "defs.h"

#define SIB 0
#define REGREG 1
#define REGDISP 2
#define DISPREG 3

#define REG 1
#define DISP 2
#define IMM 3

#define REGIMM 1
#define DISPIMM 2

#define DIVIDE_BY_ZERO_ERROR 0
#define DEBUG 1
#define NON_MASKABLE_INTERRUPT 2
#define BREAKPOINT 3
#define OVERFLOW 4
#define BOUND_RANGE_EXCEEDEDD 5
#define INVALID_OPCODE 6
#define DEVICE_NOT_AVAILABLE 7
#define DOUBLE_FAULT 8
#define INVALID_TSS 9
#define SEGMENT_NOT_PRESENT 10
#define STACK_SEGMENT_FAULT 11
#define GENERAL_PROTECTION_FAULT 12
#define PAGE_FAULT 13
#define FLOATING_POINT_EXCEPTION 14
#define ALIGMENT_CHECK 15
#define MACHINE_CHECK 16
#define VIRTUALIZATION_EXCEPTION 17

class CPU {
public:
    // Starts cpu from outside, made for main entry
    void Start(RAM * ram);
    // Sends an interrupt to force power-off the cpu, equivilent to unplugging a pc
    void Exit();
    // Requests an interrupt to be handled
    void InterruptRequest(dword interrupt);

    bool OFF; // OFF# signal
    bool INIT; // INIT# signal
    bool RESET; // RESET# signal
    dword * ports; // array of cpu ports

private:
    // INIT# signal
    void Init();
    // OFF# signal
    void Off();
    // RESET# signal
    void Reset();
    // Execution loop of the CPU cycle
    void ExecutionLoop();
    // Fetches the next byte from memory
    byte FetchByte();
    // Fetches the next word from memory
    word FetchWord();
    // Fetches the next double-word from memory
    dword FetchDWord();
    // Reads a byte from memory
    byte ReadByte(dword address);
    // Reads a word from memory
    word ReadWord(dword address);
    // Reads a double-word from memory
    dword ReadDWord(dword address);
    // Reads a quad-word from memory (used in 32-bit mode for GDT)
    qword ReadQWord(dword address);
    // Writes byte in memory
    void WriteByte(dword address, byte value);
    // Writes word in memory
    void WriteWord(dword address, word value);
    // Writes double-word in memory
    void WriteDWord(dword address, dword value);
    // Pushes byte onto stack
    void PushByte(byte value);
    // Pushes word onto stack
    void PushWord(word value);
    // Pushes double-word onto stack
    void PushDWord(dword value);
    // Pops byte from stack
    byte PopByte();
    // Pops word from stack
    word PopWord();
    // Pops double-word from stack
    dword PopDWord();
    // Sets an 8-bit register
    void SetReg8Bit(int reg, byte value);
    // Sets a 16-bit register
    void SetReg16Bit(int reg, word value);
    // Sets a 32-bit register
    void SetReg32Bit(int reg, dword value);
    // Sets a Status Register
    void SetStatusRegister(int Sreg, dword value);
    // Gets an 8-bit register value
    byte GetReg8Bit(int reg);
    // Gets a 16-bit register value
    word GetReg16Bit(int reg);
    // Gets a 32-bit register value
    dword GetReg32Bit(int reg);
    // Gets a Status Register value, first 3-bit codes are all segment register for Sreg operations
    // The rest are psr (processor-specific registers)
    dword GetStatusRegister(int Sreg);
    // Handles an interrupt
    void HandleInterrupt();
    // Gets the real start address of a segment
    dword GetGDTSegmentLocation(dword address);
    // Gets the real address of the interrupt handle
    dword GetIDTLocation(dword interrupt);

    RAM * ram; // pointer to global RAM struct

    bool RequestingInterrupt; // prevents race condition by having a request waiting system
    dword InterruptData; // interrupt code
    bool paging; // paging-enabled flag
    bool cancel; // used for exitting a instruction after an exception occurs

    // Registers
    word eax; // a
    word ebx; // b
    word ecx; // c
    word edx; // d
    word esp; // stack-pointer; Using an incrementing stack
    word eip; // instruction-pointer
    word ebp; // base-pointer
    word edp; // destination-pointer

    word cs; // code
    word ds; // data
    word ss; // stack
    word es; // extra
    word fs; // extra
    word gs; // extra

    dword flags; // using an int instead of a struct for simplicity

    dword idtr; // interrupt descriptor table register
    qword gdtr; // global descriptor table register
};

#endif
