section .text
    global asm_reset_ball

; void asm_reset_ball(GameState* state);
; RDI contains pointer to GameState

asm_reset_ball:
    push rbp
    mov rbp, rsp
    
    ; ball_x = ext_max_x / 2
    mov eax, dword [rdi + 0]    ; ext_max_x
    sar eax, 1                  ; Arithmetic shift right halves the dimension
    mov dword [rdi + 16], eax
    
    ; ball_y = ext_max_y / 2
    mov eax, dword [rdi + 4]    ; ext_max_y
    sar eax, 1
    mov dword [rdi + 20], eax
    
    ; Alternate initial direction based on parity of sum of scores
    mov eax, dword [rdi + 40]   ; p1_score
    add eax, dword [rdi + 52]   ; p2_score
    and eax, 1
    jnz .go_left
    
.go_right:
    mov dword [rdi + 24], 1     ; dx = 1
    mov dword [rdi + 28], 1     ; dy = 1
    jmp .done
    
.go_left:
    mov dword [rdi + 24], -1    ; dx = -1
    mov dword [rdi + 28], -1    ; dy = -1
    
.done:
    pop rbp
    ret