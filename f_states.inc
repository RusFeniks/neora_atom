.data

NewMp_back dd 00412CAFh
NewMp_back2 dd 00412CB5h
NewMp_nomp dd 00412CD1h

S4XXXYYY_id dd 0h
S4XXXYYY_next dd 0h
S4XXXYYY_owner dd 0h

S60XXX_ID dd 0h
S60XXX_OWNER dd 0h

S1xxxyyy_back dd 00412C5Bh

State_checker dd 0h

.code
my_states proc

	PUSH EDX ;reserve
	PUSH EAX ;reserve
	PUSH ECX ;reserve
	PUSH EBX ;reserve
	PUSH EDI ;reserve

	cmp EAX, 30000
	jl[skip_myStates]
	cmp eax, 39999
	jle[state_3XYZZ]
	cmp eax, 49999
	jle[state_4YXXX]
	cmp eax, 94000
	jl[skip_myStates]
	cmp eax, 94999
	jle[state_94XXX]
	cmp EAX, 600000
	jl[skip_myStates]
	cmp eax, 600999
	jle[state_600XXX]
	cmp eax, 610000
	je[state_610000]
	cmp eax, 4000000
	jl[compare_end]
	cmp eax, 4999999
	jle[state_4xxxyyy]
compare_end:
	jmp[skip_myStates]
	
	
state_3XYZZ: ; ����� �������� ����������� �� �� x � ����������� ���� �� y. � ������ ������ zz.
	
	mov edx,dword ptr ds:[ebx+edi*4h+3ECh]
	cmp dword ptr ds:[edx+88h],0
	JG[skip_myStates]
	
	mov ecx,edx
	
	xor edx,edx
	mov ebx, 100
	div ebx ; �������� ��������� 2 ����� �������, ��� ������ � ECX
	push edx
	
	xor edx,edx
	mov ebx, 10
	div ebx ; �������� ����� ��� ������ ����
	push edx
	
	xor edx,edx
	mov ebx, 10
	div ebx ; �������� ����� ��� ������ ��
	push edx

	mov eax, dword ptr ds:[ecx+198h]
	
	pop ecx
	mov byte ptr ds:[eax+0h],cl
	
	pop ecx
	mov byte ptr ds:[eax+1h],cl
	
	pop ecx
	mov word ptr ds:[eax+2h],cx
	
	jmp[skip_myStates]

	
state_4YXXX: ; �������� ������� � ����������� itr kind 4000X
	
	
	; EAX - �����, ��������� �������� ������
	; EBX - ����� �������, �������� �������
	; ECX - �������� �������
	; EDX - ��� ��������� ��� �����
	; EDI - ����� �������, ��� ����� ������� ������ �������� � �������� ������ �����

		PUSH EAX ; ����� ��� ���� �� �����, ������� ��� � ����
		
		MOV ECX, DWORD PTR DS:[EBX+EDI*4h+3ECh] ; ����������� � �������
		MOV EDI, DWORD PTR DS:[ECX+354h] ; ������ ����� ��� �������
		CMP EDI, 0h ; ��������, �� ������� �������
		JL[state_4YXXX_skip] ; ���� ��� - ������
		
		MOV EAX,DWORD PTR DS:[EBX+EDI*4h+3ECh] ; ������� � EAX
		MOV EBX, DWORD PTR DS:[EAX+70h] ; ����������� � ������ �������
		IMUL EBX,1B0h ; �� ���� ��� ~ (��������� �� ������ ������)
		ADD EBX, DWORD PTR DS:[EAX+368h] ; ����� ����������� � ������ �������
		POP EDX ; ������ �����
		PUSH EAX ; �������� ������ �� �������
		MOV EAX, EDX ; ��� �������� �������� ����� � EAX
		PUSH ECX
		XOR EDX, EDX
		MOV ECX,1000
		DIV ECX ; ����� �� 1000, �������� � edx XXX
		PUSH EDX
		XOR EDX, EDX
		MOV ECX, 10
		DIV ECX ; ����� �� 10, �������� � edx y, � � eax �������� ����
		MOV EAX, EDX
		POP EDX
		POP ECX
		ADD EAX, 40000 ; ��� ������� �������� � itr kind
		
		MOV EDI,DWORD PTR DS:[EBX+958h] ; ����� ���������� itr ������
		
