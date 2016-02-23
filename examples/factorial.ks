readw     ; [N]
push 0x1  ; [N] 0x1
.start
    swap       ; 0x1 [N]
    dup        ; 0x1 [N] [N]
    jmpe .end  ; if [N] is zero, factorial is one
    swap       ; [N] 0x1
    deep 0x1   ; [N] 0x1 [N]
    mul        ; [N] 0x1*[N]=[N]
    swap       ; [N] [N]
    dec        ; [N] [N-1]
    swap       ; [N-1] [N]
    jmp .start ; Now we will check than N-1 greater zero, and mul N and N-1

; Write answer, break line and out
.end
    pop
    writew
    push 13
    writea
    halt