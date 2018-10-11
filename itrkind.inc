.data

ik8_back1	dd 0043002Dh
ik8_back2	dd 0043087Ch

ik8_fix1	dd 00417535h
ik8_fix2	dd 00417A10h
	
.code
itr_kind8 proc
	

	CMP EDX,8
	JE kind8_dvx_X ; standart
	
	
	CMP EDX,700 ; itr ��������� ����� (����� ���)
	JE kind_700
	
	
	CMP EDX,800  ; Type 0
	JE kind8_dvx_X ; standart
	CMP EDX,801
	JE kind8_dvx_X_Y
	CMP EDX,802
	JE kind8_dvx_Y
	CMP EDX,803
	JE kind8_X
	CMP EDX,804
	JE kind8_X_Y
	CMP EDX,805
	JE kind8_Y
	CMP EDX,806
	JE kind8_dvx
	
	CMP EDX,807
	JE kind8_dvx_enemy
	
	CMP EDX,808
	JE kind8_x_y_enemy
	
	CMP EDX,809
	JE kind8_dvx_enemy_no_team

	CMP EDX,810  ; Type 1
	JE kind8_dvx_X ; standart
	CMP EDX,811
	JE kind8_dvx_X_Y
	CMP EDX,812
	JE kind8_dvx_Y
	CMP EDX,813
	JE kind8_X
	CMP EDX,814
	JE kind8_X_Y
	CMP EDX,815
	JE kind8_Y
	CMP EDX,816
	JE kind8_dvx
	
	CMP EDX,820  ; Type 2
	JE kind8_dvx_X ; standart
	CMP EDX,821
	JE kind8_dvx_X_Y
	CMP EDX,822
	JE kind8_dvx_Y
	CMP EDX,823
	JE kind8_X
	CMP EDX,824
	JE kind8_X_Y
	CMP EDX,825
	JE kind8_Y
	CMP EDX,826
	JE kind8_dvx
	
	CMP EDX,830  ; Type 3
	JE kind8_dvx_X ; standart
	CMP EDX,831
	JE kind8_dvx_X_Y
	CMP EDX,832
	JE kind8_dvx_Y
	CMP EDX,833
	JE kind8_X
	CMP EDX,834
	JE kind8_X_Y
	CMP EDX,835
	JE kind8_Y	
	CMP EDX,836
	JE kind8_dvx
		
	CMP EDX,837
	JE kind8_dvx_enemy
		
	CMP EDX,838
	JE kind8_x_y_enemy
	
	CMP EDX,840  ; Type 4
	JE kind8_dvx_X ; standart
	CMP EDX,841
	JE kind8_dvx_X_Y
	CMP EDX,842
	JE kind8_dvx_Y
	CMP EDX,843
	JE kind8_X
	CMP EDX,844
	JE kind8_X_Y
	CMP EDX,845
	JE kind8_Y
	CMP EDX,846
	JE kind8_dvx
	
	CMP EDX,850  ; Type 5
	JE kind8_dvx_X ; standart
	CMP EDX,851
	JE kind8_dvx_X_Y
	CMP EDX,852
	JE kind8_dvx_Y
	CMP EDX,853
	JE kind8_X
	CMP EDX,854
	JE kind8_X_Y
	CMP EDX,855
	JE kind8_Y
	CMP EDX,856
	JE kind8_dvx
	
	CMP EDX,860  ; Type 6
	JE kind8_dvx_X ; standart
	CMP EDX,861
	JE kind8_dvx_X_Y
	CMP EDX,862
	JE kind8_dvx_Y
	CMP EDX,863
	JE kind8_X
	CMP EDX,864
	JE kind8_X_Y
	CMP EDX,865
	JE kind8_Y
	CMP EDX,866
	JE kind8_dvx
	
	CMP EDX,870  ; Complex of Types: 1,2,4,6
	JE kind8_dvx_X ; standart
	CMP EDX,871
	JE kind8_dvx_X_Y
	CMP EDX,872
	JE kind8_dvx_Y
	CMP EDX,873
	JE kind8_X
	CMP EDX,874
	JE kind8_X_Y
	CMP EDX,875
	JE kind8_Y
	CMP EDX,876
	JE kind8_dvx

	JMP [ik8_back1]
	

kind_700:
	
	; EBX - ������, ��������� ����
	; EDI - ������, ���������� ����
	
	PUSH EAX
	PUSH EDX
	PUSH ECX
	
	
	MOV EAX, DWORD PTR SS:[EBX+364h]
	CMP EAX, DWORD PTR SS:[EDI+364h]
	JE [kind_700_skip]
	
	SUB DWORD PTR SS:[EDI+2FCh], 15
	ADD DWORD PTR SS:[EDI+0ECh], 90
	
