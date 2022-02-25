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
    /// Starts cpu from outside, made for main entry
    /// @param ram  pointer to virtual ram
    void Start(RAM * ram);

    /// Sends an interrupt to force power-off the cpu, equivilent to unplugging a pc
    void Exit();

    // Requests an interrupt to be handled
    /// @param interrupt    interrupt data
    void InterruptRequest(dword interrupt);

    bool OFF; // OFF# signal
    bool INIT; // INIT# signal
    bool RESET; // RESET# signal
    dword * ports; // array of cpu ports

private:
    /// INIT# signal
    void Init();

    /// OFF# signal
    void Off();

    /// RESET# signal
    void Reset();

    /// Execution loop of the CPU cycle
    void ExecutionLoop();

    /// Fetches the next byte from memory
    /// @return value
    byte FetchByte();

    /// Fetches the next word from memory
    /// @return value
    word FetchWord();

    /// Fetches the next double-word from memory
    /// @return value
    dword FetchDWord();

    /// Reads a byte from memory
    /// @param address  memory index
    /// @return value
    byte ReadByte(dword address);

    /// Reads a word from memory
    /// @param address  memory index
    /// @return value
    word ReadWord(dword address);

    /// Reads a double-word from memory
    /// @param address  memory index
    /// @return value
    dword ReadDWord(dword address);

    /// Reads a quad-word from memory (used in 32-bit mode for GDT)
    /// @param address  memory index
    /// @return value
    qword ReadQWord(dword address);

    /// Writes byte in memory
    /// @param address  memory index
    /// @param value    value to write
    void WriteByte(dword address, byte value);

    /// Writes word in memory
    /// @param address  memory index
    /// @param value    value to write
    void WriteWord(dword address, word value);

    /// Writes double-word in memory
    /// @param address  memory index
    /// @param value    value to write
    void WriteDWord(dword address, dword value);

    /// Pushes byte onto stack
    /// @param value    value to push
    void PushByte(byte value);

    /// Pushes word onto stack
    /// @param value    value to push
    void PushWord(word value);

    /// Pushes double-word onto stack
    /// @param value    value to push
    void PushDWord(dword value);

    /// Pops byte from stack
    /// @return value
    byte PopByte();

    /// Pops word from stack
    /// @return value
    word PopWord();

    /// Pops double-word from stack
    /// @return value
    dword PopDWord();

    /// Sets an 8-bit register
    /// @param reg      register code to write to
    /// @param value    value to write
    void SetReg8Bit(int reg, byte value);

    /// Sets a 16-bit register
    /// @param reg      register code to write to
    /// @param value    value to write
    void SetReg16Bit(int reg, word value);

    /// Sets a 32-bit register
    /// @param reg      register code to write to
    /// @param value    value to write
    void SetReg32Bit(int reg, dword value);

    /// Sets a Status Register
    /// @param Sreg     Sreg code to write to
    /// @param value    value to write
    void SetStatusRegister(int Sreg, dword value);

    /// Gets an 8-bit register value
    /// @param reg  reg code to fetch
    /// @return register value
    byte GetReg8Bit(int reg);

    // Gets a 16-bit register value
    /// @param reg  reg code to fetch
    /// @return register value
    word GetReg16Bit(int reg);

    // Gets a 32-bit register value
    /// @param reg  reg code to fetch
    /// @return register value
    dword GetReg32Bit(int reg);

    /// Gets a Status Register value, first 3-bit codes are all segment register for Sreg operations
    /// The rest are psr (processor-specific registers)
    /// @param Sreg reg code to fetch
    /// @return register value
    dword GetStatusRegister(int Sreg);

    /// Handles an interrupt
    void HandleInterrupt();

    /// Gets the real start address of a segment
    /// @param address  pointer to GDT entry
    /// @return address to start of segment
    dword GetGDTSegmentLocation(dword address);

    /// Gets the real address of the interrupt handle
    /// @param interrupt    points to IDT entry
    /// @return address to start of interrupt routine
    dword GetIDTLocation(dword interrupt);

    RAM * ram; // pointer to global RAM struct

    bool RequestingInterrupt; // prevents race condition by having a request waiting system
    dword InterruptData; // interrupt code
    bool paging; // paging-enabled flag
    bool cancel; // used for exitting a instruction after an exception occurs

    // Registers (32-bit)
    dword eax; // a
    dword ebx; // b
    dword ecx; // c
    dword edx; // d
    dword esp; // stack-pointer; Using an incrementing stack
    dword eip; // instruction-pointer
    dword ebp; // base-pointer
    dword edp; // destination-pointer

    dword cs; // code
    dword ds; // data
    dword ss; // stack
    dword es; // extra
    dword fs; // extra
    dword gs; // extra

    dword flags; // using an int instead of a struct for simplicity

    dword idtr; // interrupt descriptor table register
    qword gdtr; // global descriptor table register
};

#endif
