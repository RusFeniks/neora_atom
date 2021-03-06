.Data

e1_t1_e9 dd 0042F554h
e1_t2_e9 dd 0042F54Fh
e1_t3_e9 dd 0042F594h ;0042F58Fh ; ���� ������������ ������� ����� ����������

e_finish dd 0043087Ch ; ���� ������ ��� ������� ����� ���� ��������� � ����������.
					  ; � ���� ���� �� ������������, �� ����� ��������� �������� �� ����
e50_back1 dd 0042E918h

.Code


itr_effect_1xxx_to_9xxx proc

	CMP EAX,3 ; Ice Effect
	JE [Back1]
	
state999:
	CMP EAX, 3E7h ; 999
	JNE [state1xxx]
	
	PUSH EAX ; �����������
	PUSH EBX ; �����������
	PUSH ECX ; �����������
	PUSH EDX ; �����������
	
	MOV EAX,DWORD PTR DS:[EDI+2FCh] ; �������� �� ���������� � �B�
	CMP EAX, 0h ; ���������� �� � 1
	JG [backlol] ; ���� ������, ������
	
	MOV EAX,DWORD PTR DS:[EBX+364h] ; �������� ������� ���������� � �B�
	MOV DWORD PTR DS:[EDI+2FCh] ,100 ; ��� ����� 100 ��
	MOV DWORD PTR DS:[EDI+364h], EAX

backlol:
	POP EDX ; ���������������
	POP ECX ; ���������������
	POP EBX ; ���������������
	POP EAX ; ���������������
	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������


	JMP [e1_t3_e9] ; ��������� ���������

state1xxx:
	CMP EAX, 3E8h ; 1000
	JL [Back2]  ; ���� ������ 1000, ������ �����
	CMP EAX, 7CFh ; 1999
	JG [state2xxx]
	

	PUSH EAX ; �����������
	PUSH EBX ; �����������
	PUSH ECX ; �����������
	PUSH EDX ; �����������
	
	SUB EAX,3E8h ; -1000, �������� ����� ��� �����
	MOV ECX,DWORD PTR DS:[EBX+0A0h] ; ?
	MOV EDX,DWORD PTR DS:[ESI+ECX*4+3ECh] ; ����������� � ����������
	MOV EBX,DWORD PTR DS:[EDX+2FCh] ; �������� �� ���������� � �B�
	SUB EBX, EAX ; �������� �� �� ������ ����.
	CMP EBX, 0 ; ���������, ��� ���������� �������� �� ������ ����
	JGE [valid_1xxx]
	MOV EBX, 0 ; ���� ����� ���� � �����, ���������� 0, ����-���
	valid_1xxx:
	MOV DWORD PTR DS:[EDX+2FCh],EBX ; ���������� ���������� ��

	POP EDX ; ���������������
	POP ECX ; ���������������
	POP EBX ; ���������������
	POP EAX ; ���������������
	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������


	JMP [e1_t3_e9] ; ��������� ���������


state2xxx:
	CMP EAX, 0BB7h ; 2999
	JG [state3xxx]

	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type2] ; ��������� ���������, �� ������������ ����

	PUSH EAX ; �����������
	PUSH EBX ; �����������
	PUSH ECX ; �����������
	PUSH EDX ; �����������
	
	SUB EAX,7D0h ; -2000, ����� ��� ������
	MOV ECX,DWORD PTR DS:[EBX+0A0h] ; ?
	MOV EDX,DWORD PTR DS:[ESI+ECX*4+3ECh] ; ����������� � ����������
	ADD DWORD PTR DS:[EDX+2FCh],EAX ; ��������� ���������� ��

	POP EDX ; ���������������
	POP ECX ; ���������������
	POP EBX ; ���������������
	POP EAX ; ���������������
	
	wrong_type2:	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������
	
	JMP [e1_t3_e9] ; ��������� ���������

