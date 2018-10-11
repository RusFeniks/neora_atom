.data
write_pointer_to_char_back dd 00402447h

init_called_proc dd 00402400h
init_back1 dd 0042D6D8h
init_back2 dd 00427161h
init_back3 dd 0042410Fh
init_back4 dd 0042D432h
init_back5 dd 0041FDA1h
init_back6 dd 0042D320h
init_back7 dd 00420CD8h
init_back8 dd 00446506h
init_back9 dd 0041F14Dh
init_back10 dd 004375C8h



decimal db "%d", 00
float db "%f", 00
string db "%s", 00

wrong_data dd 0040F2EDh
next_bmp_atribute dd 0040F79Ch


weapon_hp_str db "weapon_hp:",00
shadow_type_str db "shadow_type:",00
start_hp_str db "start_hp:",00



wrong_frame dd 0041054Eh
next_frame dd 004106D0h


test_var_str db "test_var:",00
pointingx_speed_str db "pointing_speed_x:",00
pointingy_speed_str db "pointing_speed_y:",00
pointingz_speed_str db "pointing_speed_z:",00
pointingx_velocity_str db "pointing_velocity_x:",00
pointingz_velocity_str db "pointing_velocity_z:",00
pointing_height_str db "pointing_height:",00


.code



loading_dat_file proc

weapon_hp:
	LEA EDX,DWORD PTR SS:[EBP+90h]
	LEA EDI,[weapon_hp_str]
	LEA ESI,DWORD PTR SS:[ESP+70h]
	MOV ECX,11
	REPE CMPSB [EDI],[ESI]
	JNZ [shadow_t]
	JMP EAX
shadow_t:
        LEA EDX,DWORD PTR SS:[EBP+0B4h] 
        LEA EDI,[shadow_type_str]
        LEA ESI,DWORD PTR SS:[ESP+70h]
        MOV ECX,0Dh
        REPE CMPSB [EDI],[ESI]
        JNZ [f_bmp_atributes]
        JMP EAX

f_bmp_atributes:
	f_bmp_atributes_memory:
	MOV EAX, DWORD PTR DS:[EBP+0B8h]	; проверка на то что память уже выделена и поинтер записан
	CMP EAX, 0h
	JNE [f_bmp_atributes_memory_skip]
	
	;-------------------------------------------------------------------------------------------------
	;	выделение и очистка памяти
	;-------------------------------------------------------------------------------------------------
	MOV ECX, 200h					; сколько памяти надо выделить (ищет свободное место и делает дело)
	PUSH ECX							
	CALL DWORD PTR DS:[447194h] 		; mAlloc (вызов процедуры выделения памяти)
	POP ECX							; восстановление стека
	MOV DWORD PTR DS:[EBP+0B8h],EAX	; запись указателя на начало выделенной области
	
	f_bmp_atributes_memory_clear:		; очистка выделенной памяти от мусора
	DEC ECX
	MOV BYTE PTR DS:[EAX+ECX],0h
	CMP ECX, 0h
	JG [f_bmp_atributes_memory_clear]
	;-------------------------------------------------------------------------------------------------
	
	f_bmp_atributes_memory_skip:
	MOV EDX, EAX						; помещаем начало области памяти
	
	start_hp:
		LEA ESI,DWORD PTR SS:[ESP+70h]	; тут хранится обрабатываемая в данный момент строка
		LEA EDI, [start_hp_str]			; кладём в EDI строку, с которой будем сравнивать обрабатываемую строку
		MOV ECX, 10					; указываем размер сравниваемой строки +1 (на еденицу больше чем на самом деле)
		REPE CMPSB [EDI],[ESI]
		JNZ [loading_dat_file_wrong]
		ADD EDX, 0h					; смещение по выделенной памяти (листингу)
		JMP [f_bmp_write_decimal]

loading_dat_file_wrong:
	MOV EAX,0040F78Bh				; обязательное системное восстановление
	JMP [wrong_data]

f_bmp_write_decimal:
	LEA EAX,[decimal]
	PUSH EAX
	JMP [f_bmp_write_start]

f_bmp_write_start:
	POP ECX
	MOV EAX, DWORD PTR SS:[ESP+14h]
	PUSH EDX
	PUSH ECX
	PUSH EAX
	CALL EBX
	ADD ESP,0Ch
	JMP [next_bmp_atribute]

loading_dat_file endp

loading_frame proc

hit_da:
	LEA EDI,[hitDa_str] 
	LEA ESI,DWORD PTR SS:[ESP+70h] 
	MOV ECX,8h
	REPE CMPSB [EDI],[ESI]
	JNZ [level_obj]
	ADD EDX,38h
	JMP EAX
	
