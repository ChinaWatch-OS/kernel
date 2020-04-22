/*
* This file is part of the ChinaWatch OS project.
*
* Copyright (C) 2020 ChinaWatch OS
* Copyright (C) 2019 AJScorp
*
* This program is free software; you can redistribute it and/or modify 
* it under the terms of the GNU General Public License as published by 
* the Free Software Foundation; version 3 of the License.
*
* This program is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty of 
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License 
* along with this program; if not, write to the Free Software 
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA. 
*/
#pragma once
#include <systypes.h>
#include <mt6261.h>
#include <drivers/gpio.h>

#define SPI_CS        GPIO26
#define SPI_CS_MODE   GPIO26_MODE_SPICS
#define SPI_SCLK      GPIO27
#define SPI_SCLK_MODE GPIO27_MODE_SPISCK
#define SPI_MOSI      GPIO28
#define SPI_MOSI_MODE GPIO28_MODE_SPIMOSI
#define SPI_MISO      GPIO29
#define SPI_MISO_MODE GPIO29_MODE_SPIMISO

#define SPI_DDRX   (*(volatile uint32_t *)(SPI_base + 0x0))
#define SPI_PORTX   (*(volatile uint32_t *)(SPI_base + 0x4))

// Defines the SPI TX source address register.
#define SPI_TX_SRC_REG (*(volatile uint32_t *)(SPI_base + 0x8))
// Defines the SPI RX destination address register.
#define SPI_RX_DST_REG (*(volatile uint32_t *)(SPI_base + 0xC))
// Defines the SPI TX data (fifo) register.
#define SPDR_TX (*(volatile uint32_t *)(SPI_base + 0x10))
// Defines the SPI RX data (fifo) register.
#define SPDR_RX (*(volatile uint32_t *)(SPI_base + 0x14))

// SPI Control Register
#define SPCR    (*(volatile uint32_t *)(SPI_base + 0x18))
// SPI Status Registers
#define SPSR0 (*(volatile uint32_t *)(SPI_base + 0x1C))
#define SPSR1 (*(volatile uint32_t *)(SPI_base + 0x20))

#define SPR0  0
#define SPR1  1
#define CPHA  2
#define CPOL  3
#define MSTR  4
#define DORD  5
#define SPE   6
#define SPIE  7

#define SPI2X 0
#define SPIF  7

enum SPI_DIRECTION
{
    SPI_TX, // Transmission
    SPI_RX  // Reception
};
typedef enum SPI_DIRECTION SPI_DIRECTION;

void SPI_Init(void);

bool SPI_IsBusy(void);
uint8_t SPI_ReadByte(uint8_t data);
void SPI_ReadArray(uint8_t *data, uint16_t length);
void SPI_WriteByte(uint8_t data);
void SPI_WriteArray(uint8_t *data, uint16_t length);