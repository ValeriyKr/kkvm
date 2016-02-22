readw
push 0x1
.start
    swap
    dup
    jmpe .end
    swap
    deep 0x1
    mul
    swap
    dec
    swap
    jmp .start
.end
    pop
    writew
    push 13
    writea