state3xxx:
	CMP EAX, 0F9Fh ; 3999
	JG [state4xxx]

	PUSH EAX ; �����������
	PUSH ECX ; �����������
	PUSH EDX ; �����������
	
	SUB EAX,0BB8h ; -3000
	MOV ECX,DWORD PTR DS:[EBX+0A0h] ; ?
	MOV EDX,DWORD PTR DS:[ESI+ECX*4+3ECh] ; ����������� � ����������
	ADD DWORD PTR DS:[EDX+2FCh],EAX ; ��������� ���������� ��

	POP EDX ; ���������������
	POP ECX ; ���������������
	POP EAX ; ���������������

	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������
	
	JMP [e1_t3_e9] ; ��������� ���������

state4xxx:
	CMP EAX, 1387h ; 4999
	JG [state5xxx]

	PUSH EAX ; �����������
	PUSH EBX ; �����������
	PUSH ECX ; �����������
	PUSH EDX ; �����������
	
	SUB EAX,0FA0h ; -4000
	MOV ECX,DWORD PTR DS:[EBX+0A0h] ; ?
	MOV EDX,DWORD PTR DS:[ESI+ECX*4+3ECh] ; ����������� � ����������
	SUB DWORD PTR DS:[EDX+308h],EAX ; �������� ����

	POP EDX ; ���������������
	POP ECX ; ���������������
	POP EBX ; ���������������
	POP EAX ; ���������������
	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������
	
	JMP [e1_t3_e9] ; ��������� ���������



state5xxx:
	CMP EAX, 176Fh ; 5999
	JG [state6xxx]
	
	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type5] ; ��������� ���������, �� ������������ ����

	PUSH EAX ; �����������
	PUSH EBX ; �����������
	PUSH ECX ; �����������
	PUSH EDX ; �����������
	
	SUB EAX,1388h ; -5000
	MOV ECX,DWORD PTR DS:[EBX+0A0h] ; ?
	MOV EDX,DWORD PTR DS:[ESI+ECX*4+3ECh] ; ����������� � ����������
	ADD DWORD PTR DS:[EDX+308h],EAX ; ��������� ����

	POP EDX ; ���������������
	POP ECX ; ���������������
	POP EBX ; ���������������
	POP EAX ; ���������������
	
	wrong_type5:	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������
	
	JMP [e1_t3_e9] ; ��������� ���������



state6xxx:
	CMP EAX, 1B57h ; 6999
	JG [state7xxx]

	PUSH EAX ; �����������
	PUSH EBX ; �����������
	PUSH ECX ; �����������
	PUSH EDX ; �����������
	
	SUB EAX,1770h ; -6000
	MOV ECX,DWORD PTR DS:[EBX+0A0h] ; ?
	MOV EDX,DWORD PTR DS:[ESI+ECX*4+3ECh] ; ����������� � ����������
	ADD DWORD PTR DS:[EDX+308h],EAX ; ��������� ����

	POP EDX ; ���������������
	POP ECX ; ���������������
	POP EBX ; ���������������
	POP EAX ; ���������������
	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������
	
	JMP [e1_t3_e9] ; ��������� ���������


state7xxx:
	CMP EAX, 1F3Fh ; 7999
	JG [state8xxx]
	
	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type7] ; ��������� ���������, �� ������������ ����

	PUSH EAX ; �����������
	
	SUB EAX,1B58h ; -7000
	SUB DWORD PTR DS:[EDI+308h], EAX ; �������� ����

	POP EAX ; ���������������
	
	wrong_type7:	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������
	
	JMP [e1_t3_e9] ; ��������� ���������



state8xxx:
	CMP EAX, 2327h ; 8999
	JG [state9xxx] 
	
	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type8] ; ��������� ���������, �� ������������ ����

	PUSH EAX ; �����������
	PUSH EBX ; �����������
	PUSH ECX ; �����������
	PUSH EDX ; �����������
	
	SUB EAX,1F40h ; -8000
	SUB DWORD PTR DS:[EDI+308h], EAX ; �������� ����
	
	MOV ECX,DWORD PTR DS:[EBX+0A0h] ; ?
	MOV EDX,DWORD PTR DS:[ESI+ECX*4+3ECh] ; ����������� � ����������
	ADD DWORD PTR DS:[EDX+308h],EAX ; ��������� ����
	
	POP EDX ; ���������������
	POP ECX ; ���������������
	POP EBX ; ���������������
	POP EAX ; ���������������
	
	wrong_type8:	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������
	
	JMP [e1_t3_e9] ; ��������� ���������


