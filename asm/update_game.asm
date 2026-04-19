section .text
    global asm_update_game
    extern asm_reset_ball

; void asm_update_game(GameState* state);
; RDI contains the pointer to state (struct offset size 60 bytes)

asm_update_game:
    push rbp
    mov rbp, rsp
    push rbx
    sub rsp, 8                  ; Align stack to 16 bytes for SysV ABI call parity

    ; ball_x += ball_dx
    mov eax, dword [rdi + 24]   ; ball_dx
    add dword [rdi + 16], eax   ; ball_x += ball_dx

    ; ball_y += ball_dy
    mov eax, dword [rdi + 28]   ; ball_dy
    add dword [rdi + 20], eax   ; ball_y += ball_dy

    ; --- Top / Bottom Collision ---
    ; if ball_y <= 1 (Top boundary)
    cmp dword [rdi + 20], 1
    jg .check_bottom
    mov dword [rdi + 20], 1
    mov eax, dword [rdi + 28]
    neg eax
    mov dword [rdi + 28], eax
    jmp .check_paddle1

.check_bottom:
    ; if ball_y >= field_height
    mov eax, dword [rdi + 12]   ; field_height
    cmp dword [rdi + 20], eax
    jl .check_paddle1
    mov dword [rdi + 20], eax
    mov eax, dword [rdi + 28]
    neg eax
    mov dword [rdi + 28], eax

.check_paddle1:
    ; --- Paddle 1 Collision ---
    ; if ball_x <= p1_x + 1  (ball is at or behind paddle X)
    mov eax, dword [rdi + 32]   ; p1_x
    inc eax
    cmp dword [rdi + 16], eax
    jg .check_paddle2

    ; check if within paddle Y span (p1_y - 2 <= ball_y <= p1_y + 2)
    mov ebx, dword [rdi + 36]   ; p1_y
    sub ebx, 2
    cmp dword [rdi + 20], ebx
    jl .score_p2                ; ball is above paddle
    add ebx, 4                  ; p1_y + 2
    cmp dword [rdi + 20], ebx
    jg .score_p2                ; ball is below paddle

    ; Hit on Paddle 1! Reverse X velocity
    mov dword [rdi + 16], eax   ; Force placement in front to prevent stickiness
    mov eax, dword [rdi + 24]
    cmp eax, 0
    jg .check_paddle2           ; Already escaping right, continue
    neg eax
    mov dword [rdi + 24], eax
    jmp .check_paddle2

.score_p2:
    ; P2 Scores if ball_x <= 0
    cmp dword [rdi + 16], 0
    jg .check_paddle2           ; Keep animating till fully offscreen
    inc dword [rdi + 52]        ; p2_score++
    call asm_reset_ball
    jmp .end

.check_paddle2:
    ; --- Paddle 2 Collision ---
    ; if ball_x >= p2_x - 1
    mov eax, dword [rdi + 44]   ; p2_x
    dec eax
    cmp dword [rdi + 16], eax
    jl .end

    ; check if within paddle Y span (p2_y - 2 <= ball_y <= p2_y + 2)
    mov ebx, dword [rdi + 48]   ; p2_y
    sub ebx, 2
    cmp dword [rdi + 20], ebx
    jl .score_p1
    add ebx, 4
    cmp dword [rdi + 20], ebx
    jg .score_p1

    ; Hit on Paddle 2! Reverse X velocity
    mov dword [rdi + 16], eax
    mov eax, dword [rdi + 24]
    cmp eax, 0
    jl .end                     ; Already escaping left, continue
    neg eax
    mov dword [rdi + 24], eax
    jmp .end

.score_p1:
    ; P1 Scores if ball_x is past right window margin
    mov eax, dword [rdi + 8]    ; field_width
    inc eax
    cmp dword [rdi + 16], eax
    jl .end
    inc dword [rdi + 40]        ; p1_score++
    call asm_reset_ball

.end:
    add rsp, 8
    pop rbx
    pop rbp
    ret