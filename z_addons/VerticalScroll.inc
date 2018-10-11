.data
blood_scrolling_ret dd 0041AA0Dh
shadow_scrolling_ret dd 0041A74Ch
vert_back	 	dd 0040BDEBh
bg_scrl_ret dd 0041A18Dh
bg_scrl2_ret dd 0041A260h
bg_scrl3_ret dd 0041A2E0h
bg_scrl4_ret dd 0041A92Bh
vertical_ret dd 0041BC65h
cam_coords_calc_ret dd 0041BA81h

cam_players 		db 0h
cam_y_coord_point 	dd 0h
cam_y_coord_current dd 0h
cam_y_coord_speed 	dd 0h

callf1 	dd 0040BE10h
callf2 	dd 0040BD50h
callf3 	dd 00401080h
BG_painting dd 0041A050h
vert_paint  dd 0043F010h

.code
;	z: 250
;	y: dynamic

blood_scrolling proc
	
	MOV ECX, DWORD PTR DS:[EBX+368h]
	CMP DWORD PTR DS:[ECX+6F4h],331
	JE[no_spark]
	
	MOV ECX,DWORD PTR SS:[EBP+14h]
	PUSH ECX
	PUSH 0
	PUSH 1
	PUSH EAX
	MOV EAX,DWORD PTR DS:[ESI-28h]
	SUB EAX,28h
	ADD EAX,cam_y_coord_current
	PUSH EAX
	MOV EDX,DWORD PTR DS:[ESI-50h]
	SUB EDX,32h
	SUB EDX,DWORD PTR DS:[450BC4h]
	PUSH EDX
	MOV ECX,DWORD PTR DS:[44F8FCh]
	CALL [vert_paint]
no_spark:
	JMP [blood_scrolling_ret]
blood_scrolling endp

shadow_scrolling proc ; рассчет отрисовки тени
	MOV EDX,DWORD PTR SS:[EBP+14h]
	PUSH EDX
	PUSH 0
	PUSH 1
	PUSH -1
	MOV EDX,DWORD PTR DS:[EAX+18h]
	SHR EDX,1
	NEG EDX
	
	MOV EDI, DWORD PTR DS:[ESI+368h]
	CMP DWORD PTR DS:[EDI+0B4h],1
	JE[shadow_small]
	
	ADD EDX,DWORD PTR DS:[ESI+18h]
	ADD EDX,DWORD PTR DS:[ESI+10Ch]
	ADD EDX,cam_y_coord_current
	PUSH EDX
	MOV EDX,DWORD PTR DS:[ESI+10h]
	SUB EDX,ECX
	SUB EDX,DWORD PTR DS:[450BC4h]
	PUSH EDX
	MOV ECX,DWORD PTR DS:[EAX+1EE0h]
	CALL [vert_paint]
	JMP [shadow_scrolling_ret]
	
shadow_small:
	ADD EDX,DWORD PTR DS:[ESI+18h]
	ADD EDX, 8
	ADD EDX,DWORD PTR DS:[ESI+10Ch]
	ADD EDX,cam_y_coord_current
	PUSH EDX
	MOV EDX,DWORD PTR DS:[ESI+10h]
	ADD EDX, 12
	SUB EDX,ECX
	SUB EDX,DWORD PTR DS:[450BC4h]
	PUSH EDX
	MOV ECX,DWORD PTR DS:[small_shadow_addr]
	CALL [vert_paint]
	JMP [shadow_scrolling_ret]

shadow_scrolling endp

vertic proc	; рассчет отрисовки объектов с учетом камеры
	PUSH ESI
	PUSH EDI
	PUSH 1
	PUSH EAX
	
	MOV EDI, DWORD PTR SS:[ESP+18h]
	MOV EDI, DWORD PTR DS:[EDI+198h]
	
	CMP DWORD PTR DS:[EDI+64h],0h
	JLE [opacity_change]
	
	MOV EAX, DWORD PTR DS:[EDI+64h]
	
	CMP DWORD PTR DS:[EDI+6Ch],EAX
	JL[opacity_up]
	CMP DWORD PTR DS:[EDI+6Ch],EAX
	JG[opacity_down]

	mov dword ptr ds:[edi+64h],0h
	
	JMP [opacity_change]
	
