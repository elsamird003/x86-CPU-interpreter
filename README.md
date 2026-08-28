# x86-lite CPU Interpreter (C)

A low-level educational project that simulates a simplified x86-style CPU in software. The program loads assembly-like instructions from a text file and executes them by updating simulated CPU state: registers, instruction memory, data memory, and a stack.

This is **not** a full x86 emulator. It interprets a small, text-based subset of x86-style assembly for learning how registers, memory, stacks, and control flow work at a low level.

## Features

- Models CPU state with registers (`%EAX`, `%EDX`, `%ECX`, `%ESP`, `%EBP`, `%EIP`)
- Loads programs from text instruction files
- Executes a subset of x86-style instructions
- Implements stack operations using `%ESP` and `%EBP`
- Supports conditional and unconditional control flow (`JMP`, `JE`, `JNE`, `JL`, `JG`, `CALL`, `RET`)
- Validates operands and memory accesses with error handling (`INSTRUCTION_ERROR`, `MEMORY_ERROR`, `PC_ERROR`)

## Supported Instructions

| Instruction | Description |
|-------------|-------------|
| `MOVL` | Move a value into a register or memory location |
| `ADDL` | Add source to destination |
| `PUSHL` | Push a value onto the stack |
| `POPL` | Pop a value from the stack |
| `CMPL` | Compare two operands and set the comparison flag |
| `JMP` | Unconditional jump to a label |
| `JE`, `JNE`, `JL`, `JG` | Conditional jumps based on the comparison flag |
| `CALL` | Call a function at a label |
| `RET` | Return from a function |
| `END` | Stop program execution |

## Operand Formats

| Format | Example | Meaning |
|--------|---------|---------|
| Register | `%EAX` | Value in register EAX |
| Constant | `$10` | Immediate value 10 |
| Memory | `(%EAX)` | Value at address in EAX |
| Memory + offset | `-4(%EBP)` | Value at EBP minus 4 |

Labels start with `.` (for example `.loop`) and are used as jump/call targets.

## Project Structure

```
x86_CPU_Emulator/
├── include/
│   └── interpreter.h   # CPU types and function declarations
├── src/
│   ├── main.c            # Program entry point
│   └── interpreter.c   # Emulator logic and instruction handlers
├── test.txt              # Sample instruction file
├── Makefile              # Build configuration
└── README.md
```

## Requirements

- GCC
- Make
- Linux or WSL (recommended)

## Build

From the project root:

```bash
make
```

This produces an executable named `interpreter`.

To remove build artifacts:

```bash
make clean
```

## Run

The program takes one argument: a path to an instruction file.

```bash
./interpreter test.txt
```

Example output:

```
Register EAX: 14
Register EDX: 50
Register ECX: 30
```

## Example Program

`test.txt` exercises move, add, compare, conditional jump, stack, call/return, and unconditional jump instructions:

```asm
MOVL $10, %EAX
ADDL %EDX, %EAX
CMPL %ECX, %EAX
JG .skip_fail
MOVL $99, %EAX
.skip_fail
MOVL $20, %EDX
PUSHL %EAX
PUSHL %EDX
POPL %ECX
POPL %EAX
CALL .add_one
MOVL $50, %EDX
JMP .done
.add_one
ADDL $1, %EAX
RET
.done
MOVL $30, %ECX
END
```

## How It Works

1. **`initialize_system`** — resets registers, memory, and stack pointers
2. **`load_instructions_from_file`** — reads instructions from a file into memory until `END`
3. **`execute_instructions`** — fetches instructions using `%EIP`, parses them, and dispatches to the appropriate handler
4. Individual **`execute_*`** functions — perform each instruction and enforce memory/operand safety

## Registers

| Register | Purpose |
|----------|---------|
| `%EAX`, `%EDX`, `%ECX` | General-purpose data registers |
| `%ESP` | Stack pointer |
| `%EBP` | Base/frame pointer for stack addressing |
| `%EIP` | Instruction pointer (program counter) |

## What This Project Is Not

- Not a complete x86 CPU or instruction set implementation
- Not a binary machine-code emulator (programs are text-based)
- Not dynamic heap allocation — memory is a fixed-size simulated array