state9xxx:
	CMP EAX, 270Fh ; 9999
	JG [state1xxxx] ;  ��������� ������
	
	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type9] ; ��������� ���������, �� ������������ ����

		PUSH ECX
		PUSH EDX
		
		IMUL ECX,DWORD PTR DS:[EBX+70h],1B0h
		ADD ECX,DWORD PTR DS:[EBX+368h] ;
		MOV ECX,DWORD PTR DS:[ECX+934h] ; �������� ������� ���������� � ecx
		
		IMUL EDX,DWORD PTR DS:[EDI+70h],1B0h
		ADD EDX,DWORD PTR DS:[EDI+368h] ;
		MOV EDX,DWORD PTR DS:[EDX+934h] ; �������� ������� ���������� � edx
		
		;������� ������
		CMP ECX,EDX
		JL [level9_below] ; ������� ����
		CMP ECX,EDX
		JG [level9_above] ; ������� ����
		CMP ECX,EDX
		JE [levels9_equal] ; ������ �����
		
		POP EDX
		POP ECX
		
level9_below:
		
		POP EDX
		POP ECX
		JMP[wrong_type9]
		
level9_above:
		
		POP EDX
		POP ECX
		PUSH EAX ; �����������
		SUB EAX,2328h ; -9000
		MOV DWORD PTR DS:[EDI+70h],EAX ; ���������� ����
		POP EAX ; ���������������
		JMP[wrong_type9]
		
levels9_equal:
		POP EDX
		POP ECX
		JMP[wrong_type9]


wrong_type9:	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������
	
	JMP [e1_t3_e9] ; ��������� ���������
	

state1xxxx:
	CMP EAX, 4E1Fh ;19999
	JG [state20xxx] ;  ��������� ������
	
	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type10] ; ��������� ���������, �� ������������ ����
	
	SUB EAX, 2710h
	
	PUSH EDI
	PUSH EDX
	
	XOR EDI, EDI

proverka:
	CMP DWORD PTR DS:[ESI+EDI+4h],0h
	JE [no_object]
	
	MOV EDX, DWORD PTR DS:[ESI+EDI*4+3ECh] 
	MOV DWORD PTR DS:[EDX+150h], -1
	PUSH EAX
	MOV EAX, DWORD PTR DS:[EDX+2FCh]
	MOV DWORD PTR DS:[EDX+198h], EAX
	POP EAX
	
no_object:
	INC EDI
	CMP EDI, 1000
	JL [proverka]
	
	POP EDX
	POP EDI

	MOV DWORD PTR DS:[EBX+150h], -1
	PUSH EAX
	MOV EAX, DWORD PTR DS:[EBX+2FCh]
	MOV DWORD PTR DS:[EBX+198h], EAX
	POP EAX
	MOV DWORD PTR DS:[EDI+150h], -1
	MOV DWORD PTR DS:[EDI+198h], -1
	MOV DWORD PTR DS:[ts_timer], EAX ;������ �������
	MOV DWORD PTR DS:[ts_type],4 ; ��� ���������
	
	wrong_type10:	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������

	JMP [e1_t3_e9] ; ��������� ���������


state20xxx:
	CMP EAX, 5207h ; 20999
	JG [state30xxx]

	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JE [type0]
	
		PUSH ECX
		PUSH EDX
		
		IMUL ECX,DWORD PTR DS:[EBX+70h],1B0h
		ADD ECX,DWORD PTR DS:[EBX+368h] ;
		MOV ECX,DWORD PTR DS:[ECX+934h] ; �������� ������� ���������� � ecx
		
		IMUL EDX,DWORD PTR DS:[EDI+70h],1B0h
		ADD EDX,DWORD PTR DS:[EDI+368h] ;
		MOV EDX,DWORD PTR DS:[EDX+934h] ; �������� ������� ���������� � edx
		
		;������� ������
		CMP ECX,EDX
		JL [level20_below] ; ������� ����
		CMP ECX,EDX
		JG [level20_above] ; ������� ����
		CMP ECX,EDX
		JE [levels20_equal] ; ������ �����
		
		POP EDX
		POP ECX
		
