.data
Loading_sparks_ret 			dd 0043C06Ch
Sparki_MAlloc_ret 			dd 0040243Ch
Sparki_creation_orig_ret 	dd 00430A0Ah
Sparki_creation_ret 		dd 00430A50h
Sparks_drawing_ret 			dd 0041A995h
Sparks_drawing_function 	dd 0043F010h
Sparks_random_1_ret 		dd 004309B1h
Sparks_random_2_ret 		dd 004309FDh

;Strings:
spark_config_file_str 	db "sparks.dat",0
quadro_d 				db "%d %d %d %d",0
spark_itr_tag 			dd 00447E3Ch
num_seven 				db 07h
sparks_zaglushka		dd 28F883h
Sparks_Triple_NOP 		dd 909090h

spark_tag_str 		db "<spark>",0
spark_str			db "spark:",0

sprite_str			db "sprite:",0
amount_str			db "amount:",0
grid_str			db "grid:",0
wait_str			db "wait:",0
speed_str			db "speed:",0

sprite_d_str		db "sprite_d:",0
amount_d_str		db "amount_d:",0
grid_d_str			db "grid_d:",0
wait_d_str			db "wait_d:",0
speed_d_str			db "speed_d:",0

sprite_bd_str		db "sprite_bd:",0
amount_bd_str		db "amount_bd:",0
grid_bd_str			db "grid_bd:",0
wait_bd_str			db "wait_bd:",0
speed_bd_str		db "speed_bd:",0

spark_end_tag_str	db "<spark_end>",0

;------------------------------
;-----------Vars---------------
;------------------------------
TU_game 			dd 45
Sparks_total_cap 	dd 20
;------------------------------
;------------------------------

spark_addr 			dd 0h
spark_need_mem 		dd 64h

.data?
Sparks_temp_path 	db 064h dup(?)


.code

;������� �������� ���� � �  ++++++���

Sparks_random_2 proc
	ADD ESP,8
    MOV EDX,DWORD PTR SS:[ESP+14h]
    MOV EDX,DWORD PTR DS:[EDX+10h]
    SHR EDX,2
    ADD DWORD PTR SS:[ESP],EDX
    MOV EDX,EAX
    SHR EAX,3
    TEST EDX,1
    JZ [s2nd_option]
    NEG EAX
s2nd_option:
    ;ADD DWORD PTR SS:[ESP],EAX
    JMP [Sparks_random_2_ret]
Sparks_random_2 endp
Sparks_random_1 proc
	ADD ESP,8
    MOV ECX,DWORD PTR DS:[00458B00h] 
    MOV EDX,DWORD PTR SS:[EBP-4]
    MOV EDX,DWORD PTR DS:[ECX+EDX*4+3ECh]
    MOV ECX,DWORD PTR DS:[EDX+10h]
    MOV DWORD PTR SS:[ESP],ECX

    AND EAX,15
    CMP DWORD PTR DS:[EDX+80h],0
    JZ [skipper54779863567896]
    NEG EAX
    ADD EAX,7
    JMP [skipperhdfhsdh]
skipper54779863567896:

    SUB EAX,7
skipperhdfhsdh:
    ADD DWORD PTR SS:[ESP],EAX
    JMP [Sparks_random_1_ret]
Sparks_random_1 endp

Sparks_drawing proc ;EDI EAX ECX EBX
	
	MOV EBX,DWORD PTR DS:[ESI+184h]
	
	XOR EDI,EDI
	
cycle1:
	CMP DWORD PTR DS:[EBX],0
	JNZ [give_it_a_try]
cycle_inc:
	ADD EBX,4h
	INC EDI
	CMP EDI,Sparks_total_cap
	JGE [exit]
	JMP [cycle1]
	
give_it_a_try:
	PUSH EBP
	PUSH EDX
	PUSH ESI
	PUSH EDI
	MOV EAX,DWORD PTR DS:[EBX]
	MOV EDX,spark_addr
	XOR ECX,ECX
