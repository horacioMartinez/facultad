! Trabajo practico de estructura del computador
! Martinez Horacio, 94926

	.begin
	.org 2048
eject .equ 1
play .equ 2
stop .equ 4
pause .equ 8

reproductor .equ 1
motor .equ 2
bandeja .equ 4
disco .equ 0x80000000 !2^31, bit mas significativo


dirEntradas .equ 0xB032C008
dirSalidas .equ 0xB032C00C 
num_espera .equ 8333333 ! numero de ciclos de "esperar" para alcanzar 3s a 1Ghz
			    ! calculado a partir de lo que tarda cada ciclo (218 clks)
ptr_entradas : dirEntradas
ptr_salidas : dirSalidas
mask_disco: disco
mask_num_espera: num_espera


		!estado inicial: cerrado
reset:		ld [ptr_entradas], %r1
		ld [ptr_salidas], %r2
		ld %r2, %r3
		andn %r3,bandeja+motor+reproductor,%r3
		st %r3,%r2
		ld [mask_disco],%r10
		ld [mask_num_espera],%r27
		ba cerrado

abrir:		ld %r2, %r3
		or %r3, bandeja,%r3
		st %r3,%r2
		ba abierto

cerrar:	ld %r2, %r3
		andn %r3, bandeja,%r3
		st %r3,%r2
		ba cerrado

reproducir:	ld %r2, %r3
		or %r3, reproductor+motor,%r3
		st %r3,%r2
		ba reproduciendo

pausar:	ld %r2, %r3
		andn %r3, reproductor,%r3
		st %r3,%r2
		ba pausado

detener:	ld %r2, %r3
		andn %r3, reproductor+motor,%r3
		st %r3,%r2
		ba cerrado

esperar:	ld %r2, %r3
		andn %r3, bandeja+motor+reproductor,%r3
		st %r3,%r2
		ld %r7, %r6
		add %r6,1,%r6 !ir incrementando r6 hasta alcanzar num_espera
		st %r6,%r7
		subcc %r6,%r27,%r0
		be abrir
		ba esperar

cerrado:	st %r0, %r7 ! resetea a 0 el contador de 3s
		ld %r1, %r4 ! r4 entradas
		ld %r2, %r3 ! r3 sensor de disco
		subcc %r4, eject, %r0 !abrir
		be abrir
		add %r10,play,%r12
		add %r4,%r3,%r13
		subcc %r13, %r12, %r0 !si r12=r13 hay disco y se apreto play
		be reproducir		
		ba cerrado

abierto:	ld %r1, %r4
		subcc %r4, eject, %r0 !cerrar
		be cerrar
		ba abierto

reproduciendo:	ld %r1, %r4
			subcc %r4, eject, %r0
			be esperar
			subcc %r4, pause, %r0
			be pausar
			subcc %r4, stop, %r0
			be detener
			ba reproduciendo

pausado:	ld %r1, %r4
		subcc %r4, eject, %r0
		be esperar
		subcc %r4, play, %r0
		be reproducir
		subcc %r4, stop, %r0
		be detener
		ba pausado
 

.end
	
