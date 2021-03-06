.data

Transform1	dd 0041F675h ;state8xxx
TransBack1  dd 0041F60Ah ;state4xxxx
TurnBack1   dd 00413350h ;StateTurn
TurnBack2 	dd 0041336Fh
BackSt_9x_1 dd 0042ECAFh
BackSt_9x_2 dd 0042ED2Ch

;state_turning
st_r1		dd 00414099h
st_r2		dd 00414243h
st_r3		dd 00414159h
;hit_teammates
ht_r1		dd 004177CAh
ht_r2		dd 00417866h
ht_r3		dd 0041780Bh

Izanami_Time dd -1h
Izanami_Loop dd -1h
Izanami_MaxLoop dd 7h
Izanami_MaxTime dd 130h
Izanami_Condition db 0
Izanami_damage_caster dd 0h
Izanami_damage_target dd 0h

.code

State8xxx proc

		CMP EDX, 38
		JE plus140
		CMP EDX, 37
		JE plus140
		CMP EDX, 36
		JE plus140
		CMP EDX, 35
		JE plus140
		CMP EDX, 34
		JE plus140
		CMP EDX, 33
		JE plus140
		CMP EDX, 32
		JE plus140
		CMP EDX, 31
		JE plus140
		CMP EDX, 30
		JE plus140

		MOV EDX,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV DWORD PTR DS:[EDX+70h],0
		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV DWORD PTR DS:[EAX+318h],0
		JMP [Transform1]

plus140:
		MOV EDX,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV DWORD PTR DS:[EDX+70h],0
		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV DWORD PTR DS:[EAX+318h],8Ch
		JMP [Transform1]


State8xxx endp





StateMore proc

		PUSH EDX ;reserve
		PUSH EAX ;reserve
		PUSH ECX ;reserve
		PUSH EBX ;reserve
		PUSH EDI ;reserve
		
		CMP EAX,60000 ; 60000
		JL  [skip] ; ���� ������ - � ������� ���
		CMP EAX,69999 ; 69999
		JLE [State6xxxx]
		CMP EAX,79999 ; 79999
		JLE [State7xxxx]
		CMP EAX,89999 ; 89999
		JLE [State8xxxx]
		CMP EAX,90000 ; 90000
		JE [State90000]
		CMP EAX,90999 ; 90xxx
		JLE [State90xxx]
		CMP EAX,91999 ; 91xxx
		JLE [State91xxx]
		CMP EAX,92999 ; 92xxx
		JLE [State92xxx]
		CMP EAX,93000 ; 93000 (�������� ���������)
		JE [State93000]
		CMP EAX, 93001 ; 93001 - �������
		JE[State93001]
		CMP EAX,2000000 ; 2xxxyyy
		JL  [skip] ; ���� ������ - � ������� ���
		CMP EAX,2999999 ; 2999999
		JLE [State2xxxyyy]
		CMP EAX,3999999 ; 3999999
		JLE [State3xxxyyy]
		
		JMP [skip] ; ���� �� ���� �� ������� ����

State2xxxyyy:
		MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
		CMP DWORD PTR DS:[ECX+88h],0 ; �������
		JNE [skip]
		
		SUB EAX, 2000000 ; 2xxxyyy

		MOV EBX,1000
		CDQ
		IDIV EBX
		CMP DWORD PTR DS:[ECX+308h],EAX
		JL [not_enough_mp]
		SUB DWORD PTR DS:[ECX+308h], EAX
		ADD DWORD PTR DS:[ECX+350h], EAX
		JMP [skip]
		
not_enough_mp:	
		MOV DWORD PTR DS:[ECX+70h],EDX
		MOV DWORD PTR DS:[ECX+88h],0
		JMP [skip]
		
;==============================================================
;====================== Time Stop State =======================
;==============================================================
State3xxxyyy:

		MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
		CMP DWORD PTR DS:[ECX+88h],0 ; �������
		JNE [skip]
		
		PUSH EBX ; �������� ����� ������ ��������

		SUB EAX,3000000 ; 3xxyzzz
		MOV ECX,10000
		CDQ
		IDIV ECX ; % � EAX, ������� � EDX
		
		CMP EAX, 0
		JE [skip_random]
		
		MOV EBX,EAX ; ���� ����� ������ �� 0, �� �������� ��� �� ����� ����� �������� �������
		PUSH 100 ; ���� ����� �������
		PUSH EDX ; ����������� �������
		CALL DWORD PTR [random] ; result in EAX ~ EDX
		POP EAX ; ���������� ������� � EAX ��� ����������� ��������
		ADD ESP,4h ; ����������� ����
		CMP EBX,EDX ; ���������� (��� %) � (������ %)
		JL [TS_no_random] ; ���� �� ������� - ���������, ��� ���� ������ ��������� �� ����
		JMP [check_type]

