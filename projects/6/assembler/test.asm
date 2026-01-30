// Test Cases for Hack Assembler Parser

// 1. A-Instruction
@100
@sum

// 2. L-Instruction
(LOOP)
(END)

// 3. C-Instruction (dest=comp)
D=M
M=D+1

// 4. C-Instruction (comp;jump)
0;JMP
D;JGT

// 5. C-Instruction (dest=comp;jump)
MD=M-1;JEQ
