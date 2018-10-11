.data

Rowing100108_back1 dd 00413B6Eh
Rowing100108_back2 dd 00413BEEh

Collision_back1 dd 00417618h
Collision_back2 dd 004175E4h
Collision_back3 dd 004175C8h

TpSubAdd_back dd 00403482h

Clone_Name_back1 dd 0041A892h
Clone_Name_back2 dd 0041A890h

Mpoint_Clone_Fix_back1 dd 0044652Ch

Wait_Reset_back dd 00412CC2h

hitG_enert_back dd 0041AE4Eh
mpoint_dvx_fix_back dd 0044661Ch

hitG_state_fix_back dd 0041AE29h

hit_FaSpeed1_back dd 00408113h
hit_FaSpeed2_back dd 00408131h

hit_FaSpeed3_back dd 0040814Fh
hit_FaSpeed4_back dd 0040816Dh

hit_FaSpeed5_back dd 00407FEFh
hit_FaSpeed6_back dd 0040802Ch

hit_FaSpeed7_back dd 004080B3h
hit_FaSpeed8_back dd 004080A4h

StageType3_act_set dd 00437748h
StageType3_act_back dd 00437730h
StageType3_act_back2 dd 0043774Fh
.code

Rowing100108 proc
	
	CMP BYTE PTR DS:[ESI+0BFh],0
	JLE SHORT [Rowing100108_normal_back1]
	
	PUSH EAX
	PUSH ECX
	
	MOV ECX,100
	MOV EAX,DWORD PTR DS:[ESI+368h]
	IMUL ECX,ECX,1B0h
	CMP DWORD PTR DS:[EAX+ECX+830h],1
	JNE [Rowing100108_skip] 
		
	MOV ECX,108
	MOV EAX,DWORD PTR DS:[ESI+368h]
	IMUL ECX,ECX,1B0h
	CMP DWORD PTR DS:[EAX+ECX+830h],1
	JNE [Rowing100108_skip] 
	
	POP ECX
	POP EAX
	JMP [Rowing100108_back1]
	
	Rowing100108_normal_back1:
	JMP [Rowing100108_back2]
	
	Rowing100108_skip:
	POP ECX
	POP EAX
	JMP [Rowing100108_back2]

Rowing100108 endp

Collision proc
	
	check_for_untouchability_1:
	MOV EAX, DWORD PTR DS:[ESI+198h]
	CMP DWORD PTR DS:[EAX+8Ch],0
	JG SHORT [check_for_untouchability_2]
	JMP [standart_team_check]
	
	check_for_untouchability_2:
	MOV EAX, DWORD PTR DS:[EDI+198h]
	CMP DWORD PTR DS:[EAX+8Ch],0
	JG SHORT [standart_team_check]
	JMP[no_attack]
	
	standart_team_check:
	MOV EAX,DWORD PTR DS:[EDI+364h]
	CMP DWORD PTR DS:[ESI+364h],EAX
	JNZ SHORT [attack_success]
	JMP SHORT [next_cmp]
	
	attack_success:
	JMP [Collision_back1]
	
	no_attack:
	JMP [Collision_back2]
	
	next_cmp:
	JMP [Collision_back3]

Collision endp

TpSub proc
	PUSH ECX
	MOV ECX, DWORD PTR DS:[ESI+70h]
	IMUL ECX,ECX,1B0h
	ADD ECX, DWORD PTR DS:[ESI+368h]
	CMP DWORD PTR DS:[ECX+938h],0h
	JE [TpSub_standart]
	PUSH EAX
	FILD DWORD PTR SS:[ESP+0h]
	FISUB DWORD PTR DS:[ECX+938h]
	FISTP DWORD PTR SS:[ESP+0h]
	POP EAX
	POP ECX
	JMP [TpSubAdd_back]
	
	TpSub_standart:
	SUB EAX,78h
	POP ECX
	JMP [TpSubAdd_back]
	
TpSub endp
TpAdd proc
	PUSH ECX
	MOV ECX, DWORD PTR DS:[ESI+70h]
	IMUL ECX,ECX,1B0h
	ADD ECX, DWORD PTR DS:[ESI+368h]
	CMP DWORD PTR DS:[ECX+938h],0h
	JE [TpAdd_standart]
	PUSH EAX
	FILD DWORD PTR SS:[ESP+0h]
	FIADD DWORD PTR DS:[ECX+938h]
	FISTP DWORD PTR SS:[ESP+0h]
	POP EAX
	POP ECX
	JMP [TpSubAdd_back]
	
	
	TpAdd_standart:
	ADD EAX,78h
	POP ECX
	JMP [TpSubAdd_back]
	
TpAdd endp

Clone_Name proc
	CMP EAX,0Ah
	JL [Name_Player_And_Clon]
	CMP DWORD PTR DS:[EDI+2F4h], -1
	JE SHORT [No_Clone]
	