level_obj:
	LEA EDI,[level_str] 
	LEA ESI,DWORD PTR SS:[ESP+70h] 
	MOV ECX,7h 
	REPE CMPSB [EDI],[ESI]
	JNZ [var_frame]
	ADD EDX,104h
	JMP EAX
	
var_frame:
	LEA EDI,[var_str] 
	LEA ESI,DWORD PTR SS:[ESP+70h] 
	MOV ECX,4h 
	REPE CMPSB [EDI],[ESI]
	JNZ [f_loading_frame]
	ADD EDX, 108h
	JMP EAX
	
	
f_loading_frame:

	f_loading_frame_memory:
	MOV EAX, DWORD PTR DS:[EDX+110h]	; проверка на то что память уже выделена и поинтер записан
	CMP EAX, 0h
	JNE [f_loading_frame_memory_skip]
	
	;-------------------------------------------------------------------------------------------------
	;	выделение и очистка памяти
	;-------------------------------------------------------------------------------------------------
	PUSH EDX
	MOV ECX, 50h					; сколько памяти надо выделить (ищет свободное место и делает дело)
	PUSH ECX							
	CALL DWORD PTR DS:[447194h] 		; mAlloc (вызов процедуры выделения памяти)
	POP ECX							; восстановление стека
	POP EDX
	MOV DWORD PTR DS:[EDX+110h],EAX	; запись указателя на начало выделенной области
	
	f_loading_frame_memory_clear:		; очистка выделенной памяти от мусора
	DEC ECX
	MOV BYTE PTR DS:[EAX+ECX],0h
	CMP ECX, 0h
	JG [f_loading_frame_memory_clear]
	;-------------------------------------------------------------------------------------------------
	
	f_loading_frame_memory_skip:
	MOV EDX, EAX						; помещаем начало области памяти
	
	test_var:
		LEA ESI,DWORD PTR SS:[ESP+70h]	; тут хранится обрабатываемая в данный момент строка
		LEA EDI, [test_var_str]			; кладём в EDI строку, с которой будем сравнивать обрабатываемую строку
		MOV ECX, 10					; указываем размер сравниваемой строки +1 (на еденицу больше чем на самом деле)
		REPE CMPSB [EDI],[ESI]
		JNZ [pointingx_speed]
		ADD EDX, 0h					; смещение по выделенной памяти (листингу)
		JMP [f_frame_write_decimal]
	
	pointingx_speed:
		LEA ESI,DWORD PTR SS:[ESP+70h]	; тут хранится обрабатываемая в данный момент строка
		LEA EDI, [pointingx_speed_str]			; кладём в EDI строку, с которой будем сравнивать обрабатываемую строку
		MOV ECX, 18					; указываем размер сравниваемой строки +1 (на еденицу больше чем на самом деле)
		REPE CMPSB [EDI],[ESI]
		JNZ [pointingz_speed]
		ADD EDX, 4h					; смещение по выделенной памяти (листингу)
		JMP [f_frame_write_decimal]	
		
	pointingz_speed:
		LEA ESI,DWORD PTR SS:[ESP+70h]	; тут хранится обрабатываемая в данный момент строка
		LEA EDI, [pointingz_speed_str]			; кладём в EDI строку, с которой будем сравнивать обрабатываемую строку
		MOV ECX, 18					; указываем размер сравниваемой строки +1 (на еденицу больше чем на самом деле)
		REPE CMPSB [EDI],[ESI]
		JNZ [pointingx_velocity]
		ADD EDX, 8h					; смещение по выделенной памяти (листингу)
		JMP [f_frame_write_decimal]
		
	pointingx_velocity:
		LEA ESI,DWORD PTR SS:[ESP+70h]	; тут хранится обрабатываемая в данный момент строка
		LEA EDI, [pointingx_velocity_str]			; кладём в EDI строку, с которой будем сравнивать обрабатываемую строку
		MOV ECX, 21					; указываем размер сравниваемой строки +1 (на еденицу больше чем на самом деле)
		REPE CMPSB [EDI],[ESI]
		JNZ [pointingz_velocity]
		ADD EDX, 0Ch					; смещение по выделенной памяти (листингу)
		JMP [f_frame_write_decimal]
				
	pointingz_velocity:
		LEA ESI,DWORD PTR SS:[ESP+70h]	; тут хранится обрабатываемая в данный момент строка
		LEA EDI, [pointingz_velocity_str]			; кладём в EDI строку, с которой будем сравнивать обрабатываемую строку
		MOV ECX, 21					; указываем размер сравниваемой строки +1 (на еденицу больше чем на самом деле)
		REPE CMPSB [EDI],[ESI]
		JNZ [pointingy_speed]
		ADD EDX, 10h					; смещение по выделенной памяти (листингу)
		JMP [f_frame_write_decimal]	
				
	pointingy_speed:
		LEA ESI,DWORD PTR SS:[ESP+70h]	; тут хранится обрабатываемая в данный момент строка
		LEA EDI, [pointingy_speed_str]			; кладём в EDI строку, с которой будем сравнивать обрабатываемую строку
		MOV ECX, 18					; указываем размер сравниваемой строки +1 (на еденицу больше чем на самом деле)
		REPE CMPSB [EDI],[ESI]
		JNZ [pointing_height]
		ADD EDX, 14h					; смещение по выделенной памяти (листингу)
		JMP [f_frame_write_decimal]	
						
	pointing_height:
		LEA ESI,DWORD PTR SS:[ESP+70h]	; тут хранится обрабатываемая в данный момент строка
		LEA EDI, [pointing_height_str]			; кладём в EDI строку, с которой будем сравнивать обрабатываемую строку
		MOV ECX, 17					; указываем размер сравниваемой строки +1 (на еденицу больше чем на самом деле)
		REPE CMPSB [EDI],[ESI]
		JNZ [loading_frame_wrong]
		ADD EDX, 18h					; смещение по выделенной памяти (листингу)
		JMP [f_frame_write_decimal]	
	
	
	
	