kind_700_skip:
	POP ECX
	POP EDX
	POP EAX
	JMP [ik8_false]


kind8_dvx_X:
	MOV EAX,DWORD PTR SS:[ESP+0Ch]
	MOV EDX,DWORD PTR DS:[EAX+44h] ; gets HEAL from Injury tag of ITR
	ADD EDX,3E8h
	MOV DWORD PTR DS:[EDI+0E0h],EDX ; writes heal to curing function
	MOV EDX,DWORD PTR DS:[EAX+2Ch] ; ���� �������� �������� � ���� �� �������
	ADD DWORD PTR DS:[EDI+308h],EDX ; ����� ����
	FLD DWORD PTR DS:[EAX+14h] ; ��������� dvx �� itr
	FISTP DWORD PTR DS:[EBX+70h] ; ������ ���� ��� � dvx
	
	FLD QWORD PTR DS:[EDI+58h] ; ��������� X ��������� �������
	FSTP QWORD PTR DS:[EBX+58h] ; ���������� � ����������� �������
	
	FLD QWORD PTR DS:[EDI+68h] ; ��������� Z ��������� �������
	FADD QWORD PTR DS:[447A08h]
	FSTP QWORD PTR DS:[EBX+68h] ; ���������� Z ����������� �������
	JMP [ik8_return]
	
kind8_dvx_X_Y:

	push ECX
	MOV ECX, DWORD PTR DS:[EDI+364h]
	CMP DWORD PTR DS:[EBX+364h], ECX
	pop ECX
	JNE [ik8_false]

	MOV EAX,DWORD PTR SS:[ESP+0Ch]
	MOV EDX,DWORD PTR DS:[EAX+44h] ; gets HEAL from Injury tag of ITR
	ADD EDX,3E8h
	MOV DWORD PTR DS:[EDI+0E0h],EDX ; writes heal to curing function
	FLD DWORD PTR DS:[EAX+14h] ; ��������� dvx �� itr
	FISTP DWORD PTR DS:[EBX+70h] ; ������ ���� ��� � dvx
	
	FLD QWORD PTR DS:[EDI+58h] ; ��������� X ��������� �������
	FSTP QWORD PTR DS:[EBX+58h] ; ���������� � ����������� �������
	
	FLD QWORD PTR DS:[EDI+60h] ; ��������� Y ��������� �������
	FSTP QWORD PTR DS:[EBX+60h] ; ���������� Y ����������� �������
	
	FLD QWORD PTR DS:[EDI+68h] ; ��������� Z ��������� �������
	FADD QWORD PTR DS:[447A08h]
	FSTP QWORD PTR DS:[EBX+68h] ; ���������� Z ����������� �������
	JMP [ik8_return]

kind8_dvx_Y:
	MOV EAX,DWORD PTR SS:[ESP+0Ch]
	MOV EDX,DWORD PTR DS:[EAX+44h] ; gets HEAL from Injury tag of ITR
	ADD EDX,3E8h
	MOV DWORD PTR DS:[EDI+0E0h],EDX ; writes heal to curing function
	FLD DWORD PTR DS:[EAX+14h] ; ��������� dvx �� itr
	FISTP DWORD PTR DS:[EBX+70h] ; ������ ���� ��� � dvx
	
	FLD QWORD PTR DS:[EDI+60h] ; ��������� Y ��������� �������
	FSTP QWORD PTR DS:[EBX+60h] ; ���������� Y ����������� �������
	
	FLD QWORD PTR DS:[EDI+68h] ; ��������� Z ��������� �������
	FADD QWORD PTR DS:[447A08h]
	FSTP QWORD PTR DS:[EBX+68h] ; ���������� Z ����������� �������
	JMP [ik8_return]

kind8_X:
	MOV EAX,DWORD PTR SS:[ESP+0Ch]
	MOV EDX,DWORD PTR DS:[EAX+44h] ; gets HEAL from Injury tag of ITR
	ADD EDX,3E8h
	MOV DWORD PTR DS:[EDI+0E0h],EDX ; writes heal to curing function
	FLD QWORD PTR DS:[EDI+58h] ; ��������� X ��������� �������
	FSTP QWORD PTR DS:[EBX+58h] ; ���������� � ����������� �������
	
	FLD QWORD PTR DS:[EDI+68h] ; ��������� Z ��������� �������
	FADD QWORD PTR DS:[447A08h]
	FSTP QWORD PTR DS:[EBX+68h] ; ���������� Z ����������� �������
	JMP [ik8_return]
	
