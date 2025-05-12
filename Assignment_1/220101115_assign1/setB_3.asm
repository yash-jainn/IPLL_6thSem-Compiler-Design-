section .data
    input_filename db "input.txt", 0    ; File name to open (null-terminated)
    file_buffer   times 1024 db 0        ; Buffer to store file contents (1 KB max)
    err_open_fail db "Error: Unable to open file.", 0
    err_len equ $ - err_open_fail

section .bss
    file_desc resd 1         ; File descriptor for the opened file
    bytes_processed resd 1   ; Number of bytes read from the file

section .text
    global _start

_start:
    ; Try to open the file in read-write mode (O_RDWR)
    mov eax, 5                ; sys_open system call
    mov ebx, input_filename   ; Address of the file name
    mov ecx, 2                ; Open mode (O_RDWR)
    int 0x80
    test eax, eax
    js open_error             ; Jump to open_error if the file cannot be opened
    mov [file_desc], eax      ; Store file descriptor

    ; Attempt to read the file content into the buffer
    mov eax, 3                ; sys_read system call
    mov ebx, [file_desc]      ; File descriptor
    mov ecx, file_buffer      ; Buffer to store the data
    mov edx, 1024             ; Maximum number of bytes to read
    int 0x80
    test eax, eax
    js open_error             ; Jump to open_error if reading fails
    mov [bytes_processed], eax ; Store the number of bytes read

    ; Process each byte in the buffer (replace non-printable characters with '*')
    mov ecx, file_buffer      ; Pointer to the buffer
    mov edx, [bytes_processed] ; Number of bytes to process

process_loop:
    test edx, edx
    jz reposition_file         ; If no more bytes, jump to reposition file
    mov al, byte [ecx]        ; Load current byte
    cmp al, 32
    jl replace_with_star      ; If less than 32 (non-printable), replace
    cmp al, 126
    jg replace_with_star      ; If greater than 126 (non-printable), replace
    jmp next_byte             ; Otherwise, move to the next byte

replace_with_star:
    mov byte [ecx], '*'       ; Replace current byte with '*'

next_byte:
    inc ecx                   ; Move to the next byte in the buffer
    dec edx                   ; Decrement the byte count
    jmp process_loop          ; Continue processing

reposition_file:
    ; Seek to the beginning of the file to overwrite it
    mov eax, 19               ; sys_lseek system call
    mov ebx, [file_desc]      ; File descriptor
    mov ecx, 0                ; Offset (seek to the beginning)
    mov edx, 0                ; Whence (SEEK_SET)
    int 0x80

    ; Write the modified buffer back to the file
    mov eax, 4                ; sys_write system call
    mov ebx, [file_desc]      ; File descriptor
    mov ecx, file_buffer      ; Buffer with modified data
    mov edx, [bytes_processed] ; Number of bytes to write
    int 0x80

    ; Display the modified content on the console
    mov eax, 4                ; sys_write system call
    mov ebx, 1                ; File descriptor (stdout)
    mov ecx, file_buffer      ; Buffer to print
    mov edx, [bytes_processed] ; Number of bytes to write
    int 0x80

    ; Close the file after processing
    mov eax, 6                ; sys_close system call
    mov ebx, [file_desc]      ; File descriptor
    int 0x80

    ; Exit the program successfully
    mov eax, 1                ; sys_exit system call
    xor ebx, ebx              ; Return code 0
    int 0x80

open_error:
    ; Print error message to stdout and exit
    mov eax, 4                ; sys_write system call
    mov ebx, 1                ; File descriptor (stdout)
    mov ecx, err_open_fail    ; Error message
    mov edx, err_len          ; Length of the error message
    int 0x80

    mov eax, 1                ; sys_exit system call
    mov ebx, 1                ; Return code 1 (error)
    int 0x80

