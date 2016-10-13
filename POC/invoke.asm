
section .text

GLOBAL __invoke

;uint32_t _invoke(Method m, Object_t obj, size_t argc, uint32_t *arguments);
__invoke:
	push ebp
	mov ebp, esp

	push dword [ebp+12] ; pass the object as arg.
	mov ecx, [ebp+16] ; take the amount of elements
	mov edx, [ebp+20] ; take the address of the array
	

.cicle:
	cmp ecx, 0
	jz .doCall
	dec ecx
	lea eax, [edx+4*ecx]
	push dword [eax]

	jmp .cicle

.doCall:
	call dword [ebp+8]

	leave
	ret