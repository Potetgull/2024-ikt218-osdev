global setGdt
GLOBAL idt_flush    ; Allows the C code to call idt_flush().

gdtr DW 0 ; For limit storage
     DD 0 ; For base storage
 
setGdt:
   MOV   AX, [esp + 4]

   LGDT  [eax]

   MOV   AX, 0x10 ; 0x10 is a stand-in for your data segment
   MOV   DS, AX
   MOV   ES, AX
   MOV   FS, AX
   MOV   GS, AX
   MOV   SS, AX
   JMP   0x08:.reload_cs ;Must jump in order to reset the cs register. It does not react any other way.

.reload_cs
 RET


idt_flush:
   mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter.
   lidt [eax]        ; Load the IDT pointer.
   ret