cycle2:
	CMP DWORD PTR DS:[EDX+ECX*4],0
	JZ [cycle2_skip]
	MOV ESI,DWORD PTR DS:[EDX+ECX*4]
	CMP DWORD PTR DS:[ESI],EAX
	JZ [cycle2_found]
cycle2_skip:
	INC ECX
	CMP ECX,Sparks_total_cap
	JL [cycle2]
	POP EDI
	POP ESI
	POP EDX
	POP EBP
	JMP [cycle_inc]
	
cycle2_found:
;ESI = spark_attributes pointer
	MOV EDX,Sparks_total_cap
	IMUL ECX,EDX,20
	
	SAL EDX,2
	MOV EDI,DWORD PTR DS:[EBX+ECX]
	PUSH EDI
	IMUL EDI,EDI,20h
	
	PUSH EDX
	CMP DWORD PTR DS:[ESI+EDI+4h],0
	JNZ [skip44]
	XOR EDI,EDI
skip44:
	
	MOV ECX,DWORD PTR SS:[EBP+14h]
	PUSH ECX
	PUSH 0
	PUSH 1
	MOV EAX,DWORD PTR DS:[EBX+EDX]
	PUSH EAX
	
	;IMUL ECX,EDI,18h
	MOV EAX,DWORD PTR DS:[ESI+EDI+18h]
	SHR EAX,1
	NEG EAX
	ADD EAX,DWORD PTR DS:[EBX+EDX*4]
	ADD EAX,cam_y_coord_current
	PUSH EAX
	
	;IMUL ECX,EDI,14h
	MOV EAX,DWORD PTR DS:[ESI+EDI+14h]
	SHR EAX,1
	NEG EAX
	LEA ECX,DWORD PTR DS:[EDX*2+EDX]
	ADD EAX,DWORD PTR DS:[EBX+ECX]
	SUB EAX,DWORD PTR DS:[450BC4h]
	PUSH EAX
	
	MOV ECX,DWORD PTR DS:[ESI+EDI+4h]
	CALL [Sparks_drawing_function]
	
	POP EDX
	POP EDI
	CMP DWORD PTR DS:[0044FB60h],0
	JNZ [cycle1_ret]
	
	;IMUL EDI,EDI,20h
	INC DWORD PTR DS:[EBX+EDX*2]
	IMUL ECX,EDI,20h
	MOV EAX,DWORD PTR DS:[ESI+ECX+1Ch]
	CMP DWORD PTR DS:[EBX+EDX*2],EAX
	JL [cycle1_ret]
	MOV DWORD PTR DS:[EBX+EDX*2],0
	INC DWORD PTR DS:[EBX+EDX]
	MOV EAX,DWORD PTR DS:[ESI+ECX+8h]
	CMP DWORD PTR DS:[EBX+EDX],EAX
	JL [cycle1_ret]
	MOV DWORD PTR DS:[EBX+EDX],0
	MOV DWORD PTR DS:[EBX],0
cycle1_ret:
	POP EDI
	POP ESI
	POP EDX
	POP EBP
	JMP [cycle_inc]
	
exit:
	
back:
	MOV EBX,ESI
	MOV EAX,DWORD PTR DS:[ESI+36Ch]
	TEST EAX,EAX
	JMP [Sparks_drawing_ret]
Sparks_drawing endp

Sparki_creation proc
	ADD EAX,36Ch
;ECX. ESP+10 = itr
	MOV ECX,DWORD PTR SS:[ESP+10h]
	CMP DWORD PTR DS:[ECX+68h],0
	JNZ [skip1]
	JMP [Sparki_creation_orig_ret]
skip1:
	
	PUSH EAX
	PUSH EBX
	PUSH EDX
	PUSH EDI
	PUSH ESI
	PUSH EBP
	
	PUSH ECX
	PUSH EDX
	PUSH EDI
	PUSH DWORD PTR SS:[ESP+38h]
	;PUSH EDI
	
	MOV EAX,DWORD PTR DS:[ECX+68h]
	MOV EBX,spark_addr
	XOR ECX,ECX
