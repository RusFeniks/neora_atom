.data
per1        dd 004214E4h
per2        dd 0042179Bh
per3        dd 00421552h
per4        dd 0042154Eh
per5        dd 0042179Bh
per6		dd 0042D5D4h
per7		dd 0042D312h
per8		dd 0042D47Ah

.code

perspective proc	
	CMP DWORD PTR DS:[450BB8h],1
	JE SHORT p4
	CMP DWORD PTR DS:[450BB8h],3
	JNZ SHORT p5
	MOV EAX,DWORD PTR DS:[EBX+7D4h]
	XOR ESI,ESI
	CMP DWORD PTR DS:[EAX+4D82380h],ESI
	MOV DWORD PTR SS:[ESP+44h],EDI
	JLE SHORT p6
	JMP SHORT p1
	LEA EBX,DWORD PTR DS:[EBX]
p1:	MOV ECX,DWORD PTR DS:[EBX+7D4h]
	MOV EDX,DWORD PTR DS:[ECX+ESI*4]
	MOV EAX,DWORD PTR DS:[EDX+6F4h]
	MOV ECX,DWORD PTR DS:[459FF8h]
	CMP ECX,0
	JE SHORT p3
	CMP EAX,ECX
	JNZ SHORT p2
	MOV DWORD PTR SS:[ESP+EDI*4+114h],ESI
	ADD EDI,1
p2:	MOV EAX,DWORD PTR DS:[EBX+7D4h]
	ADD ESI,1
	CMP ESI,DWORD PTR DS:[EAX+4D82380h]
	JL p1
	JMP per4
p3:	JMP per5
 
p4:	JMP per1
p5: JMP per2
p6: JMP per3
 
perspective endp
 
perspective2 proc
	MOV DWORD PTR DS:[450C1Ch],EBP
	MOV BYTE PTR DS:[450BB8h],3
	JMP per6
perspective2 endp
 
perspective3 proc
	MOV ECX,DWORD PTR DS:[EAX+EDI+4D45DBCh]
	MOV DWORD PTR DS:[459FF8h],ECX
	MOV EAX,DWORD PTR DS:[EAX+EDI+4D45DB0h]
	JMP per7
perspective3 endp
 
perspective4 proc
	MOV EAX,DWORD PTR DS:[EDX+EDI+4D45DB0h]
	MOV ECX,DWORD PTR DS:[EDX+EDI+4D45DBCh]
	MOV DWORD PTR DS:[459FF8h],ECX
	JMP per8
perspective4 endp