[bits 16]


mov eax, 0xffff0002
mov cx, ax

inf_loop:
adc ch, cl
jmp inf_loop

