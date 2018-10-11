.data

	Itr_kind_checker_back dd 0041F5FCh
	
	opacity_procent dq 2.55
	
	random_func dd 00417170h
	number_zero dq 0.0

.code

Itr_checker proc
	
	
	MOV EAX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
	
	MOV EDX, DWORD PTR DS:[EAX+198h]
	MOV DWORD PTR DS:[EDX+94h], 0h
	MOV DWORD PTR DS:[EDX+98h], 0h
	
	MOV ECX,DWORD PTR DS:[EAX+70h]
	MOV EDX,DWORD PTR DS:[EAX+368h]
	IMUL ECX,ECX,1B0h
	
	; EAX - Объект
	; EDX - Поинт ер на дат а сегмент
	; ECX - Смещение по номеру фрейма
	; Получение какой-т о част и фрейма: EDX+ECX+Смещение
	
	PUSHAD
	MOV EDI, DWORD PTR DS:[EDX+ECX+958h] ; Количест во Itr блоков в фрейме
	
Itr_check_cycle:
	CMP EDI, 0h
	JLE [itr_check_end]
	SUB EDI, 1h
	
	IMUL EBX, EDI, 70h
	ADD EBX, DWORD PTR DS:[EDX+ECX+960h]
	MOV ESI, DWORD PTR DS:[EBX+0h]
	
	; EBX - Поинт ер на обрабат ываемый Itr
	; ESI - Itr Kind
	
	PUSH ECX
	PUSH EDX
	PUSH EDI
	
	
ik_100000:
	; МАНИПУЛЯЦИЯ С ХП
	; injury - свет лая полоска хп 
	; bdefend - т емная
	CMP ESI, 100000
	JNE [ik_100001]
	CMP DWORD PTR DS:[EAX+88h],0h
	JNE [ik_100001]
	MOV ECX, DWORD PTR DS:[EBX+44h]
	ADD DWORD PTR DS:[EAX+2FCh],ECX
	MOV ECX, DWORD PTR DS:[EBX+40h]
	ADD DWORD PTR DS:[EAX+300h],ECX
	
	
ik_100001:
	; МАНИПУЛЯЦИЯ С МАНОЙ
	; injury - количест во
	; dvx - кадр, куда перейт и при нехват ке
	CMP ESI, 100001
	JNE [ik_100009]
	CMP DWORD PTR DS:[EAX+88h],0h
	JNE [ik_100009]
	MOV ECX, DWORD PTR DS:[EBX+44h]
	ADD DWORD PTR DS:[EAX+308h],ECX
	CMP DWORD PTR DS:[EAX+308h], 0h
	JNL [ik_100009]
	SUB DWORD PTR DS:[EAX+308h],ECX
	FLD DWORD PTR DS:[EBX+14h]
	FISTP DWORD PTR DS:[EAX+70h]
	MOV DWORD PTR DS:[EAX+88h], 0h
	
ik_100009:
	; ТАЙМЕРЫ
	; arest - время дейст вия т аймера в wait
	; dvx - кадр, куда перейт и когда т аймер окончит  работ у
	; vrest - добавляет  к работ ающему т аймеру время в wait
	CMP ESI, 100009
	JNE [ik_100009_recovery]
	CMP DWORD PTR DS:[EAX+88h],0h
	JNE [ik_100009_recovery]
	MOV ECX, DWORD PTR DS:[EAX+198h]
	CMP DWORD PTR DS:[ECX+78h], 0h
	JG [ik_100009_working]
	MOV EDX, DWORD PTR DS:[EBX+20h]
	MOV DWORD PTR DS:[ECX+78h], EDX
ik_100009_working:
	MOV EDX, DWORD PTR DS:[EBX+24h]
	ADD DWORD PTR DS:[ECX+78h], EDX
	FLD DWORD PTR DS:[EBX+14h]
	FISTP DWORD PTR DS:[ECX+7Ch]
	JMP [ik_100009_recovery]
ik_100009_recovery:
	JMP [ik_100010]
ik_100009_end:
	
ik_100010:
	; ДЕЙСТВИЕ ПРИ ДОСТИЖЕНИИ КРАЯ КАРТЫ
	; dvx - кадр, куда перейт и если ст олкнулся слева
	; dvy - кадр, куда перейт и если ст олкнулся справа
	; effects:
	;	1 - разворот
	; -------------------------------------------------------------------
	CMP ESI, 100010
	JNE [ik_100011]
	MOV ECX, DWORD PTR DS:[EAX+10h]
	MOV EDX, DWORD PTR DS:[00452984h]
	CMP  ECX, 0h
	JLE [ik_100010_left_border]
	CMP ECX, DWORD PTR DS:[EDX]
	JGE [ik_100010_right_border]
	JMP [ik_100010_end]
	
ik_100010_right_border:
	
	MOV ECX, DWORD PTR DS:[EAX+24h]
	MOV DWORD PTR DS:[EAX+24h],1h
	FLD QWORD PTR DS:[EAX+58h]
	FISUB DWORD PTR DS:[EAX+24h]
	FIST DWORD PTR DS:[EAX+10h]
	FSTP QWORD PTR DS:[EAX+58h]
	MOV DWORD PTR DS:[EAX+24h],ECX
	
	CMP  DWORD PTR DS:[EBX+2Ch], 1
	JE [ik_100010_right_effect1]
	JMP [ik_100010_right_border_dvx]
ik_100010_right_effect1:
	CMP BYTE PTR DS:[EAX+80h], 0h
	JNE [ik_100010_right_border_dvx]
	MOV BYTE PTR DS:[EAX+80h], 1h
	JMP [ik_100010_right_border_dvx]
ik_100010_right_border_dvx:
	CMP  DWORD PTR DS:[EBX+18h], 0h
	JE [ik_100010_end]
	FLD DWORD PTR DS:[EBX+18h]
	FISTP DWORD PTR DS:[EAX+70h]
	MOV DWORD PTR DS:[EAX+88h], 0h
	JMP [ik_100010_end]
	
ik_100010_left_border:
	
	MOV ECX, DWORD PTR DS:[EAX+24h]
	MOV DWORD PTR DS:[EAX+24h],1h
	FLD QWORD PTR DS:[EAX+58h]
	FIADD DWORD PTR DS:[EAX+24h]
	FIST DWORD PTR DS:[EAX+10h]
	FSTP QWORD PTR DS:[EAX+58h]
	MOV DWORD PTR DS:[EAX+24h],ECX
	
	CMP  DWORD PTR DS:[EBX+2Ch], 1
	JE [ik_100010_left_effect1]
	JMP [ik_100010_left_border_dvx]
ik_100010_left_effect1:
	CMP BYTE PTR DS:[EAX+80h], 1h
	JNE [ik_100010_left_border_dvx]
	MOV BYTE PTR DS:[EAX+80h], 0h
	JMP [ik_100010_left_border_dvx]
