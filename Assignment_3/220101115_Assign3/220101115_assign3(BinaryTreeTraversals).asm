section .data
    prompt1 db "Enter the number of nodes(max 100): ", 0
    prompt2 db "For each node, print x y z where x = current node, y=left child, z= right child (999 for NULL i.e. no child)",10, 0
    format db "%d",0
    error_prompt db "Error, wrong input format ",10,0
    check db "here",0
    print_format db "%d ",0
    inorder_prompt db "Inorder traversal is: ",0
    preorder_prompt db "Preorder traversal is: ",0
    postorder_prompt db "Postorder traversal is: ",0
    newline db 10

section .bss
    left resd 101
    right resd 101
    n resd 1
    temp resd 1

section .text
    global main
    extern printf, scanf

main:
    push prompt1
    call printf
    add esp, 4

    push n
    push format
    call scanf
    add esp,8

    push prompt2
    call printf
    add esp,4

    xor esi,esi ;esi will be the counting index for our input_loop

    jmp input_loop

input_loop:

    
    cmp esi,dword[n]
    je print_starter

    ;take input for current node i.e. esi +1 
    push temp
    push format
    call scanf
    add esp,8

    inc esi 

    cmp dword[temp],esi
    jne show_error

    lea eax,[left + esi*4]
    
    push eax
    push format
    call scanf
    add esp,8

    lea eax,[right + esi*4]
    
    push eax
    push format
    call scanf
    add esp,8

    jmp input_loop



show_error:
    push error_prompt
    call printf
    add esp,4

    jmp exit



print_starter:
    push inorder_prompt
    call printf
    add esp,4

    mov ecx,1 
    call inorder_fn

    ; call print_new_line

    push preorder_prompt
    call printf
    add esp,4

    mov ecx,1
    call preorder_fn

    ; call print_new_line

    push postorder_prompt
    call printf
    add esp,4

    mov ecx,1
    call postorder_fn
    ; call print_new_line

    jmp exit



inorder_fn:
    push ecx
    push ebx

    mov ebx,ecx

    cmp ecx,999
    je return_from_fn

    

    mov ecx, [left+ ebx*4]
    call inorder_fn

    push ebx
    push print_format
    call printf
    add esp,8
    
    mov ecx, [right + ebx*4]
    call inorder_fn
    
    jmp return_from_fn




postorder_fn:
    push ecx
    push ebx

    mov ebx,ecx

    cmp ecx,999
    je return_from_fn

    

    mov ecx, [left+ ebx*4]
    call postorder_fn
    
    mov ecx, [right + ebx*4]
    call postorder_fn

    push ebx
    push print_format
    call printf
    add esp,8
    
    jmp return_from_fn



preorder_fn:
    push ecx
    push ebx

    mov ebx,ecx

    cmp ecx,999
    je return_from_fn

    push ebx
    push print_format
    call printf
    add esp,8

    mov ecx, [left+ ebx*4]
    call preorder_fn
    
    mov ecx, [right + ebx*4]
    call preorder_fn
    
    jmp return_from_fn

return_from_fn:
    pop ebx
    pop ecx
    ret

; print_new_line:
;     push newline
;     call printf 
;     add esp,4

;     ret



exit:
    ret




    









