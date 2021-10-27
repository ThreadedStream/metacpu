# Preamble
Hey, stranger! In this chapter of my repositorial life, i'll try to make something i have never done before -- design a cpu and build an assembler for it.

The project is considered to be a working-on-weekends, no-huge-plans-involved, and probably a long-term one. 

# Design decisions
The actual cpu is going to be built in Logisim Evolution. Speaking of assembler, the latter will be written in C++.

## Design of an assembly language
Here's the dumbest possible way to write "Hello world" program in metasm
```asm
  .start:
      clac
  .H:
      addi 72
      outb
      ucb e
  .e:
      clac
      addi 101
      outb
      ucb l1
  .l1:
      clac
      addi 108
      outb
      outb
      ucb o1

  .o1:
      clac
      addi 111
      outb
      ucb whitespace

  .whitespace:
      clac
      addi 32
      outb
      ucb w

  .w:
      clac
      addi 119
      outb
      ucb o2
  .o2:
      clac
      addi 111
      outb
      ucb r

  .r:
      clac
      addi 114
      outb
      ucb l2

  .l2:
      clac
      addi 108
      outb
      ucb d

  .d:
      clac
      addi 100
      outb
      ucb exc_mark

  .exc_mark:
      clac
      addi 33
      outb
      ucb end

  .end:
      clac
      addi 10
      outb
      leave

  BEGINDATA
  {
      h = 0
      y = 66
      z = 0
  }
```
For simplicity sake, we might want to keep first 16 addresses reserved for .data section. The rest of space is allotted to the actual program.

Here's a list of supported instructions with their respective opcodes <br>
```cpp
static std::unordered_map<std::string, uint8_t> opcodes = {
        {"addi",  0x00},
        {"add",   0x01},
        {"subi",  0x02},
        {"sub",   0x03},
        {"clac",  0x04},
        {"bnz",   0x05},
        {"bz",    0x06},
        {"ucb",   0x07},
        {"str",   0x08},
        {"leave", 0x09},
        {"cmp",   0x0A},
        {"cmpi",  0x0B},
        {"outd",  0x0C},
        {"big",   0x0D},
        {"bil",   0x0E},
        {"outb",  0x0F},
        {"ret",   0x10},
        {"submem", 0x11},
        {"addmem", 0x12},
};
```

