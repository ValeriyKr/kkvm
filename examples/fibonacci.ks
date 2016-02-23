readw
dup
jmpe .end
push 0x20
push 1
writew
writea
dec
dup
jmpe .end
push 0x20
push 1
writew
writea
dec
dup
jmpe .end
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
.end
    push 13
    writea
    halt
