.data

opoint_maker_call1 dd 00402400h
opoint_maker_call2_random dd 00417170h

.code

;������� �� �������� ��� �������� � ����� states.inc, ���� �������� ������ ���� ����� �������� � ������ ����
;����������� ��� ��������� �����������, ��� ���� ������������ � ��, ����� ���������� ���������������
;� ������ ������ ����� ������ � ������ ������� �����, ��� �� ����� ��������������, ����� ����� ��� ����������


;������������
;Opoint_Maker PROTO :dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword
;invoke Opoint_Maker,121,0,-50,0,100,10,5,500,0,0,0,10,-2,ECX

Opoint_Maker proc id,centerx,centery,centerz,x,y,z,hp,act,framea,facing,dvx,dvy,addr_master:dword

;---------------------------------------- facing	framea	act	 	hp 		z 		y 		x 		id 		return
;------------------------------------------- +20	+1c		+18		+14		+10		+c 		+8 		+4 		0
	
	
	PUSHAD
	SUB ESP,20h
	
	MOV EAX,facing
	TEST EAX,EAX
	JGE [skip0]
	NEG EAX
skip0:
	MOV ECX,10
	CDQ
	IDIV ECX
	TEST EAX,EAX
	JNZ [skip01]
	OR EAX,1
skip01:
	MOV DWORD PTR SS:[ESP+8h],EAX ;������� �������� ��������� � ������� �������
	MOV DWORD PTR SS:[ESP+10h],EAX ;����� �� ������ ��������, ����� ���� �� ����
	AND EAX,0FFFFFEh               ;��������� �� ������� ����. �.�. ������ ������� ��� ��������/����������
	MOV DWORD PTR SS:[ESP+0Ch],EAX ;dvz_calc �������� ��� ������ �������� �� ��� ��� ��������
	
cycle_BIG:
	
	MOV EDX,50 						;����� ������ ��������� ������ �������� ���� � 50, ��� ������ ������ ������ ��������� ������ � �.�.
	MOV EBX,DWORD PTR DS:[458B00h]
cycle1:
	CMP BYTE PTR DS:[EBX+EDX+4h],0
	JZ [cycle1_end]
	INC EDX
	CMP EDX,1000
	JL [cycle1]
	JMP [back]
	
cycle1_end:
	MOV BYTE PTR DS:[EBX+EDX+4h],1
	MOV ESI, DWORD PTR DS:[EBX+EDX*4+3ECh]
	MOV ECX,ESI
	MOV object_link,EDX
	CALL [opoint_maker_call1]		;����� ��������� ������, "������" �, ����� �������� ��������� ������������� �������,
									;��� ����������� � ��������� ��������� �� ����� ������, ��� ��� ��� ��������



	MOV DWORD PTR SS:[ESP+4h],-1 	;���� �� �������� ���������� ������������ ������� ������� �� ����
	MOV EDX,DWORD PTR DS:[452980h] 	;���������� ��� ������ ����, ��� ����� ������ ���������� � ������ ��������
	XOR EAX,EAX
	CMP DWORD PTR DS:[452990h],EAX	;���� ���� � ���� ��������� ��� ������ ������ �� ���-���� � �������� ���� ����� �������
	JLE SHORT [j1]					;���� ������������ ���
	MOV ECX,id
	MOV DWORD PTR SS:[ESP],EDX
j2:
	MOV EDX,DWORD PTR SS:[ESP]
	MOV EDX,DWORD PTR DS:[EDX]
	CMP DWORD PTR DS:[EDX+6F4h],ECX
	JE SHORT [j3]
	MOV EDX,DWORD PTR DS:[452980h]
	ADD DWORD PTR SS:[ESP],4
	INC EAX
	CMP EAX,DWORD PTR DS:[452990h]
	JL SHORT [j2]
	JMP SHORT [j1]
j3:
	MOV ECX,EAX
	MOV DWORD PTR SS:[ESP+4h],1		;���� = ��������
	JMP SHORT [j4]		
j1:
	
	
	CMP DWORD PTR SS:[ESP+4h],-1
	JZ [back]
j4:
	MOV DWORD PTR DS:[ESI+368h],EDX
	MOV EBX,addr_master

owner_find:
	MOV EAX,DWORD PTR DS:[458B00h]
	MOV EDX, -1
owner_find_next:
	CMP EDX,20
	JGE [no_owner]
	ADD EDX, 1
	CMP DWORD PTR DS:[EAX+EDX*4+3ECh],EBX
	JNE [owner_find_next]
	JMP [owner_write]
	
no_owner:
	MOV DWORD PTR DS:[ESI+354h],-1
	JMP [owner_find_end]
owner_write:
	MOV DWORD PTR DS:[ESI+354h],EDX
	JMP [owner_find_end]
	
owner_find_end:
	
	MOV EDX,DWORD PTR DS:[EBX+10h] 	
	ADD EDX,centerx					;edx = ���������� ��� �������� + ����� ��������� � ������ �������
	MOV EAX,x
	TEST EAX,EAX
	JGE [skip1]
	NEG EAX							;��� ������� eax ������ ������������� �������������
skip1:
	MOV DWORD PTR SS:[ESP+4h],EAX	;������ ������������ ��������
	IMUL EAX,2						;� ������� ��������� ���������� �� 2
	PUSH EAX						
	PUSH EDX 						;��������� ��� ��������� EDX
	CALL [opoint_maker_call2_random]	
	POP EDX
	ADD EDX,EAX						;��������� ��������� �������
	SUB EDX,DWORD PTR SS:[ESP+8h]	;� �������� ������������ ��������. ����� ��� ��� ������� ������ ������ � ���� [-EAX;+EAX]
	ADD ESP,4
	MOV DWORD PTR DS:[ESI+10h],EDX	;� ���������
									;���� ��� ����������
	
	MOV EDX,DWORD PTR DS:[EBX+14h]
	ADD EDX,centery
	MOV EAX,y
	TEST EAX,EAX
	JGE [skip2]
	NEG EAX