cycle1:
	CMP DWORD PTR DS:[EBX+ECX*4],0
	JZ [cycle1_skip]
	MOV ESI,DWORD PTR DS:[EBX+ECX*4]
	CMP DWORD PTR DS:[ESI],EAX
	JZ [cycle1_found]
	
cycle1_skip:
	INC ECX
	CMP ECX,Sparks_total_cap
	JL [cycle1]
;the needed spark doesn't exist 
	ADD ESP,10h
	POP EBP
	POP ESI
	POP EDI
	POP EDX
	POP EBX
	POP EAX
	JMP [Sparki_creation_orig_ret]
;! Found
cycle1_found:
	POP EDI
	POP ESI
	MOV EDI,DWORD PTR DS:[EDI+184h]
	XOR ECX,ECX
cycle2:
	CMP DWORD PTR DS:[EDI],0
	JZ [cycle2_end]
	INC ECX
	CMP ECX,Sparks_total_cap
	JGE [back2]
	ADD EDI,4
	JMP [cycle2]
cycle2_end:
	MOV DWORD PTR DS:[EDI],EAX ;� ������
	MOV ECX,Sparks_total_cap
	MOV DWORD PTR DS:[EDI+ECX*4],0 ;� �������
	MOV DWORD PTR DS:[EDI+ECX*8],0 ;����
	POP EDX
	LEA EDI,DWORD PTR DS:[EDI+ECX*8]
	MOV DWORD PTR DS:[EDI+ECX*8],EDX ;y
	;POP EAX ;itr
	ADD ESP,4
	MOV EDX,DWORD PTR SS:[ESP+18h]
	MOV DWORD PTR DS:[EDI+ECX*4],EDX ;x
	LEA EDI,DWORD PTR DS:[EDI+ECX*8]
	
	MOV EAX,DWORD PTR DS:[ESI+70h]
	IMUL EAX,1B0h
	MOV ESI,DWORD PTR DS:[ESI+368h]
	CMP DWORD PTR DS:[ESI+EAX+838h],7
	JNZ [skip33]
	MOV DWORD PTR DS:[EDI+ECX*4],1
skip33:
	CMP DWORD PTR DS:[ESI+EAX+838h],8
	JNZ [back3]
	MOV DWORD PTR DS:[EDI+ECX*4],2
	
	JMP [back3]
	
back2:
	ADD ESP,8
back3:
	POP EBP
	POP ESI
	POP EDI
	POP EDX
	POP EBX
	POP EAX
	ADD ESP,4
back:
	JMP [Sparki_creation_ret]
Sparki_creation endp

Sparki_MAlloc proc
	FLDZ
	FST QWORD PTR DS:[ESI+68h]
	
	CMP DWORD PTR DS:[ESI+184h],0
	JNZ [back]
	
	PUSHAD
	
	MOV EAX,Sparks_total_cap
	IMUL EAX,24
	
	PUSH EAX
	PUSH EAX
	CALL DWORD PTR DS:[447194h]
	ADD ESP,4h
	MOV DWORD PTR DS:[ESI+184h],EAX
	POP ECX
	MOV EDI,EAX
	XOR EAX,EAX
	REP STOS BYTE PTR ES:[EDI]
	
	
	
	
	POPAD
back:
	JMP [Sparki_MAlloc_ret]
Sparki_MAlloc endp

Sparks_Load_One_Pic proc
;adr str_pntr return esi ebx 
	PUSH ESI
	PUSH EBX
	MOV ESI,0043EE30h
	MOV ECX,DWORD PTR SS:[ESP+0Ch]	;������
	PUSH 0
	PUSH 0
	PUSH ECX
	CALL ESI
	POP EAX
	MOV EBX,DWORD PTR SS:[ESP+10h]	;����� ��� ������
	MOV DWORD PTR DS:[EBX],EAX
	POP EBX
	POP ESI	
	ret 8h
