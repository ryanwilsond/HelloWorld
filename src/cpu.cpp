#include "cpu.h"
#include "engine.h"

// debugging infinite loop
int counter = 0;

void CPU::Start(RAM * ram) {
    this->OFF = false;
    this->ram = ram;

    this->INIT = true;
    this->Init();
}

void CPU::Exit() {
    this->Off();
}

void CPU::Init() {
    this->gdtr = 0;
    this->idtr = 0;
    this->eax = 0;
    this->ebx = 0;
    this->ecx = 0;
    this->ebp = 0;
    this->edp = 0;
    this->cs = 0;
    this->ds = 0;
    this->ss = 0;
    this->fs = 0;
    this->gs = 0;
    this->paging = false;
    this->cancel = false;
    bool RequestingIRQ = false;
    bool RequestingNMI = false;

    this->esp = 520;
    this->eip = 0;

    this->flags = 0x00000000;

    this->ports = new dword[512]; // add up to 2^16 if needed

    this->INIT = false;
    // load first sector into ram here...
    this->ExecutionLoop();
}

void CPU::Off() {
    this->OFF = true;
}

void CPU::Reset() {
    this->RESET = true;
    this->Off();
    this->Init();
    this->RESET = false;
}

void CPU::InterruptRequest(dword interrupt) {
    this->RequestingInterrupt = true;
    this->InterruptData = interrupt;
}

void CPU::HandleInterrupt() {
    auto cs = 0;
    this->RequestingInterrupt = false;
    if (((this->flags & 0b100) >> 2) == 1) {
        this->PushDWord(this->eip);
        this->eip = this->GetIDTLocation(this->InterruptData);
    }
}

