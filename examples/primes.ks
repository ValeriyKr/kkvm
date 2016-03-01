readw
push 1

.checkNext
    inc         ; Now 2
    
    dup
    deep 2
    sub         ; Now 2 [Now-2]
    jmpe .print ; Now 2 -- print if is prime
    
    dup
    deep 2
    div
    swap
    pop             ; Now 2 [Now % 2]
    jmpn .checkNext ; Now 2
    
.newNumber
    pop            ; Now
    dec            ; [Now - 1]
    
    push 2
    deep 1
    sub
    jmpe .end
    
    push 1
    jmp .checkNext ; [Now - 1] 1

.print
    pop
    dup
    writew
    push 10
    writea
    dec
    
    push 2
    deep 1
    sub
    jmpe .end
    
    push 1
    jmp .checkNext

.end
    halt
