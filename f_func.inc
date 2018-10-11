.data

small_shadow 		db "bg\shadows\small.png",0
small_shadow_addr	dd 0h
normal_shadow 		db "bg\shadows\normal.png",0
normal_shadow_addr	dd 0h
big_shadow 			db "bg\shadows\big.png",0
big_shadow_addr		dd 0h

spec_mp 			db "SPRITE\custom_mp.png",0
spec_mp_addr		dd 0h


object_link dd 0h
object_type dd 0h


load_img_ret	dd 004274B0h

CallFunc2	dd 0043F010h
shadow_back	dd 0041A74Ch


var_str db "var:",00
level_str db "level:",00
hitDa_str db "hit_Da:",00




delta dd 2710h



rigth_tback dd 00413140h
left_tback dd 00413154h
up_tback dd 00413168h
down_tback dd 0041317Ch
defend_tback dd 00413190h
jump_tback dd 004131A4h
attack_tback dd 004131B7h

keywait_time db 5

fps_back dd 0043D13Eh
fps_je_back dd 0043D13Eh

mana_res_back dd 0042E792h

damage_mod_back dd 0042E6FDh

atk_addons_back dd 0042E767h



leveling1_back dd 0042F38Ch
leveling2_back dd 0042F2E5h
leveling3_back dd 0042ED15h
leveling3t3_back dd 0042ED2Ch

no_team_change dd 0042F203h

fps_str dd 16h
fps_remover db 0h

object_num dd 0h
object_nuback dd 0041A673h

Opoint_Maker PROTO :dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword
.code
load_img proc

	PUSH ESI
	MOV ESI,0043EE30h
	
	PUSH 0
	PUSH 0
	MOV EAX, offset small_shadow 
	PUSH EAX
	CALL ESI
	POP EAX
	MOV small_shadow_addr,EAX
		
	PUSH 0
	PUSH 0
	MOV EAX, offset normal_shadow 
	PUSH EAX
	CALL ESI
	POP EAX
	MOV normal_shadow_addr,EAX
		
	PUSH 0
	PUSH 0
	MOV EAX, offset big_shadow 
	PUSH EAX
	CALL ESI
	POP EAX
	MOV big_shadow_addr,EAX
		
	PUSH 0
	PUSH 0
	MOV EAX, offset spec_mp 
	PUSH EAX
	CALL ESI
	POP EAX
	MOV spec_mp_addr,EAX
	
	POP ESI
		
	JMP [load_img_ret]

load_img endp








gui_object proc
	
	MOV ESI,DWORD PTR DS:[EBX+ECX*4h+3ECh]
	PUSH ECX
	CMP ECX, 10
	JNGE[obj_num_write]
	SUB ECX, 10
	
obj_num_write:
	MOV object_num, ECX
	POP ECX
	JMP [object_nuback]

gui_object endp

green_shadow proc
	
	PUSH EBX
	PUSH EDI
	PUSH EDX
	PUSH EBP
	
	PUSH EDX
	PUSH 0
	PUSH 1
	PUSH -1
	MOV EDX,DWORD PTR DS:[EAX+18h]
	SHR EDX,1
	NEG EDX
	
	MOV EDI, DWORD PTR DS:[ESI+368h]
	CMP DWORD PTR DS:[EDI+0B4h],1
	JE[shadow_t1]
	
	CMP DWORD PTR DS:[EDI+0B4h],2
	JE[shadow_t2]
	
	CMP DWORD PTR DS:[EDI+0B4h],3
	JE[shadow_t3]
	
	ADD EDX,DWORD PTR DS:[ESI+18h]
	ADD EDX,DWORD PTR DS:[ESI+10Ch]
	PUSH EDX
	MOV EDX,DWORD PTR DS:[ESI+10h]
	SUB EDX,ECX
	SUB EDX,DWORD PTR DS:[450BC4h]
	PUSH EDX	
	MOV ECX,DWORD PTR DS:[EAX+1EE0h]
	JMP[skip]
	
shadow_t1:
	ADD EDX,DWORD PTR DS:[ESI+18h]
	ADD EDX, 8
	ADD EDX,DWORD PTR DS:[ESI+10Ch]
	PUSH EDX
	MOV EDX,DWORD PTR DS:[ESI+10h]
	ADD EDX, 12
	SUB EDX,ECX
	SUB EDX,DWORD PTR DS:[450BC4h]
	PUSH EDX
	MOV ECX,DWORD PTR DS:[small_shadow_addr]
	JMP[skip]
		
shadow_t2:
	MOV ECX,DWORD PTR DS:[normal_shadow_addr]
	JMP[skip]
		
shadow_t3:
	MOV ECX,DWORD PTR DS:[big_shadow_addr]
	JMP[skip]
	
