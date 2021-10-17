# Preamble
Hey, stranger! In this chapter of my repositorial life, i'll try to make something i have never done before -- design a cpu and build an assembler for it.

The project is considered to be a one-time, working-on-weekends, no-huge-plans-involved, and probably a long-term one. 

# Design decisions
The actual cpu is going to be built in Logisim Evolution. Speaking of assembler, the latter will be written in C++.

## Design of an assembly language
Here's a sample program written in our hypothetical assembly language
```asm
.text
  clac
  addi 43
  subi 21
  str  a
.endtext
.data
  .label a // address: 0x0
  .label b // address: 0x1
  .label c // address: 0x2
.endata  
```
For simplicity sake, we might want to keep first 16 addresses reserved for .data section. The rest of space is allotted to .text. 