loading_frame_wrong:
	MOV EAX, 004106C0h				; восстановление EAX, чтобы не провоцировать баги
	MOV EDX, DWORD PTR SS:[ESP+10h]
	jmp [wrong_frame]
	
f_frame_write_decimal:
	LEA EAX, [decimal]
	PUSH EAX
	JMP SHORT [f_frame_write]
	
f_frame_write_float:
	LEA EAX, [float]
	PUSH EAX
	JMP SHORT [f_frame_write]
	
f_frame_write:
	POP ECX
	MOV EAX,DWORD PTR SS:[ESP+14h]
	PUSH EDX
	PUSH ECX
	PUSH EAX
	CALL EBX
	ADD ESP,0Ch
	JMP [next_frame]


loading_frame endp





write_pointer_to_char proc
	PUSHAD
	
	MOV ECX, 200h					; сколько памяти надо выделить (ищет свободное место и делает дело)
	PUSH ECX							
	CALL DWORD PTR DS:[447194h] 		; mAlloc (вызов процедуры выделения памяти)
	POP ECX							; восстановление стека
	MOV DWORD PTR DS:[ESI+198h],EAX	; запись указателя на начало выделенной области
	
	write_pointer_to_char_memory_clear:	; очистка выделенной памяти от мусора
	DEC ECX
	MOV BYTE PTR DS:[EAX+ECX],0h
	CMP ECX, 0h
	JG [write_pointer_to_char_memory_clear]
	
	; ==== Блок для установки специальных значений ===;
	
	mov ecx, object_type
	mov dword ptr ds:[eax+28h],ecx
	mov object_type,0
	mov dword ptr ds:[eax+6Ch],255
	
	;=== ============================ ===;
	
	POPAD
		
	MOV ECX,1F4h
	jmp[write_pointer_to_char_back]
write_pointer_to_char endp




initialization_obj1 proc
	
	mov object_link,ebx
	call [init_called_proc]
	jmp [init_back1]

initialization_obj1 endp
initialization_obj2 proc
	
	mov object_link,esi
	call [init_called_proc]
	jmp [init_back2]

initialization_obj2 endp
initialization_obj3 proc
	
	mov object_link,eax
	call [init_called_proc]
	jmp [init_back3]

initialization_obj3 endp
initialization_obj4 proc
	
	cmp ebx, 20
	jg [no_call_6]
	mov object_link,ebx
	mov object_type,1h
no_call_6:
	call [init_called_proc]
	jmp [init_back4]

initialization_obj4 endp
initialization_obj5 proc
	
	mov object_link,esi
	call [init_called_proc]
	jmp [init_back5]

initialization_obj5 endp
initialization_obj6 proc
	
	mov object_link,ebx
	mov object_type,2h
	call [init_called_proc]
	jmp [init_back6]

initialization_obj6 endp
initialization_obj7 proc
	
	mov object_link,esi
	call [init_called_proc]
	jmp [init_back7]

initialization_obj7 endp
initialization_obj8 proc
	
	mov object_link,esi
	call [init_called_proc]
	jmp [init_back8]

initialization_obj8 endp
initialization_obj9 proc
	
	mov object_link,eax
	call [init_called_proc]
	jmp [init_back9]

initialization_obj9 endp


initialization_obj10 proc
	
	mov object_link,esi
	call [init_called_proc]
	jmp [init_back10]

initialization_obj10 endp