ik_100010_left_border_dvx:
	CMP  DWORD PTR DS:[EBX+14h], 0h
	JE [ik_100010_end]
	FLD DWORD PTR DS:[EBX+14h]
	FISTP DWORD PTR DS:[EAX+70h]
	MOV DWORD PTR DS:[EAX+88h], 0h
	JMP [ik_100010_end]
	
ik_100010_end:
	JMP [ik_100011]
	
	
ik_100011:
	; ТЕЛЕПОРТАЦИЯ ОБЪЕКТА
	; Effects:
	;	1 - По осям x,y,z
	;	2 - Смещение по осям x,y,z
	;	4 - По координат ам x,y,z владельца объект а
	;	5 - На цент р экрана по осям X, Y, Z
	;	6 - Цент р экрана по X
	;	7 - Цент р экрана по Y
	;	8 - Цент р экрана по Z
	;	9 - Центр карты по X,Y,Z
	;	10-Случайный вражеский Иргок (type 0), x - расстояние до противника
	CMP ESI, 100011
	JNE [ik_100011_reset]
	
	CMP DWORD PTR DS:[EBX+2Ch],1
	JE [ik_100011_effect_1X]	
	CMP DWORD PTR DS:[EBX+2Ch],2
	JE [ik_100011_effect_2X]
	CMP DWORD PTR DS:[EBX+2Ch],4
	JE [ik_100011_effect_4X]
	CMP DWORD PTR DS:[EBX+2Ch],5
	JE [ik_100011_effect_5XYZ]
	CMP DWORD PTR DS:[EBX+2Ch],6
	JE [ik_100011_effect_5X]	
	CMP DWORD PTR DS:[EBX+2Ch],7
	JE [ik_100011_effect_5Y]	
	CMP DWORD PTR DS:[EBX+2Ch],8
	JE [ik_100011_effect_5Z]	
	CMP DWORD PTR DS:[EBX+2Ch],9
	JE [ik_100011_effect_9]
	CMP DWORD PTR DS:[EBX+2Ch],10
	JE [ik_100011_effect_10]
	JMP [ik_100011_reset]
	
ik_100011_effect_1X:
	CMP DWORD PTR DS:[EBX+4h],0
	JE [ik_100011_effect_1Y]
	FILD DWORD PTR DS:[EBX+4h]
	FIST DWORD PTR DS:[EAX+10h]
	FSTP QWORD PTR DS:[EAX+58h]
ik_100011_effect_1Y:
	CMP DWORD PTR DS:[EBX+8h],0
	JE [ik_100011_effect_1Z]
	FILD DWORD PTR DS:[EBX+8h]
	FIST DWORD PTR DS:[EAX+14h]
	FSTP QWORD PTR DS:[EAX+60h]
ik_100011_effect_1Z:
	CMP DWORD PTR DS:[EBX+4Ch],0
	JE [ik_100011_reset]
	FILD DWORD PTR DS:[EBX+4Ch]
	FIST DWORD PTR DS:[EAX+18h]
	FSTP QWORD PTR DS:[EAX+68h]
	JMP [ik_100011_reset]
	
	
ik_100011_effect_2X:
	CMP DWORD PTR DS:[EBX+4h],0
	JE [ik_100011_effect_2Y]
	FLD QWORD PTR DS:[EAX+58h]
	FIADD DWORD PTR DS:[EBX+4h]
	CMP BYTE PTR DS:[EAX+80h],0h
	JE [ik_100011_effect_2X_facing]
	FISUB DWORD PTR DS:[EBX+4h]
	FISUB DWORD PTR DS:[EBX+4h]
ik_100011_effect_2X_facing:
	FIST DWORD PTR DS:[EAX+10h]
	FSTP QWORD PTR DS:[EAX+58h]
ik_100011_effect_2Y:
	CMP DWORD PTR DS:[EBX+8h],0
	JE [ik_100011_effect_2Z]
	FLD QWORD PTR DS:[EAX+60h]
	FIADD DWORD PTR DS:[EBX+8h]
	FIST DWORD PTR DS:[EAX+14h]
	FSTP QWORD PTR DS:[EAX+60h]
ik_100011_effect_2Z:
	CMP DWORD PTR DS:[EBX+4Ch],0
	JE [ik_100011_reset]
	FLD QWORD PTR DS:[EAX+68h]
	FIADD DWORD PTR DS:[EBX+4Ch]
	FIST DWORD PTR DS:[EAX+18h]
	FSTP QWORD PTR DS:[EAX+68h]
	JMP [ik_100011_reset]
	
	
ik_100011_effect_4X:
	MOV EDI, DWORD PTR DS:[EAX+354h]
	MOV EDX, DWORD PTR DS:[00458B00h]
	MOV ECX,DWORD PTR DS:[EDX+EDI*4h+3ECh]
	
	CMP DWORD PTR DS:[EBX+4h],0
	JE [ik_100011_effect_4Y]
	FLD QWORD PTR DS:[ECX+58h]
	FIST DWORD PTR DS:[EAX+10h]
	FSTP QWORD PTR DS:[EAX+58h]
	
	ik_100011_effect_4Y:
	CMP DWORD PTR DS:[EBX+8h],0
	JE [ik_100011_effect_4Z]
	FLD QWORD PTR DS:[ECX+60h]
	FIST DWORD PTR DS:[EAX+14h]
	FSTP QWORD PTR DS:[EAX+60h]
	
	ik_100011_effect_4Z:
	CMP DWORD PTR DS:[EBX+4Ch],0
	JE [ik_100011_reset]
	FLD QWORD PTR DS:[ECX+68h]
	FIST DWORD PTR DS:[EAX+18h]
	FSTP QWORD PTR DS:[EAX+68h]
	JMP [ik_100011_reset]
	
ik_100011_effect_5XYZ:
ik_100011_effect_5X:
	MOV EDX, DWORD PTR DS:[00450B7Ch]
	MOV ECX, DWORD PTR DS:[00450B78h]
	CMP EDX, 0h
	JNE [ik_100011_effect_5X_replay]
	MOV EDX, DWORD PTR DS:[00450BC4h]
	MOV ECX, DWORD PTR DS:[00450BC8h]
ik_100011_effect_5X_replay:
	PUSH ECX
	PUSH EDX
	FILD DWORD PTR DS:[ESP+0h]
	FIADD DWORD PTR DS:[ESP+4h]
	FIST DWORD PTR DS:[EAX+10h]
	FSTP QWORD PTR DS:[EAX+58h]
	ADD ESP, 8h
	CMP DWORD PTR DS:[EBX+2Ch],5h
	JNE [ik_100011_end]
ik_100011_effect_5Y:
	FILD [cam_y_coord_point]
	FCHS
	FIADD [cam_y_coord_speed]
	FIST DWORD PTR DS:[EAX+14h]
	FSTP QWORD PTR DS:[EAX+60h]
	CMP DWORD PTR DS:[EBX+2Ch],5h
	JNE [ik_100011_end]
