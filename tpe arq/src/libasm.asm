GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand
GLOBAL  _keyboardHandler
GLOBAL  _mascaraPIC1,_mascaraPIC2,_Cli,_Sti
GLOBAL  _debug

EXTERN  int_08
EXTERN  int_09


SECTION .text


_Cli:
	cli			; limpia flag de interrupciones
	ret

_Sti:

	sti			; habilita interrupciones por flag
	ret

_mascaraPIC1:			; Escribe mascara del PIC 1
	push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out	21h,al
        pop     ebp
        retn

_mascaraPIC2:			; Escribe mascara del PIC 2
	push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out	0A1h,al
        pop     ebp
        retn

_read_msw:
        smsw    ax		; Obtiene la Machine Status Word
        retn


_lidt:				; Carga el IDTR
        push    ebp
        mov     ebp, esp
        push    ebx
        mov     ebx, [ss: ebp + 6] ; ds:bx = puntero a IDTR 
	rol	ebx,16		    	
	lidt    [ds: ebx]          ; carga IDTR
        pop     ebx
        pop     ebp
        retn


_int_08_hand:				; Handler de INT 8 ( Timer tick)
        push    ds
        push    es                      ; Se salvan los registros
        pusha                           ; Carga de DS y ES con el valor del selector
        mov     ax, 10h			; a utilizar.
        mov     ds, ax
        mov     es, ax
        
        ;LECTURA DEL REAL TIME CLOCK
        
        
        mov 	eax, 0			; Borro ax
        mov 	al, 00h			; Leo las SEG del RTC
	out 	70h, al
	in 	al,71h
	push 	eax			; Lo paso como parametro
	
	mov 	eax, 0
	mov 	al, 02h			; Leo las MIN del RTC
	out 	70h, al
	in 	al,71h
	push 	eax			; Lo paso como parametro
	
	mov 	eax, 0
	mov 	al, 04h			; Leo las HS del RTC
	out 	70h, al
	in 	al,71h
	push 	eax			; Lo paso como parametro
        			
				                
        ;LLAMADA A FUNCION DE KERNEL.C
        
        call    int_08                 
        mov	al,20h			; Envio de EOI generico al PIC
	out	20h,al
	pop 	eax
	pop 	eax
	pop 	eax
	
	
	popa                            
        pop     es
        pop     ds
        iret

_keyboardHandler:			; Handler de INT 9 ( Keyboard )
	push    ds
        push    es          ; Se salvan los registros
        pusha               ; Carga de DS y ES con el valor del selector
        mov     ax, 10h		
        mov     ds, ax
        mov     es, ax      
        
        mov 	eax, 0		; Limpio ah
        in 	al, 60h		; Puerto de datos del teclado
        push	eax             ; Paso scancode como parametro
        call    int_09
        mov	al,20h		; Envio de EOI generico al PIC
	out 	20h,al
	pop 	eax
		
	popa
        pop     es
        pop     ds
        iret


; Debug para el BOCHS, detiene la ejecució; Para continuar colocar en el BOCHSDBG: set $eax=0
;


_debug:
        push    bp
        mov     bp, sp
        push	ax
vuelve:	mov     ax, 1
        cmp	ax, 0
	jne	vuelve
	pop	ax
	pop     bp
        retn
