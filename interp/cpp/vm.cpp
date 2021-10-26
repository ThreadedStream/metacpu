#include "vm.h"
#include "instructions.h"

// updates state of the flags by first clearing off an old state, and then 
// setting a new one.
#define SET_FLAGS vm_->flags = (vm_->flags >> 2) | ((vm_->acc == 0 ? 1 : 0) | ((vm_->acc < 0 ? 1 : 0) << 1));


bool Interpreter::initializeVm(const std::string &path) {
    vm_ = static_cast<vm *>(calloc(1, sizeof(vm)));
    if (!vm_) {
        fputs(errors[FAILED_TO_ALLOCATE_MEMORY], stderr);
        return false;
    }

    vm_->memory = static_cast<uint16_t *>(calloc(memory_bank_size, sizeof(uint16_t)));
    if (!vm_->memory) {
        fputs(errors[FAILED_TO_ALLOCATE_MEMORY], stderr);
        return false;
    }


    int32_t size;
    const auto success = loadMachineCodeIntoMemory(path.c_str(), &vm_->memory, &size);
    assert(success);

    return true;
}

void Interpreter::simulate() {
    assert(vm_ && "vm must be initialized!");

    auto &pc = vm_->pc;
    while ((vm_->memory[pc] & instruction_mask) != LEAVE) {
        const auto instr = vm_->memory[pc];
        const auto opcode = vm_->memory[pc] & instruction_mask;
        switch (opcode) {
            case ADDI:
                addi(instr & value_mask);
                break;
            case ADD:
                add(instr & value_mask);
                break;
            case SUBI:
                subi(instr & value_mask);
                break;
            case SUB:
                sub(instr & value_mask);
                break;
            case CLAC:
                clac();
                break;
            case BNZ:
                bnz(instr & value_mask);
                break;
            case BZ:
                bz(instr & value_mask);
                break;
            case UCB:
                ucb(instr & value_mask);
                break;
            case STR:
                str(instr & value_mask);
                break;
            case CMP:
                cmp(instr & value_mask);
                break;
            case CMPI:
                cmpi(instr & value_mask);
                break;
            case OUTD:
                outd();
                break;
            case OUTB:
                outb();
                break;
            case BIG:
                big(instr & value_mask);
                break;
            case BIL:
                bil(instr & value_mask);
                break;
            case RET:
                ret();
                break;
            default:
                printf("unknown instruction %d", opcode);
                break;
        }
        pc++;
    }

    printf("leave\n");

}

void Interpreter::addi(uint8_t value) {
    vm_->acc += value;
    SET_FLAGS
}

void Interpreter::add(uint8_t addr) {
    const auto value = vm_->memory[addr];
    vm_->acc += value;
    SET_FLAGS
}

void Interpreter::subi(uint8_t value) {
    vm_->acc -= value;
    SET_FLAGS
}

void Interpreter::sub(uint8_t addr) {
    const auto value = vm_->memory[addr];
    vm_->acc -= value;
    SET_FLAGS
}

void Interpreter::clac() {
    // Zero out accumulator
    vm_->acc ^= vm_->acc;
    // set zero flag
    vm_->flags |= 0x1;
}


// TODO(threadedstream): push pc onto the stack as a return address
// The same goes for every jump instruction
void Interpreter::bnz(uint8_t addr) {
    if (!is_zf_set(vm_->flags)) {
        stack_.push(vm_->pc);
        // assign addr - 1, since pc is incremented each loop
        vm_->pc = addr - 1;
    }
}

void Interpreter::bz(uint8_t addr) {
    if (is_zf_set(vm_->flags)) {
        stack_.push(vm_->pc);
        vm_->pc = addr - 1;
    }
}

void Interpreter::ucb(uint8_t addr) {
    stack_.push(vm_->pc);
    vm_->pc = addr - 1;
}

void Interpreter::str(uint8_t addr) {
    vm_->memory[addr] = vm_->acc;
}

void Interpreter::cmp(uint8_t addr) {
    const auto temp = vm_->acc;
    vm_->acc -= vm_->memory[addr];
    SET_FLAGS
    vm_->acc = temp;
}

void Interpreter::cmpi(uint8_t value) {
    const auto temp = vm_->acc;
    vm_->acc -= value;
    SET_FLAGS
    vm_->acc = temp;
}

void Interpreter::outd() {
    fprintf(stdout, "%d", vm_->acc);
}

void Interpreter::outb() {
    fprintf(stdout, "%c", vm_->acc);
}

void Interpreter::big(uint8_t addr) {
    if (!is_sf_set(vm_->flags) && !is_zf_set(vm_->flags)) {
        stack_.push(vm_->pc);
        vm_->pc = addr - 1;
    }
}

void Interpreter::bil(uint8_t addr) {
    if (is_sf_set(vm_->flags) && !is_zf_set(vm_->flags)) {
        stack_.push(vm_->pc);
        vm_->pc = addr - 1;
    }
}

void Interpreter::ret() {
    vm_->pc = stack_.top();
    stack_.pop();
}