level20_below:
		
		POP EDX
		POP ECX
		JMP[type0]
		
level20_above:
		
		POP EDX
		POP ECX
		JMP[wrong_type20]
		
levels20_equal:
		POP EDX
		POP ECX
		PUSH EAX
		SUB EAX,20000 ; -20000
		MOV DWORD PTR DS:[EBX+70h],EAX ; ���������� ����
		POP EAX
		JMP[wrong_type20]
		
type0:
	PUSH EAX
	SUB EAX,20000 ; -20000
	MOV DWORD PTR DS:[EBX+70h],EAX ; ���������� ����
	POP EAX
	
	
wrong_type20:	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG

	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������
	
	JMP [e1_t3_e9] ; ��������� ���������


state30xxx:
	CMP EAX, 30999 ; 30999
	JG [state31xxx] ;  ��������� ������
	
	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type30] ; ��������� ���������, �� ������������ ����
	
	PUSH EAX ; �����������
	PUSH EBX ; �����������
	PUSH ECX ; �����������
	PUSH EDX ; �����������

	XOR ECX, ECX
	MOV CL, BYTE PTR DS:[EBX+80h]
	CMP BYTE PTR DS:[EDI+80h],CL
	JE[state30xxx_cancel]
	
	FLD QWORD PTR DS:[EDI+58h]
	FSTP QWORD PTR DS:[EBX+58h]	
	
	FLD QWORD PTR DS:[EDI+68h]
	FSTP QWORD PTR DS:[EBX+68h]
	
	
	SUB EAX,30000 ; -30000
	MOV DWORD PTR DS:[EDI+70h],EAX ; ���������� ����
	
	IMUL ECX,DWORD PTR DS:[EBX+70h],1B0h
	ADD ECX,DWORD PTR DS:[EBX+368h] ;
	MOV ECX,DWORD PTR DS:[ECX+864h] ; �������� ������� ���������� � ecx
	CMP ECX,0
	JE[state30xxx_noHitUa]
	MOV DWORD PTR DS:[EBX+70h],ECX ; ���������� ����
	JMP[state30xxx_cancel]
	
state30xxx_noHitUa:
	MOV DWORD PTR DS:[EBX+70h],EAX ; ���������� ����
	JMP[state30xxx_cancel]
	
state30xxx_cancel:	
	POP EDX ; ���������������
	POP ECX ; ���������������
	POP EBX ; ���������������
	POP EAX ; ���������������
	
wrong_type30:	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������
	
	JMP [e1_t3_e9] ; ��������� ���������

state31xxx:
	CMP EAX, 31999 ; 30999
	JG [state32xxx] ;  ��������� ������
	
	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type31] ; ��������� ���������, �� ������������ ����
	
	PUSH EAX ; �����������
	SUB EAX,31000 ; -31000
	MOV DWORD PTR DS:[EDI+70h],EAX ; ���������� ����
	POP EAX ; ���������������
	
wrong_type31:	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������
	JMP [e1_t3_e9] ; ��������� ���������	


state32xxx:
	CMP EAX, 32999 ; 32999
	JG [effect_1XXYYY] ;  ��������� ������
	
	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type32] ; ��������� ���������, �� ������������ ����
	
	PUSH EAX ; �����������
	
	FLD QWORD PTR DS:[EDI+58h]
	FSTP QWORD PTR DS:[EBX+58h]	
	
	FLD QWORD PTR DS:[EDI+68h]
	FSTP QWORD PTR DS:[EBX+68h]
	
	
	SUB EAX,32000 ; -32000
	MOV DWORD PTR DS:[EBX+70h],EAX ; ���������� ����

	POP EAX ; ���������������
	
wrong_type32:	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������
	
	JMP [e1_t3_e9] ; ��������� ���������



effect_1XXYYY:
	CMP EAX, 186A0h ; ���� �� ������ ������ ��������
	JL [Back2]
	CMP EAX, 30D3Fh ; 199999
	JG [Back2]
	
	PUSHAD
	
	CMP DWORD PTR DS:[EDI+2FCh],0
	JLE [effect_1XXYYY_end]
	
	CMP DWORD PTR DS:[EBX+354h],-1
	JE [effect_1XXYYY_noOwner]
	
	MOV EDX,DWORD PTR DS:[458B00h]
	MOV ECX,DWORD PTR DS:[EBX+354h]
	MOV EBX,DWORD PTR DS:[EDX+ECX*4+3ECh]
	
