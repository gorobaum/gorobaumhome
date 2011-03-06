;------------------------------------------------------------------------------;
;--MAC211 - Laboratorio de Programação                                       --;
;--IME - USP - Primeiro semestre de 2010                                     --;
;--Turma 45 - Prof. Fabio Kon                                                --;
;--                                                                          --;
;--Primeiro Exercicio-programa                                               --;
;--Arquivo filtra.asm                                                        --;
;--                                                                          --;
;--Aluno:									Numero USP:                      --;
;--Wilson Kazuo Mizutani				    6797230                          --;
;--Thiago G. Nunes							6797289                          --;
;--                                                                          --;
;--06/04/2010                                                                --;
;------------------------------------------------------------------------------;

section .data

    ;-- Valores uteis fornecidos pelo monitor.
    ;-- Alguns modos de abertura de arquivo
    O_RDONLY equ 	  00
    O_WRONLY equ  	  01
    O_CREAT  equ    0100

    ;-- File descriptors (fd)
    STDIN    equ       0  ;-- codigo do fd da entrada padrao
    STDOUT   equ       1  ;-- codigo do fd da saida padrao
    
    ;-- Final de arquivo.
    EOF      equ      -1
    
    ;-- Codigo das chamadas ao sistema.
    S_CLOSE  equ       6
    S_OPEN   equ       5
    S_WRITE  equ       4
    S_READ   equ       3
    S_EXIT   equ       1
    
section .text

;------------------------------------------------------------------------------;

;-- Toda funcao tem isso no final.
finish:

    ;-- Restaura os registradores.
    pop     ebx
    pop     ecx
    pop     edx
    ;-- Restaura a pilha.
    leave
    ;-- Retorna.
    ret
    
;------------------------------------------------------------------------------;

section .data

    ;-- Tamanho dos buffers.
    m        equ 2000000  ;-- Tamnho do buffer de numeros. Max = 10^6 numeros.
    
    ;-- Posicao relativa dos parametros na pilha.
    p        equ       8  ;-- Posicao do parametro p
    r        equ      12  ;-- Posicao do parametro r
    namein   equ      16  ;-- Posicao do parametro nome_arquivo_entrada
    nameout  equ      20  ;-- Posicao do parametro nome_arquivo_saida
    
    ;-- Posicao relativa das variaveis locais na pilha.
    filein   equ     -16  ;-- File descriptor filein
    fileout  equ     -20  ;-- File descriptor fileout
    
    txt     db  "lol",0xa
    len     equ  $ - txt
    
section .bss

    buffin   resb     10  ;-- Buffer de entrada.
    buffnum  resb      m  ;-- Buffer dos numeros.
    count    resb      4  ;-- Contador.
    total    resb      4
    

section .text

    global filtra_os_primos