kind8_X_Y:
	
	push ECX
	MOV ECX, DWORD PTR DS:[EDI+364h]
	CMP DWORD PTR DS:[EBX+364h], ECX
	pop ECX
	JNE [ik8_false]
	
kind8_x_y_enemy:

	MOV EAX,DWORD PTR SS:[ESP+0Ch]
	MOV EDX,DWORD PTR DS:[EAX+44h] ; gets HEAL from Injury tag of ITR
	ADD EDX,3E8h
	MOV DWORD PTR DS:[EDI+0E0h],EDX ; writes heal to curing function
	FLD QWORD PTR DS:[EDI+58h] ; ��������� X ��������� �������
	FSTP QWORD PTR DS:[EBX+58h] ; ���������� � ����������� �������
	
	FLD QWORD PTR DS:[EDI+60h] ; ��������� Y ��������� �������
	FSTP QWORD PTR DS:[EBX+60h] ; ���������� Y ����������� �������
	
	FLD QWORD PTR DS:[EDI+68h] ; ��������� Z ��������� �������
	FADD QWORD PTR DS:[447A08h]
	FSTP QWORD PTR DS:[EBX+68h] ; ���������� Z ����������� �������
	JMP [ik8_return]

kind8_Y:
	MOV EAX,DWORD PTR SS:[ESP+0Ch]
	MOV EDX,DWORD PTR DS:[EAX+44h] ; gets HEAL from Injury tag of ITR
	ADD EDX,3E8h
	MOV DWORD PTR DS:[EDI+0E0h],EDX ; writes heal to curing function
	FLD QWORD PTR DS:[EDI+60h] ; ��������� Y ��������� �������
	FSTP QWORD PTR DS:[EBX+60h] ; ���������� Y ����������� �������
	
	FLD QWORD PTR DS:[EDI+68h] ; ��������� Z ��������� �������
	FADD QWORD PTR DS:[447A08h]
	FSTP QWORD PTR DS:[EBX+68h] ; ���������� Z ����������� �������
	JMP [ik8_return]
	
kind8_dvx:	
	push ECX
	MOV ECX, DWORD PTR DS:[EDI+364h]
	CMP DWORD PTR DS:[EBX+364h], ECX
	pop ECX
	JNE [ik8_false]
kind8_dvx_enemy:

	PUSH ECX
	MOV ECX, DWORD PTR DS:[EDI+364h] 
	MOV DWORD PTR DS:[EBX+364h], ECX
	POP ECX
kind8_dvx_enemy_no_team:	
	MOV EAX,DWORD PTR SS:[ESP+0Ch]
	MOV EDX,DWORD PTR DS:[EAX+44h] ; gets HEAL from Injury tag of ITR
	CMP EDX, 20000
	JGE [kind8_dvx_damage_mp]
	CMP EDX, 10000
	JGE [kind8_dvx_damage_hp]
	ADD DWORD PTR DS:[EDI+304h], EDX
	ADD DWORD PTR DS:[EDI+300h], EDX
	ADD DWORD PTR DS:[EDI+2FCh], EDX
	MOV DWORD PTR DS:[EDI+0E0h],EDX ; writes heal to curing function
	FLD DWORD PTR DS:[EAX+14h] ; ��������� dvx �� itr
	FISTP DWORD PTR DS:[EBX+70h] ; ������ ���� ��� � dvx
	JMP [ik8_return]


kind8_dvx_damage_hp:
	SUB EDX, 10000
	CMP DWORD PTR DS:[EDI+2FCh], EDX
	JLE [deathkind]
	SUB DWORD PTR DS:[EDI+2FCh], EDX
	SUB DWORD PTR DS:[EDI+300h], EDX
	ADD DWORD PTR DS:[EDI+34Ch], EDX	
		
	push eax
	
	MOV edi, DWORD PTR DS:[EBX+354h]
	mov eax,dword ptr ds:[esi+edi*4+3ECh]
	ADD DWORD PTR DS:[EAX+348h], EDX
	
	pop eax
	
	MOV ECX, DWORD PTR DS:[EAX+14h]
	CMP ECX, 0
	JNE [godvxkadr]
	
	JMP [ik8_return]
	
	
kind8_dvx_damage_mp:

	;push ecx
	;push eax
	;push edx
	
	;MOV ecx, 0
	
