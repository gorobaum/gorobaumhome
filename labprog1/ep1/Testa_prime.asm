
bolinha equ 0

xor ecx, ecx
xor ebx, ebx
inc ecx

inc_ecx:
	cmp [ecx], 256
	jge fim 
	inc ecx

testa:
	xor edx, edx
	cmp [buffer+bolinha], -1
	jnz inc_bolinha
	mov eax, [buffer+bolinha]
	div ecx
	cmp edx, 0
	jz  tira_num
	inc bolinha
	cmp bolinha, totalnum
	jz inc_ecx
	jmp testa  
	
tira_num:
	mov edx, -1
	mov [buffer+bolinha], edx
	jmp inc_bolinha
	
inc_bolinha:
	inc bolinha
	jmp testa