;-- int filtra_os_primos(unsigned short int p, unsigned short int r,
;--   char * nome_arquivo_entrada, char * nome_arquivo_saida)
filtra_os_primos:

    ;-- Desloca a pilha.
    push    ebp
    mov     ebp, esp
    
    ;-- Guarda o valor dos registradores.
    push    edx
    push    ecx
    push    ebx
    
    ;-- Abre espaco pras variaveis locais.
    sub     esp, 8
    
    ;-- Abre o arquivo de entrada.
    ;-- open(nome_arquivo_entrada, O_RDONLY, 0)
    mov     edx, 0
    mov     ecx, O_RDONLY
    mov     ebx, [ebp+namein]
    mov     eax, S_OPEN
    int     0x80
    cmp     eax, 1
    jl      err
    
    ;-- Guarda o file descriptor devolvido.
    mov     [ebp+filein], eax
    
    ;-- Cria o arquivo de saida, caso necessario.
    ;-- open(nome_arquivo_saida, O_CREAT, 0o755)
    mov     edx, 0o755          ;-- Valor fornecido pelo monitor.
    mov     ecx, O_CREAT
    mov     ebx, [ebp+nameout]
    mov     eax, S_OPEN
    int     0x80
    cmp     eax, 1
    jl      err
    
    ;-- Abre o arquivo de saida.
    ;-- open(nome_arquivo_saida, O_CREAT, 0)
    mov     edx, 0
    mov     ecx, O_WRONLY
    mov     ebx, [ebp+nameout]
    mov     eax, S_OPEN
    int     0x80
    cmp     eax, 1
    jge     read
    
    err:
    
        ;-- Nada a fazer, termina a funcao.
        xor     eax, eax
        mov     [count], eax
        jmp     finish_primos
        
    read:
        
        ;-- Guarda o file descriptor devolvido.
        mov     [ebp+fileout], eax
        
        ;-- Prepara o contador e mantem o fd de saida em edx.
        xor     ecx, ecx
        mov     edx, [ebp+fileout]
    
    ;-- Le os numeros de entrada e guarda os que estao entre p e r.
    loop_read:
    
        ;-- Le proximo numero.
        mov     eax, [ebp+filein]
        push    eax
        call    read_num
        add     esp, 4
        
        ;-- Verifica se chegou ao final do arquivo.
        cmp     ax, EOF
        jz      no_more
        
        ;-- Verifica se o numero esta' entre p e r. Se nao esta', pula para
        ;-- o proximo.
        cmp     ax, [ebp+p]
        jl      loop_read
        cmp     ax, [ebp+r]
        jg      loop_read
        
        ;-- Numero no intervalo, guarda ele em buffnum.
        mov     [ecx+buffnum], ax
        ;-- Incrementa contador.
        inc     ecx
        
        ;-- Repete para o proximo numero.
        jmp     loop_read
    
    no_more:
    
        mov     [total], ecx
        
        xor     ecx, ecx
        xor     ebx, ebx
        inc     ecx

    inc_cx:
    
        cmp     cx, 256
        jge     doit
        inc     cx

    test:
    
        xor     edx, edx
        mov     dx, -1
        cmp     [buffnum+ebx], dx
        xor     edx, edx
        jz      inc_ebx
        mov     ax, [buffnum+ebx]
        div     cx
        cmp     dx, 0
        jz      rmv_num
        inc     ebx
        cmp     ebx, [total]
        jge     inc_cx
        jmp     test

    rmv_num:
    
        mov edx, -1
        mov [buffnum+ebx], edx
        jmp inc_ebx

    inc_ebx:
    
        inc ebx
	    jmp test
	    
	doit:
    
    finish_primos:
    
        ;-- Desaloca as variaveis locais.
        add     esp, 8
    
        ;-- Fecha o arquivo de entrada.
        mov     ebx, [ebp+filein]
        mov     eax, S_CLOSE
        int     0x80
        
        ;-- Fecha o arquivo de saida.
        mov     ebx, [ebp+fileout]
        mov     eax, S_CLOSE
        int     0x80
        
        ;-- Armazena o numero de primos encontrados em eax como valor de retorno
        mov     eax, [count]
        jmp     finish
        
;------------------------------------------------------------------------------;

section .data

    ;-- Posicao relativa dos parametros.
    fdout    equ       8  ;-- Posicao do parametro fdout.
    num      equ      12  ;-- Posicao do parametro num.

section .text

    global print_num