skip2:
	MOV DWORD PTR SS:[ESP+4h],EAX
	IMUL EAX,2
	PUSH EAX
	PUSH EDX
	CALL [opoint_maker_call2_random]
	POP EDX
	ADD EDX,EAX
	SUB EDX,DWORD PTR SS:[ESP+8h]
	ADD ESP,4
	MOV DWORD PTR DS:[ESI+14h],EDX
	
	
	MOV EDX,DWORD PTR DS:[EBX+18h]
	ADD EDX,centerz
	MOV EAX,z
	TEST EAX,EAX
	JGE [skip3]
	NEG EAX
skip3:
	MOV DWORD PTR SS:[ESP+4h],EAX
	IMUL EAX,2
	PUSH EAX
	PUSH EDX
	CALL [opoint_maker_call2_random]
	POP EDX
	ADD EDX,EAX
	SUB EDX,DWORD PTR SS:[ESP+8h]
	ADD ESP,4
	MOV DWORD PTR DS:[ESI+18h],EDX
	PUSH ECX
	PUSH EDX
	
	MOV ECX,DWORD PTR DS:[ESI+198h]
	
	MOV EDX,DWORD PTR DS:[ESI+10h]
	SUB EDX,DWORD PTR DS:[EBX+10h]
	MOV DWORD PTR DS:[ECX+18h],EDX
	
	MOV EDX,DWORD PTR DS:[ESI+14h]
	SUB EDX,DWORD PTR DS:[EBX+14h]
	MOV DWORD PTR DS:[ECX+1Ch],EDX
	
	MOV EDX,DWORD PTR DS:[ESI+18h]
	SUB EDX,DWORD PTR DS:[EBX+18h]
	MOV DWORD PTR DS:[ECX+20h],EDX
	
	POP EDX
	POP ECX
	
	;��������� ����� ����������
	FILD DWORD PTR DS:[ESI+10h]
	FSTP QWORD PTR DS:[ESI+58h]
	FILD DWORD PTR DS:[ESI+14h]
	FSTP QWORD PTR DS:[ESI+60h]
	FILD DWORD PTR DS:[ESI+18h]
	FSTP QWORD PTR DS:[ESI+68h]
	
	;��������� �������� �� � ������ ��, ���������, ������, �������� � ����
	MOV EAX,hp
	MOV DWORD PTR DS:[ESI+2FCh],EAX
	MOV DWORD PTR DS:[ESI+300h],EAX
	MOV DWORD PTR DS:[ESI+304h],EAX
	MOV DWORD PTR DS:[ESI+308h],EAX
	MOV DWORD PTR DS:[ESI+31Ch],EAX
	
	;������ �� ������, �� ������ �������� ��
	MOV EAX,framea
	TEST EAX,EAX
	JNZ [skip11]
	JGE [skip10]
	NEG EAX
skip10:
	PUSH EAX
	PUSH 1
	CALL [opoint_maker_call2_random]
	ADD ESP,8h
skip11:
	;� ���������� ������� �������� ������������� ��������, ��� ����� ������ ������
	ADD EAX,act
	MOV DWORD PTR DS:[ESI+70h],EAX
	
	
	MOV EAX,facing
	TEST EAX,EAX
	JGE [skip12]
	NEG EAX
skip12:
	TEST EAX,EAX
	JNZ [skip13]
	MOV EAX,10
skip13:
	CDQ
	MOV ECX,10
	IDIV ECX
	TEST EDX,EDX
	JZ [skip14]
	MOV CL,1
	SUB CL,BYTE PTR DS:[EBX+80h] 	;���������� �� ������� ����� � �������� ���� �� ������ ��������.
	MOV BYTE PTR DS:[EBX+80h],CL 
skip14:
	
	;������ ���������� dvx � dvy
	MOV EAX,dvx
	MOV DWORD PTR DS:[ESI+40h],EAX
	FILD DWORD PTR DS:[ESI+40h]
	FSTP QWORD PTR DS:[ESI+40h]
	MOV EAX,dvy
	MOV DWORD PTR DS:[ESI+48h],EAX
	FILD DWORD PTR DS:[ESI+48h]
	FSTP QWORD PTR DS:[ESI+48h]
	
	;��� ������� ����, ������� ������ ��������
	MOV EAX,DWORD PTR SS:[ESP+0Ch]
	TEST EAX,EAX
	JNZ [back]
	JL [skip20]
	NEG DWORD PTR SS:[ESP+0Ch]
	JMP SHORT [skip21]
skip20:
	MOV EDX,EAX
	NEG EDX
	SAL EDX,1
	MOV DWORD PTR SS:[ESP+0Ch],EDX
skip21:
	MOV DWORD PTR DS:[ESI+50h],EAX
	FILD DWORD PTR DS:[ESI+50h]
	FSTP QWORD PTR DS:[ESI+50h]
	
	
	
back2:
back:
	;�ר�������
	DEC DWORD PTR SS:[ESP+8h]
	CMP DWORD PTR SS:[ESP+8h],0
	JGE [cycle_BIG]
	ADD ESP,20h
	POPAD
	
back_END:
	ret
Opoint_Maker endp