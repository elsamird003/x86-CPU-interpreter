# x86-lite CPU Interpreter (C)

A low-level educational project that simulates a simplified x86-style CPU in software. The program loads assembly-like instructions from a text file and executes them by updating simulated CPU state: registers, instruction memory, data memory, and a stack.

## What it does
- Models CPU state (`%EAX`, `%EDX`, `%ECX`, `%ESP`, `%EBP`, `%EIP`)
- Executes a subset of x86-style instructions: `MOVL`, `ADDL`, `PUSHL`, `POPL`, `CMPL`, `JMP`, `JE`, `JNE`, `JL`, `JG`, `CALL`, `RET`
- Implements stack operations via `%ESP` / `%EBP`
- Validates memory accesses and instruction operands (`MEMORY_ERROR`, `PC_ERROR`, etc.)

## What it is not
- Not a full x86 emulator (no complete instruction set or binary decoding)
- Not a hardware simulator — it interprets text-based assembly-like instructions

## Build & run
make
./interpreter test.txt
