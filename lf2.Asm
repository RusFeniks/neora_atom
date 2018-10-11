.386
.Model Flat, StdCall
OPTION CASEMAP :NONE

include C:\masm32\include\windows.inc
include C:\masm32\include\masm32.inc
include C:\masm32\include\user32.inc
include C:\masm32\include\kernel32.inc
include C:\masm32\include\debug.inc
includelib C:\masm32\lib\masm32.lib
includelib C:\masm32\lib\user32.lib
includelib C:\masm32\lib\kernel32.lib
includelib C:\masm32\lib\debug.lib

include addresses.inc
include lf2.inc
include generic.inc
include itreff.inc
include itrkind.inc
include states.inc
include ai.inc
include window.inc
include replay.inc
include battle.inc
include regen.inc
include spawner.inc
include cursor.inc
include external.inc
include UI.inc
include time.inc
include hack.inc
include f_func.inc
include f_func2.inc
include f_states.inc
include f_itrs.inc
include f_itr_states.inc
include f_time.inc
include f_standarts.inc
include f_loading.inc

include z_addons\VerticalScroll.inc
include z_addons\Opointer.inc
include z_addons\sparki.inc

.data
memAlloc dd ?
solAlloc dd ?
; as long as you're using Neora you're agreed and accept rule to keep this string as it is 
copycat  db "Neora Engine by Archer-Dante",00
	
	GameName		db "Naruto: Operation Red Moon",00 ; Name of the Game Window
	Unlock_Teams	dd 1		; Allows to change Team in Stage Mode. (1 - on, 0 - off)
	F7_for_dead		dd 1		; Allows to use F7 after round ends. (1 - on, 0 - off)
.data?


.code
DllEntryPoint proc hInstDLL:DWORD, reason:DWORD, unused:DWORD

	mov eax,reason
	.if eax == DLL_PROCESS_ATTACH											; Called when our dll loaded
		invoke VirtualAlloc, NULL, 4000, MEM_COMMIT,PAGE_READWRITE
        mov memAlloc,eax  
        invoke VirtualAlloc, NULL, 20000, MEM_COMMIT,PAGE_READWRITE
        mov solAlloc,eax       
		call DLLStartup														; Memory patches and jmp patches
	.endif
	ret

DllEntryPoint endp