;foreach:
	;CMP BYTE PTR DS:[esi+ecx+4h],0
	;JE [no_object]
	
	;MOV eax,DWORD PTR DS:[esi+ecx*4+3ECh]
	
	;push ecx
	;mov ecx, DWORD PTR DS:[EDI+364h]
	;cmp DWORD PTR DS:[EAX+364h],ecx
	;pop ecx
	;JE [no_object]
	;cmp DWORD PTR DS:[EAX+20], 1
	;JNE [no_object]
	;SUB DWORD PTR DS:[EAX+308h], 1
	;ADD DWORD PTR DS:[EDI+308h], 1
	
	;no_object:
	;	INC ecx
	;	CMP ecx,1000
	;	JL [foreach]
	
	;pop edx
	;pop eax
	;pop ecx

	JMP [ik8_return]

godvxkadr:
	FLD DWORD PTR DS:[EAX+14h] ; ��������� dvx �� itr
	FISTP DWORD PTR DS:[EBX+70h] ; ������ ���� ��� � dvx
	JMP [ik8_return]

deathkind:
	SUB DWORD PTR DS:[EDI+2FCh], EDX
	SUB DWORD PTR DS:[EDI+300h], EDX
	ADD DWORD PTR DS:[EDI+34Ch], EDX
	MOV DWORD PTR DS:[EDI+70h], 226
	JMP [ik8_return]

 
ik8_return:
	JMP [ik8_back2]
	
ik8_false:
	JMP [ik8_back1]
 
itr_kind8 endp








itr_kind8_types proc

	MOV ECX, DWORD PTR SS:[ESI+368h]
	
	CMP DWORD PTR DS:[EBX],8 ; �������� ��� ��� IK8
	JE kind80x_type0
	
	CMP DWORD PTR DS:[EBX],800 ; �������� ��� ��� IK800
	JE kind80x_type0
	CMP DWORD PTR DS:[EBX],801
	JE kind80x_type0
	CMP DWORD PTR DS:[EBX],802
	JE kind80x_type0
	CMP DWORD PTR DS:[EBX],803
	JE kind80x_type0
	CMP DWORD PTR DS:[EBX],804
	JE kind80x_type0
	CMP DWORD PTR DS:[EBX],805
	JE kind80x_type0
	CMP DWORD PTR DS:[EBX],806
	JE kind80x_type0
	
	CMP DWORD PTR DS:[EBX],810
	JE kind81x_type1
	CMP DWORD PTR DS:[EBX],811
	JE kind81x_type1
	CMP DWORD PTR DS:[EBX],812
	JE kind81x_type1
	CMP DWORD PTR DS:[EBX],813
	JE kind81x_type1
	CMP DWORD PTR DS:[EBX],814
	JE kind81x_type1
	CMP DWORD PTR DS:[EBX],815
	JE kind81x_type1
	CMP DWORD PTR DS:[EBX],816
	JE kind81x_type1
	
	CMP DWORD PTR DS:[EBX],820
	JE kind82x_type2
	CMP DWORD PTR DS:[EBX],821
	JE kind82x_type2
	CMP DWORD PTR DS:[EBX],822
	JE kind82x_type2
	CMP DWORD PTR DS:[EBX],823
	JE kind82x_type2
	CMP DWORD PTR DS:[EBX],824
	JE kind82x_type2
	CMP DWORD PTR DS:[EBX],825
	JE kind82x_type2
	CMP DWORD PTR DS:[EBX],826
	JE kind82x_type2
	
	CMP DWORD PTR DS:[EBX],830
	JE kind83x_type3
	CMP DWORD PTR DS:[EBX],831
	JE kind83x_type3
	CMP DWORD PTR DS:[EBX],832
	JE kind83x_type3
	CMP DWORD PTR DS:[EBX],833
	JE kind83x_type3
	CMP DWORD PTR DS:[EBX],834
	JE kind83x_type3
	CMP DWORD PTR DS:[EBX],835
	JE kind83x_type3
	CMP DWORD PTR DS:[EBX],836
	JE kind83x_type3
	
	CMP DWORD PTR DS:[EBX],840
	JE kind84x_type4
	CMP DWORD PTR DS:[EBX],841
	JE kind84x_type4
	CMP DWORD PTR DS:[EBX],842
	JE kind84x_type4
	CMP DWORD PTR DS:[EBX],843
	JE kind84x_type4
	CMP DWORD PTR DS:[EBX],844
	JE kind84x_type4
	CMP DWORD PTR DS:[EBX],845
	JE kind84x_type4
	CMP DWORD PTR DS:[EBX],846
	JE kind84x_type4
	
	CMP DWORD PTR DS:[EBX],850
	JE kind85x_type5
	CMP DWORD PTR DS:[EBX],851
	JE kind85x_type5
	CMP DWORD PTR DS:[EBX],852
	JE kind85x_type5
	CMP DWORD PTR DS:[EBX],853
	JE kind85x_type5
	CMP DWORD PTR DS:[EBX],854
	JE kind85x_type5
	CMP DWORD PTR DS:[EBX],855
	JE kind85x_type5
	CMP DWORD PTR DS:[EBX],856
	JE kind85x_type5
	
	CMP DWORD PTR DS:[EBX],860
	JE kind86x_type6
	CMP DWORD PTR DS:[EBX],861
	JE kind86x_type6
	CMP DWORD PTR DS:[EBX],862
	JE kind86x_type6
	CMP DWORD PTR DS:[EBX],863
	JE kind86x_type6
	CMP DWORD PTR DS:[EBX],864
	JE kind86x_type6
	CMP DWORD PTR DS:[EBX],865
	JE kind86x_type6
	CMP DWORD PTR DS:[EBX],866
	JE kind86x_type6
	
	CMP DWORD PTR DS:[EBX],870
	JE kind87x_type1_2_4_6
	CMP DWORD PTR DS:[EBX],871
	JE kind87x_type1_2_4_6
	CMP DWORD PTR DS:[EBX],872
	JE kind87x_type1_2_4_6
	CMP DWORD PTR DS:[EBX],873
	JE kind87x_type1_2_4_6
	CMP DWORD PTR DS:[EBX],874
	JE kind87x_type1_2_4_6
	CMP DWORD PTR DS:[EBX],875
	JE kind87x_type1_2_4_6
	CMP DWORD PTR DS:[EBX],876
	JE kind87x_type1_2_4_6
	
	JMP [ik8_fix1]