ik_100011_effect_5Z:
	MOV EDX, DWORD PTR DS:[00452984h]
	FILD DWORD PTR DS:[EDX+8h]
	FIST DWORD PTR DS:[EAX+18h]
	FSTP QWORD PTR DS:[EAX+68h]
	MOV EDX, 600
	SUB EDX, DWORD PTR DS:[EAX+18h]
	MOV ECX, DWORD PTR DS:[EAX+198h]
	MOV DWORD PTR DS:[ECX+60h], EDX
	JMP [ik_100011_end]
	
ik_100011_effect_9:
	MOV EDX, DWORD PTR DS:[00452984h]
	PUSH 2

	FILD DWORD PTR DS:[EDX]
	FIDIV DWORD PTR SS:[ESP]
	FIST DWORD PTR DS:[EAX+10h]
	FSTP QWORD PTR DS:[EAX+58h]
	
	FILD DWORD PTR DS:[EDX+8h]
	FISUB DWORD PTR DS:[EDX+4h]
	FIDIV DWORD PTR SS:[ESP]
	FIADD DWORD PTR DS:[EDX+4h]
	FIST DWORD PTR DS:[EAX+18h]
	FSTP QWORD PTR DS:[EAX+68h]
	
	POP ECX
JMP [ik_100011_reset]
	
	
ik_100011_effect_10:
	
	CMP DWORD PTR DS:[EAX+88h],0h
	JNE [ik_100011_reset]
	
	PUSHAD
	
	MOV EBX, DWORD PTR SS:[ESP+3Ch]
	MOV ESI, 0
	MOV EDI, 0
	SUB ESP, 50h
	
	
	ik_100011_effect_10_next_object:
	CMP BYTE PTR DS:[EBX+ESI+4h],0		; наличие объекта
	JE[ik_100011_effect_10_discrepancy]
	MOV EDX, DWORD PTR DS:[EBX+ESI*4+3ECh]
	MOV ECX, DWORD PTR DS:[EAX+364h]
	CMP DWORD PTR DS:[EDX+364h],ECX	; сравнение команды
	JE [ik_100011_effect_10_discrepancy]
	CMP DWORD PTR DS:[EDX+2FCh], 0h	; у объекта больше 0 хп
	JLE [ik_100011_effect_10_discrepancy]
	MOV ECX, DWORD PTR DS:[EDX+368h]
	CMP DWORD PTR DS:[ECX+6F8h],0	; объект является персонажем (type: 0)
	JNE [ik_100011_effect_10_discrepancy]
	MOV DWORD PTR SS:[ESP+EDI*4h], EDX
	INC EDI
	
	ik_100011_effect_10_discrepancy:
	INC ESI
	CMP ESI, 1000
	JL [ik_100011_effect_10_next_object]
	
	CMP EDI,0
	JLE [ik_100011_effect_10_exit]
	
	
	PUSH EAX
	PUSH ECX
	PUSH EDX
	
	PUSH EDI
	PUSH 0h
	CALL [random_func]
	
	MOV EDI, EDX
	
	ADD ESP, 8h
	
	POP EDX
	POP ECX
	POP EAX
	
	MOV EDX, DWORD PTR SS:[ESP+EDI*4h]
	MOV ECX, DWORD PTR DS:[EAX+198h]
	MOV EBX, DWORD PTR SS:[ESP+60h]
	
	FLD QWORD PTR DS:[EDX+58h]
	CMP BYTE PTR DS:[EAX+80h],0h
	JNE SHORT [ik_100011_effect_10_f1]
	ik_100011_effect_10_f0:
	FISUB DWORD PTR DS:[EBX+4h]
	JMP SHORT [ik_100011_effect_10_ff]
	ik_100011_effect_10_f1:
	FIADD DWORD PTR DS:[EBX+4h]
	ik_100011_effect_10_ff:
	FST QWORD PTR DS:[EAX+58h]
	FST QWORD PTR DS:[ECX+100h]
	FISTP DWORD PTR DS:[EAX+10h]
	FLD QWORD PTR DS:[EDX+60h]
	FST QWORD PTR DS:[EAX+60h]
	FST QWORD PTR DS:[ECX+108h]
	FISTP DWORD PTR DS:[EAX+14h]
	FLD QWORD PTR DS:[EDX+68h]
	FST QWORD PTR DS:[EAX+68h]
	FST QWORD PTR DS:[ECX+110h]
	FISTP DWORD PTR DS:[EAX+18h]
	
	FLD [number_zero]
	FST QWORD PTR DS:[EAX+2Ch]
	FST QWORD PTR DS:[EAX+30h]
	FST QWORD PTR DS:[EAX+38h]
	FST QWORD PTR DS:[EAX+40h]
	FST QWORD PTR DS:[EAX+48h]
	FSTP QWORD PTR DS:[EAX+50h]
	
	
ik_100011_effect_10_exit:
	ADD ESP, 50h
	POPAD
	
JMP [ik_100011_reset]
	
	
	
	
	
ik_100011_reset:
	MOV ECX, DWORD PTR DS:[EAX+198h]
	MOV DWORD PTR DS:[ECX+60h], 0h
ik_100011_end:
	JMP [ik_100012]
	
ik_100012:
	; РАЗВОРОТ
	;  Effects
	; 0 - чет ко влево
	; 1 - чет ко вправо
	; 2 - в прот ивоположную ст орону
	; 3 - в ст орону,в кот орую смот рит  владелец
	CMP ESI, 100012
	JNE [ik_100012_end]
	CMP DWORD PTR DS:[EAX+88h],0h
	JNE [ik_100012_end]
	
	CMP DWORD PTR DS:[EBX+2Ch],0h
	JE [ik_100012_left]
	CMP DWORD PTR DS:[EBX+2Ch],1h
	JE [ik_100012_right]
	CMP DWORD PTR DS:[EBX+2Ch],2h
	JE [ik_100012_mirror]
	CMP DWORD PTR DS:[EBX+2Ch],3h
	JE [ik_100012_owner]

ik_100012_left:
	MOV BYTE PTR DS:[EAX+80h],1h
	JMP [ik_100012_end]
ik_100012_right:
	MOV BYTE PTR DS:[EAX+80h],0h
	JMP [ik_100012_end]
ik_100012_mirror:
	CMP BYTE PTR DS:[EAX+80h],1h
	JE [ik_100012_right]
	CMP BYTE PTR DS:[EAX+80h],0h
	JE [ik_100012_left]
	JMP [ik_100012_end]
ik_100012_owner:
	MOV EDI, DWORD PTR DS:[EAX+354h]
	MOV EDX, DWORD PTR DS:[00458B00h]
	MOV ECX,DWORD PTR DS:[EDX+EDI*4h+3ECh]
	MOV DL, BYTE PTR DS:[ECX+80h]
	MOV BYTE PTR DS:[EAX+80h], DL
	JMP [ik_100012_end]