Name_Player_And_Clon:
	PUSH EAX
	MOV EAX, DWORD PTR DS:[EDI+354h]
	IMUL ESI,EAX,0Bh
	ADD ESI,0044FCC0h
	POP EAX
	JMP [Clone_Name_back2]

	No_Clone:
	JMP [Clone_Name_back1]

Clone_Name endp
Mpoint_CloneFix proc 
	
	MOV EAX,DWORD PTR DS:[ECX+354h]
	MOV DWORD PTR DS:[EBX+354h],EAX
	MOV DWORD PTR DS:[EBX+2F4h],EAX
	JMP [Mpoint_Clone_Fix_back1]
	
Mpoint_CloneFix endp

Fix_Stop_Running proc
	
	NOP
	NOP
	NOP

Fix_Stop_Running endp

Wait_Reset proc
	
	MOV DWORD PTR DS:[ESI+70h],EBX
	MOV DWORD PTR DS:[ESI+88h],0h
	MOV EAX,DWORD PTR SS:[ESP+10h]
	JMP [Wait_Reset_back]
	
Wait_Reset endp

hitG_enert proc 
	
	FSTP QWORD PTR DS:[ESI+48h]
	PUSH 3h
	FLD QWORD PTR DS:[ESI+40h]
	FIDIV DWORD PTR SS:[ESP]
	FSTP QWORD PTR DS:[ESI+40h]
	FLD QWORD PTR DS:[ESI+50h]
	FIDIV DWORD PTR SS:[ESP]
	FSTP QWORD PTR DS:[ESI+50h]
	ADD ESP,4h
	JMP [hitG_enert_back]

hitG_enert endp

mpoint_dvx_fix proc
	
	FILD DWORD PTR SS:[ESP+4h]
	FILD DWORD PTR SS:[ESP+8h]
	CMP BYTE PTR DS:[EBX+80h],1h
	JNE SHORT [mpoint_dvx_fix_no_facing]
	FCHS
	mpoint_dvx_fix_no_facing:
	FSTP QWORD PTR DS:[EBX+40h]
	JMP [mpoint_dvx_fix_back]

mpoint_dvx_fix endp

hitG_state_fix proc
	
	JMP [hitG_state_fix_back]

hitG_state_fix endp

hit_FaSpeed1 proc
	
	PUSH EAX
	PUSH EDX
	
	MOV EAX, DWORD PTR DS:[ECX+70h]
	IMUL EAX, EAX, 1B0h
	MOV EDX, DWORD PTR DS:[ECX+368h]
	
	MOV EDX, DWORD PTR DS:[EAX+EDX+940h]
	CMP DWORD PTR DS:[EDX+4h],0h
	JE [hit_FaSpeed1_standart]
	
	FILD DWORD PTR DS:[EDX+4h]
	POP EDX
	POP EAX
	JMP [hit_FaSpeed1_back]
	
hit_FaSpeed1_standart:
	FLD QWORD PTR DS:[004479F0h]
	POP EDX
	POP EAX
	JMP [hit_FaSpeed1_back]
	
hit_FaSpeed1 endp

hit_FaSpeed2 proc
	
	PUSH EAX
	PUSH EDX
	
	MOV EAX, DWORD PTR DS:[ECX+70h]
	IMUL EAX, EAX, 1B0h
	MOV EDX, DWORD PTR DS:[ECX+368h]
	
	MOV EDX, DWORD PTR DS:[EAX+EDX+940h]
	CMP DWORD PTR DS:[EDX+4h],0h
	JE [hit_FaSpeed2_standart]
	
	FILD DWORD PTR DS:[EDX+4h]
	FCHS
	POP EDX
	POP EAX
	JMP [hit_FaSpeed2_back]
	
hit_FaSpeed2_standart:
	FLD QWORD PTR DS:[004479E8h]
	POP EDX
	POP EAX
	JMP [hit_FaSpeed2_back]
	
hit_FaSpeed2 endp

hit_FaSpeed3 proc
	
	PUSH EAX
	PUSH EDX
	
	MOV EAX, DWORD PTR DS:[ECX+70h]
	IMUL EAX, EAX, 1B0h
	MOV EDX, DWORD PTR DS:[ECX+368h]
	
	MOV EDX, DWORD PTR DS:[EAX+EDX+940h]
	CMP DWORD PTR DS:[EDX+8h],0h
	JE [hit_FaSpeed3_standart]
	
	FILD DWORD PTR DS:[EDX+8h]
	POP EDX
	POP EAX
	JMP [hit_FaSpeed3_back]
	
hit_FaSpeed3_standart:
	FLD QWORD PTR DS:[004479E0h]
	POP EDX
	POP EAX
	JMP [hit_FaSpeed3_back]
	
hit_FaSpeed3 endp