skip_random:
		XCHG EAX,EDX ; ���������� � EAX �������
check_type:
		MOV ECX,1000
		CDQ
		IDIV ECX ; ������� � EAX ���, � � EDX �����
		
		XOR ECX,ECX
		POP EBX
		
		CMP EAX,0
		JE [ts_setup_0]
		CMP EAX,1
		JE [ts_setup_1]
		CMP EAX,2
		JE [ts_setup_2]
		CMP EAX,3
		JE [ts_setup_3]
		JMP [skip]

ts_setup_0:
		CMP BYTE PTR DS:[EBX+ECX+4h],0
		JE [doesnt_exist_0]
		
		MOV EAX,DWORD PTR DS:[EBX+ECX*4+3ECh] 
		MOV DWORD PTR DS:[EAX+150h],EDX ; ���������� ������� ������

		doesnt_exist_0:
		INC ECX
		CMP ECX,1000
		JL [ts_setup_0]
		
		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh] ; �������� �������� ������
		MOV DWORD PTR DS:[EAX+150h],-1 ; �������� ��� ��� ��������������� �������
		MOV DWORD PTR DS:[ts_timer],EDX ; ������ ������� �� ��� ������
		
		MOV DWORD PTR DS:[ts_team],0 ; ��������� �������, ����� �� 0 ������� ����� �� 1
		MOV DWORD PTR DS:[ts_type],0 ; ���������� Time Stop Type
		JMP [skip]

ts_setup_1:
		PUSH ESI
		MOV ESI,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV ESI,DWORD PTR DS:[ESI+364h] ; ������� � ESI
		MOV DWORD PTR DS:[ts_team],ESI ; ���������� ��� �������������� TS
		
	next_object_s1:
		CMP BYTE PTR DS:[EBX+ECX+4h],0
		JE [doesnt_exist_1]
		
		MOV EAX,DWORD PTR DS:[EBX+ECX*4+3ECh] 
		CMP DWORD PTR DS:[EAX+364h],ESI ; �������� �������
		MOV DWORD PTR DS:[EAX+150h],EDX ; ���������� ������� ������
		JNE [doesnt_exist_1]
		MOV DWORD PTR DS:[EAX+150h],-1 ; ���� �����, �� ���� ������������� ��

		doesnt_exist_1:
		INC ECX
		CMP ECX,1000
		JL [next_object_s1]
		

		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh] ; �������� �������� ������
		MOV DWORD PTR DS:[EAX+150h],-1 ; �������� ��� ��� ��������������� �������
		MOV DWORD PTR DS:[ts_timer],EDX ; ������ ������� �� ��� ������
		MOV DWORD PTR DS:[ts_type],1 ; ���������� Time Stop Type
		POP ESI
		JMP [skip]


ts_setup_2:
		CMP BYTE PTR DS:[EBX+ECX+4h],0
		JE [doesnt_exist_2]
		
		MOV EAX,DWORD PTR DS:[EBX+ECX*4+3ECh] 
		MOV DWORD PTR DS:[EAX+150h],EDX ; ���������� ������� ������

		doesnt_exist_2:
		INC ECX
		CMP ECX,1000
		JL [ts_setup_2]
		
		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh] ; �������� �������� ������
		MOV DWORD PTR DS:[EAX+150h],-1 ; �������� ��� ��� ��������������� �������
		MOV DWORD PTR DS:[ts_timer],EDX ; ������ ������� �� ��� ������
		
		MOV DWORD PTR DS:[ts_team],0 ; ��������� �������, ����� �� 0 ������� ����� �� 1
		MOV DWORD PTR DS:[ts_type],2 ; ���������� Time Stop Type
		JMP [skip]
		