skip:
	CALL [CallFunc2] 
	
	
	POP EBP
	POP EDX
	POP EDI
	POP EBX
	
	JMP [shadow_back]
	
green_shadow endp



Right_Timer proc
	
	PUSH 6
	PUSH EAX
	MOV AL,keywait_time
	MOV BYTE PTR DS:[EDI+4],AL
	POP EAX
	JMP [rigth_tback]

Right_Timer endp

Left_Timer proc
	
	PUSH 4
	PUSH EAX
	MOV AL,keywait_time
	MOV BYTE PTR DS:[EDI+5],AL
	POP EAX
	JMP [left_tback]

Left_Timer endp

Up_Timer proc
	
	PUSH 8
	PUSH EAX
	MOV AL,keywait_time
	MOV BYTE PTR DS:[EDI+6],AL
	POP EAX
	JMP [up_tback]

Up_Timer endp

Down_Timer proc
	
	PUSH 2
	PUSH EAX
	MOV AL,keywait_time
	MOV BYTE PTR DS:[EDI+7],AL
	POP EAX
	JMP [down_tback]

Down_Timer endp

Defend_Timer proc
	
	PUSH 9
	PUSH EAX
	MOV AL,keywait_time
	MOV BYTE PTR DS:[EDI+2],AL
	POP EAX
	JMP [defend_tback]

Defend_Timer endp

Jump_Timer proc
	
	PUSH 0
	PUSH EAX
	MOV AL,keywait_time
	MOV BYTE PTR DS:[EDI+1],AL
	POP EAX
	JMP [jump_tback]

Jump_Timer endp

Attack_Timer proc
	
	PUSH 5
	PUSH EAX
	MOV AL,keywait_time
	MOV BYTE PTR DS:[EDI],AL
	POP EAX
	JMP [attack_tback]

Attack_Timer endp


fps_change proc
	
	MOV EBX,3h
	CMP DWORD PTR DS:[0044D02Ch],0h
   	JE [fps_je]
   	
   	CMP fps_remover, 0h
   	JE [normal_fps]
   	CMP fps_remover, 1h
   	JE [sub_fps]
   	CMP fps_remover, 2h
   	JE [add_fps]
   	

normal_fps:
	ADD EBX, fps_str; 45 fps
	JMP [fps_back]
	
sub_fps:
	ADD fps_str,1h
	ADD EBX, fps_str
	CMP fps_str,35h
	JGE[fps_reverse]
	JMP [fps_back]

fps_reverse:
	MOV fps_remover, 2h
	JMP [fps_back]

add_fps:
	MOV DWORD PTR DS:[00450BD4h],0
	JNE[noadd_fps]
	SUB fps_str,1h
	ADD EBX, fps_str
	CMP fps_str,16h
	JLE[fps_normalize]
	JMP [fps_back]
	
noadd_fps:
	ADD EBX, fps_str
	JMP [fps_back]

fps_normalize:
	MOV fps_str,16h
	MOV fps_remover, 0h
	JMP [fps_back]
	
fps_je:
	JMP[fps_je_back]

fps_change endp


mana_restore_attack proc
	
	PUSH ECX
	CMP DWORD PTR DS:[EDI+2F4h], -1
	JNZ[mana_restore_none]
	CMP DWORD PTR DS:[EBX+354h], -1
	JE [mana_restore_self]
	ADD DWORD PTR DS:[EAX+348h],ECX
	SUB ECX,15
	CMP ECX, 0
	JLE [mana_restore_none]
	ADD DWORD PTR DS:[EAX+308h],ECX
	JMP [mana_restore_none]
	
mana_restore_self:
	ADD DWORD PTR DS:[EBX+348h],ECX
	SUB ECX,15
	CMP ECX, 0
	JLE [mana_restore_none]
	ADD DWORD PTR DS:[EBX+308h],ECX
mana_restore_none:
	POP ECX
	JMP [mana_res_back]
	
mana_restore_attack endp

damage_modificators proc
	
	mov eax, 0h ; обнуление урона
	PUSH EBX
	