ik_100012_end:
	JMP [ik_100013]
	
ik_100013:
	; УПРАВЛЕНИЕ ПРОЗРАЧНОСТЬЮ
	; effect - какой процент  прозрачност и выдат ь объект у
	; arest - время в wait на изменение прозрачност и
	; vrest - время в wait для сохранения прозрачност и
	; fall - какое изначальное значение прозрачност и мгновенно выдат ь объект у
	CMP ESI, 100013
	JNE [ik_100013_end]
	CMP DWORD PTR DS:[EAX+88h],0h
	JNE [ik_100013_end]
	
	MOV ECX, DWORD PTR DS:[EAX+198h]
	
	CMP DWORD PTR DS:[EBX+1Ch], 0
	JLE [ik_100013_anim]
	FILD DWORD PTR DS:[EBX+1Ch]
	FMUL [opacity_procent]
	FRNDINT
	FISTP DWORD PTR DS:[ECX+6Ch]
	
ik_100013_anim:
	CMP DWORD PTR DS:[EBX+2Ch], 0
	JL [ik_100013_end]
	CMP DWORD PTR DS:[EBX+2Ch], 100
	JG [ik_100013_end]
	
	FILD DWORD PTR DS:[EBX+2Ch]
	FMUL [opacity_procent]
	FRNDINT
	FISTP DWORD PTR DS:[ECX+64h]
	
ik_100013_speed:
	MOV DWORD PTR DS:[ECX+68h], 1h
	CMP DWORD PTR DS:[EBX+20h], 0h
	JL [ik_100013_time]
	
	FILD DWORD PTR DS:[ECX+64h]
	FISUB DWORD PTR DS:[ECX+6Ch]
	FIDIV DWORD PTR DS:[EBX+20h]
	FRNDINT
	FABS
	FISTP DWORD PTR DS:[ECX+68h]
	
ik_100013_time:
	CMP DWORD PTR DS:[EBX+24h],1
	JL [ik_100013_end]
	MOV EDX, DWORD PTR DS:[EBX+24h]
	MOV DWORD PTR DS:[ECX+70h], EDX
	MOV EDX, DWORD PTR DS:[ECX+6Ch]
	MOV DWORD PTR DS:[ECX+74h],EDX
	
ik_100013_end:
	JMP [ik_100014]
	
ik_100014:
	; УПРАВЛЕНИЕ ОБЪЕКТАМИ
	; x - частота взаимодействия (аналог Y в Ik8)
	; w - радиус взаимодействия
	; effect:
	;	0 - только на объект ы, принадлижащие одному владельцу и имеющие т ребуемый ит р
	;	1 - на все объект ы, имеющие одну команду и т ребуемый ит р
	;	2 - на все вражеские объект ы на карт е, имеющие т ребуемый ит р
	;	3 - на все объект ы на карт е, имеющие т ребуемый ит р
	; dvx - кадр, в кот орый перейдёт  объект  с которым происходит  взаимодейст вие
	; dvy - кадр, в кот орый перейдёт  объект  который инициировал взаимодейст вие
	; vrest:
	;	0 - itr приёмник
	;	1 - itr раздат чик
	; arest:
	;	0 - все объект ы, подходящие под условия
	;	1 - ближайший к персонажу объект 
	
	CMP ESI, 100014
	JNE [ik_100014_remove]
	CMP DWORD PTR DS:[EBX+24h], 1h
	JNE [ik_100014_remove]
	
	CMP DWORD PTR DS:[EAX+88h],0
	JNE [ik_100014_no_wait_zero]
	
	MOV EDI, DWORD PTR DS:[EAX+198h]
	MOV DWORD PTR DS:[EDI+80h],-1h
	MOV DWORD PTR DS:[EDI+84h],0FFFFFFh

ik_100014_no_wait_zero:
	MOV EDI, 0h
	
ik_100014_object_cycle:
	; Проверка на наличие объекта и подключение к нему
	MOV EDX, DWORD PTR DS:[00458B00h]
	CMP BYTE PTR DS:[EDX+EDI+4h],0
	JE [ik_100014_itr_cycle_next]
	MOV ECX,DWORD PTR DS:[EDX+EDI*4h+3ECh]
	CMP EAX, ECX
	JE [ik_100014_itr_cycle_next]
	
	; проверка на команду (в зависимости от effect)
	CMP DWORD PTR DS:[EBX+2Ch], 0h
	JE [ik_100014_effect_0]
	CMP DWORD PTR DS:[EBX+2Ch], 1h
	JE [ik_100014_effect_1]
	CMP DWORD PTR DS:[EBX+2Ch], 2h
	JE [ik_100014_effect_2]
	CMP DWORD PTR DS:[EBX+2Ch], 3h
	JE [ik_100014_effect_3]
	
ik_100014_effect_0:
	MOV EDX, DWORD PTR DS:[EAX+354h]
	CMP DWORD PTR DS:[ECX+354h], EDX
	JNE [ik_100014_itr_cycle_next]
	JMP [ik_100014_object_itr_check]
	
ik_100014_effect_1:
	MOV EDX, DWORD PTR DS:[EAX+364h]
	CMP DWORD PTR DS:[ECX+364h], EDX
	JNE [ik_100014_itr_cycle_next]
	JMP [ik_100014_object_itr_check]
	
ik_100014_effect_2:
	MOV EDX, DWORD PTR DS:[EAX+364h]
	CMP DWORD PTR DS:[ECX+364h], EDX
	JE [ik_100014_itr_cycle_next]
	JMP [ik_100014_object_itr_check]
	
ik_100014_effect_3:
	JMP [ik_100014_object_itr_check]

ik_100014_object_itr_check:
	; ------------------------------------------------------------------------
	; Подключение к кадру объекта и проверка наличия itr'ов
	MOV EDX, DWORD PTR DS:[ECX+70h]
	IMUL EDX, EDX, 1B0h
	ADD EDX,DWORD PTR DS:[ECX+368h]
	MOV ECX, DWORD PTR DS:[EDX+958h]
	; -----------------------------------------------------------------------

ik_100014_itr_cycle:
	CMP ECX, 1
	JL [ik_100014_itr_cycle_next]
	DEC ECX
	PUSH ECX
	IMUL ECX, ECX, 70h
	ADD ECX, DWORD PTR DS:[EDX+960h]
	
ik_100014_start_processing:
	PUSH ECX
	PUSH EDX
	PUSH EDI
	
	CMP DWORD PTR DS:[ECX+0h], 100014
	JNE [ik_100014_end_processing]
	
	CMP DWORD PTR DS:[ECX+24h], 0
	JNE [ik_100014_end_processing]
	
	MOV EDX, DWORD PTR DS:[EBX+4h]
	CMP DWORD PTR DS:[ECX+4h],EDX
	JNE [ik_100014_end_processing]
	
	MOV EDX, DWORD PTR DS:[EBX+0Ch]
	CMP DWORD PTR DS:[ECX+0Ch], EDX
	JG [ik_100014_min_width]
	CMP DWORD PTR DS:[ECX+0Ch], 0h
	JE [ik_100014_min_width]
	MOV EDX, DWORD PTR DS:[ECX+0Ch]