itr_kind4000X_check:
		CMP EDI, 0 ; ���������� � 0
		JLE [state_4YXXX_xxx] ; ���� ���� itr - ������
		PUSH EDX
		XOR EDX,EDX
		SUB EDI,1 ; ��� ������� ������
		IMUL EDX, EDI, 70h ; ����� �������� ������ itr kind'�
		ADD EDX,DWORD PTR DS:[EBX+960h] ; �������� ������ � ������ itr
		CMP EAX,DWORD PTR DS:[EDX+0h] ; ���������� itr kind � �����
		JE [state_4YXXX_success] ; ���� �������, ��� ������� ������
		POP EDX
		JMP [itr_kind4000X_check] ; ��������� ��������� ���� itr

state_4YXXX_success:
		POP EDI
		POP EAX ; ������ ������ �� �������
		FLD QWORD PTR DS:[EAX+58h] ; ������������ �� x
		CMP BYTE PTR DS:[EAX+80h],0h
		JE [state_4YXXX_success_facing]
		MOV BYTE PTR DS:[ECX+80h],1h
		FIADD DWORD PTR DS:[EBX+880h]
		FISUB DWORD PTR DS:[EDX+4h]
		JMP [state_4YXXX_success_fasing_next]
state_4YXXX_success_facing:
		MOV BYTE PTR DS:[ECX+80h],0h
		FISUB DWORD PTR DS:[EBX+880h]
		FIADD DWORD PTR DS:[EDX+4h]
state_4YXXX_success_fasing_next:
		FSTP QWORD PTR DS:[ECX+58h]
		FLD QWORD PTR DS:[EAX+40h]
		FSTP QWORD PTR DS:[ECX+40h]
		FLD QWORD PTR DS:[EAX+2Ch]
		FSTP QWORD PTR DS:[ECX+2Ch]

		
		FLD QWORD PTR DS:[EAX+60h] ; ������������ �� y
		FISUB DWORD PTR DS:[EBX+884h]
		FIADD DWORD PTR DS:[EDX+8h]
		FIST DWORD PTR DS:[ECX+14h]
		FSTP QWORD PTR DS:[ECX+60h]
		FLD QWORD PTR DS:[EAX+48h]
		FSTP QWORD PTR DS:[ECX+48h]
		FLD QWORD PTR DS:[EAX+30h]
		FSTP QWORD PTR DS:[ECX+30h]
		
		FLD QWORD PTR DS:[EAX+68h] ; ��������� Z ��������� �������
		CMP DWORD PTR DS:[EDX+4Ch],0h
		JE[state_4YXXX_success_z]
		FIADD DWORD PTR DS:[EDX+4Ch]
state_4YXXX_success_z:
		FSTP QWORD PTR DS:[ECX+68h] ; ���������� Z ����������� �������
		FLD QWORD PTR DS:[EAX+50h]
		FSTP QWORD PTR DS:[ECX+50h]
		FLD QWORD PTR DS:[EAX+38h]
		FSTP QWORD PTR DS:[ECX+38h]
		
		CMP DWORD PTR DS:[EDX+14h],0h
		JNE [state_4YXXX_dvx]
		
		PUSH ECX
		JMP[state_4YXXX_skip]
		
state_4YXXX_xxx:
		CMP EDX, 999
		JE [state_4YXXX_skip]
		MOV DWORD PTR DS:[ECX+70h],EDX
		MOV DWORD PTR DS:[ECX+80h],0
		JMP [state_4YXXX_skip]
		
state_4YXXX_dvx:
		FLD DWORD PTR DS:[EDX+14h] ; ��������� dvx �� itr
		FISTP DWORD PTR DS:[ECX+70h] ; ������ ���� ��� � dvx
		PUSH ECX
		JMP [state_4YXXX_skip]
		
