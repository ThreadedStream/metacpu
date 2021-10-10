#include <cstdint>
#include <iostream>

struct Vec3 {
    int8_t x, y, z;

    explicit Vec3() :
            x{0}, y{0}, z{0} {};
};

Vec3 operator*(const Vec3 &vec, const int8_t scalar) {
    Vec3 out;
    out.x = static_cast<int8_t>(vec.x * scalar);
    out.y = static_cast<int8_t>(vec.y * scalar);
    out.z = static_cast<int8_t>(vec.z * scalar);
    return vec;
}

int8_t dot(const Vec3 &a, const Vec3 &b) {
    return static_cast<int8_t>(a.x * b.x) +
           static_cast<int8_t>(a.y * b.y) +
           static_cast<int8_t>(a.z * b.z);
}

Vec3 cross(Vec3 &a, Vec3 &b) {
    //TODO(threadedstream): fill in later
    return Vec3{};
}

enum Opcodes {
    OP_ADD = 0b000,
    OP_SUB = 0b001,
    OP_MUL = 0b010,
    OP_DIV = 0b011,
    OP_DOT = 0b100,
    OP_CROSS = 0b101
};

struct GlobalData {
    union {
        Vec3 vector{};
        int8_t integer;
    };

    GlobalData() : integer{0} {}
};

static int16_t pc = 0;

// registers[2] = acc
// registers[1] = stk
// registers[0] = some register i don't use yet
static int8_t registers[3] = {};
static GlobalData global_data_buffer[256] = {};

constexpr uint16_t OPCODE_MASK = 0b1110000000000000;
constexpr uint16_t REGISTER_MASK = 0b0001100000000000;
constexpr uint16_t DATA_MASK = 0b0000011111111000;
constexpr uint16_t IS_IMM_MASK = 0b0000000000000111;

// TODO(threadedstream): add status flags:
//  OF - overflow flag, CF - carry flag, ZF - zero flag
static int8_t ZF = 0;


inline uint8_t normalizeOpcodeNum(uint16_t val) {
    uint16_t shift_factor = 13;
    val &= OPCODE_MASK;
    return static_cast<uint8_t>(val >> shift_factor);
}

// 0b0001100000000000 -> 0b0000000000000011
inline uint8_t normalizeRegNum(uint16_t val) {
    uint16_t shift_factor = 11;
    val &= REGISTER_MASK;
    return static_cast<uint8_t>(val >> shift_factor);
}


// 0b0000011111111000 -> 0b0000000011111111
inline uint8_t normalizeDataNum(uint16_t val) {
    uint16_t shift_factor = 3;
    val &= DATA_MASK;
    return static_cast<uint8_t>(val >> shift_factor);
}


// fetches current instruction from instruction buffer
inline void fetchAndDecodeInstruction(const int16_t *instruction_buffer,
                                      uint8_t &opcode,
                                      uint8_t &reg,
                                      uint8_t &data,
                                      bool &is_imm
) {
    auto current_instruction = instruction_buffer[pc];
    opcode = normalizeOpcodeNum(current_instruction);
    reg = normalizeRegNum(current_instruction);
    data = normalizeDataNum(current_instruction);
    is_imm = static_cast<bool>(current_instruction & IS_IMM_MASK);
}

int8_t executeInstruction(uint8_t opcode,
                          uint8_t reg,
                          uint8_t data,
                          bool is_imm) {
    int8_t res = 0;
    switch (opcode) {
        case OP_ADD:
            if (is_imm) {
                res = static_cast<int8_t>(registers[reg] + data);
            } else {
                // now data is treated as an index to global data buffer
                auto idx = data;
                res = static_cast<int8_t>(registers[reg] + global_data_buffer[idx].integer);
            }
            break;
        case OP_SUB:
            if (is_imm) {
                res = static_cast<int8_t>(registers[reg] - data);
            } else {
                // now data is treated as an index to global data buffer
                auto idx = data;
                res = static_cast<int8_t>(registers[reg] - global_data_buffer[idx].integer);
            }
            break;
        case OP_MUL:
            if (is_imm) {
                res = static_cast<int8_t>(registers[reg] * data);
            } else {
                // now data is treated as an index to global data buffer
                auto idx = data;
                res = static_cast<int8_t>(registers[reg] * global_data_buffer[idx].integer);
            }
            break;
        case OP_DIV:
            // it does not throw exception upon division by zero
            // i think it's silly
            if (is_imm) {
                res = static_cast<int8_t>(registers[reg] / data);
            } else {
                // now data is treated as an index to global data buffer
                auto idx = data;
                res = static_cast<int8_t>(registers[reg] / global_data_buffer[idx].integer);
            }
            break;
            // TODO(threadedstream): need vector types
        case OP_DOT:
            if (is_imm) {
                throw std::runtime_error("should reference to global data buffer");
            }

//        case OP_CROSS:
//            // TODO(threadedstream): fill in later
//            break;
        default:
            throw std::runtime_error("unknown instruction");
    }

    return res;
}

inline void putResultBackInMemory(int8_t *ptr,
                                  int8_t res) {
    *ptr = res;
}

void loopOverInstructions(const int16_t *instruction_buffer,
                          const int16_t size) {
    uint8_t opcode, reg, data;
    bool is_imm;
    while (pc < size) {

        fetchAndDecodeInstruction(instruction_buffer, opcode,
                                  reg, data, is_imm);
        auto res = executeInstruction(opcode, reg, data, is_imm);
        putResultBackInMemory(&registers[reg], res);
        pc++;
    }
}


void setFlags(int8_t res) {
    if (res == 0) {
        ZF = 1;
    }
}

int main(int argc, const char *argv[]) {
    int16_t size = 3; // 2
    auto instruction_buffer = (int16_t *) calloc(size, sizeof(int16_t)); // 2 * 3 = 6 bytes
    if (!instruction_buffer) {
        return -1;
    }
    instruction_buffer[0] = 0b0001000001010001;
    instruction_buffer[1] = 0b0011000000000001;
    instruction_buffer[2] = 0b0101000000000001;

    loopOverInstructions(instruction_buffer, size);
}