ts_setup_3:
		PUSH ESI
		MOV ESI,DWORD PTR DS:[EBX+EDI*4+3ECh]
		
	next_object_s3:
		CMP BYTE PTR DS:[EBX+ECX+4h],0
		JE [doesnt_exist_3]
		
		MOV EAX,DWORD PTR DS:[EBX+ECX*4+3ECh] 
		CMP DWORD PTR DS:[EAX+354h],EDI ; �������� ���������
		MOV DWORD PTR DS:[EAX+150h],EDX ; ���������� ������� ������
		JNE [doesnt_exist_3]
		MOV DWORD PTR DS:[EAX+150h],-1 ; ���� �����, �� ���� ������������� ��

		doesnt_exist_3:
		INC ECX
		CMP ECX,1000
		JL [next_object_s3]
		

		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh] ; �������� �������� ������
		MOV DWORD PTR DS:[EAX+150h],-1 ; �������� ��� ��� ��������������� �������
		MOV DWORD PTR DS:[ts_timer],EDX ; ������ ������� �� ��� ������
		MOV DWORD PTR DS:[ts_type],3 ; ���������� Time Stop Type
		POP ESI
		JMP [skip]


TS_no_random:
		POP EBX
;==============================================================

State6xxxx:
		SUB EAX, 60000 ; 60000
		
		MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
		MOV DWORD PTR DS:[ECX+10h],EAX ; change X of object
		FILD DWORD PTR DS:[ECX+10h] ; load X as float
		FSTP QWORD PTR DS:[ECX+58h] ; store it to float number zone

		JMP [skip]
		
State7xxxx:
		SUB EAX, 70000 ; 70000
		NEG EAX
		
		MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
		MOV DWORD PTR DS:[ECX+14h],EAX ; change Y of object
		FILD DWORD PTR DS:[ECX+14h] ; load Y as float
		FSTP QWORD PTR DS:[ECX+60h] ; store it to float number zone

		JMP [skip]
		
State8xxxx:
		SUB EAX, 80000 ; 80000
		
		MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
		MOV DWORD PTR DS:[ECX+18h],EAX ; change Z of object
		FILD DWORD PTR DS:[ECX+18h] ; load Z as float
		FSTP QWORD PTR DS:[ECX+68h] ; store it to float number zone

		JMP [skip]

State90000:
		;SUB EAX, 90000 ; 90000

		MOV EAX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
		
		MOV EBX,DWORD PTR DS:[EDX+ECX+908h]
		CMP EBX, 64h; weapon kind 100
		JNE [skip]
	
		FLD DWORD PTR DS:[EDX+ECX+920h]
		FSTP QWORD PTR DS:[EAX+58h]
		
		FLD DWORD PTR DS:[EDX+ECX+924h]
		FCHS
		FSTP QWORD PTR DS:[EAX+60h]
		
		FLD DWORD PTR DS:[EDX+ECX+928h]
		FSTP QWORD PTR DS:[EAX+68h]
		
		JMP [skip]
		
State90xxx:
		SUB EAX, 90000
		MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
		ADD DWORD PTR DS:[ECX+304h], EAX
		ADD DWORD PTR DS:[ECX+300h], EAX
		ADD DWORD PTR DS:[ECX+2FCh], EAX
		JMP [skip]
		
State91xxx:
		SUB EAX, 91000
		MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
		CMP DWORD PTR DS:[ECX+2FCh], EAX
		JLE [NoHp91xxx]
		SUB DWORD PTR DS:[ECX+304h], EAX
		SUB DWORD PTR DS:[ECX+300h], EAX
		SUB DWORD PTR DS:[ECX+2FCh], EAX
		JMP [skip]
		
NoHp91xxx:
		MOV EAX,226
		MOV DWORD PTR DS:[ECX+70h], EAX
		JMP [skip]
			
State92xxx:
		SUB EAX, 92000
		MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
		MOV DWORD PTR DS:[ECX+304h], EAX
		MOV DWORD PTR DS:[ECX+300h], EAX
		MOV DWORD PTR DS:[ECX+2FCh], EAX
		JMP [skip]
		
State93000:
		MOV ECX, DWORD PTR DS:[EBX+EDI*4h+3ECh]
		MOV EDI, DWORD PTR DS:[ECX+354h]
		
		CMP EDI, 0h
		JL[State93000_skip]
		
		MOV EDI, DWORD PTR DS:[EBX+EDI*4h+3ECh]
		
		FLD QWORD PTR DS:[EDI+58h] ; ��������� X ��������� �������
		FSTP QWORD PTR DS:[ECX+58h] ; ���������� � ����������� �������
	
		FLD QWORD PTR DS:[EDI+60h] ; ��������� Y ��������� �������
		FSTP QWORD PTR DS:[ECX+60h] ; ���������� Y ����������� �������
	
		FLD QWORD PTR DS:[EDI+68h] ; ��������� Z ��������� �������
		FADD QWORD PTR DS:[447A08h]
		FSTP QWORD PTR DS:[ECX+68h] ; ���������� Z ����������� �������
		