effect_1XXYYY_noOwner:
	MOV EBP,EBX
	
	SUB EAX, 100000
	MOV ECX, 1000
	XOR EDX, EDX
	DIV ECX
	
	MOV EBX, EAX
	MOV ESI, EDX
	
	MOV ECX, DWORD PTR DS:[EDI+198h]
	CMP dword ptr ds:[ECX+4h],0h
	JLE[noadd_time]
	MOV EAX, dword ptr ds:[ECX+4h]
	
	SUB EAX, 100000
	MOV ECX, 1000
	XOR EDX, EDX
	DIV ECX
	
	CMP EBX, EAX
	JL [noadd_damage]
	MOV EAX, EBX
noadd_damage:
	CMP ESI, EDX
	JL [noadd_time]
	MOV EDX, ESI
noadd_time:
	IMUL EAX,1000
	ADD EAX, EDX
	ADD EAX, 100000
	
	MOV ECX, DWORD PTR DS:[EDI+198h]
	mov dword ptr ds:[ECX+4h], eax
	MOV DWORD PTR DS:[ECX+24h],EBP
effect_1XXYYY_end:
	POPAD

	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ������������ ���
	PUSH DWORD PTR DS:[ECX+28h]
	MOV EAX,DWORD PTR DS:[EDI+10h]
	JMP [e1_t3_e9]
	

Back1: 
	JMP [e1_t1_e9] ; ���� ��� ��������� �����, �� ���� ������
Back2:
	JMP [e1_t2_e9] ; ���� �� �������� ������ ��������, ���� �� ���� �� ������
Back3:
	JMP [e_finish]
	
Back4:
	POP EDX ; ���������������
	POP ECX ; ���������������
	POP EBX ; ���������������
	POP EAX ; ���������������
	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������
	
	JMP [e1_t3_e9] ; ��������� ���������

itr_effect_1xxx_to_9xxx endp


effect50 proc

		PUSH EDX
		PUSH ECX
		
		IMUL ECX,DWORD PTR DS:[EBX+70h],1B0h ; �������� �������� ������
		FSTP ST
		ADD ECX,DWORD PTR DS:[EBX+368h]
		LEA ECX,DWORD PTR DS:[ECX+958h] 
		CMP DWORD PTR DS:[ECX],0 	
		JLE [skip]
		MOV ECX,DWORD PTR DS:[ECX+8]
		MOV EDX,DWORD PTR DS:[ECX+2Ch] ; ������
		CMP EDX, 50
		JE [eff_50]
		CMP EDX, 30000
		JL [leveling_system]
		CMP EDX, 30999
		JLE [eff_50]
		CMP EDX, 31999
		JLE [eff_50]
		CMP EDX, 100000
		JL [leveling_system]
		CMP EDX, 199999
		JLE [eff_50]
		
leveling_system:

		PUSH ECX
		PUSH EDX
		
		IMUL ECX,DWORD PTR DS:[EBX+70h],1B0h
		ADD ECX,DWORD PTR DS:[EBX+368h] ;
		MOV ECX,DWORD PTR DS:[ECX+934h] ; �������� ������� ���������� � ecx
		
		IMUL EDX,DWORD PTR DS:[EDI+70h],1B0h
		ADD EDX,DWORD PTR DS:[EDI+368h] ;
		MOV EDX,DWORD PTR DS:[EDX+934h] ; �������� ������� ���������� � edx
		
		
izanami_check:
		PUSH EAX
		PUSH EDX
		PUSH EBX
		PUSH EDI

