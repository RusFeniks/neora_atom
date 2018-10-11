.Data

mp_back	dd 0041FAEBh
hp_back	dd 0041F9E8h

.Code

mana_speed proc
	
	push ecx ; reserve
	push edx ; reserve
	push ebx ; reserve
	push edi ; reserve

	MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh] ; connetion to object
	MOV EDX,DWORD PTR DS:[ECX+368h] ; data-file
	MOV EDX,DWORD PTR DS:[EDX+6F4h] ; ID of object
	JMP [mp_std]

    mp_std:
	pop edi ; reserve
	pop ebx ; reserve
    pop edx ; reserve
    pop ecx ; reserve
    ADD DWORD PTR DS:[ESI+308h],2h ; standart regen
    
    JMP [mp_back]
       
mana_speed endp

hp_speed proc
	
	push ecx ; reserve
	push edx ; reserve
	push ebx ; reserve
	push edi ; reserve

	MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh] ; connetion to object
	MOV EDX,DWORD PTR DS:[ECX+368h] ; data-file
	MOV EDX,DWORD PTR DS:[EDX+6F4h] ; ID of object
	JMP [hp_std]

    hp_std:
	pop edi ; reserve
	pop ebx ; reserve
    pop edx ; reserve
    pop ecx ; reserve
    ADD DWORD PTR DS:[ESI+2FCh],0 ; standart regen

    JMP [hp_back]
    
hp_speed endp