void CPU::ExecutionLoop() {
    byte instruction;
    byte modrm;

    while (!this->OFF) {
        if (this->RequestingInterrupt) this->HandleInterrupt();

        instruction = this->FetchByte();
        printf("(%i) Executing opcode %i at address %i\n", counter, instruction, this->eip-1);

        switch (instruction) {
            case 0x01: { // HLT         0b00000001
                word oldip = this->eip;
                // Halt state:
                while (true) {
                    if (oldip != this->eip) break;
                    if (this->RESET == true) return;
                    if (this->INIT == true) return;
                    if (this->OFF == true) return;
                } // stuck until interrupt changes ip or power signal
                break;
            }
            case 0x02: { // RET (near)  0b00000010
                auto cs = 0;
                word oldip = this->PopWord();
                if (this->paging) cs = GetGDTSegmentLocation(this->cs);
                this->eip = cs + oldip;
                break;
            }
            case 0x03: { // RET (far)   0b00000011
                word oldip = this->PopWord();
                this->eip = oldip;
                break;
            }
            case 0x04: { // MOV-8       0b000001-00
                modrm = this->FetchByte();
                auto mod = (modrm & 0b11000000) >> 6;
                auto reg1 = (modrm & 0b00111000) >> 3;
                auto reg2 = modrm & 0b00000111;
                dword address = 0;

                if (this->paging) {
                    address += GetGDTSegmentLocation(this->ds);
                }
                if (this->cancel) {
                    this->cancel = false; break;
                }

                if (mod == SIB) {
                    printf("SIB mode is unsupported\n");
                } else if (mod == REGREG) {
                    this->SetReg8Bit(reg1, this->GetReg8Bit(reg2));
                } else if (mod == REGDISP) {
                    address += this->FetchWord();
                    byte value = this->ReadByte(address);
                    this->SetReg8Bit(reg1, value);
                } else if (mod == DISPREG) {
                    address += this->FetchDWord();
                    byte value = this->GetReg8Bit(reg1);
                    this->WriteByte(address, value);
                }

                break;
            }
            case 0x05: { // MOV-16      0b000001-01
                modrm = this->FetchByte();
                auto mod = (modrm & 0b11000000) >> 6;
                auto reg1 = (modrm & 0b00111000) >> 3;
                auto reg2 = modrm & 0b00000111;
                dword address = 0;

                if (this->paging) {
                    address += GetGDTSegmentLocation(this->ds);
                }
                if (this->cancel) {
                    this->cancel = false; break;
                }

                if (mod == SIB) {
                    printf("SIB mode is unsupported\n");
                } else if (mod == REGREG) {
                    this->SetReg16Bit(reg1, this->GetReg16Bit(reg2));
                } else if (mod == REGDISP) {
                    address += this->FetchDWord();
                    word value = this->ReadWord(address);
                    this->SetReg16Bit(reg1, value);
                } else if (mod == DISPREG) {
                    address += this->FetchDWord();
                    word value = this->GetReg16Bit(reg1);
                    this->WriteWord(address, value);
                }

                break;
            }
            case 0x06: { // MOV-32      0b000001-10
                modrm = this->FetchByte();
                auto mod = (modrm & 0b11000000) >> 6;
                auto reg1 = (modrm & 0b00111000) >> 3;
                auto reg2 = modrm & 0b00000111;
                dword address = 0;

                if (this->paging) {
                    address += GetGDTSegmentLocation(this->ds);
                }
                if (this->cancel) {
                    this->cancel = false; break;
                }

                if (mod == SIB) {
                    printf("SIB mode is unsupported\n");
                } else if (mod == REGREG) {
                    this->SetReg32Bit(reg1, this->GetReg32Bit(reg2));
                } else if (mod == REGDISP) {
                    address += this->FetchDWord();
                    dword value = this->ReadDWord(address);
                    this->SetReg32Bit(reg1, value);
                } else if (mod == DISPREG) {
                    address += this->FetchDWord();
                    dword value = this->GetReg32Bit(reg1);
                    this->WriteDWord(address, value);
                }

                break;
            }
            case 0x07: { // MOV-Sreg    0b000001-11
                modrm = this->FetchByte();
                auto mode = (modrm & 0b01000000) >> 6;
                auto Sreg = (modrm & 0b00111000) >> 3;
                auto reg = modrm & 0b00000111;

                if (mode == 0) {
                    this->SetStatusRegister(Sreg, this->GetReg32Bit(reg));
                } else if (mode == 1) {
                    this->SetReg32Bit(reg, this->GetStatusRegister(Sreg));
                }

                break;
            }
            case 0x81: { // MOV-imm     0b1-0000001
                modrm = this->FetchByte();
                auto mod = (modrm & 0b11000000) >> 6;
                auto size = (modrm & 0b00110000) >> 5;
                auto reg = (modrm & 0b00001110) >> 2;
                dword address = 0;

                if (this->paging) {
                    address += GetGDTSegmentLocation(this->ds);
                }
                if (this->cancel) {
                    this->cancel = false; break;
                }

                if (mod == REGIMM) {
                    if (size == 0) {
                        byte value = this->FetchByte();
                        this->SetReg8Bit(reg, value);
                    } else if (size == 1) {
                        word value = this->FetchWord();
                        this->SetReg16Bit(reg, value);
                    } else if (size == 2) {
                        dword value = this->FetchDWord();
                        this->SetReg32Bit(reg, value);
                    }
                } else if (mod == DISPIMM) {
                    if (size == 0) {
                        address += this->FetchDWord();
                        byte value = this->FetchByte();
                        this->WriteByte(address, value);
                    } else if (size == 1) {
                        address += this->FetchDWord();
                        word value = this->FetchWord();
                        this->WriteWord(address, value);
                    } else if (size == 2) {
                        address += this->FetchDWord();
                        dword value = this->FetchDWord();
                        this->WriteDWord(address, value);
                    }
                }

                break;
            }
            case 0x08: { // JMP-8       0b000010-00
                counter++;
                modrm = this->FetchByte();
                auto mod = (modrm & 0b11000000) >> 6;
                auto reg = (modrm & 0b00111000) >> 3;
                auto type = (modrm & 0b00000100) >> 2;
                word tempIP = 0;

                // near=0, absolute=1
                if (this->paging) {
                    if (type == 0) {
                        tempIP += GetGDTSegmentLocation(this->cs);
                    }
                    if (this->cancel) {
                        this->cancel = false; break;
                    }
                }

                if (mod == SIB) {
                    printf("SIB mode is unsupported\n");
                } else if (mod == REG) {
                    tempIP += this->GetReg8Bit(reg);
                } else if (mod == DISP) {
                    dword disp = this->FetchDWord();
                    byte value = this->ReadByte(disp);
                    tempIP += value;
                } else if (mod == IMM) {
                    byte value = this->FetchByte();
                    tempIP += value;
                }

                this->eip = tempIP;

                break;
            }
            case 0x09: { // JMP-16      0b000010-01
                modrm = this->FetchByte();
                auto mod = (modrm & 0b11000000) >> 6;
                auto reg = (modrm & 0b00111000) >> 3;
                auto type = (modrm & 0b00000100) >> 2;
                word tempIP = 0;

                // near=0, absolute=1
                if (this->paging) {
                    if (type == 0) {
                        tempIP += GetGDTSegmentLocation(this->cs);
                    }
                    if (this->cancel) {
                        this->cancel = false; break;
                    }
                }

                if (mod == SIB) {
                    printf("SIB mode is unsupported\n");
                } else if (mod == REG) {
                    tempIP += this->GetReg16Bit(reg);
                } else if (mod == DISP) {
                    dword disp = this->FetchDWord();
                    word value = this->ReadWord(disp);
                    tempIP += value;
                } else if (mod == IMM) {
                    word value = this->FetchWord();
                    tempIP += value;
                }

                this->eip = tempIP;

                break;
            }
            case 0x0A: { // JMP-32      0b000010-10
                modrm = this->FetchByte();
                auto mod = (modrm & 0b11000000) >> 6;
                auto reg = (modrm & 0b00111000) >> 3;
                auto type = (modrm & 0b00000100) >> 2;
                word tempIP = 0;

                // near=0, absolute=1
                if (this->paging) {
                    if (type == 0) {
                        tempIP += GetGDTSegmentLocation(this->cs);
                    }
                    if (this->cancel) {
                        this->cancel = false; break;
                    }
                }

                if (mod == SIB) {
                    printf("SIB mode is unsupported\n");
                } else if (mod == REG) {
                    tempIP += this->GetReg32Bit(reg);
                } else if (mod == DISP) {
                    dword disp = this->FetchDWord();
                    dword value = this->ReadDWord(disp);
                    tempIP += value;
                } else if (mod == IMM) {
                    dword value = this->FetchDWord();
                    tempIP += value;
                }

                this->eip = tempIP;

                break;
            }
            case 0x0B: { // JMP (far)   0b000010-11
                modrm = this->FetchByte();
                auto mod = (modrm & 0b11000000) >> 6;
                auto Sreg = (modrm & 0b00111000) >> 3;
                auto reg = modrm & 0b00000111;
                word tempIP = 0;

                if (this->paging) {
                    tempIP += GetGDTSegmentLocation(GetStatusRegister(Sreg));
                    if (this->cancel) {
                        this->cancel = false; break;
                    }
                }

                if (mod == SIB) {
                    printf("SIB mode is unsupported\n");
                } else if (mod == REG) {
                    tempIP += this->GetReg32Bit(reg);
                } else if (mod == DISP) {
                    dword disp = this->FetchDWord();
                    dword value = this->ReadDWord(disp);
                    tempIP += value;
                } else if (mod == IMM) {
                    dword value = this->FetchDWord();
                    tempIP += value;
                }

                this->eip = tempIP;

                break;
            }
            case 0x0C: { // PUSH-8      0b000011-00
            }
            case 0x0D: { // PUSH-16     0b000011-01
            }
            case 0x0E: { // PUSH-32     0b000011-10
            }
            case 0x0F: { // PUSH-eflags 0b000011-11
            }
            case 0x10: { // POP-8       0b000100-00
            }
            case 0x11: { // POP-16      0b000100-01
            }
            case 0x12: { // POP-32      0b000100-10
            }
            case 0x13: { // POP-eflags  0b000100-11
            }
            case 0x14: { // PUSH-dflags 0b000101-00
            }
            case 0x15: { // PUSH-flags  0b000101-01
            }
            case 0x16: { // POP-dflags  0b000101-10
            }
            case 0x17: { // POP-flags   0b000101-11
            }
            case 0x18: { // PUSH-Streg  0b000110-00
            }
            case 0x19: { // POP-Streg   0b000110-01
            }
            case 0x1C: { // AND-8       0b000111-00
            }
            case 0x1D: { // AND-16      0b000111-01
            }
            case 0x1E: { // AND-32      0b000111-10
            }
            case 0x20: { // OR-8        0b001000-00
            }
            case 0x21: { // OR-16       0b001000-01
            }
            case 0x22: { // OR-32       0b001000-10
            }
            case 0xBB: { // LGDT
                modrm = this->FetchByte();
                auto mode = (modrm & 0b11000000) >> 6;
                auto reg = (modrm & 0b00111000) >> 3;
                this->paging = true;

                if (mode == 0) {
                    this->gdtr = this->FetchDWord();
                } else if (mode == 1) {
                    this->gdtr = this->GetReg32Bit(reg);
                }
            }
            case 0xAA: { // printal
                printf("%c\n", this->GetReg8Bit(0));
                break;
            }
            default: {
                printf("Unknown opcode %i at %i\n", instruction, this->eip-1);
                this->InterruptRequest(INVALID_OPCODE);
                this->HandleInterrupt();
                return;
            }
        }
    }
}