Sparks_Load_One_Pic endp

Sparks_filler proc
	;+0 ret. +4 sprite
	
	PUSH EAX
	PUSH EBX
	PUSH ECX
	PUSH EDX
	PUSH EDI
	PUSH ESI
	PUSH EBP
	
	MOV EBX,DWORD PTR SS:[ESP+24h]
	MOV ECX,DWORD PTR DS:[EBX+8h]
	MOV EDI,DWORD PTR DS:[ESP+20h]
	MOV DWORD PTR DS:[EDI+0Ch],ECX
	
	ADD EDI,10h
	PUSH ECX
	MOV ECX,DWORD PTR DS:[EBX+0Ch]
	PUSH ECX
	MOV ESI,DWORD PTR DS:[EBX+14h]
	MOV EBP,DWORD PTR DS:[EBX+18h]
	XOR EAX,EAX
	XOR EDX,EDX
	
filler_cycle:
	
	MOV DWORD PTR DS:[EDI],EAX
	MOV DWORD PTR DS:[EDI+7D0h],EDX
	MOV DWORD PTR DS:[EDI+0FA0h],ESI
	MOV DWORD PTR DS:[EDI+1770h],EBP
	
	LEA EAX,DWORD PTR DS:[EAX+ESI+1]
	ADD EDI,4
	
	DEC DWORD PTR SS:[ESP+4h]
	JLE [filler_ender]
	
	DEC ECX
	JG [filler_cycle]
	MOV ECX,DWORD PTR DS:[EBX+0Ch]
	XOR EAX,EAX
	LEA EDX,DWORD PTR DS:[EDX+EBP+1]
	JMP [filler_cycle]

filler_ender:
	ADD ESP,8
exit:
	POP EBP
	POP ESI
	POP EDI
	POP EDX
	POP ECX
	POP EBX
	POP EAX
	
	ret 8

Sparks_filler endp

Loading_sparks proc
	MOV DWORD PTR SS:[ESP+24h],EAX
	MOV DWORD PTR SS:[ESP+28h],EAX

;+0			+4 			
;current 	cur_addr 	

	PUSHAD
	
	SUB ESP,40h
	MOV DWORD PTR SS:[ESP],0
	
	MOV EAX,Sparks_total_cap
	IMUL EAX,4
	PUSH EAX
	PUSH EAX
	CALL DWORD PTR DS:[447194h]
	ADD ESP,4h
	MOV spark_addr,EAX
	MOV EDI,EAX
	XOR EAX,EAX
	POP ECX
	REP STOS BYTE PTR ES:[EDI]
	
	
	LEA EAX,spark_config_file_str
	PUSH EAX
	CALL DWORD PTR DS:[4143D0h]               ; \Neora.004143E0
	TEST EAX,EAX
	JE [back]
	MOV EBX,EAX
	
	
BIG_cycle:
	PUSH OFFSET [Sparks_temp_path]
	PUSH 004477FCh                     ;  ASCII "%s"
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]              ;  Neora.00414490
	ADD ESP,0Ch
	
	LEA EDI,spark_tag_str
	LEA ESI,Sparks_temp_path
	MOV ECX,8h
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [BIG_end]
	MOV ECX,Sparks_total_cap
	CMP DWORD PTR SS:[ESP],ECX
	JGE [BIG_end]
	
	
	MOV ECX,DWORD PTR SS:[ESP]
	MOV EAX,spark_addr
	LEA ECX,DWORD PTR DS:[EAX+ECX*4]
	PUSH ECX
	PUSH spark_need_mem
	CALL DWORD PTR DS:[447194h]
	ADD ESP,4h
	POP ECX
	MOV DWORD PTR DS:[ECX],EAX
	MOV DWORD PTR SS:[ESP+4h],EAX
	MOV ECX,spark_need_mem
	MOV EDI,EAX
	XOR EAX,EAX
	REP STOS BYTE PTR ES:[EDI]
	
