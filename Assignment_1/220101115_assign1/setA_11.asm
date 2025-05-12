section .data
    input_string db "a32 4## 1", 0      ; Input string (modifiable)
    alpha_count db 0                    ; Counter for alphabetic characters
    digit_count db 0                    ; Counter for digits
    special_count db 0                  ; Counter for special characters
    message_alpha db "Alphabets: ", 0    ; Message for alphabets
    message_digit db "Digits: ", 0      ; Message for digits
    message_special db "Special symbols: ", 0
    newline db 10, 0                    ; Newline character

section .bss
    num_result resb 10                  ; Buffer to store number in string format

section .text
    global _start

_start:
    mov esi, input_string              ; Load address of the input string

process_string:
    lodsb                               ; Load next byte from string into AL
    cmp al, 0                           ; Check if end of string is reached
    je display_results                  ; Jump to results if end of string

    ; Check if it's an uppercase alphabet
    cmp al, 'A'
    jge check_lower
    jmp check_for_digits

check_lower:
    cmp al, 'Z'
    jle count_alpha
    cmp al, 'a'                         ; Check if it's a lowercase alphabet
    jge check_second_lower
    jmp check_for_digits

check_second_lower:
    cmp al, 'z'
    jle count_alpha
    jmp check_for_digits

count_alpha:
    inc byte [alpha_count]              ; Increment alphabet counter
    jmp process_string

check_for_digits:
    cmp al, '0'                         ; Check if character is a digit
    jge check_digit_upper
    jmp count_specials

check_digit_upper:
    cmp al, '9'
    jle count_digit
    jmp count_specials

count_digit:
    inc byte [digit_count]              ; Increment digit counter
    jmp process_string

count_specials:
    inc byte [special_count]            ; Increment special symbol counter
    jmp process_string

display_results:
    ; Display number of Alphabets
    mov eax, 4                          ; sys_write system call
    mov ebx, 1                          ; File descriptor (stdout)
    mov ecx, message_alpha              ; Message: "Alphabets: "
    mov edx, 11                         ; Length of the message
    int 0x80                             ; Call kernel

    movzx eax, byte [alpha_count]       ; Load the alphabet count into eax
    call convert_to_string              ; Convert to string and print

    ; Display number of Digits
    mov eax, 4
    mov ebx, 1
    mov ecx, message_digit
    mov edx, 8
    int 0x80

    movzx eax, byte [digit_count]
    call convert_to_string

    ; Display number of Special Symbols
    mov eax, 4
    mov ebx, 1
    mov ecx, message_special
    mov edx, 17
    int 0x80

    movzx eax, byte [special_count]
    call convert_to_string

    ; Exit
    mov eax, 1                          ; sys_exit system call
    xor ebx, ebx                        ; Exit code 0
    int 0x80                             ; Call kernel

convert_to_string:
    mov ecx, num_result                 ; Address of the result buffer
    mov ebx, 10                         ; Divisor (for decimal conversion)
    xor edx, edx                        ; Clear remainder

convert_loop:
    div ebx                              ; Divide eax by 10 (result in eax, remainder in edx)
    add dl, '0'                          ; Convert remainder to ASCII character
    dec ecx                              ; Move buffer pointer backward
    mov [ecx], dl                        ; Store the character in buffer
    test eax, eax                        ; Check if quotient is 0
    jnz convert_loop                     ; Continue if quotient is non-zero

    ; Write the string to stdout
    mov edx, num_result                  ; Set the buffer address
    sub edx, ecx                         ; Calculate the string length
    mov eax, 4                           ; sys_write
    mov ebx, 1                           ; File descriptor (stdout)
    mov ecx, ecx                         ; Set pointer to the result string
    int 0x80                              ; Call kernel
    ret

