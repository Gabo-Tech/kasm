# kasm

A MIPS-like virtual machine, compiler, and assembler.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

* CMake >= 3.2

### Checkout

```sh
git clone https://github.com/widberg/kasm.git
cd kasm
```

### Build

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

## KASM Environment

### Tools

✅ kasm - Assembler
✅ kdsm - Disassembler
✅ kvm - Virtual Machine
🟩 kdbg - Debugger
⬜ klang - K Structured Programming Language Compiler

### Directives

| KASM | Description |
| --- | --- |
| .text | Move the cursor to the first unwritten byte of the text segment |
| .data | Move the cursor to the first unwritten byte of the data segment |
| .word i|a[, i|a]... | Align the cursor to the nearest word boundary and writes each immediate or memory direct address as a word to the data segment in sequence |
| .word i|a:X | Align the cursor to the nearest word boundary and writes the immediate or labeled address as a word to the data segment the specified number of times |
| .byte i|a[, i|a]... | Write each immediate or labeled address as a byte to the data segment in sequence |
| .byte i|a:X | Write the immediate or memory direct address as a byte to the data segment the specified number of times |
| .align X | Align the cursor to the nearest 2^X address |
| .ascii "string" | Write the characters of `string` to the data segment as bytes in sequence |
| .asciiz "string" | Write the characters of `string` to the data segment as bytes in sequence followed by a null byte |
| .space X | Move the cursor forward by X bytes |
| .include "file" | Insert the contents of `file` into the input stream in place of this directive |
| .message "msg" | Print `msg` to the standard output stream |
| .error "msg" | Print `msg` to the standard output stream and throw an assembler exception |
| .dbg "msg" | Dummy directive to test assembler |
| .dbgbp | In debug builds cause a debug breakpoint |
| .define IDENTIFIER XXXXX | Define an inline macro |
| .macro IDENTIFIER([parameter0[, parameter1]...]) | Begin a macro function definition |
| .end | End macro function definition |
| IDENTIFIER([argument0[, argument1]...]) | Insert the contents of the macro body with parameter replacement into the input stream in place of this directive |

### Registers

| ID | Name | Conventional Purpose |
| --- | --- | --- |
| 0 | zero | Hard-wired to 0 |
| 1 | at | Reserved for pseudo-instructions |
| 2-3 | v0-v1 | Return values from functions |
| 4-7 | a0-a3 | Arguments to functions |
| 8-17 | t0-t9 | Temporary data |
| 18-27 | s0-s9 | Saved registers |
| 28 | gp | Global Area Pointer |
| 29 | sp | Stack Pointer |
| 30 | fp | Frame Pointer |
| 31 | ra | Return Address |

### Address Encoding

Instructions are (1 word | 4 bytes | 32 bits) long.

Addresses are stored inline with the instruction. Bits used for the address fieldS may not be used for the instruction fields.

```text
|------DDDDDDDDDDDDDDDDDDDDDDDDDD| Direct Address Absolute
|----------------AAAAAAAAAAAAAAAA| Address Offset
|-----------RRRRR----------------| Register
```

### Addressing Modes

| Mode | Format | Effective Address |
| --- | --- | --- |
| Memory Direct | label | Address of label |
| Register Indirect | ($s) | Contents of `$s` |
| Immediate Offset | i($s) | Contents of `$s` + `i` |
| Label Offset | label($s) | Contents of `$s` + address of label |
| Label + Immediate | label+i | Address of label + `i` |
| Label + Immediate Offset | label+i($s) | Address of label + `i` + contents of `$s` |

### Instruction Encoding

Instructions are (1 word | 4 bytes | 32 bits) long.

```text
|OOOOOO--------------------------| Opcode
|------AAAAABBBBBCCCCC-----------| Register slots A, B, and C
|----------------IIIIIIIIIIIIIIII| Immediate
```

### Instruction Set

| KASM | Operation | Encoding |
| --- | --- | --- |
| add $d, $s, $t | $d = $s + $t; advancePC(); | 0000 00dd ddds ssss tttt t--- ---- ---- |
| addi $d, $s, i | $d = $s + i; advancePC(); | 0000 01dd ddds ssss iiii iiii iiii iiii |

### System Calls

System services are called by storing the service's code in the `$a0` register and executing the `sys` instruction. Some services require additional arguments to be executed; these arguments are stored in the `$ax` registers according to the table below. Some services return values; these return values can be accessed by reading them from the `$vx` registers according to the table below.

| Code | Service | Arguments | Returns |
| --- | --- | --- | --- |
| 0 | exit | $a1 = exit code |  |

### Standard Macro Library

The KASM Standard Macro Library is located in `std.kasm`.