state_4YXXX_skip:
		POP ECX
		JMP [skip_myStates]


state_600XXX:
		MOV ECX, DWORD PTR DS:[EBX+EDI*4h+3ECh]
		FLD QWORD PTR DS:[ECX+2Ch]
		FISTP DWORD PTR DS:[ECX+24h]
		CMP DWORD PTR DS:[ECX+24h],0h
		JE[skip_myStates]
		
		XOR EDX,EDX
		MOV EBX,1000
		DIV EBX
		MOV DWORD PTR DS:[ECX+70h],EDX
		
		JMP [skip_myStates]        

state_610000:
		PUSH ECX
		PUSH EDI
		PUSH EAX
		PUSH EBX
		
		MOV ECX, DWORD PTR DS:[EBX+EDI*4h+3ECh] ; ����������� � �������
		MOV EDI, DWORD PTR DS:[ECX+354h] ; ������ ����� ��� �������
		CMP EDI, -1h ; ��������, �� ������� �������
		JE[state_610000_end] ; ���� ��� - ������
		
		MOV EAX,DWORD PTR DS:[EBX+EDI*4h+3ECh] ; ������� � EAX
		
		
		MOV EDX,DWORD PTR DS:[ECX+198h]
		
		MOV EBX, DWORD PTR DS:[EAX+10h]
		ADD EBX, DWORD PTR DS:[EDX+18h]
		MOV DWORD PTR DS:[ECX+10h],EBX
		
		MOV EBX, DWORD PTR DS:[EAX+14h]
		ADD EBX, DWORD PTR DS:[EDX+1Ch]
		MOV DWORD PTR DS:[ECX+14h],EBX
		
		MOV EBX, DWORD PTR DS:[EAX+18h]
		ADD EBX, DWORD PTR DS:[EDX+20h]
		MOV DWORD PTR DS:[ECX+18h],EBX
		
		FILD DWORD PTR DS:[ECX+10h]
		FSTP QWORD PTR DS:[ECX+58h]
		FILD DWORD PTR DS:[ECX+14h]
		FSTP QWORD PTR DS:[ECX+60h]
		FILD DWORD PTR DS:[ECX+18h]
		FSTP QWORD PTR DS:[ECX+68h]
		
		FLD QWORD PTR DS:[EAX+40h]
		FSTP QWORD PTR DS:[ECX+40h]
		FLD QWORD PTR DS:[EAX+2Ch]
		FSTP QWORD PTR DS:[ECX+2Ch]
		
		FLD QWORD PTR DS:[EAX+48h]
		FSTP QWORD PTR DS:[ECX+48h]
		FLD QWORD PTR DS:[EAX+30h]
		FSTP QWORD PTR DS:[ECX+30h]
		
		FLD QWORD PTR DS:[EAX+50h]
		FSTP QWORD PTR DS:[ECX+50h]
		FLD QWORD PTR DS:[EAX+38h]
		FSTP QWORD PTR DS:[ECX+38h]
		
		JMP[state_610000_end]
		
state_610000_end:
		POP EBX
		POP EAX
		POP EDI
		POP ECX
		JMP [skip_myStates]



state_4xxxyyy:
		PUSHA
		
		SUB EAX, 4000000
		XOR EDX, EDX
		MOV ECX, 1000
		DIV ECX
		
		MOV S4XXXYYY_id, EAX ; id �������
		MOV S4XXXYYY_next, EDX ; ���� �������� ��� ���������
		MOV S4XXXYYY_owner, EDI ; ����� ��������� �������
		
		MOV ECX, 0 ; ECX - ������� ������� ��������
		
