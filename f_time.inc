.data
	every_one_tick_back dd 0041D7E5h
	every_back dd 0041F9CFh
	every_tick_t0 dd 0041FB28h
	every_tick_tf dd 0041F9AEh
.code 

Every1Tick_NotPlayer proc
	
Izanami_check:
	PUSH EAX
	PUSH EDX
	PUSH ECX
	PUSH EDI
	
	CMP[Izanami_Time],0
	JG[Izanami_working]
	
	CMP[Izanami_Time],0
	JE[Izanami_restoring]
	
	JMP[Izanami_check_back]
	
	
Izanami_working:
	DEC [Izanami_Time]
	JMP [Izanami_check_back]



Izanami_restoring:
	
	CMP [Izanami_Loop], 0h
	JLE [Izanami_stop]
	
	MOV EDX, [Izanami_MaxTime]
	MOV [Izanami_Time], EDX
	DEC [Izanami_Loop]
	
	MOV [Izanami_Condition], 0
	
Izanami_start_cycle_restoring:
	MOV EDI, 0h
	
Izanami_restoring_check_object:
	
	MOV EDX,DWORD PTR DS:[00458B00h]
	CMP BYTE PTR DS:[EDX+EDI+4h],0
	JE[Izanami_restoring_next_object]
	
	MOV ECX, DWORD PTR DS:[EDX+EDI*4h+3ECh]
	
	MOV EAX, DWORD PTR DS:[ECX+368h]
	CMP DWORD PTR DS:[EAX+6F8h],0
	JNE[Izanami_restoring_next_object]
	
	CMP [Izanami_Condition], 0
	JE [Izanami_check_damage]	
	
	CMP [Izanami_Condition],1
	JE [Izanami_rewrite_params]
	
	CMP [Izanami_Condition],2
	JE [Izanami_backup_params]
	
	
	
	
Izanami_check_damage:
	MOV EAX, DWORD PTR DS:[ECX+198h]
	
	CMP DWORD PTR DS:[EAX+2Ch],3
	JE[Izanami_caster]
	CMP DWORD PTR DS:[EAX+2Ch],2
	JE[Izanami_target]
	JMP [Izanami_restoring_next_object]
	
Izanami_caster:
	invoke Opoint_Maker,336,18,-35,0,1,1,1,15,652,0,10,0,0,ECX
	MOV EDX, DWORD PTR DS:[EAX+30h]
	MOV DWORD PTR DS:[EAX+30h], 0h
	MOV [Izanami_damage_caster], EDX
	JMP [Izanami_restoring_next_object]
Izanami_target:
	MOV EDX, DWORD PTR DS:[EAX+30h]
	MOV DWORD PTR DS:[EAX+30h], 0h
	MOV [Izanami_damage_target], EDX
	JMP [Izanami_restoring_next_object]
	
	
Izanami_rewrite_params:
	MOV EAX, DWORD PTR DS:[ECX+198h]
	
	MOV EDX, DWORD PTR DS:[ECX+2FCh]
	MOV DWORD PTR DS:[EAX+40h],EDX
	MOV EDX, DWORD PTR DS:[ECX+300h]
	MOV DWORD PTR DS:[EAX+44h],EDX
	MOV EDX, DWORD PTR DS:[ECX+308h]
	MOV DWORD PTR DS:[EAX+48h],EDX
	JMP [Izanami_restoring_next_object]
	
	
Izanami_backup_params:
	MOV EAX, DWORD PTR DS:[ECX+198h]
	
	MOV EDX, DWORD PTR DS:[EAX+40h]
	MOV DWORD PTR DS:[ECX+2FCh],EDX
	MOV EDX, DWORD PTR DS:[EAX+44h]
	MOV DWORD PTR DS:[ECX+300h],EDX
	MOV EDX, DWORD PTR DS:[EAX+48h]
	MOV DWORD PTR DS:[ECX+308h],EDX
	JMP [Izanami_restoring_next_object]

;	MOV DWORD PTR DS:[ECX+70h],EDX
;	MOV EDX, DWORD PTR DS:[EAX+40h]
;	MOV DWORD PTR DS:[ECX+88h],EDX
;	MOV DL, BYTE PTR DS:[EAX+44h]
;	MOV BYTE PTR DS:[ECX+80h],DL
;	MOV EDX, DWORD PTR DS:[EAX+48h]
;	MOV DWORD PTR DS:[ECX+0B0h],EDX
;	MOV EDX, DWORD PTR DS:[EAX+4Ch]
;	MOV DWORD PTR DS:[ECX+0B4h],EDX
;	MOV EDX, DWORD PTR DS:[EAX+50h]
;	MOV DWORD PTR DS:[ECX+0B8h],EDX

