.data

delay_back dd 100011E1h
join_back dd 0042A386h
random_back dd 0042A632h
random2_back dd 0042BEF8h
cname_back dd 0042A5B3h
indep_back dd 0042ADD0h
team11_back dd 0042ABF3h
team21_back dd 0042AC6Ah
team31_back dd 0042ACE1h
team41_back dd 0042AD58h
indep2_back dd 0042C5D0h
team12_back dd 0042C66Ah
team22_back dd 0042C704h
team32_back dd 0042C79Eh
team42_back dd 0042C838h
cname2_back dd 0042BE5Fh
HumComp_back dd 004330B4h
HumComp2_back dd 00435171h
random3_back dd 00434FD5h
random4_back dd 00432F0Fh
cname3_back dd 00435036h
cname4_back dd 00432F79h

custom_999_back dd 0040DCE4h

new_mp_back	dd 0041AF37h

proc_100 dq 100.0

mp_1proc dq 0h
bar_1proc dq 1.24

mp_Nproc dq 0h
bar_Nproc dq 0h

bar_x dd 0
bar_y dd 0

new_mp_result dd 0h

innertion_back dd 00419928h
innertion_skip dd 004198DEh

no_facing_weapon_back dd 0042F0CBh

center_y_back dd 10004D13h

no_shadow_itr_back1 dd 0041A74Ch
no_shadow_itr_back2 dd 0041A6ACh

no_name_back1 dd 0041A981h
no_name_back2 dd 0041A830h
no_name_back3 dd 0041A882h
.code

gravity proc
	
	ADD BYTE PTR DS:[EAX],AL
	ADD BYTE PTR DS:[EAX],AL
	ADD BYTE PTR DS:[EAX],AL
	CLC
	AAS

gravity endp

custom_delays proc
	
	MOV DWORD PTR DS:[EBX+0B4h],0
	MOV ECX,DWORD PTR SS:[ESP+0Ch]
	MOV DWORD PTR DS:[EDI+0B4h],0
	JMP [delay_back]

custom_delays endp

custom_999_inAir proc
	
	MOV EAX,729
	JMP [custom_999_back]

custom_999_inAir endp

join_nomi proc
	
	LEA EBX,DWORD PTR DS:[EDI+0B1h] 
	PUSH EBX 
	SHL EAX,8h
	OR EAX,ECX 
	PUSH 0FFFFFFh 
	PUSH 0
	JMP [join_back]
	
join_nomi endp

random_nomi proc
	
	SHL EAX,8h
	OR EAX,ECX
	PUSH 0999999h
	PUSH 0
	JMP[random_back]

random_nomi endp

name_nomi proc
	
	SHL EAX,8h
	OR EAX,ECX
	PUSH 0999999h
	JMP[cname_back]

name_nomi endp

indep_nomi proc
	
	SHL EDX,8h
	OR EDX,EAX
	PUSH 0999999h
	PUSH 0
	JMP [indep_back]

indep_nomi endp

random2_nomi proc
	
	SHL EDX,8h
	OR EDX,EAX
	PUSH 0999999h
	PUSH 0
	JMP [random2_back]

random2_nomi endp

team1_1 proc
	
	SHL EDX,8h
	OR EDX,EAX
	PUSH 0CC6600h
	PUSH 0
	JMP[team11_back]

team1_1 endp

team2_1 proc
	
	SHL EDX,8h
	OR EDX,EAX
	PUSH 00000CCh
	PUSH 0
	JMP[team21_back]

team2_1 endp

team3_1 proc
	
	SHL EDX,8h
	OR EDX,EAX
	PUSH 0009900h
	PUSH 0
	JMP[team31_back]

team3_1 endp

team4_1 proc
	
	SHL EDX,8h
	OR EDX,EAX
	PUSH 00099FFh
	PUSH 0
	JMP[team41_back]

team4_1 endp

indep2_nomi proc
	
	SHL EAX,8h
	OR EAX,ECX
	PUSH 0999999h
	PUSH 0
	JMP[indep2_back]