ik_100014_min_width:
	PUSH EDX
	PUSH EBX
	MOV EBX, DWORD PTR DS:[00458B00h]
	MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
	POP EBX
	FLD QWORD PTR DS:[EAX+58h]
	FSUB QWORD PTR DS:[ECX+58h]
	FABS
	FISTP DWORD PTR SS:[ESP]
	
	POP ECX
	
	CMP EDX, 0h
	JE [ik_100014_no_width]
	CMP ECX, EDX
	JG [ik_100014_end_processing]
	
ik_100014_no_width:
	CMP DWORD PTR DS:[EBX+20h], 0h
	JE [ik_100014_success_width]
	MOV EDX, DWORD PTR DS:[EAX+198h]
	CMP DWORD PTR DS:[EDX+80h], -2h
	JE [ik_100014_end_processing]
	CMP DWORD PTR DS:[EDX+84h],ECX
	JL [ik_100014_end_processing]
	MOV DWORD PTR DS:[EDX+84h], ECX
	MOV DWORD PTR DS:[EDX+80h], EDI
	MOV ECX, DWORD PTR SS:[ESP+8h]
	MOV DWORD PTR DS:[EDX+88h], ECX
	JMP [ik_100014_end_processing]
	
ik_100014_success_width:
ik_100014_dvx_v1:
	CMP DWORD PTR DS:[EBX+14h], 0h
	JLE [ik_100014_dvx_v2]
	MOV EDX, DWORD PTR DS:[00458B00h]
	MOV ECX, DWORD PTR DS:[EDX+EDI*4h+3ECh]
	FLD DWORD PTR DS:[EBX+14h]
	FISTP DWORD PTR DS:[ECX+70h]
	MOV DWORD PTR DS:[ECX+88h],0h
	JMP [ik_100014_dvy_v1]
ik_100014_dvx_v2:
	MOV ECX, DWORD PTR SS:[ESP+8h]
	CMP DWORD PTR DS:[ECX+14h], 0h
	JLE [ik_100014_dvy_v1]
	MOV EDX, DWORD PTR DS:[00458B00h]
	MOV EDX, DWORD PTR DS:[EDX+EDI*4h+3ECh]
	FLD DWORD PTR DS:[ECX+14h]
	FISTP DWORD PTR DS:[EDX+70h]
	MOV DWORD PTR DS:[EDX+88h],0h
	JMP [ik_100014_dvy_v1]
	
ik_100014_dvy_v1:
	CMP DWORD PTR DS:[EBX+18h], 0h
	JLE [ik_100014_dvy_v2]
	FLD DWORD PTR DS:[EBX+18h]
	FISTP DWORD PTR DS:[EAX+70h]
	MOV DWORD PTR DS:[EAX+88h],0h
	JMP [ik_100014_end_processing]
ik_100014_dvy_v2:
	MOV ECX, DWORD PTR SS:[ESP+8h]
	CMP DWORD PTR DS:[ECX+18h], 0h
	JLE [ik_100014_end_processing]
	FLD DWORD PTR DS:[ECX+18h]
	FISTP DWORD PTR DS:[EAX+70h]
	MOV DWORD PTR DS:[EAX+88h],0h
	JMP [ik_100014_end_processing]
	
	
ik_100014_end_processing:
	POP EDI
	POP EDX
	POP ECX
	POP ECX
	JMP [ik_100014_itr_cycle]
	
ik_100014_itr_cycle_next:
	INC EDI
	CMP EDI, 1000
	JL [ik_100014_object_cycle]
	
	CMP DWORD PTR DS:[EBX+20h], 0h
	JE [ik_100014_itr_skip_arest]
	
	MOV EDX, DWORD PTR DS:[EAX+198h]
	MOV EDI, DWORD PTR DS:[EDX+80h]
	
	CMP EDI, 0h
	JL [ik_100014_itr_skip_arest]
	
	MOV DWORD PTR DS:[EDX+80h], -2h
	
	
ik_100014_dvx_v1_arest:
	CMP DWORD PTR DS:[EBX+14h], 0h
	JLE [ik_100014_dvx_v2_arest]
	MOV EDX, DWORD PTR DS:[00458B00h]
	MOV ECX, DWORD PTR DS:[EDX+EDI*4h+3ECh]
	FLD DWORD PTR DS:[EBX+14h]
	FISTP DWORD PTR DS:[ECX+70h]
	MOV DWORD PTR DS:[ECX+88h],0h
	JMP [ik_100014_dvy_v1_arest]
ik_100014_dvx_v2_arest:
	MOV EDX, DWORD PTR DS:[EAX+198h]
	MOV ECX, DWORD PTR DS:[EDX+88h]
	CMP DWORD PTR DS:[ECX+14h], 0h
	JLE [ik_100014_dvy_v1_arest]
	MOV EDX, DWORD PTR DS:[00458B00h]
	MOV EDX, DWORD PTR DS:[EDX+EDI*4h+3ECh]
	FLD DWORD PTR DS:[ECX+14h]
	FISTP DWORD PTR DS:[EDX+70h]
	MOV DWORD PTR DS:[EDX+88h],0h
	JMP [ik_100014_dvy_v1]
	
ik_100014_dvy_v1_arest:
	CMP DWORD PTR DS:[EBX+18h], 0h
	JLE [ik_100014_dvy_v2_arest]
	FLD DWORD PTR DS:[EBX+18h]
	FISTP DWORD PTR DS:[EAX+70h]
	MOV DWORD PTR DS:[EAX+88h],0h
	JMP [ik_100014_itr_skip_arest]
ik_100014_dvy_v2_arest:
	MOV EDX, DWORD PTR DS:[EAX+198h]
	MOV ECX, DWORD PTR DS:[EDX+88h]
	CMP DWORD PTR DS:[ECX+18h], 0h
	JLE [ik_100014_itr_skip_arest]
	FLD DWORD PTR DS:[ECX+18h]
	FISTP DWORD PTR DS:[EAX+70h]
	MOV DWORD PTR DS:[EAX+88h],0h
	JMP [ik_100014_itr_skip_arest]

ik_100014_itr_skip_arest:
	JMP [ik_100014_remove]
	
ik_100014_remove:
	JMP [ik_100015]
ik_100014_end:


ik_100015:
	; БАФФ НЕУЯЗВИМОСТИ
	; Arest - установить или прибавить время
	; Effect:
	; 1 - действует только в течении кадра
	; 2 - пауза действия
	CMP ESI, 100015
	JNE [ik_100015_remove]
	
	CMP DWORD PTR DS:[EBX+2Ch],0
	JE SHORT [ik_100015_passive]
	CMP DWORD PTR DS:[EBX+2Ch],1
	JE SHORT [ik_100015_static]
	CMP DWORD PTR DS:[EBX+2Ch],2
	JE [ik_100015_pause]
	JMP [ik_100015_remove]
	