state_4xxxyyy_idcheck:
		CMP BYTE PTR DS:[EBX+ECX+4h],0
		JE [state_4xxxyyy_nextid]
		
		MOV EDI, DWORD PTR DS:[EBX+ECX*4+3ECh] ; EBX - ������� �� ����������� ������
		MOV EDX, DWORD PTR DS:[EDI+368h] ; EDX - ��������� �������
		
		MOV EAX, [S4XXXYYY_id] ; EAX - �������� ID
		CMP DWORD PTR DS:[EDX+6F4h],EAX ; ���������� id
		JNE[state_4xxxyyy_nextid]
		
		MOV EAX, [S4XXXYYY_owner] ; EAX - �������� ���������
		CMP DWORD PTR DS:[EDI+354h],EAX ; ���������� ����������
		JNE[state_4xxxyyy_nextid]
		
		MOV EDX, DWORD PTR DS:[EBX+EAX*4+3ECh]
		MOV EBX, DWORD PTR DS:[EDX+70h] 
		IMUL EBX,1B0h 
		ADD EBX, DWORD PTR DS:[EDX+368h] 
		MOV EAX, DWORD PTR DS:[EBX+87Ch] 
		ADD DWORD PTR DS:[EDX+308h],EAX
		MOV EAX, DWORD PTR DS:[EBX+850h] 
		ADD DWORD PTR DS:[EDX+2FCh],EAX
		
		MOV EAX, [S4XXXYYY_next]
		MOV DWORD PTR DS:[EDX+70h],EAX
		MOV DWORD PTR DS:[EDX+88h],0h
		JMP[state_4xxxyyy_endcheck]
state_4xxxyyy_nextid:
		INC ECX
		CMP ECX, 1000
		JL [state_4xxxyyy_idcheck]
state_4xxxyyy_endcheck:
		POPA
		JMP [skip_myStates]
		
		
state_94XXX:
	; ����� ��� ������� �� ����� � ���������� �� ���.
	PUSHA
	
	SUB EAX, 94000
	MOV ECX, 0
	
state_94XXX_id_check:
	CMP BYTE PTR DS:[EBX+ECX+4h],0
	JE[state_94XXX_next]
	
	MOV EDX, DWORD PTR DS:[EBX+ECX*4+3ECh]
	MOV ESI, DWORD PTR DS:[EDX+368h]
	CMP EAX, DWORD PTR DS:[ESI+6F4h]
	JNE [state_94XXX_next]
	CMP EDI, DWORD PTR DS:[EDX+354h]
	JNE [state_94XXX_next]
	
	MOV ESI, DWORD PTR DS:[EBX+EDI*4+3ECh]
	MOV EAX, DWORD PTR DS:[EDX+70h]
	IMUL EBX, EAX, 1B0h
	ADD EBX, DWORD PTR DS:[EDX+368h] ; ������������ � itr �������
	
	MOV EAX,DWORD PTR DS:[EBX+958h]

State_94XXX_itr_check:
	CMP EAX, 0
	JLE [State_94XXX_no_itrs] ; ���� ���� itr - ������
	SUB EAX,1
	IMUL EDI, EAX, 70h 
	ADD EDI,DWORD PTR DS:[EBX+960h]
	CMP DWORD PTR DS:[EDI+0h],94000
	JNE [State_94XXX_itr_check] ; ��������� ��������� ���� itr
	
	
	FLD QWORD PTR DS:[EDX+58h]
	FISUB DWORD PTR DS:[EBX+880h]
	FIADD DWORD PTR DS:[EDI+4h]
	FSTP QWORD PTR DS:[ESI+58h]
	FLD QWORD PTR DS:[EDX+40h]
	FSTP QWORD PTR DS:[ESI+40h]
	FLD QWORD PTR DS:[EDX+2Ch]
	FSTP QWORD PTR DS:[ESI+2Ch]
	
	MOV AL, BYTE PTR DS:[EDX+80h]
	MOV BYTE PTR DS:[ESI+80h], AL
	
	FLD QWORD PTR DS:[EDX+60h]
	FISUB DWORD PTR DS:[EBX+884h]
	FIADD DWORD PTR DS:[EDI+8h]
	FSTP QWORD PTR DS:[ESI+60h]
	FLD QWORD PTR DS:[EDX+48h]
	FSTP QWORD PTR DS:[ESI+48h]
	FLD QWORD PTR DS:[EDX+30h]
	FSTP QWORD PTR DS:[ESI+30h]
	
	FLD QWORD PTR DS:[EDX+68h]
	CMP DWORD PTR DS:[EDI+4Ch],0h
	JE[state_64XXX_noz]
	FIADD DWORD PTR DS:[EDI+4Ch]
