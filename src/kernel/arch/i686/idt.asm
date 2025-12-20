[bits 32]

; void i686_IDTLoad(IDTDescriptor *desc);

global i686_IDTLoad
i686_IDTLoad:
  push ebp
  mov ebp, esp

  mov eax, [ebp + 8]
  lidt [eax]

  mov esp, ebp
  pop ebp
  ret