dword CPU::GetGDTSegmentLocation(dword address) {
    dword addr = ((this->gdtr & 0xffffffff00000000) >> 32) + address;
    if (addr > (this->gdtr & 0xffffffff))
        this->InterruptRequest(SEGMENT_NOT_PRESENT);
        this->HandleInterrupt();
        this->cancel = true;
        return 0;
    qword gdtentry = this->ReadQWord(addr);
    return (gdtentry & 0xffffffff00000000) >> 32;
}

dword CPU::GetIDTLocation(dword interrupt) {
    qword entry = this->ReadQWord(this->idtr + (interrupt)*8);
    dword addr = (entry & 0xffffffff00000000) >> 32;
    addr += this->GetGDTSegmentLocation((entry & 0xffff0000) >> 16);
    return addr;
}

byte CPU::GetReg8Bit(int reg) {
    switch (reg) {
        case 0: return this->eax & 0xff;
        case 1: return this->ebx & 0xff;
        case 2: return this->ecx & 0xff;
        case 3: return this->edx & 0xff;
        case 4: return (this->eax & 0xff00) >> 8;
        case 5: return (this->ebx & 0xff00) >> 8;
        case 6: return (this->ecx & 0xff00) >> 8;
        case 7: return (this->edx & 0xff00) >> 8;
        default:
            printf("Unknown reg-code %i (at %i)\n", reg, this->eip-1);
            return 0;
    }
}

