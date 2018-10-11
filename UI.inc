.Data

backbotamount dd 0042B8C7h
backbotamount2 dd 0042B8BDh
.Code


opacity proc
	PUSH 1
opacity endp

ResetCoord proc
	PUSH 0
ResetCoord endp
botamount proc
	PUSH 0
	Jmp [backbotamount]
botamount endp


botamount2 proc
	PUSH 09397B2h
	Jmp [backbotamount2]
botamount2 endp

map_random Proc
	
	SUB EAX,0

map_random endp