izanami_itachi_attacker:
		MOV EAX, DWORD PTR DS:[EBX+368h]
		CMP DWORD PTR DS:[EAX+6F4h],57 
		JNE[izanami_itachi_attacked] ; ���� �� ������� �� �� ���
		
		MOV EDX, DWORD PTR DS:[EDI+368h]
		CMP DWORD PTR DS:[EDX+6F8h],0
		JNE[izanami_itachi_attacked] ; ���� �� ��� ����  �� ���������
		
		MOV EAX, DWORD PTR DS:[EBX+198h]
		CMP DWORD PTR DS:[EAX+2Ch],1
		JNE[izanami_itachi_attacked] ; ���� ������� �� ��� ��� � ��� ������ ��� ��� ����� ��� 
		
		MOV EAX, DWORD PTR DS:[EBX+198h]
		MOV DWORD PTR DS:[EAX+2Ch], 3
		MOV EAX, DWORD PTR DS:[EDI+198h]
		MOV DWORD PTR DS:[EAX+2Ch], 2
		
		MOV EDI, 0h
		
		JMP[Izanami_start_save_params]
		
		
izanami_itachi_attacked:
		MOV EAX, DWORD PTR DS:[EDI+368h]
		CMP DWORD PTR DS:[EAX+6F4h],57 
		JNE[izanami_check_back] ; ���� �� ������� �� �� ���
		
		MOV EDX, DWORD PTR DS:[EBX+368h]
		CMP DWORD PTR DS:[EDX+6F8h],0
		JNE[izanami_check_back] ; ���� �� ��� ����  �� ��������
		
		MOV EAX, DWORD PTR DS:[EDI+198h]
		CMP DWORD PTR DS:[EAX+2Ch],1
		JNE[izanami_check_back] ; ���� ������� �� ��� ��� � ��� ������ ��� ��� ����� ��� 
		
		MOV EAX, DWORD PTR DS:[EBX+198h]
		MOV DWORD PTR DS:[EAX+2Ch], 2
		MOV EAX, DWORD PTR DS:[EDI+198h]
		MOV DWORD PTR DS:[EAX+2Ch], 3
		
		MOV EDI, 0h
		
		JMP[Izanami_start_save_params]
	
Izanami_start_save_params:
		MOV EDX,DWORD PTR DS:[00458B00h]
		CMP BYTE PTR DS:[EDX+EDI+4h],0
		JE[Izanami_next_save_params]
		
		MOV EBX, DWORD PTR DS:[EDX+EDI*4h+3ECh]
		MOV EAX, DWORD PTR DS:[EBX+198h]
		
		MOV DWORD PTR DS:[EAX+30h],0h	
			
		MOV EDX, DWORD PTR DS:[EBX+2FCh] ; ��������
		MOV DWORD PTR DS:[EAX+40h],EDX
		MOV EDX, DWORD PTR DS:[EBX+300h] ; Ҹ���� ������� ��������
		MOV DWORD PTR DS:[EAX+44h],EDX
		MOV EDX, DWORD PTR DS:[EBX+308h] ; ����
		MOV DWORD PTR DS:[EAX+48h],EDX
;		
;		MOV EDX, DWORD PTR DS:[EBX+70h]
;		MOV DWORD PTR DS:[EAX+3Ch],EDX
;		MOV EDX, DWORD PTR DS:[EBX+88h]
;		MOV DWORD PTR DS:[EAX+40h],EDX
;		MOV DL, BYTE PTR DS:[EBX+80h]
;		MOV BYTE PTR DS:[EAX+44h],DL
;		MOV EDX, DWORD PTR DS:[EBX+0B0h]
;		MOV DWORD PTR DS:[EAX+48h],EDX
;		MOV EDX, DWORD PTR DS:[EBX+0B4h]
;		MOV DWORD PTR DS:[EAX+4Ch],EDX
;		MOV EDX, DWORD PTR DS:[EBX+0B8h]
;		MOV DWORD PTR DS:[EAX+50h],EDX
;		
;		FLD QWORD PTR DS:[EBX+58h]
;		FSTP QWORD PTR DS:[EAX+58h]
;		FLD QWORD PTR DS:[EBX+60h]
;		FSTP QWORD PTR DS:[EAX+60h]
;		FLD QWORD PTR DS:[EBX+68h]
;		FSTP QWORD PTR DS:[EAX+68h]
;		
;		FLD QWORD PTR DS:[EBX+28h]
;		FSTP QWORD PTR DS:[EAX+70h]
;		FLD QWORD PTR DS:[EBX+30h]
;		FSTP QWORD PTR DS:[EAX+78h]
;		FLD QWORD PTR DS:[EBX+38h]
;		FSTP QWORD PTR DS:[EAX+80h]
;		
;		FLD QWORD PTR DS:[EBX+40h]
;		FSTP QWORD PTR DS:[EAX+88h]	
;		FLD QWORD PTR DS:[EBX+48h]
;		FSTP QWORD PTR DS:[EAX+90h]	
;		FLD QWORD PTR DS:[EBX+50h]
;		FSTP QWORD PTR DS:[EAX+98h]
		
		JMP[Izanami_next_save_params]
		