State93000_skip:
		JMP [skip]
		
State93001:
		MOV ECX, DWORD PTR DS:[EBX+EDI*4h+3ECh]
		CMP DWORD PTR DS:[ECX+88h],0
		JNE[State93001_end]
		MOV EAX, DWORD PTR DS:[ECX+198h]
		
		; 0 - ������� �� ������������
		; 1 - ������� ������ � ���������
		; 2 - ������� ��������
		
		CMP DWORD PTR DS:[EAX+2Ch],0 ; �������� �� ��,��� ����� ������� ��� �� �����������
		JE[Izanami_activation]
		
		CMP DWORD PTR DS:[EAX+2Ch],2 ; �������� �� �� ��� ������� ��������
		JE[Izanami_end]
		
		JMP [State93001_end]

Izanami_activation:
		MOV DWORD PTR DS:[EAX+2Ch],1
		JMP [State93001_end]
		
Izanami_end:
		MOV [Izanami_Loop], 0h
		MOV [Izanami_Time], 0h
		JMP [State93001_end]
		
		
		

State93001_end:
		JMP [skip]

skip:	
		POP EDI ;reserve
		POP EBX ;reserve	
		POP ECX ;reserve
		POP EAX ;reserve
		POP EDX ;reserve
		ret

StateMore endp


StateTurn3x proc

		CMP EDX,1Eh ; State 30
		JE [State30]
		CMP EDX,1Fh ; State 31
		JE [State31]
		CMP EDX,20h ; State 32
		JE [State32]
		CMP EDX,21h ; State 33
		JE [State33]
		CMP EDX,12Dh ; State 301
		JMP [TurnBack1]

State30:
		CMP BYTE PTR DS:[ESI+82h],1h
		JGE [State30_3]
		ADD BYTE PTR DS:[ESI+82h],1h
		
State30_1:
		CMP BH, 1h
		JGE [State30_2]
		ADD BH, 1h
		MOV BYTE PTR DS:[ESI+80h],BH
		JMP [TurnBack2]
		
State30_2:
		XOR BH,BH
		MOV BYTE PTR DS:[ESI+80h],BH
		JMP [TurnBack2]
		
State30_3:
		MOV BYTE PTR DS:[ESI+82h],0h
		JMP [TurnBack2]



State31:
		MOV BH, 1h
		MOV BYTE PTR DS:[ESI+80h],BH
		JMP [TurnBack2]

State32:
		XOR BH,BH ; set 0 WTF
		MOV BYTE PTR DS:[ESI+80h], BH
		JMP [TurnBack2]


State33:
	
		MOV BH, BYTE PTR DS:[ESI+0CFh]
		CMP BH, 1
		JE [State33_left]
		
		MOV BH, BYTE PTR DS:[ESI+0D0h]
		CMP BH, 1
		JE [State33_right]
		
		MOV BH, BYTE PTR DS:[ESI+80h]
		MOV BYTE PTR DS:[ESI+80h], BH
		JMP [State33_end]
		
State33_left:

		MOV BH, 1h
		MOV BYTE PTR DS:[ESI+80h], BH
		JMP [State33_end]
		
State33_right:
		
		MOV BH, 0h
		MOV BYTE PTR DS:[ESI+80h], BH
		JMP [State33_end]
		
State33_end:
		JMP [TurnBack2]

StateTurn3x endp




State9xxx proc
	
	MOV EAX, DWORD PTR DS:[ECX+EDX+838h]
    CMP EAX,0BB8h ; 3000
	JE [Back1] ; regular code, for state 3000
	CMP EAX,2328h ; 9000 - minimum
	JL SHORT [Back2] ; regular code, for another states
	CMP EAX,2647h ; 9799 - limit
	JG SHORT [Back2] ; regular code, for another states
	

	SUB EAX, 2328h
	MOV DWORD PTR DS:[EBX+70h],EAX
	MOV DWORD PTR DS:[EBX+88h],0h
	FST QWORD PTR DS:[EBX+40h]
	FLD DWORD PTR DS:[ECX+EDX+848h]
	FSTP QWORD PTR DS:[EBX+50h]
	JMP [BackSt_9x_2]
	
Back1:
	JMP [BackSt_9x_1]
	
Back2:
	JMP [BackSt_9x_2]

State9xxx endp