;-- Imprime o numero na tela.
;-- print_num(fd fdout, unsigned short num)
print_num:

    ;-- Desloca a pilha.
    push    ebp
    mov     ebp, esp
    
    ;-- Guarda a informacao dos registradores.
    push    edx
    push    ecx
    push    ebx
    push    eax
    
    xor     ebx, ebx
    mov     ebx, ' '
    dec     esp
    mov     [esp], bl    
    
    ;-- TOs registradores sao usados da seguinte maneira:
    ;-- ax:     o numero sendo dividido.
    ;-- bx:     guarda o dez.
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
    inc     ecx
    
    ;-- Dividimos ax por dez consecutivamente, empilhando o resto na pilha e
    ;-- contando o numero de bytes.
    loop01:
        
        div     bx          ;-- ax = dx:ax/bx, dx = dx:ax%bx < 10 => dx = dl
        add     dl, '0'     ;-- ajusta para ascii
        dec     esp         ;-- abre espaco na pilha
        mov     [esp], dl   ;-- guarda o digito nela
        xor     dl, dl      ;-- fax dx ser zero de novo
        inc     ecx         ;-- incrementa o contador
        cmp     ax, 0       ;-- ve se foi o ultimo digito
        jnz     loop01      ;-- se nao foi repita
    
    ;-- Imprime o numero usando a pilha como buffer.     
    mov     edx, ecx         ;-- o tamanho e' o numero de bytes contados
    mov     ecx, esp         ;-- o buffer e' a pilha
    mov     ebx, [ebp+fdout] ;-- fd passado como argumento.
    mov     eax, 4           ;-- sys_write
    int     0x80             ;-- chama o kernel
    
    ;-- Limpa e finaliza.
    finish_print_num:
    
        ;-- Libera os digitos.
        add     esp, edx
        ;-- Funcao void, restaura o eax.
        pop     eax
        ;-- Finaliza.
        jmp     finish
;------------------------------------------------------------------------------;
    
section .data

    ;-- Posicao relativa dos parametros.
    fdin     equ       8  ;-- Posicao do parametro fdout.
    
    ;-- Posicao relativa das variaveis locais na pilha.
    rdnum    equ     -14  ;-- Numero sendo lido.
    
section .bss

    bufchar  resb      1
    
section .text

;-- unsigned short read_num(fd fdin)
;-- Devolve o proximo numero lido em fdin.
read_num:

    ;-- Desloca a pilha.
    push    ebp
    mov     ebp, esp
    
    ;-- Guarda a informacao dos registradores.
    push    edx
    push    ecx
    push    ebx
    
    ;-- Variavel local rdnum comeca com zero.
    xor     eax, eax
    push    ax
    
    loop02:
    
        ;-- read(fdin, bufchar, 1)
        mov     edx, 1
        mov     ecx, bufchar
        mov     ebx, [ebp+fdin]
        mov     eax, S_READ
        int     0x80
        
        ;-- Se read devolveu 0, acabou o arquivo.
        cmp     eax, 0
        jz      eof
        
        xor     eax, eax            ;-- zera eax
        mov     al, [bufchar]       ;-- guarda o char lido em al
        
        
        
        ;mov     edx, 1
        ;mov     ecx, bufchar
        ;mov     ebx, STDOUT
        ;mov     eax, 4
        ;int     0x80
        
        ;--jmp      exit
        
        xor     eax, eax            ;-- zera eax
        mov     al, [bufchar]       ;-- guarda o char lido em al
        
        ;-- Se o char nao e' digito, o numero acabou.
        cmp     al, '0'
        jl      finish_read_num
        
        cmp     al, '9'
        jg      finish_read_num
        
        mov     ebx, 10
        
        ;-- Acrescenta o digito no numero.
        mov     ax, [ebp+rdnum]
        mul     bx
        xor     ecx, ecx
        mov     cl, [bufchar]
        sub     cx, '0'
        add     ax, cx
        mov     [ebp+rdnum], ax
        
        
        jmp     loop02
    
    eof:
    
        mov     eax, EOF
        mov     [ebp+rdnum], ax
    
    finish_read_num:
    
        ;-- Devolve o numero lido em eax.
        xor     eax, eax
        pop     ax
        
        ;--push    ax
        ;--mov     ebx, STDOUT
        ;--push    ebx
        ;--call    print_num
        ;--add     esp, 6
        
        ;--mov     edx, len
        ;--mov     ecx, endline
        ;--mov     ebx, STDOUT
        ;--mov     eax, S_WRITE
        ;--int     0x80
        
        ;-- Finaliza.
        jmp     finish
    
    
;------------------------------------------------------------------------------;
    
;-- Termina o programa.
exit:

    mov     ebx, 0       ;-- codigo de saida
    mov     eax, S_EXIT  ;-- codigo da sub-rotina
    int     0x80         ;-- chama o kernel

    
    
    
        
