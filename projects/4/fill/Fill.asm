// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be clearedk

(INIT)

    @KBD
    D=M

    @color
    M=0

    @SCREEN
    D=A

    @curr_addr
    M=D

    @8192
    D=A

    @counter
    M=D

    @counter
    M=D

    @KBD
    D=M

    @BLACK
    D;JGT // if KBD > 0

    @DRAW
    0;JMP

(BLACK)
    @color
    M=-1

(DRAW)

    @counter
    D=M

    @INIT
    D;JEQ

    @color
    D=M

    @color
    M=D

    @curr_addr
    A=M
    M=D

    @curr_addr
    D=M+1

    @curr_addr
    M=D

    @counter
    D=M-1

    @counter
    M=D

    @DRAW
    0;JMP