Izanami_next_save_params:
		INC EDI
		CMP EDI, 1000
		JL [Izanami_start_save_params]
		
		; ��� ������ ������� ����� ��� �������
		MOV EAX, [Izanami_MaxLoop]
		MOV [Izanami_Loop], EAX
		MOV EAX, [Izanami_MaxTime]
		MOV [Izanami_Time], EAX
		
		JMP [izanami_check_back]
		
izanami_check_back:
		POP EDI
		POP EBX
		POP EDX
		POP EAX
		
		
		;������� ������
		CMP ECX,EDX
		JL [level_below] ; ������� ����
		CMP ECX,EDX
		JG [level_above] ; ������� ����
		CMP ECX,EDX
		JE [levels_equal] ; ������ �����
		
		POP EDX
		POP ECX
		jmp [eff50_next] ; �� ������ ������
		
		
		
level_below: ; ������� ����

		POP EDX
		POP ECX
		JMP [eff_50]
		
level_above: ; ������� ����
		
		POP EDX
		POP ECX
		jmp[eff50_next]
		
levels_equal: ; ������ �����
		
		MOV ECX,DWORD PTR DS:[EDI+368h]
		CMP DWORD PTR DS:[ECX+6F8h],0
		JE[levels_equal_t0]
		
		POP EDX
		POP ECX
		jmp[eff50_next]

levels_equal_t0:
		
		IMUL EDX,DWORD PTR DS:[EDI+70h],1B0h
		ADD EDX,DWORD PTR DS:[EDI+368h]
		CMP DWORD PTR DS:[EDX+838h],3
		JE[levels_equal_t0_s3]
		CMP DWORD PTR DS:[EDX+838h],33
		JE[levels_equal_t0_s3]
		
		POP EDX
		POP ECX
		jmp[eff50_next]

levels_equal_t0_s3:
		
		MOV EDX, DWORD PTR DS:[EDI+198h]
		MOV ECX, DWORD PTR DS:[EBX+198h]
		
		CMP DWORD PTR DS:[EDX+28h],1
		JE [players]
		CMP DWORD PTR DS:[ECX+28h],1
		JE [players]
		JMP[not_players]

players:
		mov fps_remover, 1h
not_players:
		POP EDX
		POP ECX
		jmp[eff_50]
		
		

eff50_next:
		IMUL ECX,DWORD PTR DS:[EDI+70h],1B0h ; �������� �������� ������
		FSTP ST
		ADD ECX,DWORD PTR DS:[EDI+368h]
		LEA ECX,DWORD PTR DS:[ECX+95Ch] ;bdy
		CMP DWORD PTR DS:[ECX],0 	
		JLE [skip]
		MOV ECX,DWORD PTR DS:[ECX+8]
		MOV EDX,DWORD PTR DS:[ECX+20h]
		TEST EDX,EDX
		JNZ [untouchable_true]
		
skip:
		POP ECX
		POP EDX
		MOV DWORD PTR DS:[EDI+70h],EDX
		MOV DWORD PTR DS:[EDI+0B0h],ECX
		JMP [e50_back1]

eff_50:
		POP ECX
		POP EDX
		MOV DWORD PTR DS:[EDI+0B0h],0
    	JMP [e50_back1]
    	
    	
untouchable_true:
		MOV EDX,DWORD PTR DS:[EDX]
		TEST EDX,EDX
		JZ [skip]

		POP ECX
		POP EDX
		MOV DWORD PTR DS:[EDI+0B0h],0
    	JMP [e50_back1]


effect50 endp
















