# Bytecode instructions

OP_ADD = 000
OP_SUB = 001
OP_MUL = 010
OP_DIV = 011
OP_DOT = 100
OP_CROSS = 101

###### 6 opcodes (3 bits), 3 registers (24 bytes), vector type (24 bytes for one vector)

Well, here's a sample instruction
```c++
OP_ADD acc, #10 // add number 10 to accumulator
OP_ADD acc, 10 // add contents of data residing in global data buffer accessed using index 10
```
Instructions can be represented in binary form.
For instance, here's a binary equivalent  of the first instruction:
```
000     10   00001010       1
OP_ADD  acc    #10     using number
```

The last bit indicates whether a second operand is a number or a reference to global data buffer.
