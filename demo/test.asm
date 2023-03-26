[bits 16]
[org 0xf000:0xfff0]

mov eax, 0x12345678
xor eax, eax
jmp eax

