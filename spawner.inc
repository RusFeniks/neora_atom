.Data

spawner1	dd 0042D6A2h
spawner2	dd 0042D518h
spawner3	dd 0042D400h
spawner4	dd 0043766Fh


.Code

SpawnerBoth1 proc

		MOV ECX,DWORD PTR DS:[ESI]
		ADD ESP,8h
		ADD EAX,32h ; Можно заменить на "MOV EAX, N", где X - координата X, по которой должны спавниться игроки
		MOV DWORD PTR DS:[ECX+10h],EAX ; Если закомментить эту строку - спавн будет рандомный на всю ширину карты
		MOV EAX,DWORD PTR DS:[ESI]
		FILD DWORD PTR DS:[EAX+10h]
		FSTP QWORD PTR DS:[EAX+58h]
		
		JMP [spawner1]
		
SpawnerBoth1 endp

SpawnerPlayer1 proc

		ADD EAX,DWORD PTR DS:[EDI+4h]
		MOV EDX,DWORD PTR DS:[ESI]
		MOV DWORD PTR DS:[EDX+18h],EAX ; спавн игроков по Z. Можно заменить EAX на число, если хочется точной точки спавна
		MOV EAX,DWORD PTR DS:[ESI]	
		MOV DWORD PTR DS:[EAX+14h],0h ; спавн игроков по Y
		MOV EAX,DWORD PTR DS:[ESI]
		ADD ESP,10h
		FILD DWORD PTR DS:[EAX+10h] ; x ???
		FSTP QWORD PTR DS:[EAX+58h] ; x ???
		MOV EAX,DWORD PTR DS:[ESI]
		FILD DWORD PTR DS:[EAX+18h] ; z ???
		FSTP QWORD PTR DS:[EAX+68h] ; z ???
		MOV ECX,DWORD PTR DS:[ESI]
		FLDZ
		MOV EAX,DWORD PTR SS:[ESP+1Ch]
		FSTP QWORD PTR DS:[ECX+60h] ; y ???
		MOV EDX,DWORD PTR DS:[ESI]
		
ID_check:
		push ecx ; reserve
		push edx ; reserve
		MOV EDX,DWORD PTR DS:[ECX+368h] ; data-file
		MOV EDX,DWORD PTR DS:[EDX+6F4h] ; ID of object
		JMP [Regular_HpMp_Start]

Regular_HpMp_Start:
		pop edx ; reserve
		pop ecx ; reserve
		
Special_MP:
		PUSH ECX
		MOV ECX, DWORD PTR DS:[EDX+368h]
		CMP DWORD PTR DS:[ECX+6F4h],14 ; Итачи
		JE[Special_MP_Itachi]
		CMP DWORD PTR DS:[ECX+6F4h],57 ; Итачи МШ
		JE[Special_MP_ItachiMS]
		CMP DWORD PTR DS:[ECX+6F4h],10 ; Пейн
		JE[Special_MP_Pein]
		CMP DWORD PTR DS:[ECX+6F4h],9 ; Тоби
		JE[Special_MP_Tobi]
		MOV ECX, DWORD PTR DS:[ECX+0B8h]
		CMP DWORD PTR DS:[ECX+0h],0h
		JNE [Spec_MP_test]
		MOV ECX, DWORD PTR DS:[EDX+198h]
		MOV DWORD PTR DS:[ECX+10h],0
		MOV DWORD PTR DS:[ECX+14h],0
		JMP[Special_MP_back]
	Spec_MP_test:
		PUSH EAX
		MOV EAX, DWORD PTR DS:[ECX+0h]
		MOV ECX, DWORD PTR DS:[EDX+198h]
		MOV DWORD PTR DS:[ECX+10h],EAX
		MOV DWORD PTR DS:[ECX+14h],EAX
		POP EAX
		JMP[Special_MP_back]
		

Special_MP_Itachi:
		MOV ECX, DWORD PTR DS:[EDX+198h]
		MOV DWORD PTR DS:[ECX+10h],50
		MOV DWORD PTR DS:[ECX+14h],100
		JMP[Special_MP_back]
		
Special_MP_ItachiMS:
		MOV ECX, DWORD PTR DS:[EDX+198h]
		MOV DWORD PTR DS:[ECX+10h],90
		MOV DWORD PTR DS:[ECX+14h],100
		JMP[Special_MP_back]

Special_MP_Pein:
		MOV ECX, DWORD PTR DS:[EDX+198h]
		MOV DWORD PTR DS:[ECX+10h],100
		MOV DWORD PTR DS:[ECX+14h],400
		JMP[Special_MP_back]

Special_MP_Tobi:
		MOV ECX, DWORD PTR DS:[EDX+198h]
		MOV DWORD PTR DS:[ECX+10h],600
		MOV DWORD PTR DS:[ECX+14h],600
		JMP[Special_MP_back]
		
Special_MP_back:
		POP ECX
		
		MOV DWORD PTR DS:[EDX+2FCh],1000 ; стартовое число хп (светлая полоска)
		MOV DWORD PTR DS:[EDX+300h],1000 ; стартовое число хп (темная полоска)
		MOV DWORD PTR DS:[EDX+304h],1000 ; стартовое число хп (максимум хп)
		MOV DWORD PTR DS:[EDX+308h],350 ; стартовое число маны
		JMP [Proceed]