opacity_up:
	MOV EAX, DWORD PTR DS:[EDI+68h]
	ADD DWORD PTR DS:[EDI+6Ch],EAX
	
	MOV EAX, DWORD PTR DS:[EDI+64h]
	CMP DWORD PTR DS:[EDI+6Ch], EAX
	JL [opacity_change]
	
	MOV DWORD PTR DS:[EDI+6Ch], EAX
	JMP [opacity_change]
	
opacity_down:
	MOV EAX, DWORD PTR DS:[EDI+68h]
	SUB DWORD PTR DS:[EDI+6Ch],EAX
	
	MOV EAX, DWORD PTR DS:[EDI+64h]
	CMP DWORD PTR DS:[EDI+6Ch], EAX
	JG [opacity_change]
	
	MOV DWORD PTR DS:[EDI+6Ch],EAX
	JMP [opacity_change]
	
	
opacity_change:
	CMP DWORD PTR DS:[EDI+6Ch], 0
	JLE [ik100015_opacity_check]
	CMP DWORD PTR DS:[EDI+6Ch], 255
	JGE [ik100015_opacity_check]
	MOV EAX, DWORD PTR DS:[EDI+6Ch]
	MOV DWORD PTR SS:[ESP+8h],EAX
	
ik100015_opacity_check:
	CMP DWORD PTR DS:[EDI+8Ch], 0
	JNG [no_opacity_change]
	SUB DWORD PTR SS:[ESP+8h],55
	
no_opacity_change:
	MOV EAX, DWORD PTR SS:[ESP+28h]
	ADD EAX, cam_y_coord_current
	ADD EAX, DWORD PTR DS:[EDI+60h]
	PUSH EAX
	MOV EAX,DWORD PTR SS:[ESP+28h]
	PUSH EAX
	

	
	JMP [vert_back]
	
vertic endp

bg_scrolling proc ; тут все очевидно
	MOV EDX,DWORD PTR DS:[ECX+ESI*4+10D0h]
	ADD EDX,DWORD PTR DS:[4529D8h]
	ADD EDX,cam_y_coord_current
	PUSH EDX
	MOV EDX,DWORD PTR DS:[ECX+ESI*4+0F40h]
	ADD EDX,EAX
	ADD EDX,DWORD PTR DS:[4529D4h]
	MOV ECX,DWORD PTR DS:[ECX+ESI*4+1D50h]
	PUSH EDX
	JMP [bg_scrl_ret]
bg_scrolling endp

bg_scrolling2 proc
	ADD EDX,DWORD PTR DS:[4529D8h]
	ADD EDX,cam_y_coord_current
	PUSH EDX
	MOV ECX,DWORD PTR DS:[EAX+1130h]
	MOV EAX,DWORD PTR SS:[ESP+2Ch]
	ADD EAX,EDI
	ADD EAX,DWORD PTR DS:[4529D4h]
	PUSH EAX
JMP [bg_scrl2_ret]
bg_scrolling2 endp

bg_scrolling3 proc
	ADD ECX,DWORD PTR DS:[4529D8h]
	ADD ECX,cam_y_coord_current
	PUSH ECX
	JMP [bg_scrl3_ret]
bg_scrolling3 endp

bg_scrolling4 proc
	PUSH ECX
	ADD EDX,cam_y_coord_current
	PUSH EDX
	PUSH EDI
	XOR ECX,ECX

	JMP [bg_scrl4_ret]
bg_scrolling4 endp

cam_coords_calc proc
	MOV cam_y_coord_point,0
	MOV cam_y_coord_current,0
	MOV cam_y_coord_speed,0
	MOV cam_players,0
		
