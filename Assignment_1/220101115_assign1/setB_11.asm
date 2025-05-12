; Compile with: nasm -f elf32 -o program.o program.asm
; Link with: gcc -m32 -no-pie program.o -o program

extern printf
extern scanf
extern exit

section .data
    prompt_n db "Enter the number of elements (n): ", 0
    prompt_k db "Enter the value of k: ", 0
    prompt_num db "Enter number %d: ", 0
    result_fmt db "The %dth largest number is: %lf", 10, 0
    scan_int db "%d", 0
    scan_float db "%lf", 0
    error_msg db "Error: k should be less than or equal to n", 10, 0

section .bss
    n: resd 1           ; Number of elements
    k: resd 1           ; K value
    numbers: resq 100   ; Array of doubles (max 100 elements)

section .text
global main

main:
    ; Preserve stack frame
    push ebp
    mov ebp, esp
    
    ; Get n
    push prompt_n       ; Push argument for printf
    call printf
    add esp, 4         ; Clean up stack

    push n             ; Push argument for scanf
    push scan_int
    call scanf
    add esp, 8         ; Clean up stack

    ; Get k
    push prompt_k
    call printf
    add esp, 4

    push k
    push scan_int
    call scanf
    add esp, 8

    ; Validate k <= n
    mov ecx, [k]
    cmp ecx, [n]
    jg error

    ; Read n numbers
    xor esi, esi       ; i = 0
input_loop:
    cmp esi, [n]
    jge sort_array

    ; Print prompt for current number
    push esi
    inc dword [esp]    ; i + 1 for display
    push prompt_num
    call printf
    add esp, 8

    ; Read number
    lea eax, [numbers + esi * 8]
    push eax
    push scan_float
    call scanf
    add esp, 8

    inc esi
    jmp input_loop

sort_array:
    ; Selection sort (descending order)
    mov ecx, [n]
    dec ecx            ; outer loop runs n-1 times
    xor esi, esi       ; i = 0
outer_loop:
    mov edi, esi
    inc edi            ; j = i + 1
inner_loop:
    cmp edi, [n]
    jge outer_next

    ; Compare numbers[j] with numbers[i]
    fld qword [numbers + esi * 8]
    fld qword [numbers + edi * 8]
    fcomip st1         ; Compare and pop
    fstp st0          ; Pop remaining value
    jbe skip_swap     ; Skip if numbers[i] >= numbers[j]

    ; Swap numbers
    fld qword [numbers + esi * 8]
    fld qword [numbers + edi * 8]
    fstp qword [numbers + esi * 8]
    fstp qword [numbers + edi * 8]

skip_swap:
    inc edi
    jmp inner_loop

outer_next:
    inc esi
    cmp esi, ecx
    jl outer_loop

    ; Print kth largest number
    mov eax, [k]
    dec eax           ; Convert to 0-based index
    fld qword [numbers + eax * 8]
    sub esp, 8        ; Make space for double
    fstp qword [esp]  ; Store double on stack
    push dword [k]    ; k value for format
    push result_fmt
    call printf
    add esp, 16       ; Clean up stack (8 for double + 4 for k + 4 for format)

    push dword 0      ; Exit status 0
    call exit         ; Exit program

error:
    push error_msg
    call printf
    add esp, 4

    push dword 1      ; Exit status 1
    call exit