DLLStartup proc

	;===============Random stuff(generic.inc)===========
	invoke JmpPatch, 004201E3h, addr Max_HP	      ;Max_HP_of_opointed_objectsT0
	;invoke JmpPatch, 00420272h, addr opoint_kind
	invoke JmpPatch, 0042EE17h, addr Shaker	      ;Shake_It_Baby!
	;===================================================

	;=============itr kind(itrkind.inc)=================
	invoke JmpPatch, 0042FFF8h, addr itr_kind8
	invoke JmpPatch, 00417526h, addr itr_kind8_types
	;===================================================

	;=============itr effects(itreff.inc)===============
	invoke JmpPatch, 0042F54Ah, addr itr_effect_1xxx_to_9xxx 
	invoke JmpPatch, 0042E90Fh, addr effect50
	;===================================================

	;=================states(states.inc)================
	invoke JmpPatch, 0041F656h, addr State8xxx ; 140-frameless fix (+id list for +140)
	invoke JmpPatch, 0041F603h, addr StateMore ; Set X-coord, Y-coord, Z-coord and more
	invoke JmpPatch, 0041334Ah, addr StateTurn3x ; Turning State 30, 31, 32
	invoke JmpPatch, 0042EC9Eh, addr State9xxx ; Go to XXX Frame if hit something. XXX from 0 to 799

	;invoke WriteMem, 0040EC13h, addr doubleNOP,2 ; Keep it, Can be usuful
	;invoke WriteMem, 0040EC15h, addr oneNOP,1 ; Keep it, Can be usuful

	;invoke JmpPatch, 004177B9h, addr Hit_teammates
	;==================================================
	
	;===============Window Properities(window.inc)=========
	invoke JmpPatch, 00401B3Ch, addr Window_Size_2	 	
	invoke JmpPatch, 00401007h, addr Window_Size_3
	invoke JmpPatch, 00401050h, addr Window_Size_4 
	invoke JmpPatch, 0042386Dh, addr Window_Size_5
	invoke JmpPatch, 0043F03Dh, addr Window_Size_6
	invoke JmpPatch, 0043F08Bh, addr Window_Size_7
	invoke JmpPatch, 0041A0AEh, addr Window_Size   
	invoke JmpPatch, 0041A1DBh, addr Window_Size_8 
	invoke JmpPatch, 0041A8FEh, addr Window_Size_9 
	invoke JmpPatch, 0041BB87h, addr Window_Size_10 
	invoke JmpPatch, 0041BC32h, addr Window_Size_11 
	invoke JmpPatch, 0042A1BFh, addr Window_Size_12 		
	invoke JmpPatch, 00437B62h, addr Window_Size_13 
	invoke JmpPatch, 004384C4h, addr Window_Size_14 
	invoke JmpPatch, 0043852Ch, addr Window_Size_15
	invoke JmpPatch, 00401B85h, addr Application_Name
	invoke WriteMem, 00401B9Ch, addr oneNOP,7 ; Annoying Karter
	;===================================================

	;=============== Replays (replay.inc)===============
	invoke JmpPatch, 004326D6h, addr comparator	 	
	;===================================================	
	
	;=============== Battle Mode (battle.inc)===========
	invoke JmpPatch, 0043947Fh, addr defence
	;===================================================	
	
	;=============== Regen (regen.inc)==================
	invoke JmpPatch, 0041FAE5h, addr mana_speed	 	
	invoke JmpPatch, 0041F9E2h, addr hp_speed
	;===================================================	

	;=============== Spawner (regen.inc)================
	invoke JmpPatch, 0042D68Fh, addr SpawnerBoth1
	invoke JmpPatch, 0042D4C0h, addr SpawnerPlayer1
	invoke JmpPatch, 0042D3ADh, addr SpawnerCom1
	invoke JmpPatch, 00437664h, addr SpawnerComStages1	
	;===================================================	
	
	;=============== Cursor (cursor.inc)=================
	invoke JmpPatch, 00425EB1h, addr CursorFix1
	invoke JmpPatch, 0042873Eh, addr CursorFix2
	invoke JmpPatch, 0043B4ECh, addr CursorFix3
	invoke JmpPatch, 0043D048h, addr CursorFix4
	;===================================================
	
	;=============== External (External.inc)=================
	invoke JmpPatch, 00426EBEh, addr CS2img
	invoke JmpPatch, 00426ECDh, addr CS3img
	invoke JmpPatch, 00426EDCh, addr CS4img
	invoke JmpPatch, 00426EEBh, addr CS5img
	invoke JmpPatch, 00426EFAh, addr CS6img
	invoke JmpPatch, 00426F09h, addr FRAMEimg
	invoke JmpPatch, 00426F18h, addr WORDS0img
	invoke JmpPatch, 00426F27h, addr WORDS1img
	invoke JmpPatch, 00426F36h, addr WORDS2img
	invoke JmpPatch, 00426F45h, addr WORDS3img
	invoke JmpPatch, 00426F54h, addr WORDS4img
	invoke JmpPatch, 00426F63h, addr WORDS5img
	invoke JmpPatch, 00425F3Fh, addr MENU_CLIPimg
	invoke JmpPatch, 00425F53h, addr MENU_CLIP2img
	invoke JmpPatch, 00425F62h, addr MENU_CLIP3img
	invoke JmpPatch, 00425F71h, addr MENU_CLIP4img
	invoke JmpPatch, 00425F80h, addr MENU_CLIP5img
	invoke JmpPatch, 00425F8Fh, addr MENU_CLIP6img
	invoke JmpPatch, 00425FADh, addr ENDINGimg
	invoke JmpPatch, 004273BCh, addr PAUSEimg
	invoke JmpPatch, 004273D0h, addr DEMOimg
	invoke JmpPatch, 004273DFh, addr SCORE_BOARD1img
	invoke JmpPatch, 004273EEh, addr SCORE_BOARD2img
	invoke JmpPatch, 004273FDh, addr SCORE_BOARD3img
	invoke JmpPatch, 0042740Ch, addr SCORE_BOARD4img
	invoke JmpPatch, 0042741Bh, addr WIN_ALIVEimg
	invoke JmpPatch, 0042742Ah, addr WIN_DEADimg
	invoke JmpPatch, 00427439h, addr LOSE_DEADimg
	invoke JmpPatch, 0040C2CDh, addr CHARMENUimg
	invoke JmpPatch, 0040C2DCh, addr CM1img
	invoke JmpPatch, 0040C2EBh, addr CM2img
	invoke JmpPatch, 0040C2FAh, addr CM3img
	invoke JmpPatch, 0040C309h, addr CM4img
	invoke JmpPatch, 0040C318h, addr CM5img
	invoke JmpPatch, 0040C327h, addr CMAimg
	invoke JmpPatch, 0040C336h, addr CMA2img
	invoke JmpPatch, 0040C345h, addr CMC_img
	invoke JmpPatch, 0040C354h, addr RFACEimg
	;===================================================

	;=============== UI Manipulation (UI.inc)===========
	
	invoke WriteMem, 0041F523h, addr numbersFix,1 ; fix debug info in corner
	invoke WriteMem, 0041AF3Ah, addr opacity,2 ; Frame
	invoke WriteMem, 0042A5D2h, addr opacity,2 ; RFace
	invoke WriteMem, 0042A53Fh, addr opacity,2 ; Character Faces
	invoke WriteMem, 0042BE93h, addr opacity,2 ; ???
	invoke WriteMem, 0042BDEBh, addr opacity,2 ; ???
	invoke WriteMem, 0042AFA2h, addr opacity,2 ; ???
	invoke WriteMem, 0042BB5Dh, addr opacity,2 ; ???
	invoke WriteMem, 0041AF85h, addr opacity,2 ; small icons in status-bar
	invoke WriteMem, 0042A415h, addr opacity,2 ; CMA.png + CMA2.png
	invoke WriteMem, 0042A444h, addr opacity,2 ; ???
	invoke WriteMem, 0042AAA0h, addr opacity,2 ; ???
	invoke WriteMem, 0042AB09h, addr opacity,2 ; RFace second phase
	;===================================================
	invoke WriteMem, 0042A1E1h, addr ResetCoord,2	; Activate by your choise,
	invoke WriteMem, 0042A1E3h, addr ResetCoord,2  ; resets CHARMENU coords to zero
	;===================================================

	;============== Time Tracing (time.inc) ============
	invoke JmpPatch, 0041310Dh, addr TimeStop 			; TimeStop Engine
	invoke JmpPatch, 0041DD4Ah, addr TS_substactor		; part of TS Engine
	
	invoke JmpPatch, 0043D154h, addr TS_menu_fix        ; resets TS while game in menu
	invoke JmpPatch, 00421191h, addr TS_fire_disable	; disables flame particles while TimeStop
	invoke JmpPatch, 00407DCAh, addr TS_JanC1_disable	; removes Tail from Jan Chase while TS
	invoke JmpPatch, 0040DA72h, addr TS_Fa_disable_1	; fixes HP substract from Balls while TS
	invoke JmpPatch, 00408378h, addr TS_Fa_disable_2	; fixes HP substract from Balls while TS
	invoke JmpPatch, 0041A12Fh, addr TS_bg_stop_1 			; stops HK Coliseum BG
	invoke WriteMem, 0041A134h, addr oneNOP,4 				; fix code
	invoke JmpPatch, 0041A1BDh, addr TS_bg_stop_2 			; stops all another BGs
	;===================================================
	
	
	;================== ВСЁ, СВЯЗАННОЕ С ЗАГРУЗКОЙ И ВЫДЕЛЕНИЕМ ПАМЯТИ =================
	
	; f_loading.inc - файл с моими модификациями
	
	
	invoke JmpPatch, 0042D6D3h, addr initialization_obj1	; мой врыв в иницилизацию объекта
	invoke JmpPatch, 0042715Ch, addr initialization_obj2		; мой врыв в иницилизацию объекта
	invoke JmpPatch, 0042410Ah, addr initialization_obj3	; мой врыв в иницилизацию объекта
	invoke JmpPatch, 0042D42Dh, addr initialization_obj4	; мой врыв в иницилизацию объекта
	invoke JmpPatch, 0041FD9Ch, addr initialization_obj5	; мой врыв в иницилизацию объекта (opoint)
	invoke JmpPatch, 0042D31Bh, addr initialization_obj6	; мой врыв в иницилизацию объекта
	invoke JmpPatch, 00420CD3h, addr initialization_obj7	; мой врыв в иницилизацию объекта
	invoke JmpPatch, 00446501h, addr initialization_obj8		; мой врыв в иницилизацию объекта (mpoint)
	invoke JmpPatch, 0041F148h, addr initialization_obj9		; мой врыв в иницилизацию объекта (вроде оружие с неба)
	invoke JmpPatch, 004375C3h, addr initialization_obj10	; мой врыв в иницилизацию объекта (стейдж)
	
	
	; Врывы используются, чтобы сохранить id объекта для последующего использования в загрузке
	
	invoke JmpPatch, 00402442h, addr write_pointer_to_char	; подключение к иницилизации объекта для выделения памяти под мои функции
	
	
	invoke JmpPatch, 0040F2D3h, addr loading_dat_file		; подключение к процессу загрузки dat файла (шапка персонажа)
	invoke JmpPatch, 00410537h, addr loading_frame		; подключение к процессу загрузки фрейма
	
	
	;=======================================================================
	
	
	
	
	invoke JmpPatch, 004274ABh, addr load_img			   ; подгрузка картинки
	invoke JmpPatch, 0041A66Ch, addr gui_object			   ; отрисовка элементов на персонаже
	invoke JmpPatch, 0041A71Dh, addr green_shadow		   ; зелёная тень зелёной команде
	invoke JmpPatch, 0041F603h, addr my_states 			   ; мои стейты на основе 8ххх


	
	invoke JmpPatch, 0041F994h, addr my_effects 		   ; подключение к процессу регенерации здоровья
	invoke JmpPatch, 0043D12Dh, addr fps_change			   ; изменение фпс
	invoke JmpPatch, 0042E78Ch, addr mana_restore_attack   ; восстановление маны от урона
	invoke JmpPatch, 0042E6F6h, addr damage_modificators   ; модификаторы урона
	invoke JmpPatch, 0042E75Bh, addr attack_addons		   ; дополнения к механике атак
	invoke JmpPatch, 0041F9C3h, addr every_tick			   ; сюда игра попадает каждый свой тик(-так)
	invoke JmpPatch, 0041F9A1h, addr every_tick_type_fix   ; небольшой фикс для типа
	invoke JmpPatch, 0042F385h, addr object_leveling1	   ; залетаю в столкновение двух объектов (тип3)
	invoke JmpPatch, 0042F2DEh, addr object_leveling2	   ; залетаю в столкновение объекта с itr'ом игрока (тип 0)
	invoke JmpPatch, 0042ED0Eh, addr object_leveling3	   ; залетаю в столкновение объекта (тип 3, стейт 3000) с игроком или объектом
	invoke JmpPatch, 0042F1F7h, addr no_team_change_obj	   ; отключение смены команды объектам при их атаке
	invoke JmpPatch, 100011C9h, addr custom_delays	  	   ; управление задержками при атаках и получениях урона
	invoke JmpPatch, 0042F0BFh, addr no_facing_weapon	; отключение функции поворота оружия в сторону взгляда атакующего
	
	invoke JmpPatch, 0042A377h, addr join_nomi 			   ; выключение мигания надписи Join?
	invoke JmpPatch, 0042A62Ah, addr random_nomi 		   ; выключение мигания надписи Random
	invoke JmpPatch, 0042A5ADh, addr name_nomi 			   ; выключение мигания надписи Name
	invoke JmpPatch, 0042ADC8h, addr indep_nomi 		   ; выключение мигания надписи Independed
	invoke JmpPatch, 0042ABEBh, addr team1_1			   ; выключение мигания надписи Team1
	invoke JmpPatch, 0042AC62h, addr team2_1 			   ; выключение мигания надписи Team2
	invoke JmpPatch, 0042ACD9h, addr team3_1 			   ; выключение мигания надписи Team3
	invoke JmpPatch, 0042AD50h, addr team4_1  			   ; выключение мигания надписи Team4
	invoke JmpPatch, 0042C5C8h, addr indep2_nomi 		   ; выключение мигания надписи Independed
	invoke JmpPatch, 0042C662h, addr team1_2 			   ; выключение мигания надписи Team1
	invoke JmpPatch, 0042C6FCh, addr team2_2 			   ; выключение мигания надписи Team2
	invoke JmpPatch, 0042C796h, addr team3_2 			   ; выключение мигания надписи Team3
	invoke JmpPatch, 0042C830h, addr team4_2 			   ; выключение мигания надписи Team4
	invoke JmpPatch, 0042BEF0h, addr random2_nomi 		   ; выключение мигания надписи Random
	invoke JmpPatch, 0042BE52h, addr name2_nomi 		   ; выключение мигания надписи Name
	invoke JmpPatch, 004330ACh, addr Hum_Comp			   ; выключение мигания надписи Human? Computer?
	invoke JmpPatch, 00435169h, addr Hum_Comp2 			   ; выключение мигания надписи Human? Computer?
	invoke JmpPatch, 00434FCAh, addr random3_nomi 		   ; выключение мигания надписи Random
	invoke JmpPatch, 0043502Bh, addr name3_nomi 		   ; выключение мигания надписи Name
	invoke JmpPatch, 00432F04h, addr random4_nomi 		   ; выключение мигания надписи Random
	invoke JmpPatch, 00432F6Eh, addr name4_nomi 		   ; выключение мигания надписи Name
	invoke WriteMem, 0042D25Fh, addr map_random,3		; восстановление рандома карт
	
	invoke JmpPatch, 0041AF24h, addr New_mp_bar			   ; отрисовка дополнительных элементов интерфейса
	invoke WriteMem, 00448348h, addr gravity,8 			   ; изменение гравитации
	invoke JmpPatch, 0040DCDFh, addr custom_999_inAir 	   ; переход в 279 кадр при next: 999 в воздухе
	invoke JmpPatch, 00412C6Ah, addr NewMp1xxxyyy		   ; state: 1xxxyyy, работающий с новым видом энергии
	invoke JmpPatch, 004198D6h, addr innertion_save		   ; fall делающий атаку не действующей
	invoke JmpPatch, 00412C53h, addr StateZxxxyyy_check	   ; Проверка на наличие стейтов 1хххууу - 5хххууу при отнятии маны
	
	invoke JmpPatch, 0041D7DFh, addr Every1Tick_NotPlayer
	
	invoke JmpPatch, 0041F5DFh, addr Itr_checker			; Сист ема навешиваемых через itr kind ст ейт ов	
	invoke JmpPatch, 0041A6A0h, addr NoShadow_Itr		; Выключение тени с помощью ITRK100016
	invoke JmpPatch, 0041A824h, addr NoName_Itr			; Выключение имени с помощью ITRk 100016
	
	
	
	;====== Изменение стандартов (f_standarts.inc) =======
	
	
	invoke JmpPatch, 00413B61h, addr Rowing100108		; Проверка на наличие кадров Rowing у персонажа
	invoke JmpPatch, 004175BAh, addr Collision			; Момент взаимодействия bdy и itr элементов (проверка на команду)
	invoke JmpPatch, 00403386h, addr TpSub				; Выбор дистанции телепорта
	invoke JmpPatch, 0040338Eh, addr TpAdd
	invoke JmpPatch, 0041A882h, addr Clone_Name			; Клоны имеют имя игрока,вместо COM
	invoke JmpPatch, 00446520h, addr Mpoint_CloneFix		; Фикс бага китайца, где призываемый объект не является клоном
	invoke WriteMem, 0040DE12h, addr Fix_Stop_Running,3	; Фикс остановки при нажатии "назад" при зацикленном беге
	invoke JmpPatch, 00412CBBh, addr Wait_Reset			; сброс счетчика wait при переходе в кадр по hit_
	invoke JmpPatch, 0041AE45h, addr hitG_enert			; сохранение скорости движения объекта по оси x, при касании земли
	;invoke JmpPatch, 0041AE1Ch, addr hitG_state_fix		; отключение проверки на 3007 стейт при использовании hit_g в объектах
	invoke JmpPatch, 00446611h, addr mpoint_dvx_fix		; фикс dvx и facing в mpoint
	
	invoke JmpPatch, 0040810Dh, addr hit_FaSpeed1		; скорость по x наводящегося по hit_Fa объекта (+13)
	invoke JmpPatch, 0040812Bh, addr hit_FaSpeed2		; скорость по x наводящегося по hit_Fa объекта (-13)
		
	invoke JmpPatch, 00408149h, addr hit_FaSpeed3		; скорость по z наводящегося по hit_Fa объекта (+2)
	invoke JmpPatch, 00408167h, addr hit_FaSpeed4		; скорость по z наводящегося по hit_Fa объекта (-2)
	
	invoke JmpPatch, 00407FE9h, addr hit_FaSpeed5		; нарастание скорости наведения по x
	invoke JmpPatch, 00408026h, addr hit_FaSpeed6		; нарастание скорости наведения по z
	
	invoke JmpPatch, 004080ADh, addr hit_FaSpeed7		; скорость наведения по оси y
	invoke JmpPatch, 0040809Eh, addr hit_FaSpeed8		; высота объекта при наведении по y
	
	;=======================================
	
	
	
	;=============== Hacked Regulars (hack.inc)==========
	;invoke JmpPatch, 00416E6Dh, addr F6_custom_modes ; Allows F6 in Stage mode (or custom list)
	;invoke JmpPatch, 00416EBDh, addr F7_custom_modes ; Allows F7 in Stage mode (or custom list)
	;invoke JmpPatch, 00416F1Dh, addr F8_custom_modes ; Allows F8 in Stage mode (or custom list)
	;invoke JmpPatch, 00416F71h, addr F9_custom_modes ; Allows F9 in Stage mode (or custom list)
	
	invoke JmpPatch, 0042184Eh, addr F7_rework  ; now cures Poison, Weak, Silence and Confuse
	invoke JmpPatch, 004217D0h, addr F9_rework  ; now is does NOT killing characters if used not in VS
												; also there is a filter by ID or type, if you're 
												; using item-key-objects in your maps or stages

	invoke JmpPatch, 00437719h, addr act_rework  		; allows to use "act:" not only with type 0 and 5
	
			CMP [F7_for_dead],TRUE
			JNE [no_F7_after_end]	
	invoke WriteMem, 00416EE0h, addr oneNOP,9 			; Allows to use F7 after round ends, like in 1.9 version!
			no_F7_after_end:
	
	;invoke JmpPatch, 0042A037h, addr Independent_Stages    ; Makes All players be in Independent team
															; disable if u're using "ChangeAble_teams" (below)
															; and on the contrary
	invoke JmpPatch, 0042A837h, addr ChangeAble_teams 	; Allows players choose Team in Stage Mode
														; Must be disabled if u're using "Independent_Stages"
	invoke JmpPatch, 0041DB46h, addr Result_Sound_Delay  	; time before sound play after last fighter defeated
														 	; has regular LF2 value, so you can keep it work
	
	invoke JmpPatch, 00437664h, addr Stage_Spawn_Coords
	;===================================================
	
	
	
	;====== Взятые у паши функции (Zapashok.inc) =======
	
	invoke JmpPatch, 0041313Ah, addr Right_Timer
	invoke JmpPatch, 0041314Eh, addr Left_Timer
	invoke JmpPatch, 00413162h, addr Up_Timer
	invoke JmpPatch, 00413176h, addr Down_Timer
	invoke JmpPatch, 0041318Ah, addr Defend_Timer
	invoke JmpPatch, 0041319Eh, addr Jump_Timer
	invoke JmpPatch, 004131B2h, addr Attack_Timer
	
	;===================================================
	
	
	invoke WriteMem, 004219D9h, addr delta,4			; фикс размера итра
	invoke JmpPatch, 0042B8C2h, addr botamount			; прозрачность элементов "выбор бота"
	invoke JmpPatch, 0042B8B8h, addr botamount2			; прозрачность элементов "выбор бота"
	
	
	
	;===================================================
	
	;---------------- vertical camera ---------------;  ; ось Y для камеры от Паши
	invoke JmpPatch, 0041A9E5h, addr blood_scrolling
	invoke JmpPatch, 0041A71Ah, addr shadow_scrolling
	invoke JmpPatch, 0040BDDCh, addr vertic
	invoke JmpPatch, 0041A168h, addr bg_scrolling 
	invoke JmpPatch, 0041A246h, addr bg_scrolling2
	invoke JmpPatch, 0041A2D9h, addr bg_scrolling3
	invoke JmpPatch, 0041A926h, addr bg_scrolling4
	invoke JmpPatch, 0041B910h, addr cam_coords_calc
	;------------- vertical camera  end -------------;
	
	;---------------- спарки от паши ---------------;
	
	;itr_loading 
	invoke WriteMem, 00411118h, addr spark_itr_tag,4 
	invoke WriteMem, 00411121h, addr num_seven,1 
	invoke WriteMem, 00430904h, addr num_74h,1 
	;sparks.dat loading 
	invoke JmpPatch, 0043C064h, addr Loading_sparks 
	;MAlloc on game loading 
	invoke JmpPatch, 00402437h, addr Sparki_MAlloc 
	;Sparks adding in fight 
	invoke JmpPatch, 004309F7h, addr Sparks_random_2 
	invoke JmpPatch, 00430964h, addr Sparks_random_1 
	invoke WriteMem, 004309B0h, addr oneNOP,1 
	invoke JmpPatch, 00430A05h, addr Sparki_creation 
	;Drawing sparks (Added by previous part) 
	invoke JmpPatch, 0041A98Bh, addr Sparks_drawing 
	invoke WriteMem, 0041A990h, addr Sparks_Triple_NOP,3 ;caaeooea, ?oiau eia ia iiei???eei
	
	;---------------- конец спарков ---------------;
	
	;call AI
	ret