;взял стандартный код подсчета координат по x. 
point11:
	CMP BYTE PTR DS:[ESI-1],0 ; есть ли такой игрок (слоты объектов 0-9, а точнее 0-7, ибо по 8 и 9 тут не пробегается)
	JE  [point21]
	CMP DWORD PTR DS:[EDI-4h],0 ; на этом ли компе этот игрок. не разобрался еще что точно за флаги, но вот както так.
	JLE  [point21]
	MOV EDX,DWORD PTR DS:[EAX-4h]
	CMP DWORD PTR DS:[EDX+2FCh],0	
	JLE  SHORT [point21]
	
	; ниже была умная считалка с учетом z координаты, "глубины" карты по z и centery персонажа 
	MOV ECX,DWORD PTR DS:[EDX+18h]
	ADD ECX,DWORD PTR DS:[EDX+14h]
	PUSH EDX
	MOV EDX,DWORD PTR DS:[ESP]
	MOV EBP,DWORD PTR DS:[EDX+368h]
	MOV EDX,DWOrD PTR DS:[EDX+70h]
	IMUL EDX,1B0h
	SUB ECX,DWORD PTR DS:[EDX+EBP+884h]
	POP EDX
	SUB ECX,210
	ADD cam_y_coord_point,ECX
	INC cam_players
	
	;дальше опять кусок стандарта
	
	MOV ECX,EDX
	MOV EBP,DWORD PTR DS:[ECX+70h]
	MOV ECX,DWORD PTR DS:[ECX+368h]
	IMUL EBP,EBP,1B0h
	CMP DWORD PTR DS:[ECX+EBP+838h],0Eh
	JE SHORT [point12]
	MOV ECX,EDX
	MOVSX EDX,BYTE PTR DS:[ECX+80h]
	MOV ECX,DWORD PTR DS:[ECX+10h]
	IMUL EDX,EDX,104h
	SUB ECX,EDX
	LEA EBX,DWORD PTR DS:[EBX+ECX+82h]
	JMP SHORT [point13]
point12:
	ADD EBX,DWORD PTR DS:[EDX+10h]
point13:
	ADD DWORD PTR SS:[ESP+10h],1
	
point21: ; второй чар
	CMP BYTE PTR DS:[ESI],0
	JE [point31]
	CMP DWORD PTR DS:[EDI],0
	JLE [point31]
	MOV EDX,DWORD PTR DS:[EAX]
	CMP DWORD PTR DS:[EDX+2FCh],0
	JLE SHORT [point31]
	
	MOV ECX,DWORD PTR DS:[EDX+18h]
	ADD ECX,DWORD PTR DS:[EDX+14h]
	PUSH EDX
	MOV EDX,DWORD PTR DS:[ESP]
	MOV EBP,DWORD PTR DS:[EDX+368h]
	MOV EDX,DWOrD PTR DS:[EDX+70h]
	IMUL EDX,1B0h
	SUB ECX,DWORD PTR DS:[EDX+EBP+884h]
	POP EDX
	SUB ECX,210
	ADD cam_y_coord_point,ECX
	INC cam_players

	MOV ECX,EDX
	MOV EBP,DWORD PTR DS:[ECX+70h]
	MOV ECX,DWORD PTR DS:[ECX+368h]
	IMUL EBP,EBP,1B0h
	CMP DWORD PTR DS:[ECX+EBP+838h],0Eh
	JE SHORT [point22]
	MOV ECX,EDX
	MOVSX EDX,BYTE PTR DS:[ECX+80h]
	MOV ECX,DWORD PTR DS:[ECX+10h]
	IMUL EDX,EDX,104h
	SUB ECX,EDX
	LEA EBX,DWORD PTR DS:[EBX+ECX+82h]
	JMP SHORT [point23]
point22:
	ADD EBX,DWORD PTR DS:[EDX+10h]
point23:
	ADD DWORD PTR SS:[ESP+10h],1
	