ik_100015_static:
	MOV EDX, DWORD PTR DS:[EAX+198h]
	CMP DWORD PTR DS:[EDX+8Ch],2h
	JG [ik_100015_remove]
	MOV DWORD PTR DS:[EDX+8Ch],2h
	JMP [ik_100015_remove]
	
ik_100015_passive:
	CMP DWORD PTR DS:[EAX+88h],0h
	JNE [ik_100015_remove]

	MOV EDX, DWORD PTR DS:[EAX+198h]
	MOV ECX, DWORD PTR DS:[EBX+20h]
	
	CMP ECX, 0
	JE SHORT [ik_100015_zero]
	CMP DWORD PTR DS:[EDX+8Ch],ECX
	JG [ik_100015_remove]
	MOV DWORD PTR DS:[EDX+8Ch],ECX
	JMP[ik_100015_remove]
	
	ik_100015_zero:
	MOV DWORD PTR DS:[EDX+8Ch],ECX
	JMP[ik_100015_remove]
	
ik_100015_pause:
	MOV EDX, DWORD PTR DS:[EAX+198h]
	
	CMP DWORD PTR DS:[EDX+8Ch],0
	JL [ik_100015_pause_addtime]
	MOV ECX, DWORD PTR DS:[EDX+8Ch]
	MOV DWORD PTR DS:[EDX+90h], ECX
ik_100015_pause_addtime:
	MOV ECX, DWORD PTR DS:[EBX+20h]
	ADD ECX, 1h
	NEG ECX
	MOV DWORD PTR DS:[EDX+8Ch], ECX
	
ik_100015_remove:
	JMP [ik_100016]
ik_100015_end:


ik_100016:
	; СКРЫТИЕ ТЕНИ И ИМЕНИ, ВЫБОР ТИПА ТЕНИ
	; Effect:
	; 0 - тень и имя отображаются нормально
	; 1 - тень скрыта, имя отображается
	; 2 - тень и имя скрыты
	
	CMP ESI, 100016
	JNE [ik_100016_remove]
	
	MOV EDX, DWORD PTR DS:[EAX+198h]
	MOV ECX, DWORD PTR DS:[EBX+2Ch]
	MOV DWORD PTR DS:[EDX+94h], ECX
	JMP SHORT [ik_100016_remove]
	
ik_100016_remove:
	JMP [ik_100017]
ik_100016_end:
	
ik_100017:
	; Шанс перехода в указанный кадр
	;  x - "частота" работы, для использования нескольких подобных функций в одном персонаже (максимум 8), если -1, работает просто как рандом
	;  dvx - кадр для перехода
	;  arest - шанс перехода в %
	;  vrest - количество пропусков проверки (откат возможности срабатывания). Если -1, условие сработает единоразово
	CMP ESI, 100017
	JNE [ik_100017_remove]
	CMP DWORD PTR DS:[EAX+88h],0h
	JNE SHORT [ik_100017_remove]
	MOV EDX, DWORD PTR DS:[EAX+198h]
	
	MOV EDI, DWORD PTR DS:[EBX+4h]
	CMP EDI, 0
	JL SHORT [ik_100017_no_timer]
	CMP EDI, 7
	JGE SHORT [ik_100017_no_timer]
	
	
	CMP DWORD PTR DS:[EDX+EDI*4+0A0h],0h
	JL SHORT [ik_100017_remove]
	CMP DWORD PTR DS:[EDX+EDI*4+0A0h],0h
	JG SHORT [ik_100017_timer]
	
ik_100017_no_timer:
	
	CMP DWORD PTR DS:[EBX+14h],0h
	JE SHORT [ik_100017_timer_setup]
	
	PUSH EAX
	PUSH ECX
	PUSH EDX
	
	PUSH 100
	PUSH 0h
	CALL [random_func]
	
	MOV EDI, EDX
	
	ADD ESP, 8h
	
	POP EDX
	POP ECX
	POP EAX
	
	CMP DWORD PTR DS:[EBX+20h],EDI
	JL SHORT [ik_100017_remove]
	
	FLD DWORD PTR DS:[EBX+14h]
	FISTP DWORD PTR DS:[EAX+70h]
	MOV DWORD PTR DS:[EAX+88h],0h
	
ik_100017_timer_setup:
	MOV EDI, DWORD PTR DS:[EBX+4h]
	CMP EDI, 0
	JL SHORT [ik_100017_remove]
	CMP EDI, 7
	JGE SHORT [ik_100017_remove]
	
	MOV ECX, DWORD PTR DS:[EBX+24h]
	MOV DWORD PTR DS:[EDX+EDI*4+0A0h],ECX
	JMP SHORT [ik_100017_remove]
ik_100017_timer:
	DEC DWORD PTR DS:[EDX+EDI*4+0A0h]
ik_100017_remove:
	JMP [ik_100018]
ik_100017_end:


ik_100018:
	; Переходы в определённые кадры при нажатии клавиш
	; Effects:
	; 0 - нажатие
	; 1 - двойное нажатие
	; dvx - кадр, в который будет совершен переход
	; injury - мана, требуемая на переход
	; Arests:
	; 0 - нажатие любой клавиши
	; 1 - нажатие вверх
	; 2 - нажатие вниз
	; 3 - нажатие строго влево
	; 4 - нажатие строго вправо
	; 5 - нажатие удара
	; 6 - нажатие прыжка
	; 7 - нажатие защиты
	; 8 - нажатие "вперед"
	; 9 - нажатие "назад"
	
	CMP ESI, 100018
	JNE [ik_100018_remove]
	MOV EDX, DWORD PTR DS:[EAX+198h]
	
	MOV ECX, DWORD PTR DS:[EBX+44h]
	CMP DWORD PTR DS:[EAX+308h],ECX
	JL [ik_100018_remove]
	
	
	ik_100018_arest_0_up:
	CMP DWORD PTR DS:[EBX+20h],0
	JNE[ik_100018_arest_1_up]
	
	CMP BYTE PTR DS:[EAX+0BEh],5
	JGE [ik_100018_dvx_goto]
	CMP BYTE PTR DS:[EAX+0BFh],5
	JGE [ik_100018_dvx_goto]
	CMP BYTE PTR DS:[EAX+0C0h],5
	JGE [ik_100018_dvx_goto]
	CMP BYTE PTR DS:[EAX+0C2h],5
	JGE [ik_100018_dvx_goto]
	CMP BYTE PTR DS:[EAX+0C3h],5
	JGE [ik_100018_dvx_goto]
	CMP BYTE PTR DS:[EAX+0C4h],5
	JGE [ik_100018_dvx_goto]
	CMP BYTE PTR DS:[EAX+0C5h],5
	JGE [ik_100018_dvx_goto]
	JMP[ik_100018_remove]	
	
	
	ik_100018_arest_1_up:
	CMP DWORD PTR DS:[EBX+20h],1
	JNE[ik_100018_arest_2_down]
	CMP BYTE PTR DS:[EAX+0C4h],5
	JL[ik_100018_remove]
	CMP DWORD PTR DS:[EBX+2Ch],0
	JE [ik_100018_dvx_goto]
	CMP DWORD PTR DS:[EBX+2Ch],1
	JNE [ik_100018_remove]
	CMP BYTE PTR DS:[EDX+0F0h],0
	JLE[ik_100018_arest_1_setTimer]
	JMP[ik_100018_dvx_goto]
	ik_100018_arest_1_setTimer:
	MOV BYTE PTR DS:[EDX+0F0h],10
	JMP[ik_100018_remove]
	
	
	
	ik_100018_arest_2_down:
	CMP DWORD PTR DS:[EBX+20h],2
	JNE[ik_100018_arest_3_left]
	CMP BYTE PTR DS:[EAX+0C5h],5
	JL[ik_100018_remove]
	CMP DWORD PTR DS:[EBX+2Ch],0
	JE [ik_100018_dvx_goto]
	CMP DWORD PTR DS:[EBX+2Ch],1
	JNE [ik_100018_remove]
	CMP BYTE PTR DS:[EDX+0F1h],0
	JLE[ik_100018_arest_2_setTimer]
	JMP[ik_100018_dvx_goto]
	ik_100018_arest_2_setTimer:
	MOV BYTE PTR DS:[EDX+0F1h],10
	JMP[ik_100018_remove]
	
	
	ik_100018_arest_3_left:
	CMP DWORD PTR DS:[EBX+20h],3
	JNE[ik_100018_arest_4_right]
	CMP BYTE PTR DS:[EAX+0C3h],5
	JL [ik_100018_remove]
	CMP DWORD PTR DS:[EBX+2Ch],0
	JE [ik_100018_dvx_goto]
	CMP DWORD PTR DS:[EBX+2Ch],1
	JNE [ik_100018_remove]
	CMP BYTE PTR DS:[EDX+0F2h],0
	JLE[ik_100018_arest_3_setTimer]
	JMP[ik_100018_dvx_goto]
	ik_100018_arest_3_setTimer:
	MOV BYTE PTR DS:[EDX+0F2h],10
	JMP[ik_100018_remove]
	
	
	
	
	
	ik_100018_arest_4_right:
	CMP DWORD PTR DS:[EBX+20h],4
	JNE[ik_100018_arest_5_attack]
	CMP BYTE PTR DS:[EAX+0C2h],5
	JL[ik_100018_remove]
	CMP DWORD PTR DS:[EBX+2Ch],0
	JE [ik_100018_dvx_goto]
	CMP DWORD PTR DS:[EBX+2Ch],1
	JNE [ik_100018_remove]
	CMP BYTE PTR DS:[EDX+0F3h],0
	JLE[ik_100018_arest_4_setTimer]
	JMP[ik_100018_dvx_goto]
	ik_100018_arest_4_setTimer:
	MOV BYTE PTR DS:[EDX+0F3h],10
	JMP[ik_100018_remove]
	
	
	ik_100018_arest_5_attack:
	CMP DWORD PTR DS:[EBX+20h],5
	JNE[ik_100018_arest_6_jump]
	CMP BYTE PTR DS:[EAX+0BEh],5
	JL[ik_100018_remove]
	CMP DWORD PTR DS:[EBX+2Ch],0
	JE [ik_100018_dvx_goto]
	CMP DWORD PTR DS:[EBX+2Ch],1
	JNE [ik_100018_remove]
	CMP BYTE PTR DS:[EDX+0F4h],0
	JLE[ik_100018_arest_5_setTimer]
	JMP[ik_100018_dvx_goto]
	ik_100018_arest_5_setTimer:
	MOV BYTE PTR DS:[EDX+0F4h],10
	JMP[ik_100018_remove]
	
	
	ik_100018_arest_6_jump:
	CMP DWORD PTR DS:[EBX+20h],6
	JNE[ik_100018_arest_7_defend]
	CMP BYTE PTR DS:[EAX+0BFh],5
	JL[ik_100018_remove]
	CMP DWORD PTR DS:[EBX+2Ch],0
	JE [ik_100018_dvx_goto]
	CMP DWORD PTR DS:[EBX+2Ch],1
	JNE [ik_100018_remove]
	CMP BYTE PTR DS:[EDX+0F5h],0
	JLE[ik_100018_arest_6_setTimer]
	JMP[ik_100018_dvx_goto]
	ik_100018_arest_6_setTimer:
	MOV BYTE PTR DS:[EDX+0F5h],10
	JMP[ik_100018_remove]
	
	ik_100018_arest_7_defend:
	CMP DWORD PTR DS:[EBX+20h],7
	JNE[ik_100018_arest_8_forvard]
	CMP BYTE PTR DS:[EAX+0C0h],5
	JL[ik_100018_remove]
	CMP DWORD PTR DS:[EBX+2Ch],0
	JE [ik_100018_dvx_goto]
	CMP DWORD PTR DS:[EBX+2Ch],1
	JNE [ik_100018_remove]
	CMP BYTE PTR DS:[EDX+0F6h],0
	JLE[ik_100018_arest_7_setTimer]
	JMP[ik_100018_dvx_goto]
	ik_100018_arest_7_setTimer:
	MOV BYTE PTR DS:[EDX+0F6h],10
	JMP[ik_100018_remove]
	
	
	
	
	ik_100018_arest_8_forvard:
	CMP DWORD PTR DS:[EBX+20h],8
	JNE[ik_100018_arest_9_back]
	CMP BYTE PTR DS:[EAX+080h],0
	JE [ik_100018_arest_8_forvard_right]
	CMP BYTE PTR DS:[EAX+0C3h],5
	JL[ik_100018_remove]
	CMP DWORD PTR DS:[EBX+2Ch],0
	JE [ik_100018_dvx_goto]
	CMP DWORD PTR DS:[EBX+2Ch],1
	JNE [ik_100018_remove]
	CMP BYTE PTR DS:[EDX+0F2h],0
	JLE[ik_100018_arest_8_setTimer1]
	JMP[ik_100018_dvx_goto]
	ik_100018_arest_8_setTimer1:
	MOV BYTE PTR DS:[EDX+0F2h],10
	JMP[ik_100018_remove]
	ik_100018_arest_8_forvard_right:
	CMP BYTE PTR DS:[EAX+0C2h],5
	JL[ik_100018_remove]
	CMP DWORD PTR DS:[EBX+2Ch],0
	JE [ik_100018_dvx_goto]
	CMP DWORD PTR DS:[EBX+2Ch],1
	JNE [ik_100018_remove]
	CMP BYTE PTR DS:[EDX+0F3h],0
	JLE[ik_100018_arest_8_setTimer2]
	JMP[ik_100018_dvx_goto]
	ik_100018_arest_8_setTimer2:
	MOV BYTE PTR DS:[EDX+0F3h],10
	JMP[ik_100018_remove]
	
	
	ik_100018_arest_9_back:
	CMP DWORD PTR DS:[EBX+20h],9
	JNE[ik_100018_remove]
	CMP BYTE PTR DS:[EAX+080h],0
	JE [ik_100018_arest_9_back_right]
	CMP BYTE PTR DS:[EAX+0C2h],5
	JL[ik_100018_remove]
	CMP DWORD PTR DS:[EBX+2Ch],0
	JE [ik_100018_dvx_goto]
	CMP DWORD PTR DS:[EBX+2Ch],1
	JNE [ik_100018_remove]
	CMP BYTE PTR DS:[EDX+0F3h],0
	JLE[ik_100018_arest_9_setTimer1]
	JMP[ik_100018_dvx_goto]
	ik_100018_arest_9_setTimer1:
	MOV BYTE PTR DS:[EDX+0F3h],10
	JMP[ik_100018_remove]
	ik_100018_arest_9_back_right:
	CMP BYTE PTR DS:[EAX+0C3h],5
	JL[ik_100018_remove]
	CMP DWORD PTR DS:[EBX+2Ch],0
	JE [ik_100018_dvx_goto]
	CMP DWORD PTR DS:[EBX+2Ch],1
	JNE [ik_100018_remove]
	CMP BYTE PTR DS:[EDX+0F2h],0
	JLE[ik_100018_arest_9_setTimer2]
	JMP[ik_100018_dvx_goto]
	ik_100018_arest_9_setTimer2:
	MOV BYTE PTR DS:[EDX+0F2h],10
	JMP[ik_100018_remove]
	
	
	ik_100018_dvx_goto:
	SUB DWORD PTR DS:[EAX+308h],ECX
	ADD DWORD PTR DS:[EAX+350h], ECX
	FLD DWORD PTR DS:[EBX+14h]
	FISTP DWORD PTR DS:[EAX+70h]
	MOV DWORD PTR DS:[EAX+88h],0h
	JMP[ik_100018_remove]
	