DLLStartup endp

AI proc

	;=================Range Stuff=================
	invoke JmpPatch, 0040AE0Ah, addr Range1
	invoke WriteMem, 0040AE0Fh, addr FourNOP,4
	invoke JmpPatch, 0040B217h, addr Range2
	invoke JmpPatch, 0040B2CBh, addr Range3
	invoke JmpPatch, 0040B383h, addr Range4
	invoke JmpPatch, 00403878h, addr Deep_Ball
	invoke WriteMem, 0040387Dh, addr doubleNOP,2
	;=============================================
	
	;==================Other AIs==================
	;Generic D>A
	invoke JmpPatch, 00403608h, addr AI_Ball1
	;Generic D>A #2
	invoke JmpPatch, 004036FBh, addr AI_Ball2
	;Deep AI
	invoke JmpPatch, 00403E89h, addr AI_Deep
	invoke WriteMem, 00403E8Eh, addr doubleNOP,2
	;John AI
	invoke JmpPatch, 00403A7Eh, addr AI_John
	invoke WriteMem, 00403A83h, addr doubleNOP,2
	;Henry AI
	invoke JmpPatch, 004041F1h, addr AI_Henry
	invoke WriteMem, 004041F6h, addr doubleNOP,2
	;Rudolf AI
	invoke JmpPatch, 0040436Eh, addr AI_Rudolf
	invoke WriteMem, 00404373h, addr doubleNOP,2
	;Louis AI
	invoke JmpPatch, 004044FAh, addr AI_Louis
	invoke WriteMem, 004044FFh, addr doubleNOP,2
	;Firen AI
	invoke JmpPatch, 00404609h, addr AI_Firen
	invoke WriteMem, 0040460Eh, addr doubleNOP,2
	;Freeze AI
	invoke JmpPatch, 0040499Ah, addr AI_Freeze
	invoke WriteMem, 0040499Fh, addr doubleNOP,2
	;Dennis AI
	invoke JmpPatch, 00405147h, addr AI_Dennis
	invoke WriteMem, 0040514Ch, addr doubleNOP,2
	;Woody AI
	invoke JmpPatch, 00404DBBh, addr AI_Woody
	invoke WriteMem, 00404DC0h, addr doubleNOP,2
	;Davis AI
	;invoke JmpPatch, 00404C12h, addr AI_Davis
	;invoke WriteMem, 00404C17h, addr doubleNOP,2
	;Sorcerer AI
	invoke JmpPatch, 0040555Dh, addr AI_Sorcerer
	invoke WriteMem, 00405562h, addr doubleNOP,2
	;=============================================
	
	ret
AI endp



End DllEntryPoint