indep2_nomi endp


team1_2 proc
	
	SHL EAX,8h
	OR EAX,ECX
	PUSH 0CC6600h
	PUSH 0
	JMP[team12_back]

team1_2 endp

team2_2 proc
	
	SHL EAX,8h
	OR EAX,ECX
	PUSH 00000CCh
	PUSH 0
	JMP[team22_back]

team2_2 endp

team3_2 proc
	
	SHL EAX,8h
	OR EAX,ECX
	PUSH 0009900h
	PUSH 0
	JMP[team32_back]

team3_2 endp

team4_2 proc
	
	SHL EAX,8h
	OR EAX,ECX
	PUSH 00099FFh
	PUSH 0
	JMP[team42_back]

team4_2 endp

name2_nomi proc
	
	SHL EDX,8h
	ADD EDI,0B1h
	OR EDX,EAX
	PUSH EDI
	PUSH 0999999h
	JMP[cname2_back]

name2_nomi endp

Hum_Comp proc
	
	CMP DWORD PTR DS:[EBX*4h+451364h],EBP
	PUSH 0FFFFFFh
	JMP[HumComp_back]
Hum_Comp endp

Hum_Comp2 proc
	
	CMP DWORD PTR DS:[EBX*4h+451364h],EDI
	PUSH 0FFFFFFh
	JMP[HumComp2_back]
Hum_Comp2 endp


random3_nomi proc
	
	SHL ECX,8h
	ADD ESI,3Bh
	PUSH ESI
	OR ECX,EDX
	PUSH 0999999h
	PUSH EDI
	JMP [random3_back]

random3_nomi endp

name3_nomi proc
	
	MOV ECX,DWORD PTR DS:[452980h]
	ADD ESI,3Bh
	PUSH ESI
	PUSH 0999999h
	JMP[cname3_back]

name3_nomi endp

random4_nomi proc
	
	SHL EDX,8h
	ADD ESI,3Bh
	PUSH ESI
	OR EDX,EAX
	PUSH 0999999h
	PUSH EBP
	JMP [random4_back]

random4_nomi endp

name4_nomi proc
	
	MOV EAX,DWORD PTR DS:[452980h]
	NOP
	ADD ESI,3Bh
	PUSH ESI
	PUSH 0999999h
	JMP[cname4_back]

name4_nomi endp

New_mp_bar proc 
	
	;Оригинальный кусок
	SUB ESP,10h
	XOR ESI,ESI
	XOR EDI,EDI
	MOV DWORD PTR SS:[ESP+0Ch],8
	MOV EBP,DWORD PTR SS:[ESP+24h]
	PUSH ESI
	PUSH EDI
	PUSH EAX
	PUSH EBX
	PUSH ECX
	PUSH EDX	
	PUSH EBP
	MOV ESI,EBP 
	
type_cmp:
	MOV EDX,DWORD PTR DS:[458B00h]
	CMP BYTE PTR DS:[EDX+EDI+4h],0
	JE [next_obj]
	MOV EAX,DWORD PTR DS:[EDX+EDI*4+3ECh]
	MOV EBX,DWORD PTR DS:[EAX+198h]
	MOV EAX,DWORD PTR DS:[EAX+368h]	
	CMP DWORD PTR DS:[EAX+6F8h],0
	JNE [next_obj]
	CMP DWORD PTR DS:[EBX+14h],0
	JNE [draw_mp]
	JMP[next_obj]
	
draw_mp:
	PUSH EAX
	PUSH EDX
	
	FILD DWORD PTR DS:[EBX+14h]
	FDIV [proc_100]
	FSTP [mp_1proc]
	
	FLD DWORD PTR DS:[EBX+10h]
	FDIV [mp_1proc]
	FSTP [mp_Nproc]
	
	FLD [mp_Nproc]
	FMUL [bar_1proc]
	FSTP [bar_Nproc]
	
	FLD [bar_Nproc]
	FSTP [new_mp_result]
	
	MOV EBX, [new_mp_result]
	
	MOV bar_x, EDI
	CMP EDI,10
	JL[no_com]
	SUB bar_x, 10
	
