[BITS 16]
[org 0x7c00]

start:
	mov [drv], dl	; enregistrer le periph de lecture dans [drv] (floppy --> 0x00)
	xor ax, ax	; fonction 0x00 pour reinitialiser
	mov ds, ax
reinit:
	mov ax, 0x00
	mov dl, [drv]	; la disquette avec
	int 13h		; l'interruption 13h
    jc reinit		; si erreur --> recommencer

	mov ax, 3	; fonction 3 pour
	int 0x10	; effacer l'ecran


lecture:		; lecture et chargement du kernel
	mov bx, 1000h	; charger le kernel à 9000h
	mov ah, 0x02	; charger la disquette dans [ES:BX]
	mov al, 17	; 18 secteurs à lire
	mov ch, 0	; premier cylindre
	mov cl, 2	; 2nd secteur pour ne pas charger le bootsector
	mov dh, 0	; la tête n°1 (Head 1)
	mov dl, [drv]	; la disquette
	int 13h		; lecture de la disquette
    jc lecture		; si erreur --> recommencer
lecture2:		; lecture de la 2nde tête
	mov al, 17
	inc dh		; 2nde tête
	int 13h
    jc lecture2


Pmode1:			; passage au mode protégé
	cli		; désactivation des interruptions
	call EnableA20
	lgdt [GDTR]	; chargement de la gdt
	mov eax, cr0
	or eax, 1
	mov cr0, eax	; mettre le registre cr0 à 1
	jmp dword CodeSel:Pmode	; saut long et reinitialisation des registres

;---- activer le A20 ----;
EnableA20:
	push ax
	mov ah,0dfh
	call GateA20
	or al,al
	jz EnableA20_ok
	stc
EnableA20_ok:
	pop ax
	ret
GateA20:
	pushf
	cli
	call Empty8042
	jnz GateA20_fail
	out 0edh, ax
	mov al,0D1h
	out 64h,al
	call Empty8042
	jnz GateA20_fail
	mov al,ah
	out 60h,al
	call Empty8042
	push cx
	mov cx,14h
GateA20_loop:
	out 0edh,ax
	loop GateA20_loop
	pop cx
GateA20_fail:
	popf
	ret
Empty8042:
	push cx
	xor cx,cx
Empty8042_try:
	out 0edh,ax
	in al,64h
	and al,2
	loopnz Empty8042_try
	pop cx
	ret
;---- Ecrire un message à l'ecran ----;
;aff:
;push ax
;.debut:
;	lodsb
;	cmp al, 0
;	jz .fin
;	mov ah, 0eh
;	int 0x10
;	jmp .debut
;.fin:
;pop ax
;ret
[BITS 32]
Pmode:
	mov eax, DataSel	; selecteur de données
	mov ss, eax
	mov ds, eax
	mov es, eax
	mov fs, eax
	mov gs, eax

	mov ax, 0x10		; chargement de la pile
	mov ss, ax
	mov esp, 0xFFFF

	mov dl, [drv]		; stopper le moteur de
	mov edx, 0x3f2		; la diquette
	mov al, 0x0c
	out dx, al
	jmp dword CodeSel:1000h	; execution du kernel

GDTR			; mise au point de la gdt
	dw GDTEnd-1
	dd GDT
GDT
nullset equ $-GDT
GDT0
	dd 0
	dd 0
CodeSel equ $-GDT
	dw 0ffffh
	dw 0
	db 0
	db 09ah
	db 0cfh
	db 0h
DataSel equ $-GDT
	dw 0ffffh
	dw 0h
	db 0h
	db 092h
	db 0cfh
	db 0
GDTEnd

;---- declaration des variables ----;
drv db 0
;b db "b",0

;---- pour rendre le fichier boot à 512 octets ----;
times 510-($-$$) db 0
;---- et mettre au point la signature ----;
dw 0xAA55
