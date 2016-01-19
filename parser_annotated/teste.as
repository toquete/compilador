	.data
x                              : dq
cesar                          : dq
guizao                         : dd
web                            : dd
teste                          : db
test1                          : db
ab                             : dd
cd                             : dd
	.text
	.global _start

_start:
	mov 654, _acc 
	mov _acc, ab
	mov 14.30e100, _acc 
	mov _acc, x
	mov x, _acc 
	add ab, _acc 
	mov $0, %rax
	call printf
	mov x, _acc 
	add ab, _acc 
	mov $0, %rax
	call printf
	mov teste, _acc 
	and true, _acc 
	or false, _acc 
	mov _acc, test1
	mov x, _acc 
	mov 15, _acc2
	add 7, _acc2
	cmp _acc, _acc2
	jne .L1
	mov 3, _acc2
	add 4, _acc2
	mul 7, _acc2
	mov _acc, web
	goto .L2
.L1:
	mov 3, _acc2
	add 7, _acc2
	mul 0, _acc2
	mov _acc, guizao
.L2:
.L3:
	mov 3.e-12, _acc2
	mov _acc, x
	mov x, _acc2
	mov 10, _acc2
	cmp _acc, _acc2
	je .L3