no_com:
	PUSH ESI
	PUSH 0
	PUSH 1
	PUSH 0
	MOV ECX,45
	CMP bar_x,4
	JLE [no_4p1]
	ADD ECX,150
no_4p1:
	PUSH ECX
	MOV ECX, bar_x
	IMUL ECX, 198
	ADD ECX, 57
	PUSH ECX
	MOV ECX,DWORD PTR DS:[spec_mp_addr]
	MOV DWORD PTR DS:[ECX+10h],0
	MOV DWORD PTR DS:[ECX+0FB0h],124
	MOV DWORD PTR DS:[ECX+7E0h],0
	MOV DWORD PTR DS:[ECX+1780h],8
	CALL [CallFunc2]
	
	PUSH ESI
	PUSH 0
	PUSH 1
	PUSH 0
	MOV ECX,45
	CMP bar_x,4
	JLE [no_4p2]
	ADD ECX,150
no_4p2:
	PUSH ECX
	MOV ECX, bar_x
	IMUL ECX, 198
	ADD ECX, 57
	PUSH ECX
	MOV ECX,DWORD PTR DS:[spec_mp_addr]
	MOV DWORD PTR DS:[ECX+10h],0
	MOV DWORD PTR DS:[ECX+0FB0h],EBX
	MOV DWORD PTR DS:[ECX+7E0h],8
	MOV DWORD PTR DS:[ECX+1780h],8
	CALL [CallFunc2]
	
	POP EDX
	POP EAX
	JMP [next_obj]
	
next_obj:
	ADD EDI,1
	CMP EDI,3E8h
	JL [type_cmp]
	JMP [mp_bar_back]
	
mp_bar_back:
	POP EBP
	POP EDX
	POP ECX
	POP EBX
	POP EAX
	POP EDI
	POP ESI
	JMP [new_mp_back]

New_mp_bar endp

innertion_save proc
	
	CMP DWORD PTR DS:[EDX+20h],EBX
	JE SHORT [innertion_saved]
	CMP DWORD PTR DS:[EDX+0B0h],EBX
	JL SHORT [innertion_saved]
	MOV EDI,DWORD PTR DS:[EDX+20h]
	JMP [innertion_skip]
innertion_saved:
	JMP [innertion_back]

innertion_save endp


no_facing_weapon proc
	
	JMP [no_facing_weapon_back]

no_facing_weapon endp


NoShadow_Itr proc
	
	CMP ECX,0DFh
	JE SHORT [YesShadow_ITR_back]
	PUSH EAX
	MOV EAX, DWORD PTR DS:[ESI+198h]
	CMP DWORD PTR DS:[EAX+94h],1h
	JE SHORT [NoShadow_ITR_back]
	CMP DWORD PTR DS:[EAX+94h],2h
	JE SHORT [NoShadow_ITR_back]
	POP EAX
	JMP [no_shadow_itr_back2]
	
	YesShadow_ITR_back:
	JMP [no_shadow_itr_back1]
	
	NoShadow_ITR_back:
	POP EAX
	JMP [no_shadow_itr_back1]
	
NoShadow_Itr endp

NoName_Itr proc
	
	MOV EDI,DWORD PTR DS:[EBX+EAX*4h+3ECh]
	MOV EDX, DWORD PTR DS:[EDI+198h]
	CMP DWORD PTR DS:[EDX+94h],2h
	JE SHORT [NoName_Itr_hide]
	CMP EAX,14h
	JL SHORT [NoName_Itr_show]
	JMP SHORT [NoName_Itr_back]

	NoName_Itr_hide:
	JMP [no_name_back1]
	
	NoName_Itr_show:
	JMP [no_name_back3]
	
	NoName_Itr_back:
	JMP [no_name_back2]
	
NoName_Itr endp