;	FLD QWORD PTR DS:[EAX+58h]
;	FIST DWORD PTR DS:[ECX+10h]
;	FSTP QWORD PTR DS:[ECX+58h]
;	FLD QWORD PTR DS:[EAX+60h]
;	FIST DWORD PTR DS:[ECX+14h]
;	FSTP QWORD PTR DS:[ECX+60h]
;	FLD QWORD PTR DS:[EAX+68h]
;	FIST DWORD PTR DS:[ECX+18h]
;	FSTP QWORD PTR DS:[ECX+68h]

;	FLD QWORD PTR DS:[EAX+70h]
;	FSTP QWORD PTR DS:[ECX+28h]
;	FLD QWORD PTR DS:[EAX+78h]
;	FSTP QWORD PTR DS:[ECX+30h]
;	FLD QWORD PTR DS:[EAX+80h]
;	FSTP QWORD PTR DS:[ECX+38h]

;	FLD QWORD PTR DS:[EAX+88h]
;	FSTP QWORD PTR DS:[ECX+40h]
;	FLD QWORD PTR DS:[EAX+90h]
;	FSTP QWORD PTR DS:[ECX+48h]
;	FLD QWORD PTR DS:[EAX+98h]
;	FSTP QWORD PTR DS:[ECX+50h]
	
	
; ‘”Õ ÷»ﬂ ”ƒ¿À≈Õ»ﬂ Œ¡⁄≈ “Œ¬ œ–»Õ¿ƒÀ≈∆¿Ÿ»’ œ≈–—ŒÕ¿∆¿Ã
;Izanami_restoring_object:
;	
;	MOV EAX, DWORD PTR DS:[ECX+354h]
;	MOV EDX, DWORD PTR DS:[EDX+EAX*4h+3ECh]
;	
;	MOV EAX, DWORD PTR DS:[EDX+198h]
;	CMP DWORD PTR DS:[EAX+2Ch],2
;	JNE[Izanami_restoring_next_object]
;	
;	CALL [opoint_maker_call1]
;	
;	JMP [Izanami_restoring_next_object]
	
	
Izanami_restoring_next_object:
	INC EDI
	CMP EDI, 1000
	JL [Izanami_restoring_check_object]
	
Izanami_condition_check:
	CMP [Izanami_Condition], 0
	JE[Izanami_condition_check_zero]
	
	JMP [Izanami_check_back]
	
	
Izanami_condition_check_zero:
	MOV EAX, [Izanami_damage_caster]
	MOV ECX, [Izanami_damage_target]
	
	CMP EAX, ECX
	JLE[Condition_set_rewrite]
	CMP EAX, ECX
	JG [Condition_set_backup]
	
Condition_set_rewrite:
	MOV [Izanami_Condition], 1
	JMP [Izanami_start_cycle_restoring]
Condition_set_backup:
	MOV [Izanami_Condition], 2
	JMP [Izanami_start_cycle_restoring]
	
	
	
	
Izanami_stop:
	MOV [Izanami_Time], -1
	MOV [Izanami_Loop], -1
	MOV [Izanami_Condition], 0
	
	MOV EDI, 0h
	
Izanami_stop_check_object:
	MOV EDX,DWORD PTR DS:[00458B00h]
	CMP BYTE PTR DS:[EDX+EDI+4h],0
	JE[Izanami_stop_next_object]
	
	MOV ECX, DWORD PTR DS:[EDX+EDI*4h+3ECh]
	MOV EAX, DWORD PTR DS:[ECX+198h]
	MOV DWORD PTR DS:[EAX+2Ch],0
	JMP [Izanami_stop_next_object]
	
Izanami_stop_next_object:
	INC EDI
	CMP EDI, 1000
	JL [Izanami_stop_check_object]
	JMP [Izanami_check_back]
	
Izanami_check_back:
	POP EDI
	POP ECX
	POP EDX
	POP EAX

	MOV DWORD PTR DS:[00450BD0h],EDX
	JMP [every_one_tick_back]

Every1Tick_NotPlayer endp


every_tick_type_fix proc
	
	JMP[every_tick_tf]

every_tick_type_fix endp


every_tick proc
	PUSH ECX
	PUSH EDX
	PUSH EAX


