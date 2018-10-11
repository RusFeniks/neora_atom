.data

	regen_back dd 0041F9A1h

.code

my_effects proc
	
	MOV ESI,DWORD PTR DS:[EBX+EDI*4+3ECh] ; стандарт
	MOV ECX,DWORD PTR DS:[ESI+368h]
	
	PUSH EAX
	PUSH ECX
	PUSH EDX
	PUSH EBX
	
debuff_1XXYYY:
	MOV EDX,DWORD PTR DS:[00450BD0h]
	TEST EDX,EDX
	JNZ [skip_effects]
	MOV ECX, DWORD PTR DS:[ESI+198h]
	MOV EAX, DWORD PTR DS:[ECX+4h]
	TEST EAX, EAX
	JZ [skip_effects]
	MOV EBX, 1000
	XOR EDX,EDX
	DIV EBX
	TEST EDX,EDX
	JZ[debuff_1XXYYY_off]
	SUB EAX, 100
	SUB DWORD PTR DS:[ESI+2FCh], EAX
	SUB DWORD PTR DS:[ECX+4h], 1h
	JMP[skip_effects]
	
debuff_1XXYYY_off:
	MOV DWORD PTR DS:[ECX+4h], 0h
	JMP[skip_effects]
	
skip_effects:
	POP EBX
	POP EDX
	POP ECX
	POP EAX
	
	jmp [regen_back]
my_effects endp