spark_cycle:
	PUSH OFFSET [Sparks_temp_path]
	PUSH 004477FCh                     ;  ASCII "%s"
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]              ;  Neora.00414490
	ADD ESP,0Ch
	
	LEA EDI,spark_str
	LEA ESI,Sparks_temp_path
	MOV ECX,07h
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [sprite]
	
	MOV EAX,DWORD PTR SS:[ESP+4h]
	;ADD EAX,20h
	PUSH EAX
	PUSH 00447B08h                    ;  ASCII "%d"
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]             ;  Neora.00414490
	ADD ESP,0Ch
	JMP [spark_cycle]
	
sprite:
	LEA EDI,sprite_str
	LEA ESI,Sparks_temp_path
	MOV ECX,07h
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [amount]
	
	PUSH OFFSET [Sparks_temp_path]
	PUSH 004477FCh                     ;  ASCII "%s"
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]             ;  Neora.00414490'
	ADD ESP,0Ch
	
	MOV EAX,DWORD PTR SS:[ESP+4h]
	ADD EAX,4h
	PUSH EAX
	PUSH OFFSET [Sparks_temp_path]
	CALL [Sparks_Load_One_Pic]
	JMP [spark_cycle]
	
amount:
	LEA EDI,amount_str
	LEA ESI,Sparks_temp_path
	MOV ECX,07h
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [grid]
	
	MOV EAX,DWORD PTR SS:[ESP+4h]
	ADD EAX,8h
	PUSH EAX
	PUSH 00447B08h                    ;  ASCII "%d"
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]             ;  Neora.00414490
	ADD ESP,0Ch
	JMP [spark_cycle]
	
grid:
	LEA EDI,grid_str
	LEA ESI,Sparks_temp_path
	MOV ECX,05h
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [wait_s]
	
	MOV EAX,DWORD PTR SS:[ESP+4h]
	ADD EAX,18h
	PUSH EAX
	SUB EAX,4
	PUSH EAX
	SUB EAX,4
	PUSH EAX
	SUB EAX,4
	PUSH EAX
	PUSH OFFSET [quadro_d]
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]             ;  Neora.00414490
	ADD ESP,18h
	JMP [spark_cycle]
	
wait_s:
	LEA EDI,wait_str
	LEA ESI,Sparks_temp_path
	MOV ECX,05h
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [speed]
	
	MOV EAX,DWORD PTR SS:[ESP+4h]
	ADD EAX,1Ch
	PUSH EAX
	PUSH 00447B08h                    ;  ASCII "%d"
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]             ;  Neora.00414490
	ADD ESP,0Ch
	JMP [spark_cycle]
	
speed:
	LEA EDI,speed_str
	LEA ESI,Sparks_temp_path
	MOV ECX,06h
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [sprite_d]
	
	MOV EAX,DWORD PTR SS:[ESP+4h]
	ADD EAX,20h
	PUSH EAX
	PUSH 004476ECh                      ;  ASCII "%f"
	;PUSH 00447B08h                    ;  ASCII "%d"
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]             ;  Neora.00414490
	ADD ESP,0Ch
	JMP [spark_cycle]
	
sprite_d:
	LEA EDI,sprite_d_str
	LEA ESI,Sparks_temp_path
	MOV ECX,0Ah
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [amount_d]
	
	PUSH OFFSET [Sparks_temp_path]
	PUSH 004477FCh                     ;  ASCII "%s"
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]             ;  Neora.00414490'
	ADD ESP,0Ch
	
	MOV EAX,DWORD PTR SS:[ESP+4h]
	ADD EAX,24h
	PUSH EAX
	PUSH OFFSET [Sparks_temp_path]
	CALL [Sparks_Load_One_Pic]
	JMP [spark_cycle]
	
