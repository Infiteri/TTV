#pragma once

#include "isr.h"

typedef void (*IRQHandler)(Registers *reg);

void i686_IRQInitialize();
void i686_IRQRegisterHanlder(int irq, IRQHandler handler);