every_1tick:
	
	Opacity_timer:
		PUSH EAX
		PUSH ECX
		MOV ECX, DWORD PTR DS:[ESI+198h]
		CMP DWORD PTR DS:[ECX+64h], 0
		JNE [Opacity_timer_skip]
		CMP DWORD PTR DS:[ECX+70h], 0
		JLE [Opacity_timer_skip]
		SUB DWORD PTR DS:[ECX+70h], 1h
		
		CMP DWORD PTR DS:[ECX+70h], 0
		JNE [Opacity_timer_skip]
		MOV EAX, DWORD PTR DS:[ECX+74h]
		MOV  DWORD PTR DS:[ECX+64h], EAX
		
		JMP [Opacity_timer_skip]
	Opacity_timer_skip:
		POP ECX
		POP EAX
	Opacity_timer_end:
	
	Timer_analog:
		PUSH EAX
		PUSH ECX
		
		MOV ECX, DWORD PTR DS:[ESI+198h]
		CMP DWORD PTR DS:[ECX+78h], 0h
		JLE [Timer_analog_recovery]
		
		CMP DWORD PTR DS:[ECX+78h], 1h
		JG [Timer_analog_sub]
		
		MOV EAX, DWORD PTR DS:[ECX+7Ch]
		MOV DWORD PTR DS:[ESI+70h], EAX
		MOV DWORD PTR DS:[ESI+88h], 0h
		
	Timer_analog_sub:
		SUB DWORD PTR DS:[ECX+78h], 1h
		
	Timer_analog_recovery:
		POP ECX
		POP EAX
	Timer_analog_end:
	
	ik_100015_timer:
		PUSH EAX
		PUSH ECX
		
		MOV ECX, DWORD PTR DS:[ESI+198h]
		CMP DWORD PTR DS:[ECX+8Ch], 0h
		JG [ik_100015_normal_timer]
		CMP DWORD PTR DS:[ECX+8Ch], 0h
		JL [ik_100015_reverse_timer]
		JMP [ik_100015_recovery]
		
		
		ik_100015_normal_timer:
		SUB DWORD PTR DS:[ECX+8Ch],1h
		SUB DWORD PTR DS:[ECX+10h],1h
		CMP DWORD PTR DS:[ECX+8Ch], 0h
		JE [ik_100015_reset]
		CMP DWORD PTR DS:[ECX+10h], 0h
		JLE [ik_100015_reset]
		JMP [ik_100015_recovery]
		
		ik_100015_reverse_timer:
		ADD DWORD PTR DS:[ECX+8Ch],1h
		CMP DWORD PTR DS:[ECX+8Ch],0
		JNE [ik_100015_recovery]
		MOV EDX, DWORD PTR DS:[ECX+90h]
		MOV DWORD PTR DS:[ECX+8Ch], EDX
		MOV DWORD PTR DS:[ECX+90h],0h
		JMP [ik_100015_recovery]
		
	ik_100015_reset:
		MOV DWORD PTR DS:[ECX+8Ch],0
		
	ik_100015_recovery:
		POP ECX
		POP EAX
	ik_100015_end:
	
	
	ik_100018_timer:
		PUSH EDX
		MOV EDX, DWORD PTR DS:[ESI+198h] 
		
		ik_100018_timer_1:
		CMP BYTE PTR DS:[EDX+0F0h],0h
		JLE[ik_100018_timer_2]
		DEC BYTE PTR DS:[EDX+0F0h]
		
		ik_100018_timer_2:
		CMP BYTE PTR DS:[EDX+0F1h],0h
		JLE[ik_100018_timer_3]
		DEC BYTE PTR DS:[EDX+0F1h]
		
		ik_100018_timer_3:
		CMP BYTE PTR DS:[EDX+0F2h],0h
		JLE[ik_100018_timer_4]
		DEC BYTE PTR DS:[EDX+0F2h]
		
		ik_100018_timer_4:
		CMP BYTE PTR DS:[EDX+0F3h],0h
		JLE[ik_100018_timer_5]
		DEC BYTE PTR DS:[EDX+0F3h]
		
		ik_100018_timer_5:
		CMP BYTE PTR DS:[EDX+0F4h],0h
		JLE[ik_100018_timer_6]
		DEC BYTE PTR DS:[EDX+0F4h]
		
		ik_100018_timer_6:
		CMP BYTE PTR DS:[EDX+0F5h],0h
		JLE[ik_100018_timer_7]
		DEC BYTE PTR DS:[EDX+0F5h]
		
		ik_100018_timer_7:
		CMP BYTE PTR DS:[EDX+0F6h],0h
		JLE[ik_100018_timer_recovery]
		DEC BYTE PTR DS:[EDX+0F6h]
		
	ik_100018_timer_recovery:
		POP EDX
	ik_100018_end:
	
	key_reset:
		PUSH EDX
		MOV EDX, DWORD PTR DS:[ESI+198h] 
		
		CMP BYTE PTR DS:[ESI+0D4h],0
		JNE [key_reset_timer]
		CMP BYTE PTR DS:[ESI+0D5h],0
		JNE [key_reset_timer]
		CMP BYTE PTR DS:[ESI+0D6h],0
		JNE [key_reset_timer]
		CMP BYTE PTR DS:[ESI+0D7h],0
		JNE [key_reset_timer]
		CMP BYTE PTR DS:[ESI+0D8h],0
		JNE [key_reset_timer]
		CMP BYTE PTR DS:[ESI+0D9h],0
		JNE [key_reset_timer]
		JMP SHORT [key_reset_zero]
		
		key_reset_timer:
		CMP DWORD PTR DS:[EDX+0F7h],0h
		JG SHORT [key_reset_timer_work]
		MOV DWORD PTR DS:[EDX+0F7h],12h
		JMP [key_reset_recovery]
		
		key_reset_timer_work:
		CMP DWORD PTR DS:[EDX+0F7h],1h
		JE SHORT [key_reset_timer_reset]
		SUB DWORD PTR DS:[EDX+0F7h],1h
		JMP [key_reset_recovery]
		
		key_reset_timer_reset:
		MOV BYTE PTR DS:[ESI+0D4h],0
		MOV BYTE PTR DS:[ESI+0D5h],0
		MOV BYTE PTR DS:[ESI+0D6h],0
		MOV BYTE PTR DS:[ESI+0D7h],0
		MOV BYTE PTR DS:[ESI+0D8h],0
		MOV BYTE PTR DS:[ESI+0D9h],0
		JMP SHORT [key_reset_zero]
		
	key_reset_zero:
		CMP DWORD PTR DS:[EDX+0F7h],0h
		JE SHORT [key_reset_recovery]
		MOV DWORD PTR DS:[EDX+0F7h],0h
	
	key_reset_recovery:
		POP EDX
	key_reset_end:
	
	
	JMP [every_2ticks]