amount_d:
	LEA EDI,amount_d_str
	LEA ESI,Sparks_temp_path
	MOV ECX,0Ah
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [grid_d]
	
	MOV EAX,DWORD PTR SS:[ESP+4h]
	ADD EAX,28h
	PUSH EAX
	PUSH 00447B08h                    ;  ASCII "%d"
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]             ;  Neora.00414490
	ADD ESP,0Ch
	JMP [spark_cycle]
	
grid_d:
	LEA EDI,grid_d_str
	LEA ESI,Sparks_temp_path
	MOV ECX,08h
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [wait_s_d]
	
	MOV EAX,DWORD PTR SS:[ESP+4h]
	ADD EAX,38h
	PUSH EAX
	SUB EAX,4
	PUSH EAX
	SUB EAX,4
	PUSH EAX
	SUB EAX,4
	PUSH EAX
	PUSH OFFSET [quadro_d]
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]             ;  Neora.00414490
	ADD ESP,18h
	JMP [spark_cycle]
	
wait_s_d:
	LEA EDI,wait_d_str
	LEA ESI,Sparks_temp_path
	MOV ECX,08h
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [speed_d]
	
	MOV EAX,DWORD PTR SS:[ESP+4h]
	ADD EAX,3Ch
	PUSH EAX
	PUSH 00447B08h                    ;  ASCII "%d"
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]             ;  Neora.00414490
	ADD ESP,0Ch
	JMP [spark_cycle]
	
speed_d:
	LEA EDI,speed_d_str
	LEA ESI,Sparks_temp_path
	MOV ECX,09h
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [sprite_bd]
	
	MOV EAX,DWORD PTR SS:[ESP+4h]
	ADD EAX,40h
	PUSH EAX
	PUSH 004476ECh                      ;  ASCII "%f"
	;PUSH 00447B08h                    ;  ASCII "%d"
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]             ;  Neora.00414490
	ADD ESP,0Ch
	JMP [spark_cycle]
	
sprite_bd:
	LEA EDI,sprite_bd_str
	LEA ESI,Sparks_temp_path
	MOV ECX,0Bh
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [amount_bd]
	
	PUSH OFFSET [Sparks_temp_path]
	PUSH 004477FCh                     ;  ASCII "%s"
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]             ;  Neora.00414490'
	ADD ESP,0Ch
	
	MOV EAX,DWORD PTR SS:[ESP+4h]
	ADD EAX,44h
	PUSH EAX
	PUSH OFFSET [Sparks_temp_path]
	CALL [Sparks_Load_One_Pic]
	JMP [spark_cycle]
	
amount_bd:
	LEA EDI,amount_bd_str
	LEA ESI,Sparks_temp_path
	MOV ECX,0Bh
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [grid_bd]
	
	MOV EAX,DWORD PTR SS:[ESP+4h]
	ADD EAX,48h
	PUSH EAX
	PUSH 00447B08h                    ;  ASCII "%d"
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]             ;  Neora.00414490
	ADD ESP,0Ch
	JMP [spark_cycle]
	
grid_bd:
	LEA EDI,grid_bd_str
	LEA ESI,Sparks_temp_path
	MOV ECX,09h
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [wait_s_bd]
	
	MOV EAX,DWORD PTR SS:[ESP+4h]
	ADD EAX,58h
	PUSH EAX
	SUB EAX,4
	PUSH EAX
	SUB EAX,4
	PUSH EAX
	SUB EAX,4
	PUSH EAX
	PUSH OFFSET [quadro_d]
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]             ;  Neora.00414490
	ADD ESP,18h
	JMP [spark_cycle]
	
wait_s_bd:
	LEA EDI,wait_bd_str
	LEA ESI,Sparks_temp_path
	MOV ECX,09h
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [speed_bd]
	
	MOV EAX,DWORD PTR SS:[ESP+4h]
	ADD EAX,5Ch
	PUSH EAX
	PUSH 00447B08h                    ;  ASCII "%d"
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]             ;  Neora.00414490
	ADD ESP,0Ch
	JMP [spark_cycle]
	
