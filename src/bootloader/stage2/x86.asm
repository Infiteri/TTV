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



; bool _cdecl x86_Disk_Reset(u8 drive);
global _x86_Disk_Reset
_x86_Disk_Reset:
    push bp
    mov bp, sp
    
    mov ah, 0
    mov dl, [bx + 4]
    stc
    int 13h

    mov ax, 1
    sbb ax, 0

    mov sp, bp
    pop bp
    ret

; bool _cdecl x86_Disk_Read(u8 drive, u16 cylinder, u16 head, u16 sectors, u8 count, u8 far *out);
global _x86_Disk_Read
_x86_Disk_Read:
    push bp
    mov bp, sp

    push bx
    push es

    mov dl, [bp + 4]
    mov ch, [bp + 6]
    mov cl, [bp + 7]
    shl cl, 6

    mov dh, [bp + 8]

    mov al, [bp + 10]
    and al, 3Fh
    or cl, al

    mov al, [bp + 12]
    mov bx, [bp + 16]
    mov es, bx
    mov bx, [bp + 14]

    mov ah, 02h
    stc
    int 13h

    mov ax, 1
    sbb ax, 0

    pop es
    pop bx

    mov sp, bp
    pop bp
    ret


; bool _cdecl x86_Disk_GetDriveParams(u8 drive, u8 *driveOut, u16 *c, u16 *s, u16 *h);
global _x86_Disk_GetDriveParams
_x86_Disk_GetDriveParams:
    push bp             
    mov bp, sp         
    
    push es
    push bx
    push si
    push di

    mov dl, [bp + 4]
    mov ah, 08h
    mov di, 0
    mov es, di
    stc
    int 13h

    ; return
    mov ax, 1
    sbb ax, 0
    
    ; out params 
    mov si, [bp + 6]
    mov [si], bl

    ; cylinder
    mov bl, ch
    mov bh, cl
    shr bh, 6
    mov si, [bp + 8]
    mov [si], bx

    ; sectors
    xor ch, ch
    and cl, 3Fh
    mov si, [bp + 10]
    mov [si], cx

    ; heads
    mov cl, dh
    mov si, [bp + 12]
    mov [si], cx

    pop di
    pop si
    pop bx
    pop es

    mov sp, bp
    pop bp
    ret