every_1tick_end:


every_2ticks:
	MOV EDX,DWORD PTR DS:[00450BD4h]
	CMP EDX,0
	JNE[every_12ticks]


combo_timer:
	MOV ECX, DWORD PTR DS:[ESI+198h]
	PUSH ECX
	MOV EAX,DWORD PTR DS:[ECX+8h]
	XOR EDX, EDX
	MOV ECX, 100
	DIV ECX
	POP ECX
	
	CMP EDX, 0
	JG [combo_sub_time]
	MOV DWORD PTR DS:[ECX+8h],0
	JMP[combo_no_time]
	
combo_sub_time:
	SUB DWORD PTR DS:[ECX+8h],1
	JMP[combo_no_time]

combo_no_time:
	JMP[state_1XYZZ_check]



state_1XYZZ_check:
	mov eax, dword ptr ds:[esi+198h]
	cmp word ptr ds:[eax+2h],0
	jg[state_1XYZZ_active]
	jmp[state_1XYZZ_skip]

state_1XYZZ_active:
	xor ebx,ebx
	mov bl, byte ptr ds:[eax+0h]
	add dword ptr ds:[esi+2FCh],ebx
	
	cmp dword ptr ds:[esi+300h],500
	jge [s1xyzz_noblack]
	add dword ptr ds:[esi+300h],ebx

s1xyzz_noblack:
	xor ebx,ebx
	mov bl, byte ptr ds:[eax+1h]
	add dword ptr ds:[esi+308h],ebx
	
	mov bx, word ptr ds:[eax+2h]
	sub bx, 1
	mov word ptr ds:[eax+2h],bx
	jmp[state_1XYZZ_skip]

state_1XYZZ_skip:
	jmp[every_12ticks]




every_12ticks:
	MOV EDX,DWORD PTR DS:[00450BD0h]
	CMP EDX,6
	JE[Special_MP_regen]
	JMP[back_to_standart]


Special_MP_regen:
	PUSH ECX
	PUSH EDX
	MOV ECX, DWORD PTR DS:[ESI+368h]
	CMP DWORD PTR DS:[ECX+6F4h],14 ; »Ú‡˜Ë
	JE[Special_MP_Itachi]
	CMP DWORD PTR DS:[ECX+6F4h],9 ; “Ó·Ë
	JE[Special_MP_Tobi]
	JMP [Special_MP_no_regen]
	