kind80x_type0:
	CMP DWORD PTR SS:[ECX+6F8h],0 ; �������� �� Type 0
	JNE [skip_kind] ; ����� ���������� ���������
	JMP [ik8_fix1] ; ���� �� ��������� - ����������
	
kind81x_type1:
	CMP DWORD PTR SS:[ECX+6F8h],1 ; �������� �� Type
	JNE [skip_kind] ; ����� ���������� ���������
	JMP [ik8_fix1] ; ���� �� ��������� - ����������
	
kind82x_type2:
	CMP DWORD PTR SS:[ECX+6F8h],2 ; �������� �� Type
	JNE [skip_kind] ; ����� ���������� ���������
	JMP [ik8_fix1] ; ���� �� ��������� - ����������
	
kind83x_type3:
	CMP DWORD PTR SS:[ECX+6F8h],3 ; �������� �� Type
	JNE [skip_kind] ; ����� ���������� ���������
	JMP [ik8_fix1] ; ���� �� ��������� - ����������	

kind84x_type4:
	CMP DWORD PTR SS:[ECX+6F8h],4 ; �������� �� Type
	JNE [skip_kind] ; ����� ���������� ���������
	JMP [ik8_fix1] ; ���� �� ��������� - ����������	
	
kind85x_type5:
	CMP DWORD PTR SS:[ECX+6F8h],5 ; �������� �� Type
	JNE [skip_kind] ; ����� ���������� ���������
	JMP [ik8_fix1] ; ���� �� ��������� - ����������	
	
kind86x_type6:
	CMP DWORD PTR SS:[ECX+6F8h],6 ; �������� �� Type
	JNE [skip_kind] ; ����� ���������� ���������
	JMP [ik8_fix1] ; ���� �� ��������� - ����������

;===============================================================
kind87x_type1_2_4_6:
	CMP DWORD PTR SS:[ECX+6F8h],1 ; �������� �� Type
	JE [kind87x_type1_2_4_6_fix] ; ����� ���������� ���������
	CMP DWORD PTR SS:[ECX+6F8h],2 ; �������� �� Type
	JE [kind87x_type1_2_4_6_fix] ; ����� ���������� ���������
	CMP DWORD PTR SS:[ECX+6F8h],4 ; �������� �� Type
	JE [kind87x_type1_2_4_6_fix] ; ����� ���������� ���������
	CMP DWORD PTR SS:[ECX+6F8h],6 ; �������� �� Type
	JE [kind87x_type1_2_4_6_fix] ; ����� ���������� ���������
	JMP [skip_kind]
kind87x_type1_2_4_6_fix:
	JMP [ik8_fix1] ; ���� �� ��������� - ����������
;===============================================================

skip_kind:
	JMP [ik8_fix2]


itr_kind8_types endp