word CPU::GetReg16Bit(int reg) {
    switch (reg) {
        case 0: return this->eax & 0xffff;
        case 1: return this->ebx & 0xffff;
        case 2: return this->ecx & 0xffff;
        case 3: return this->edx & 0xffff;
        case 4: return this->esp & 0xffff;
        case 5: return this->eip & 0xffff;
        case 6: return this->ebp & 0xffff;
        case 7: return this->edp & 0xffff;
        default:
            printf("Unknown reg-code %i (at %i)\n", reg, this->eip-1);
            return 0;
    }
}

dword CPU::GetReg32Bit(int reg) {
    switch (reg) {
        case 0: return this->eax;
        case 1: return this->ebx;
        case 2: return this->ecx;
        case 3: return this->edx;
        case 4: return this->esp;
        case 5: return this->eip;
        case 6: return this->ebp;
        case 7: return this->edp;
        default:
            printf("Unknown reg-code %i (at %i)\n", reg, this->eip-1);
            return 0;
    }
}

dword CPU::GetStatusRegister(int Sreg) {
    switch (Sreg) {
        case 0: return this->cs;
        case 1: return this->ds;
        case 2: return this->ss;
        case 3: return this->es;
        case 4: return this->fs;
        case 5: return this->gs;
        default:
            printf("Unknown status-reg-code %i (at %i)\n", Sreg, this->eip-1);
            return 0;
    }
}

void CPU::SetReg8Bit(int reg, byte value) {
    switch (reg) {
        case 0: // al
            this->eax = (this->eax & 0xffffff00) | value;
            break;
        case 1: // bl
            this->ebx = (this->ebx & 0xffffff00) | value;
            break;
        case 2: // cl
            this->ecx = (this->ecx & 0xffffff00) | value;
            break;
        case 3: // dl
            this->edx = (this->edx & 0xffffff00) | value;
            break;
        case 4: // ah
            this->eax = (value << 8) | (this->eax & 0xffff00ff);
            break;
        case 5: // bh
            this->ebx = (value << 8) | (this->ebx & 0xffff00ff);
            break;
        case 6: // ch
            this->ecx = (value << 8) | (this->ecx & 0xffff00ff);
            break;
        case 7: // dh
            this->edx = (value << 8) | (this->edx & 0xffff00ff);
            break;
        default:
            printf("Unknown reg-code %i (at %i)\n", reg, this->eip-1);
            break;
    }
}

