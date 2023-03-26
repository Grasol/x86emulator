[bits 16]
[org 0xf000:0x0000]

mov eax, 50
mov ecx, 10

continue_sub:
sub eax, ecx
jns continue_sub

mov eax, 50
dec ecx
jnz continue_sub

inf_loop:
inc eax
jmp inf_loop
 