speed_bd:
	LEA EDI,speed_bd_str
	LEA ESI,Sparks_temp_path
	MOV ECX,0Ah
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [spark_end]
	
	MOV EAX,DWORD PTR SS:[ESP+4h]
	ADD EAX,60h
	PUSH EAX
	PUSH 004476ECh                      ;  ASCII "%f"
	;PUSH 00447B08h                    ;  ASCII "%d"
	PUSH EBX
	CALL DWORD PTR DS:[4143D4h]             ;  Neora.00414490
	ADD ESP,0Ch
	JMP [spark_cycle]

	
spark_end:
	LEA EDI,spark_end_tag_str
	LEA ESI,Sparks_temp_path
	MOV ECX,0Ch
	REPE CMPS BYTE PTR ES:[EDI],BYTE PTR ES:[ESI]
	JNZ [spark_cycle]
	INC DWORD PTR SS:[ESP]
;����� ��� ������ ���� �����... �����.
	
	
	
BIG_end:
	;JMP [back]
	PUSH EBX
	CALL DWORD PTR DS:[4143D8h]             ;  Neora.00414930
	;ADD ESP,4
	TEST EAX,EAX
	JE [BIG_cycle]
;sparks_lf_temp
filler_start:
	;MOV ECX,Sparks_total_cap
	XOR ECX,ECX
	MOV EDI,spark_addr
filler_cycle:
	;LEA EDX,DWORD PTR DS:[ECX*4]
	MOV ESI,DWORD PTR DS:[EDI+ECX*4]
	PUSH ESI
	TEST ESI,ESI
	JZ [filler_skip]
	
	CMP DWORD PTR DS:[ESI+4h],0
	JZ [filler_skip]
	MOV EAX, DWORD PTR DS:[ESI+4h]
	PUSH ESI
	PUSH EAX
	CALL [Sparks_filler]
; speed->wait calculation
	CMP DWORD PTR DS:[ESI+20h],0
	JZ [speed_wait_skip1]
	FLD DWORD PTR DS:[ESI+20h]
	FIMUL TU_game
	FIDIV DWORD PTR DS:[ESI+8h]
	FISTP DWORD PTR DS:[ESI+1Ch]
	
speed_wait_skip1:
	MOV ESI,DWORD PTR SS:[ESP]
	CMP DWORD PTR DS:[ESI+24h],0
	JE [filler_skip2]
	MOV EAX, DWORD PTR DS:[ESI+24h]
	PUSH ESI
	PUSH EAX
	CALL [Sparks_filler]
; speed->wait calculation
	CMP DWORD PTR DS:[ESI+40h],0
	JZ [filler_skip2]
	FLD DWORD PTR DS:[ESI+40h]
	FIMUL TU_game
	FIDIV DWORD PTR DS:[ESI+28h]
	FISTP DWORD PTR DS:[ESI+3Ch]
	
filler_skip2:	
	CMP DWORD PTR DS:[ESI+44h],0
	JE [filler_skip]
	MOV EAX, DWORD PTR DS:[ESI+44h]
	PUSH ESI
	PUSH EAX
	CALL [Sparks_filler]
; speed->wait calculation
	CMP DWORD PTR DS:[ESI+60h],0
	JZ [filler_skip]
	FLD DWORD PTR DS:[ESI+60h]
	FIMUL TU_game
	FIDIV DWORD PTR DS:[ESI+48h]
	FISTP DWORD PTR DS:[ESI+5Ch]
	
filler_skip:
	ADD ESP,4
	
	INC ECX
	CMP ECX,Sparks_total_cap
	JNZ [filler_cycle]
	
back:
	ADD ESP,40h
	POPAD
	JMP [Loading_sparks_ret]

Loading_sparks endp