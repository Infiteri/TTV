bits 16

section _TEXT class=CODE

global _x86_div64_32
_x86_div64_32:

    push bp             ; save old call frame
    mov bp, sp          ; initialize new call frame

    push bx

    mov eax, [bp + 8]   ; eax <- upper 32 bits of dividend
    mov ecx, [bp + 12]  ; ecx <- divisor
    xor edx, edx
    div ecx             ; eax - quot, edx - remainder

    mov bx, [bp + 16]
    mov [bx + 4], eax

    mov eax, [bp + 4]   ; eax <- lower 32 bits of dividend
                        ; edx <- old remainder
    div ecx

    mov [bx], eax
    mov bx, [bp + 18]
    mov [bx], edx

    pop bx

    mov sp, bp
    pop bp
    ret

; note: Args: Character, page
global _x86_WriteCharTeletype
_x86_WriteCharTeletype:
    push bp
    mov bp, sp

    push bx

    ; bp: old call frame 
    ; bp + 2: return argument 
    ; bp + 4: Character
    ; bp + 6, page
    ; todo: Try color?
    mov ah, 0Eh
    mov al, [bp + 4]
    mov bh, [bp + 6]

    int 10h

    pop bx
    mov sp, bp
    pop bp
    ret

