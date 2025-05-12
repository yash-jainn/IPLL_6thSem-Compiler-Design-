section .data
    prompt db "Enter a decimal number: ", 0
    prompt_len equ $ - prompt
    true_msg db "TRUE", 10
    true_len equ $ - true_msg
    false_msg db "FALSE", 10
    false_len equ $ - false_msg
    newline db 10

section .bss
    num resb 32        ; Buffer for input number
    binary resb 32     ; Buffer to store binary representation
    binary_len resb 1  ; Length of binary number

section .text
    global _start

_start:
    ; Print prompt
    mov eax, 4          ; syscall: write
    mov ebx, 1          ; file descriptor: stdout
    mov ecx, prompt     ; message to write
    mov edx, prompt_len ; message length
    int 0x80

    ; Read input
    mov eax, 3          ; syscall: read
    mov ebx, 0          ; file descriptor: stdin
    mov ecx, num        ; input buffer
    mov edx, 32         ; buffer size
    int 0x80

    ; Convert ASCII to number
    mov esi, num
    xor eax, eax        ; Clear EAX
    xor ebx, ebx        ; Clear EBX

convert_loop:
    movzx ecx, byte [esi]
    cmp cl, 10          ; Check for newline
    je convert_done
    sub cl, '0'         ; Convert ASCII to number
    imul eax, 10
    add eax, ecx
    inc esi
    jmp convert_loop

convert_done:
    ; Now EAX contains the decimal number
    mov ebx, binary     ; Destination for binary string
    xor ecx, ecx        ; Counter for binary digits

to_binary:
    mov edx, eax
    and edx, 1          ; Get least significant bit
    add dl, '0'         ; Convert to ASCII
    push edx            ; Save digit
    inc ecx             ; Increment counter
    shr eax, 1          ; Shift right to get next bit
    cmp eax, 0          ; Check if number is zero
    jnz to_binary

    ; Store binary length
    mov [binary_len], cl

    ; Pop digits in reverse order (correct binary representation)
store_binary:
    pop edx
    mov [ebx], dl
    inc ebx
    loop store_binary

    ; Print binary representation
    mov eax, 4          ; syscall: write
    mov ebx, 1          ; file descriptor: stdout
    mov ecx, binary     ; message to write
    movzx edx, byte [binary_len] ; message length
    int 0x80

    ; Print newline
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80

    ; Check if palindrome
    mov esi, binary           ; Start pointer
    mov edi, binary
    add edi, [binary_len]     ; End pointer
    dec edi

check_palindrome:
    cmp esi, edi
    jge is_palindrome         ; If pointers meet or cross, it's a palindrome
    
    mov al, [esi]
    mov bl, [edi]
    cmp al, bl
    jne not_palindrome
    
    inc esi
    dec edi
    jmp check_palindrome

is_palindrome:
    mov eax, 4               ; syscall: write
    mov ebx, 1              ; file descriptor: stdout
    mov ecx, true_msg       ; message to write
    mov edx, true_len       ; message length
    int 0x80
    jmp exit

not_palindrome:
    mov eax, 4              ; syscall: write
    mov ebx, 1             ; file descriptor: stdout
    mov ecx, false_msg     ; message to write
    mov edx, false_len     ; message length
    int 0x80

exit:
    mov eax, 1             ; syscall: exit
    xor ebx, ebx          ; status: 0
    int 0x80