Special_MP_Itachi:
	MOV ECX, DWORD PTR DS:[ESI+198h]
	MOV EDX, DWORD PTR DS:[ECX+14h]
	CMP DWORD PTR DS:[ECX+10h],EDX
	JGE [Special_MP_no_regen]
	ADD DWORD PTR DS:[ECX+10h],1
	JMP [Special_MP_no_regen]	
	
Special_MP_Tobi:
	MOV ECX, DWORD PTR DS:[ESI+198h]
	MOV EDX, DWORD PTR DS:[ECX+14h]
	CMP DWORD PTR DS:[ECX+10h],EDX
	JGE [Special_MP_no_regen]
	CMP DWORD PTR DS:[ECX+8Ch], 0h
	JG [Special_MP_no_regen]
	ADD DWORD PTR DS:[ECX+10h],4
	CMP DWORD PTR DS:[ECX+10h],EDX
	JL[Special_MP_no_regen]
	MOV DWORD PTR DS:[ECX+10h],EDX
	JMP [Special_MP_no_regen]
	
Special_MP_no_regen:
	POP EDX
	POP ECX
	JMP [Amaterasu_effect]



Amaterasu_effect:
	PUSH ECX
	PUSH EDX
	PUSH EAX
	PUSH EBX
	
	MOV ECX, DWORD PTR DS:[ESI+198h]
	CMP DWORD PTR DS:[ECX+4h],0h
	JE [Amaterasu_skip]
	MOV EAX, DWORD PTR DS:[ECX+4h]
	SUB EAX, 100000
	MOV ECX, 1000
	XOR EDX, EDX
	DIV ECX
	CMP EDX, 0h
	JLE [Amaterasu_endtimer]
	CMP DWORD PTR DS:[ESI+2FCh],0
	JLE [Amaterasu_endtimer]
	SUB EDX,1
	SUB DWORD PTR DS:[ESI+2FCh],EAX
	ADD DWORD PTR DS:[ESI+34Ch],EAX
	ADD DWORD PTR DS:[ESI+34Ch],EAX
	MOV ECX,DWORD PTR DS:[ESI+198h]
	MOV EBX,DWORD PTR DS:[ECX+24h]
	ADD DWORD PTR DS:[EBX+348h],EAX
	ADD DWORD PTR DS:[EBX+348h],EAX
	MOV ECX,EAX
	IMUL ECX, 1000
	ADD ECX, EDX
	ADD ECX, 100000
	MOV EDX, DWORD PTR DS:[ESI+198h]
	MOV DWORD PTR DS:[EDX+4h],ECX
	XOR EDX, EDX
	MOV ECX, 2
	DIV ECX
	SUB DWORD PTR DS:[ESI+300h],EAX
	invoke Opoint_Maker,331,0,-30,0,15,21,5,15,350,0,10,0,0,ESI
	CMP DWORD PTR DS:[ESI+2FCh],0
	JG [Amaterasu_skip]
	CMP DWORD PTR DS:[ESI+344h],0
	JNE [Amaterasu_endtimer]
	MOV EAX, DWORD PTR DS:[ESI+368h]
	CMP DWORD PTR DS:[EAX+6F8h],0
	JNE [Amaterasu_skip]
	MOV DWORD PTR DS:[ESI+70h],180
	MOV ECX,DWORD PTR DS:[ESI+198h]
	MOV ECX,DWORD PTR DS:[ECX+24h]
	ADD DWORD PTR DS:[ECX+358h],1
	MOV DWORD PTR DS:[ESI+344h],1
	JMP[Amaterasu_endtimer]
	
Amaterasu_endtimer:
	MOV ECX, DWORD PTR DS:[ESI+198h]
	MOV DWORD PTR DS:[ECX+4h], 0h
	JMP [Amaterasu_skip]
	
Amaterasu_skip:
	POP EBX
	POP EAX
	POP EDX
	POP ECX
	JMP[back_to_standart]


back_to_standart:
	POP EAX
	POP EDX
	POP ECX
	
	CMP DWORD PTR DS:[ECX+6F8h],0
	JNZ [t0_fix]
	
	MOV EDX,DWORD PTR DS:[450BD0h]
	MOV ECX,DWORD PTR DS:[ESI+2FCh]
	JMP[every_back]

t0_fix:
	JMP[every_tick_t0]
every_tick endp