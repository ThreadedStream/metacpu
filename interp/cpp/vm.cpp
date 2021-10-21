#include "vm.h"
#include "instructions.h"

#define SET_UNSET_ZF(vm) vm_->zf = vm_->acc == 0 ? true : false;


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
    SET_UNSET_ZF(vm_)
}

void Interpreter::add(uint8_t addr) {
	const auto value = vm_->memory[addr];
    vm_->acc += value;
	SET_UNSET_ZF(vm_)
}

void Interpreter::subi(uint8_t value) {
    vm_->acc -= value;
    SET_UNSET_ZF(vm_)
}

void Interpreter::sub(uint8_t addr) {
	const auto value = vm_->memory[addr];
    vm_->acc -= value;
    SET_UNSET_ZF(vm_)
}

void Interpreter::clac() {
    // Zero out accumulator
    vm_->acc ^= vm_->acc;
    vm_->zf = true;
}

void Interpreter::bnz(uint8_t addr) {
    if (!vm_->zf) {
		// assign addr - 1, since pc is incremented each loop
        vm_->pc = addr - 1;
    }
}

void Interpreter::bz(uint8_t addr) {
    if (vm_->zf) {
        vm_->pc = addr - 1;
    }
}

void Interpreter::ucb(uint8_t addr) {
    vm_->pc = addr - 1;
}

void Interpreter::str(uint8_t addr) {
    vm_->memory[addr] = vm_->acc;
}
