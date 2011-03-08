

    ;-- read(filein, bufin, n)
    ;--mov     edx, 10
    ;--mov     ecx, buffin
    ;--mov     ebx, [ebp+filein]
    ;--mov     eax, S_READ
    ;--int     0x80
    
    ;--mov     [count], eax
    
    ;--push    ax
    ;--mov     ebx, STDOUT
    ;--push    ebx
    ;--call    print_num
    ;--add     esp, 6
    
    ;-- Guarda o numero de bytes lidos.
    ;--mov     edx, 10
    ;--mov     ecx, buffin
    ;--mov     ebx, STDOUT
    ;--mov     eax, S_WRITE
    ;--int     0x80

section .data

    num     equ 8 ;-- posicao do parametro num.

section .text

    global print_num

;-- Imprime um numero na tela.
;-- print_num(uint16 num)
print_num:

    ;-- Desloca a pilha.
    push    ebp
    mov     ebp, esp
    
    ;-- Guarda a informacao dos registradores.
    push    edx
    push    ecx
    push    ebx
    push    eax
    
    ;-- TOs registradores sao usados da seguinte maneira:
    ;-- ax:     o numero sendo dividido.
    ;-- bx:     o numero total.
    ;-- ecx:    o contador de digitos.
    ;-- edx:    deve ser zero. Guarda o digito a ser empilhado.
    
    ;-- Poe o numero empilhado como paramentro em ax.
    xor     eax, eax        ;-- limpa eax
    mov     ax, [ebp+num]   ;-- o numero
    ;-- Guarda o numero 10 em bx
    xor     ebx, ebx        ;-- ebx = 0
    mov     bx, 10          ;-- bx = 10
    ;-- Zera ecx e edx.
    xor     edx, edx        ;-- edx = 0
    xor     ecx, ecx        ;-- ecx = 0
    
    
    ;-- Dividimos ax por dez consecutivamente, empilhando o resto na pilha e
    ;-- contando o numero de bytes.
    loop01:
        
        div     bx          ;-- ax = dx:ax/bx, dx = dx:ax%bx < 10 => dx = dl
        add     dl, '0'     ;-- ajusta para ascii
        push    edx         ;-- guarda o digito, usando 4 bytes
        xor     dl, dl      ;-- fax dx ser zero de novo
        add     ecx, 4      ;-- conta os quatro bytes do digito
        cmp     ax, 0       ;-- se foi o ultimo digito
        jz      print       ;-- imprime
        jmp     loop01      ;-- caso contrario repita
    
    ;-- Imprime o numero usando a pilha como buffer.     
    print:
        
        mov     edx, ecx    ;-- o tamanho e' o numero de bytes contados
        mov     ecx, esp    ;-- o buffer e' a pilha
        mov     ebx, 1      ;-- stdout
        mov     eax, 4      ;-- sys_write
        int     0x80        ;-- chama o kernel
    
    ;-- Limpa e finaliza.
    finish_print_num:
        ;-- Libera os digitos.
        add     esp, edx
        ;-- Restaura os registradores.
        pop     eax
        pop     ebx
        pop     ecx
        pop     edx
        leave
        ret
