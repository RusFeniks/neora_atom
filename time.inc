.Data

FPS_back   		dd 0043D13Eh

tt_proceed 		dd 00413119h
tt_blocked 		dd 004143C6h

ts_sub_back 	dd 0041DD4Fh

ts_timer 		dd ?
ts_team  		dd ?
ts_type  		dd ?

ts_fix	 		dd 0043D159h
ts_fire	 		dd 004211A0h
ts_jan1	 		dd 0040704Dh
ts_jan1b 		dd 00407DD3h
ts_fa_b1 		dd 0040DA78h
ts_fa_b2 		dd 0040837Eh
ts_fa_b3 		dd 00408396h
ts_bg_b1 		dd 0041A138h
ts_bg_b2 		dd 0041A2E9h
ts_bg_b3 		dd 0041A1C6h

some_function 	dd 00417170h
.Code


TimeStop proc
		CMP DWORD PTR DS:[ts_timer],0
		JE [proceed]
		
		CMP DWORD PTR DS:[ts_team],0
		JNE [ts_setup_1]
		
		CMP DWORD PTR DS:[ts_type],2
		JE [ts_setup_2]
		
		CMP DWORD PTR DS:[ts_type],3
		JE [ts_setup_3]
				
		CMP DWORD PTR DS:[ts_type],4
		JE [ts_setup_4]
		
ts_setup_0:
		CMP DWORD PTR DS:[ESI+150h],-1
		JE [proceed]
		CMP DWORD PTR DS:[ESI+150h],0
		JE [new_object]

		MOV DWORD PTR DS:[ESI+0B4h],3
		SUB DWORD PTR DS:[ESI+150h],1
		JMP [blocked] ; ���������� ������, ��������� ���������� ����������
		
ts_setup_1:
		MOV EAX,DWORD PTR DS:[ts_team]
		CMP EAX,DWORD PTR DS:[ESI+364h] ; ��������, ��� ������� ��
		JE [proceed]

		MOV DWORD PTR DS:[ESI+0B4h],3
		SUB DWORD PTR DS:[ESI+150h],1
		JMP [blocked] ; ���������� ������, ��������� ���������� ����������
		
ts_setup_2:
		MOV EAX,DWORD PTR DS:[ESI+368h]
		CMP DWORD PTR DS:[EAX+6F8h],0
		JE [proceed]

		MOV DWORD PTR DS:[ESI+0B4h],3
		SUB DWORD PTR DS:[ESI+150h],1
		JMP [blocked] ; ���������� ������, ��������� ���������� ����������

ts_setup_3:

		CMP DWORD PTR DS:[ESI+150h],-1
		JE [proceed]
		CMP DWORD PTR DS:[ESI+150h],0
		JE [new_object_3]
		
		MOV DWORD PTR DS:[ESI+0B4h],3
		SUB DWORD PTR DS:[ESI+150h],1
		JMP [blocked] ; ���������� ������, ��������� ���������� ����������
		
ts_setup_4:

		PUSH EAX
		MOV EAX, DWORD PTR DS:[ts_timer]
		CMP EAX,1
		POP EAX
		JE [ts_s4_unnormal]

ts_s4_normal:
		CMP DWORD PTR DS:[ESI+150h],-1
		JE [proceed]
		CMP DWORD PTR DS:[ESI+150h],0
		JE [new_object_3]

		MOV DWORD PTR DS:[ESI+0B4h],3
		SUB DWORD PTR DS:[ESI+150h],1
		JMP [blocked] ; ���������� ������, ��������� ���������� ����������
		
ts_s4_unnormal:
		CMP DWORD PTR DS:[ESI+198h], -1
		JE [ts_s4_normal]
		PUSH EAX
		MOV EAX, DWORD PTR DS:[ESI+198h]
		MOV DWORD PTR DS:[ESI+2FCh], EAX
		POP EAX
		
		CMP DWORD PTR DS:[ESI+150h],-1
		JE [proceed]
		CMP DWORD PTR DS:[ESI+150h],0
		JE [new_object_3]
		
		MOV DWORD PTR DS:[ESI+0B4h],3
		SUB DWORD PTR DS:[ESI+150h],1
		JMP [blocked] ; ���������� ������, ��������� ���������� ����������
		
		
new_object:
		MOV EAX, DWORD PTR DS:[ts_timer]
		MOV DWORD PTR DS:[ESI+150h],EAX
		JMP [blocked]
		
new_object_3:
		MOV DWORD PTR DS:[ESI+150h],-1
		JMP [blocked]

proceed:
		MOV EAX,DWORD PTR DS:[ESI+368h]
		MOV EBP,DWORD PTR DS:[EAX+6F8h]
		JMP [tt_proceed]
		
blocked:
		MOV EAX,DWORD PTR DS:[ESI+368h]
		MOV EBP,DWORD PTR DS:[EAX+6F8h]
		JMP [tt_blocked]


TimeStop endp





TS_substactor proc
	
		CMP BYTE PTR DS:[44FCB0h],1 ; �������� �� �����
		JE [skip]
		
		MOV EAX, DWORD PTR DS:[ts_timer]
		CMP EAX,0 ; ���������, ���� �� ��
		JE [skip]
		
		SUB DWORD PTR DS:[ts_timer],1
	
skip:	
		MOV EAX,DWORD PTR DS:[450BDCh]
		JMP [ts_sub_back]

TS_substactor endp

 

TS_menu_fix proc

		CMP DWORD PTR DS:[44D020h],0
		JE [skip]
		MOV DWORD PTR DS:[ts_timer],0

skip:
		MOV EAX,DWORD PTR DS:[457BC8h]
		JMP [ts_fix]

TS_menu_fix endp

TS_fire_disable proc
	
		CMP DWORD PTR DS:[ts_timer],0
		JG [skip_fire]
	
		PUSH 4h
		PUSH 0CBh
		CALL [some_function];
		ADD ESP,8
		
skip_fire:
		JMP [ts_fire]

TS_fire_disable endp


TS_JanC1_disable proc

		CMP EAX,-1
		JE [skip]
		CMP DWORD PTR DS:[ts_timer],0
		JG [skip]
		JMP [ts_jan1b]
skip:
		JMP [ts_jan1]

TS_JanC1_disable endp

TS_Fa_disable_1 proc
	
		CMP DWORD PTR DS:[ts_timer],0
		JG [skip]
		SUB DWORD PTR DS:[ESI+2FCh],EAX
skip:
		JMP [ts_fa_b1]

TS_Fa_disable_1 endp


TS_Fa_disable_2 proc

		CMP DWORD PTR DS:[ts_timer],0
		JG [skip]
		FLD QWORD PTR DS:[4479C0h]
		JMP [ts_fa_b2]
skip:
		FCOMP ST(3)
		JE [nya]
		nya:
		FLD DWORD PTR DS:[4479C0h]
		FSTP QWORD PTR DS:[ECX+48h]
		JMP [ts_fa_b3]

TS_Fa_disable_2 endp



TS_bg_stop_1 proc

		CMP DWORD PTR DS:[ts_timer],0
		JG [skip]
		
		MOV DWORD PTR DS:[EDI],EDX
skip:
		LEA EAX,DWORD PTR DS:[ECX+ESI*4+1580h]
		JMP [ts_bg_b1]

TS_bg_stop_1 endp


TS_bg_stop_2 proc

		CMP DWORD PTR DS:[ts_timer],0
		JG [skip]

		MOV DWORD PTR DS:[EDI],EDX
skip:
		CMP EDX,DWORD PTR DS:[ECX+ESI*4+1580h]
		JMP [ts_bg_b3]

TS_bg_stop_2 endp