hit_FaSpeed4 proc
	
	PUSH EAX
	PUSH EDX
	
	MOV EAX, DWORD PTR DS:[ECX+70h]
	IMUL EAX, EAX, 1B0h
	MOV EDX, DWORD PTR DS:[ECX+368h]
	
	MOV EDX, DWORD PTR DS:[EAX+EDX+940h]
	CMP DWORD PTR DS:[EDX+8h],0h
	JE [hit_FaSpeed4_standart]
	
	FILD DWORD PTR DS:[EDX+8h]
	FCHS
	POP EDX
	POP EAX
	JMP [hit_FaSpeed4_back]
	
hit_FaSpeed4_standart:
	FLD QWORD PTR DS:[004479D8h]
	POP EDX
	POP EAX
	JMP [hit_FaSpeed4_back]
	
hit_FaSpeed4 endp


hit_FaSpeed5 proc
	
	PUSH ECX
	PUSH EAX
	
	MOV ECX, DWORD PTR DS:[EDX+70h]
	IMUL ECX, ECX, 1B0h
	MOV EAX, DWORD PTR DS:[EDX+368h]
	
	MOV EAX, DWORD PTR DS:[ECX+EAX+940h]
	CMP DWORD PTR DS:[EAX+0Ch],0h
	JE [hit_FaSpeed5_standart]
	
	FILD DWORD PTR DS:[EAX+0Ch]
	POP EAX
	POP ECX
	JMP [hit_FaSpeed5_back]
	
hit_FaSpeed5_standart:
	FLD QWORD PTR DS:[00447A20h]
	POP EAX
	POP ECX
	JMP [hit_FaSpeed5_back]
	
hit_FaSpeed5 endp

hit_FaSpeed6 proc
	
	PUSH ECX
	PUSH EDX
	
	MOV ECX, DWORD PTR DS:[EAX+70h]
	IMUL ECX, ECX, 1B0h
	MOV EDX, DWORD PTR DS:[EAX+368h]
	
	MOV EDX, DWORD PTR DS:[ECX+EDX+940h]
	CMP DWORD PTR DS:[EDX+10h],0h
	JE [hit_FaSpeed6_standart]
	
	FILD DWORD PTR DS:[EDX+10h]
	POP EDX
	POP ECX
	JMP [hit_FaSpeed6_back]
	
hit_FaSpeed6_standart:
	FLD QWORD PTR DS:[00447A18h]
	POP EDX
	POP ECX
	JMP [hit_FaSpeed6_back]
	
hit_FaSpeed6 endp

hit_FaSpeed7 proc
	
	PUSH ECX
	PUSH EAX
	
	MOV ECX, DWORD PTR DS:[EDX+70h]
	IMUL ECX, ECX, 1B0h
	MOV EAX, DWORD PTR DS:[EDX+368h]
	
	MOV EAX, DWORD PTR DS:[ECX+EAX+940h]
	CMP DWORD PTR DS:[EAX+14h],0h
	JE [hit_FaSpeed7_standart]
	
	FILD DWORD PTR DS:[EAX+14h]
	POP EAX
	POP ECX
	JMP [hit_FaSpeed7_back]
	
hit_FaSpeed7_standart:
	FLD QWORD PTR DS:[004479F8h]
	POP EAX
	POP ECX
	JMP [hit_FaSpeed7_back]
	
hit_FaSpeed7 endp

hit_FaSpeed8 proc
	
	PUSH ECX
	PUSH EAX
	
	MOV ECX, DWORD PTR DS:[EDX+70h]
	IMUL ECX, ECX, 1B0h
	MOV EAX, DWORD PTR DS:[EDX+368h]
	
	MOV EAX, DWORD PTR DS:[ECX+EAX+940h]
	CMP DWORD PTR DS:[EAX+18h],0h
	JE [hit_FaSpeed8_standart]
	
	MOV ECX, DWORD PTR DS:[EAX+18h]
	DEC ECX
	
	PUSH ECX
	FILD DWORD PTR SS:[ESP]
	POP ECX
	
	POP EAX
	POP ECX
	JMP [hit_FaSpeed8_back]
	
hit_FaSpeed8_standart:
	FLD QWORD PTR DS:[00447A00h]
	POP EAX
	POP ECX
	JMP [hit_FaSpeed8_back]
	
hit_FaSpeed8 endp

StageType3_act proc
	
	XOR EDX,EDX
	CMP ECX,EDX
         JE SHORT [StageType3_act_toSet]
	CMP ECX,3
	JE SHORT [StageType3_act_toSet2]
	CMP ECX,5
	JE SHORT [StageType3_act_toSet]
	JMP [StageType3_act_back]

	StageType3_act_toSet:
	JMP [StageType3_act_set]
	
	StageType3_act_toSet2:
	JMP [StageType3_act_back2]


StageType3_act endp