state_64XXX_noz:
	FSTP QWORD PTR DS:[ESI+68h]
	FLD QWORD PTR DS:[EDX+50h]
	FSTP QWORD PTR DS:[ESI+50h]
	FLD QWORD PTR DS:[EDX+38h]
	FSTP QWORD PTR DS:[ESI+38h]
	
	
		
State_94XXX_no_itrs:
	JMP[State_94XXX_end]
	
	

state_94XXX_next:
	INC ECX
	CMP ECX, 1000
	JL [state_94XXX_id_check]

State_94XXX_end:
	POPA
	JMP[skip_myStates]


skip_myStates:	
	POP EDI ;reserve
	POP EBX ;reserve	
	POP ECX ;reserve                                                       
	POP EAX ;reserve
	POP EDX ;reserve
	
	call StateMore
	
	CMP EAX,2328h ; 9000
	
	JGE SHORT [recover_1]
	JMP [TransBack1]

recover_1:
	JMP [Transform1]


my_states endp


NewMp1xxxyyy proc
	
	PUSH ECX
	MOV ECX, DWORD PTR DS:[ESI+198h]
	CMP DWORD PTR DS:[ECX+10h],EAX
	JGE SHORT [NewMp1xxxyyy_back]
	MOV EBX,EDX
	POP ECX
	PUSH EAX
	JMP [NewMp1xxxyyy_NoMp]
	
NewMp1xxxyyy_back:
	POP ECX
	PUSH EAX
	
	CMP DWORD PTR DS:[0044D034h],0h
	JE [NewMp1xxxyyy_back2]

	MOV EAX,DWORD PTR DS:[EDI+4Ch]
	TEST EAX,EAX
	JE [NewMp1xxxyyy_back2]
	CDQ
	IDIV ECX
	CMP DWORD PTR DS:[ESI+308h],EDX
	JL [NewMp1xxxyyy_NoMp]
	IMUL EAX,EAX,0Ah
	ADD EAX,DWORD PTR DS:[EDI+20h]
	CMP DWORD PTR DS:[ESI+2FCh],EAX
	JLE [NewMp1xxxyyy_NoMp]
	SUB DWORD PTR DS:[ESI+308h],EDX
	SUB DWORD PTR DS:[ESI+2FCh],EAX
	ADD DWORD PTR DS:[ESI+34Ch],EAX
	POP EAX
	
	PUSH ECX
	MOV ECX, DWORD PTR DS:[ESI+198h]
	
	CMP [State_checker], 1h
	JE [SCheck_S1]
	CMP [State_checker], 5h
	JE [SCheck_S5]
	
	JMP[SCheck_End]
	
SCheck_S1:
	SUB DWORD PTR DS:[ECX+10h],EAX
	JMP[SCheck_End]
	
SCheck_S5:
	SUB DWORD PTR DS:[ECX+10h],EAX
	SUB DWORD PTR DS:[ECX+14h],EAX
	JMP[SCheck_End]
	
SCheck_End:
	POP ECX
	JMP [NewMp_back]
	
NewMp1xxxyyy_NoMp:
	POP EAX
	JMP[NewMp_nomp]

NewMp1xxxyyy_back2:
	POP EAX
	JMP [NewMp_back2]

NewMp1xxxyyy endp

StateZxxxyyy_check proc
	
	CMP EAX, 4999999
	JLE [state1xxxyyy_check]
	CMP EAX, 5999999
	JLE[state5xxxyyy_check]
	JMP[state1xxxyyy_check]
	
state1xxxyyy_check:
	MOV ECX,000F4240h
	CDQ
	IDIV ECX
	MOV [State_checker], 1h
	jmp [S1xxxyyy_back]
	
state5xxxyyy_check:
	MOV ECX,004C4B40h
	CDQ
	IDIV ECX
	MOV [State_checker], 5h
	jmp [S1xxxyyy_back]

StateZxxxyyy_check endp
