void CPU::SetReg16Bit(int reg, word value) {
    switch (reg) {
        case 0:
            this->eax = (this->eax & 0xffff0000) | value;
            break;
        case 1:
            this->ebx = (this->ebx & 0xffff0000) | value;
            break;
        case 2:
            this->ecx = (this->ecx & 0xffff0000) | value;
            break;
        case 3:
            this->edx = (this->edx & 0xffff0000) | value;
            break;
        case 4:
            this->esp = (this->esp & 0xffff0000) | value;
            break;
        case 5:
            this->eip = (this->eip & 0xffff0000) | value;
            break;
        case 6:
            this->ebp = (this->ebp & 0xffff0000) | value;
            break;
        case 7:
            this->edp = (this->edp & 0xffff0000) | value;
            break;
        default:
            printf("Unknown reg-code %i (at %i)\n", reg, this->eip-1);
            break;
    }
}

void CPU::SetReg32Bit(int reg, dword value) {
    switch (reg) {
        case 0:
            this->eax = value;
            break;
        case 1:
            this->ebx = value;
            break;
        case 2:
            this->ecx = value;
            break;
        case 3:
            this->edx = value;
            break;
        case 4:
            this->esp = value;
            break;
        case 5:
            this->eip = value;
            break;
        case 6:
            this->ebp = value;
            break;
        case 7:
            this->edp = value;
            break;
        default:
            printf("Unknown reg-code %i (at %i)\n", reg, this->eip-1);
            break;
    }
}

void CPU::SetStatusRegister(int Sreg, dword value) {
    switch (Sreg) {
        case 0: this->cs = value;
        case 1: this->ds = value;
        case 2: this->ss = value;
        case 3: this->es = value;
        case 4: this->fs = value;
        case 5: this->gs = value;
        default:
            printf("Unknown status-reg-code %i (at %i)\n", Sreg, this->eip-1);
            break;
    }
}

byte CPU::FetchByte() {
    return this->ram->memory[this->eip++];
}

word CPU::FetchWord() {
    return (this->FetchByte() << 8) | this->FetchByte();
}

dword CPU::FetchDWord() {
    return (this->FetchWord() << 16) | this->FetchWord();
}

byte CPU::ReadByte(dword address) {
    return this->ram->memory[address];
}

word CPU::ReadWord(dword address) {
    return (this->ReadByte(address) << 8) | this->ReadByte(address+1);
}

dword CPU::ReadDWord(dword address) {
    return (this->ReadWord(address) << 16) | this->ReadWord(address+2);
}

qword CPU::ReadQWord(dword address) {
    return ((unsigned long long)this->ReadDWord(address) << 32) | this->ReadDWord(address+4);
}

void CPU::WriteByte(dword address, byte value) {
    this->ram->memory[address] = value;
}

void CPU::WriteWord(dword address, word value) {
    this->WriteByte(address, (value & 0xff00) >> 8);
    this->WriteByte(address+1, value & 0xff);
}

void CPU::WriteDWord(dword address, dword value) {
    this->WriteWord(address, (value & 0xffff0000) >> 16);
    this->WriteWord(address+2, value & 0xffff);
}

void CPU::PushByte(byte value) {
    this->ram->memory[this->esp++] = value;
}

void CPU::PushWord(word value) {
    this->PushByte((value & 0xff00) >> 8);
    this->PushByte(value & 0xff);
}

void CPU::PushDWord(dword value) {
    this->PushWord((value & 0xffff0000) >> 16);
    this->PushWord(value & 0xffff);
}

byte CPU::PopByte() {
    return this->ram->memory[--this->esp];
}

word CPU::PopWord() {
    word value = this->PopByte();
    return value | (this->PopByte() << 8);
}

dword CPU::PopDWord() {
    dword value = this->PopWord();
    return value | (this->PopWord() << 16);
}
