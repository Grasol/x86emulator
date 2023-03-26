[bits 16]
[org 0xf000:0x0000]

mov esi, string - 0xf000
mov ebx, 0x3bc
xor ecx, ecx

;mov al, 0x08
;mov byte [ebx + 2], al
mov byte [ebx + 2], 0x08
;mov al, 0x0c
;mov byte [ebx + 2], al
mov byte [ebx + 2], 0x0c

print_string:
mov al, cs:[esi + ecx]
test al, al
jz exit

busy:
mov dl, [ebx + 1]
test dl, 0x80
jz busy 

mov byte [ebx], al
;mov al, 1
;or byte [ebx + 2], al
or byte [ebx + 2], 1
;mov al, 0xfe
;and byte [ebx + 2], al
and byte [ebx + 2], 0xfe

inc ecx
jmp print_string

exit:
jmp exit


string:
db "Hello, World!", 0xa, 0