ik_100018_remove:
	JMP [ik_100019]
ik_100018_end:

ik_100019:
	; Задача конечного кадра и переход в заданный кадр
	; arest - задать кадр
	; arest: 0 - перейти в заданный кадр
	; arest: -1 - сбросить заданный кадр
	CMP ESI, 100019
	JNE SHORT [ik_100019_remove]
	MOV ECX, DWORD PTR SS:[ESP+4h]
	MOV EDX, DWORD PTR SS:[ESP+8h]
	MOV EDI, DWORD PTR DS:[EDX+ECX+83Ch]
	MOV EDX, DWORD PTR DS:[EAX+198h]
	
	CMP DWORD PTR DS:[EBX+20h], 0h
	JL SHORT [ik_100019_reset]
	JE SHORT [ik_100019_goto]
	JG SHORT [ik_100019_set]
	
	ik_100019_reset:
	MOV DWORD PTR DS:[EDX+4Ch],0h
	JMP SHORT [ik_100019_remove]
	
	ik_100019_goto:
	CMP DWORD PTR DS:[EAX+88h],EDI
	JL SHORT [ik_100019_remove]
	CMP DWORD PTR DS:[EDX+4Ch],0h
	JLE SHORT [ik_100019_remove]
	MOV ECX, DWORD PTR DS:[EDX+4Ch]
	MOV DWORD PTR DS:[EAX+70h],ECX
	MOV DWORD PTR DS:[EAX+88h],0h
	MOV DWORD PTR DS:[EDX+4Ch],0h
	JMP SHORT [ik_100019_remove]
	
	ik_100019_set:
	MOV ECX, DWORD PTR DS:[EBX+20h]
	MOV DWORD PTR DS:[EDX+4Ch],ECX
	JMP SHORT [ik_100019_remove]
	
	
ik_100019_remove:
	JMP [ik_100020]
ik_100019_end:


ik_100020:
	; Проверка объекта на движение и переход в определённый кадр
	; dvx - кадр, в который перейдёт объект
	; effects:
	; 0 - Объект перейдёт в указанный кадр при движении
	; 1 - Объект перейдёт в указанный кадр при отсутсвии движения
	CMP ESI, 100020
	JNE SHORT [ik_100020_remove]
	MOV ECX, DWORD PTR SS:[ESP+4h]
	MOV EDX, DWORD PTR SS:[ESP+8h]
	MOV EDI, DWORD PTR DS:[EDX+ECX+83Ch]
	CMP DWORD PTR DS:[EAX+88h],EDI
	JL SHORT [ik_100020_remove]
	
ik_100020_effect1:
	CMP DWORD PTR DS:[EBX+2Ch],0
	JNE [ik_100020_effect2]
	
	CMP DWORD PTR DS:[EAX+40h],0h
	JE [ik_100020_remove]
	
	FLD DWORD PTR DS:[EBX+14h]
	FISTP DWORD PTR DS:[EAX+70h]
	MOV DWORD PTR DS:[EAX+88h],0h
	
	JMP [ik_100020_remove]
	
	
ik_100020_effect2:
	CMP DWORD PTR DS:[EBX+2Ch],1
	JNE [ik_100020_remove]
	
	CMP DWORD PTR DS:[EAX+40h],0h
	JNE [ik_100020_remove]
	
	FLD DWORD PTR DS:[EBX+14h]
	FISTP DWORD PTR DS:[EAX+70h]
	MOV DWORD PTR DS:[EAX+88h],0h
	
	JMP [ik_100020_remove]
	
	
ik_100020_remove:
	JMP [ik_100021]
ik_100020_end:


ik_100021:
	; Переход и проверка на наличие рядом с объектом других объектов или персонажей
	; dvx - кадр, в который перейдёт объект "сканер"
	; dvy - кадр, в который перейдут объекты, попавшие в область действия
	; x, y, z - область проверки
	; 
	; effects:
	; 0 - Если рядом 
	; 1 - Объект перейдёт в указанный кадр при отсутсвии движения
	CMP ESI, 100021
	JNE SHORT [ik_100021_remove]
	MOV ECX, DWORD PTR SS:[ESP+4h]
	MOV EDX, DWORD PTR SS:[ESP+8h]
	
ik_100021_remove:
	JMP [ik_end]
ik_100021_end:
	
	
	
	
ik_end:
	POP EDI
	POP EDX
	POP ECX
	
	JMP [Itr_check_cycle]
	
itr_check_end:
	POPAD
	
	MOV EAX,DWORD PTR DS:[EDX+ECX+838h]
	JMP[Itr_kind_checker_back]
	
Itr_checker endp
