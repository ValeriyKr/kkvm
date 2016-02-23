readw     ; [n]
dup       ; [n]
jmpe .end ; if n == 0 then out
push 0x20 ; [n] [space]
push 1    ; [n] [space] [1]
writew
writea    ; [n]
dec
dup       ; [n-1] [n-1]
jmpe .end ; if 1 we stops too
push 0x20
push 1
writew
writea
dec
dup
jmpe .end ; 1 and 1 -- first numbers

; calculate and print another numbers
push 1
dup
deep 2
.start
    swap
    deep 2
    add
    dup
    writew
    push 0x20
    writea
    deep 2
    deep 2
    dec
    dup
    jmpn .start

; Break line and exit
.end
    push 13
    writea
    halt
