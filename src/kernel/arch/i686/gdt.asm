[bits 32]

;  void i686_GDTLoad(GDTDescriptor *desc, uint16_t codeSegment, uint16_t dataSegment);
global i686_GDTLoad
i686_GDTLoad:
  push ebp
  mov ebp, esp

  mov eax, [ebp + 8]
  lgdt [eax]

  mov eax, [ebp + 12]
  push eax
  push .rcs
  retf 

; reload code segment ?
.rcs: 
  mov ax, [ebp + 16]
  mov ds, ax 
  mov es, ax 
  mov fs, ax 
  mov gs, ax 
  mov ss, ax 

  mov esp, ebp
  pop ebp
  ret