Proceed:		
		CMP DWORD PTR DS:[EAX],1h ; проверка, что если стадии, то ману давать сразу фулл
		JNZ SHORT [Get_Back]
		MOV ECX,DWORD PTR DS:[ESI]
		MOV DWORD PTR DS:[ECX+308h],500 ; стартовое число маны для режима стадий = 500
	

Get_Back:
		MOV EDX,DWORD PTR DS:[ESI]
		MOV DWORD PTR DS:[EDX+354h],EBX
		MOV EDI,EBP
		XOR EBP,EBP
		
		JMP [spawner2]

SpawnerPlayer1 endp




SpawnerCom1 proc

		ADD EAX,DWORD PTR DS:[EDI+4h]
		MOV EDX,DWORD PTR DS:[ESI+28h]
		MOV DWORD PTR DS:[EDX+18h],EAX ; спавн компов по Z. Можно заменить EAX на число, если хочется точной точки спавна
		MOV EAX,DWORD PTR DS:[ESI+28]
		MOV DWORD PTR DS:[EAX+14h],0h ; спавн компов по Y
		MOV EAX,DWORD PTR DS:[ESI+28h]
		ADD ESP,10h
		FILD DWORD PTR DS:[EAX+10h] ; x ???
		FSTP QWORD PTR DS:[EAX+58h] ; x ???
		MOV EAX,DWORD PTR DS:[ESI+28h]
		FILD DWORD PTR DS:[EAX+18h] ; z ???
		FSTP QWORD PTR DS:[EAX+68h] ; z ???
		MOV ECX,DWORD PTR DS:[ESI+28h]
		FLDZ
		MOV EAX,DWORD PTR SS:[ESP+1Ch]
		FSTP QWORD PTR DS:[ECX+60h]
		MOV EDX,DWORD PTR DS:[ESI+28h]
		
		
ID_check_Com:
		push ecx ; reserve
		push edx ; reserve
		MOV EDX,DWORD PTR DS:[ECX+368h] ; data-file
		MOV EDX,DWORD PTR DS:[EDX+6F4h] ; ID of object
		JMP [Regular_HpMp_Start_com]	

Regular_HpMp_Start_com:
		pop edx ; reserve
		pop ecx ; reserve
			
Special_MP_com:
		PUSH ECX
		MOV ECX, DWORD PTR DS:[EDX+368h]
		
		CMP DWORD PTR DS:[ECX+6F4h],14 ; Итачи
		JE[Special_MP_Itachi_com]
		CMP DWORD PTR DS:[ECX+6F4h],57 ; Итачи МШ
		JE[Special_MP_ItachiMS_com]
		CMP DWORD PTR DS:[ECX+6F4h],10 ; Пейн
		JE[Special_MP_Pein_com]
		CMP DWORD PTR DS:[ECX+6F4h],9 ; Тоби
		JE[Special_MP_Tobi_com]
		
		MOV ECX, DWORD PTR DS:[EDX+198h]
		MOV DWORD PTR DS:[ECX+10h],0
		MOV DWORD PTR DS:[ECX+14h],0
		JMP[Special_MP_back_com]

Special_MP_Itachi_com:
		MOV ECX, DWORD PTR DS:[EDX+198h]
		MOV DWORD PTR DS:[ECX+10h],50
		MOV DWORD PTR DS:[ECX+14h],100
		JMP[Special_MP_back_com]
		
Special_MP_ItachiMS_com:
		MOV ECX, DWORD PTR DS:[EDX+198h]
		MOV DWORD PTR DS:[ECX+10h],90
		MOV DWORD PTR DS:[ECX+14h],100
		JMP[Special_MP_back_com]

Special_MP_Pein_com:
		MOV ECX, DWORD PTR DS:[EDX+198h]
		MOV DWORD PTR DS:[ECX+10h],100
		MOV DWORD PTR DS:[ECX+14h],400
		JMP[Special_MP_back_com]
		
Special_MP_Tobi_com:
		MOV ECX, DWORD PTR DS:[EDX+198h]
		MOV DWORD PTR DS:[ECX+10h],500
		MOV DWORD PTR DS:[ECX+14h],500
		JMP[Special_MP_back_com]
		
Special_MP_back_com:
		POP ECX
		
		MOV DWORD PTR DS:[EDX+2FCh],1000 ; стартовое число хп (светлая полоска)
		MOV DWORD PTR DS:[EDX+300h],1000 ; стартовое число хп (темная полоска)
		MOV DWORD PTR DS:[EDX+304h],1000 ; стартовое число хп (максимум хп)
		MOV DWORD PTR DS:[EDX+308h],350 ; стартовое число маны
		JMP [Proceed_Com]
		
Proceed_Com:		
		CMP DWORD PTR DS:[EAX],1h ; проверка, что если стадии, то ману давать сразу фулл
		JNZ SHORT [Get_Back_Com]
		MOV ECX,DWORD PTR DS:[ESI+28h]
		MOV DWORD PTR DS:[ECX+308h],500 ; стартовое число маны для режима стадий = 500

Get_Back_Com:
		JMP [spawner3]

SpawnerCom1 endp






SpawnerComStages1 proc

		ADD EAX,DWORD PTR DS:[EBX+0B0h] ; добавление рандомного числа к точки призыва по X
		;MOV EAX,DWORD PTR DS:[EBX+0B0h] ; Заменить этой строкой строчку выше, чтобы отключить рандом
		ADD ESP,8
		MOV EDX,EAX
		
		JMP [spawner4]

SpawnerComStages1 endp