point31: ; третий чар
	CMP BYTE PTR DS:[ESI+1],0
	JE [point41]
	CMP DWORD PTR DS:[EDI+4h],0
	JLE [point41]
	MOV EDX,DWORD PTR DS:[EAX+4h]
	CMP DWORD PTR DS:[EDX+2FCh],0
	JLE SHORT [point41]
	
	MOV ECX,DWORD PTR DS:[EDX+18h]
	ADD ECX,DWORD PTR DS:[EDX+14h]
	PUSH EDX
	MOV EDX,DWORD PTR DS:[ESP]
	MOV EBP,DWORD PTR DS:[EDX+368h]
	MOV EDX,DWOrD PTR DS:[EDX+70h]
	IMUL EDX,1B0h
	SUB ECX,DWORD PTR DS:[EDX+EBP+884h]
	POP EDX
	SUB ECX,210
	ADD cam_y_coord_point,ECX
	INC cam_players

	MOV ECX,EDX
	MOV EBP,DWORD PTR DS:[ECX+70h]
	MOV ECX,DWORD PTR DS:[ECX+368h]
	IMUL EBP,EBP,1B0h
	CMP DWORD PTR DS:[ECX+EBP+838h],0Eh
	JE SHORT [point32]
	MOV ECX,EDX
	MOVSX EDX,BYTE PTR DS:[ECX+80h]
	MOV ECX,DWORD PTR DS:[ECX+10h]
	IMUL EDX,EDX,104h
	SUB ECX,EDX
	LEA EBX,DWORD PTR DS:[EBX+ECX+82h]
	JMP SHORT [point33]
point32:
	ADD EBX,DWORD PTR DS:[EDX+10h]
point33:
	ADD DWORD PTR SS:[ESP+10h],1
	
point41: ; четвертый чар
	CMP BYTE PTR DS:[ESI+2],0
	JE [point51]
	CMP DWORD PTR DS:[EDI+8h],0
	JLE [point51]
	MOV EDX,DWORD PTR DS:[EAX+8h]
	CMP DWORD PTR DS:[EDX+2FCh],0
	JLE SHORT [point51]
	
	MOV ECX,DWORD PTR DS:[EDX+18h]
	ADD ECX,DWORD PTR DS:[EDX+14h]
	PUSH EDX
	MOV EDX,DWORD PTR DS:[ESP]
	MOV EBP,DWORD PTR DS:[EDX+368h]
	MOV EDX,DWOrD PTR DS:[EDX+70h]
	IMUL EDX,1B0h
	SUB ECX,DWORD PTR DS:[EDX+EBP+884h]
	POP EDX
	SUB ECX,210
	ADD cam_y_coord_point,ECX
	INC cam_players

	MOV ECX,EDX
	MOV EBP,DWORD PTR DS:[ECX+70h]
	MOV ECX,DWORD PTR DS:[ECX+368h]
	IMUL EBP,EBP,1B0h
	CMP DWORD PTR DS:[ECX+EBP+838h],0Eh
	JE SHORT [point42]
	MOV ECX,EDX
	MOVSX EDX,BYTE PTR DS:[ECX+80h]
	MOV ECX,DWORD PTR DS:[ECX+10h]
	IMUL EDX,EDX,104h
	SUB ECX,EDX
	LEA EBX,DWORD PTR DS:[EBX+ECX+82h]
	JMP SHORT [point43]
point42:
	ADD EBX,DWORD PTR DS:[EDX+10h]
point43:
	ADD DWORD PTR SS:[ESP+10h],1
	
point51:
	ADD ESI,4
	ADD EDI,10h
	ADD EAX,10h
	SUB DWORD PTR SS:[ESP+2Ch],1
	JNZ [point11]
	; тут оригинальный код окончился и я творю что хочу.

	
	MOVSX ECX,cam_players
skipper:
	TEST ECX,ECX
	JZ [exit]
	
skipper31:
	MOV EAX,cam_y_coord_point
	CDQ
	IDIV ECX
	; координата камеры - это просто среднее всех необходимых "камер" каждого игрока

	CMP EAX,0
	JLE [skipper32]
	XOR EAX,EAX ;если игра решила что камера должна уехать вниз - то предотвратить это.
skipper32:
	NEG EAX
	MOV cam_y_coord_point,EAX
	MOV cam_y_coord_current,EAX
skipper33:

skip47:
	
	
skip48:
	
exit:
	JMP [cam_coords_calc_ret]
	
	
	
cam_coords_calc endp

