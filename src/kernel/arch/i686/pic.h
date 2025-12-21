#pragma once

#include <stdint.h>

void i686_PICConfigure(uint8_t offsetPic1, uint8_t offsetPic2);
void i686_PICMask(int irq);
void i686_PICUnmask(int irq);
void i686_PICDisable();
void i686_PICSendEndOfInterrupt(int irq);
uint16_t i686_PICReadIRQRequestRegister();
uint16_t i686_PICReadInServiceRegister();
