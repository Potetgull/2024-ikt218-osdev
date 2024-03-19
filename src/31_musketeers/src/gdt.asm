global setGdt

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
   JMP   0x08:.reload_cs

.reload_cs
 RET