add_combo_multipler:
	MOV EDX, DWORD PTR DS:[EBX+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNE[damage_mod_add_injury]
	MOV EDX, DWORD PTR DS:[EBX+198h]
	CMP DWORD PTR DS:[EDX+8h],0
	JLE[damage_mod_add_injury]
	
	PUSH EAX
	PUSH ECX
	MOV EAX,DWORD PTR DS:[EDX+8h]
	MOV ECX,100
	XOR EDX, EDX
	DIV ECX
	MOV EDX,EAX
	POP ECX
	POP EAX
	ADD EAX,EDX
	
damage_mod_add_injury:
	POP EBX
	MOV EDX,DWORD PTR SS:[ESP+0Ch]
	ADD EAX,DWORD PTR DS:[EDX+44h] ; добавили урон от injury

	jmp [damage_mod_back]

damage_modificators endp



attack_addons proc
	
	PUSH EAX
	PUSH EDX
	
combo_multipler:
	MOV EAX, DWORD PTR DS:[EBX+198h]
	CMP DWORD PTR DS:[EAX+8h],0
	JG[combo_multipler_add_multipler]
	MOV DWORD PTR DS:[EAX+8h],515
	JMP [attack_NoAddons]
	
combo_multipler_add_multipler:

	PUSH ECX
	MOV EAX,DWORD PTR DS:[EAX+8h]
	MOV ECX,100
	XOR EDX, EDX
	DIV ECX
	POP ECX
	
	CMP EAX,30
	JGE[combo_multipler_add_time]
	ADD EAX,5
	
combo_multipler_add_time:
	CMP EDX, 15
	JE[combo_multipler_create_multipler]
	MOV EDX, 15
	
combo_multipler_create_multipler:
	IMUL EAX,100
	ADD EAX,EDX
	MOV EDX, DWORD PTR DS:[EBX+198h]
	MOV DWORD PTR DS:[EDX+8h],EAX
	JMP[attack_NoAddons]
	
attack_NoAddons:
	
	CMP [Izanami_Time], 0
	JLE [no_Izanami_save_damage]

	PUSH ECX
	PUSH ESI
	PUSH EDI
	
	MOV ECX, DWORD PTR DS:[EBX+354h]
	MOV ESI,  DWORD PTR DS:[EDI+354h]
	MOV EDI, DWORD PTR DS:[00458B00h]
	
	MOV EAX, DWORD PTR DS:[EDI+ECX*4h+3ECh]
	MOV EDX, DWORD PTR DS:[EDI+ESI*4h+3ECh]
	
	POP EDI
	POP ESI
	POP ECX
	
	
	
	MOV EAX, DWORD PTR DS:[EAX+198h]
	CMP DWORD PTR DS:[EAX+2Ch], 2
	JL[no_Izanami_save_damage]
	
	MOV EDX, DWORD PTR DS:[EDX+198h]
	CMP DWORD PTR DS:[EDX+2Ch], 2
	JL [no_Izanami_save_damage]
	
	ADD DWORD PTR DS:[EDX+30h], ECX
	
	JMP [no_Izanami_save_damage]
	
no_Izanami_save_damage:
	SUB DWORD PTR DS:[EDI+2FCh],ECX 
	ADD DWORD PTR DS:[EDI+34Ch],ECX
	
attack_addons_back:
	POP EDX
	POP EAX
	JMP [atk_addons_back]

attack_addons endp

object_leveling1 proc
	
		PUSH ECX
		PUSH EDX
		
		IMUL ECX,DWORD PTR DS:[EBX+70h],1B0h
		ADD ECX,DWORD PTR DS:[EBX+368h] ;
		MOV ECX,DWORD PTR DS:[ECX+934h] ; получаем уровень атакующего в ecx
		
		IMUL EDX,DWORD PTR DS:[EDI+70h],1B0h
		ADD EDX,DWORD PTR DS:[EDI+368h] ;
		MOV EDX,DWORD PTR DS:[EDX+934h] ; получаем уровень атакуемого в edx
		
		
		;сравним уровни
		CMP ECX,EDX
		JL [level1_below] ; уровень ниже
		CMP ECX,EDX
		JG [level1_above] ; уровень выше
		CMP ECX,EDX
		JE [levels1_equal] ; уровни равны
		
		POP EDX
		POP ECX
		MOV DWORD PTR DS:[EDI+70h],20
		JMP [leveling1_back] ; на всякий случай
		
level1_below:
		
		IMUL EDX,DWORD PTR DS:[EDI+70h],1B0h
		ADD EDX,DWORD PTR DS:[EDI+368h] 
		CMP DWORD PTR DS:[EDX+868h], 0
		JE [level1_normal_below]
		
		MOV EDX,DWORD PTR DS:[EDX+868h]
		MOV DWORD PTR DS:[EDI+70h], EDX
		
level1_normal_below:
		POP EDX
		POP ECX
		
		JMP [leveling2_back] ; на всякий случай
		
level1_above:
		
		POP EDX
		POP ECX
		MOV DWORD PTR DS:[EDI+70h],20
		JMP [leveling1_back] ; на всякий случай
		
levels1_equal:
		
		POP EDX
		POP ECX
	attacker:
		CMP DWORD PTR DS:[EBX+20h],1
		JNE[attacked]
		MOV DWORD PTR DS:[EBX+70h],20
	attacked:
		CMP DWORD PTR DS:[EDI+20h],1
		JNE[equal_end]
		MOV DWORD PTR DS:[EDI+70h],20
	equal_end:
		JMP [leveling1_back] ; на всякий случай
		
object_leveling1 endp

object_leveling2 proc
		
		PUSH ECX
		PUSH EDX
		PUSH EAX
		
		MOV EAX, DWORD PTR DS:[EBX+364h]
		CMP DWORD PTR DS:[EDI+364h],EAX
		JE[level2_normal_below]
		
		IMUL ECX,DWORD PTR DS:[EBX+70h],1B0h
		ADD ECX,DWORD PTR DS:[EBX+368h] ;
		MOV ECX,DWORD PTR DS:[ECX+934h] ; получаем уровень атакующего в ecx
		
		IMUL EDX,DWORD PTR DS:[EDI+70h],1B0h
		ADD EDX,DWORD PTR DS:[EDI+368h] ;
		MOV EDX,DWORD PTR DS:[EDX+934h] ; получаем уровень атакуемого в edx
		
		
		
		;сравним уровни
		CMP ECX,EDX
		JL [level2_below] ; уровень ниже
		CMP ECX,EDX
		JG [level2_above] ; уровень выше
		CMP ECX,EDX
		JE [levels2_equal] ; уровни равны
		
		POP EAX
		POP EDX
		POP ECX
		MOV DWORD PTR DS:[EDI+70h],20
		JMP [leveling2_back] ; на всякий случай
		
level2_below:
		
		IMUL EDX,DWORD PTR DS:[EDI+70h],1B0h
		ADD EDX,DWORD PTR DS:[EDI+368h]
		CMP DWORD PTR DS:[EDX+868h], 0
		JE [level2_normal_below]
		
		MOV EDX,DWORD PTR DS:[EDX+868h]
		MOV DWORD PTR DS:[EDI+70h], EDX
		
level2_normal_below:
		POP EAX
		POP EDX
		POP ECX
		
		JMP [leveling2_back] ; на всякий случай
		
level2_above:

		POP EAX
		POP EDX
		POP ECX
		MOV DWORD PTR DS:[EDI+70h],20
		JMP [leveling2_back] ; на всякий случай
		
levels2_equal:
		
		POP EAX
		POP EDX
		POP ECX
		MOV DWORD PTR DS:[EDI+70h],20
		JMP [leveling2_back] ; на всякий случай
		
object_leveling2 endp

object_leveling3 proc

		PUSH ECX
		PUSH EDX
		
		IMUL ECX,DWORD PTR DS:[EBX+70h],1B0h
		ADD ECX,DWORD PTR DS:[EBX+368h] ;
		MOV ECX,DWORD PTR DS:[ECX+934h] ; получаем уровень атакующего в ecx
		
		IMUL EDX,DWORD PTR DS:[EDI+70h],1B0h
		ADD EDX,DWORD PTR DS:[EDI+368h] ;
		MOV EDX,DWORD PTR DS:[EDX+934h] ; получаем уровень атакуемого в edx
		
		;сравним уровни
		CMP ECX,EDX
		JL [level3_below] ; уровень ниже
		CMP ECX,EDX
		JG [level3_above] ; уровень выше
		CMP ECX,EDX
		JE [levels3_equal] ; уровни равны
		
		POP EDX
		POP ECX
		MOV DWORD PTR DS:[EBX+70h],10
		JMP [leveling3_back] ; на всякий случай
		
level3_below: ; уровень ниже
		
		MOV EDX, DWORD PTR DS:[EDI+368h]
		CMP DWORD PTR DS:[EDX+368h],3
		JE[level3_below_t3]
		
		POP EDX
		POP ECX
		MOV DWORD PTR DS:[EBX+70h],10
		JMP [leveling3_back]
		
level3_below_t3:	
		
		POP EDX
		POP ECX
		MOV DWORD PTR DS:[EBX+70h],10
		JMP [leveling3_back]
		
level3_above: ; уровень выше
		
		MOV EDX, DWORD PTR DS:[EDI+368h]
		CMP DWORD PTR DS:[EDX+368h],3
		JE [level3_above_t3]
		
		POP EDX
		POP ECX
		MOV DWORD PTR DS:[EBX+70h],10
		JMP [leveling3_back]
		
level3_above_t3:
		
		POP EDX
		POP ECX
		JMP [leveling3t3_back]
		
levels3_equal: ; уровни равны
		
		MOV EDX, DWORD PTR DS:[EDI+368h]
		CMP DWORD PTR DS:[EDX+368h],3
		JE [level3_equal_t3]
		
		POP EDX
		POP ECX
		MOV DWORD PTR DS:[EBX+70h],10
		JMP [leveling3_back]
		
level3_equal_t3:
		
		POP EDX
		POP ECX
		MOV DWORD PTR DS:[EBX+70h],20
		JMP [leveling3_back]

object_leveling3 endp

no_team_change_obj proc
	
	JMP[no_team_change]

no_team_change_obj endp