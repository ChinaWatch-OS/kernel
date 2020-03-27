#include <drivers/spi.h>

void SPI_Init(void)
{
   GPIO_SetupMode(SPI_CS,   SPI_CS_MODE);
   GPIO_SetupMode(SPI_SCLK, SPI_SCLK_MODE);
   GPIO_SetupMode(SPI_MOSI, SPI_MOSI_MODE);
   GPIO_SetupMode(SPI_MISO, SPI_MISO_MODE);
	
   /* IO ports setup,
      all ports exclude MISO outputs */
   //SPI_DDRX  = (1 << SPI_MOSI) | (1 << SPI_SCLK) | (1 << SPI_CS) | (0 << SPI_MISO);  // SPI CONF0
   //SPI_PORTX = (1 << SPI_MOSI) | (1 << SPI_SCLK) | (1 << SPI_CS) | (1 << SPI_MISO);  // SPI CONF1

   SPI_DDRX  = 0b1110;
   SPI_PORTX = 0b1111;

   // /* Bigger bit forward, master, mode 0 */
   //SPCR = (1 << SPE) | (0 << DORD) | (1 << MSTR) | (0 << CPOL) | (0 << CPHA) | (1 << SPR1) | (0 << SPR0);
   SPCR = 0b1010010;
   //SPSR0 = (0 << SPI2X);
   SPSR0 = 0;
}

bool SPI_IsBusy(void)
{
	return (SPSR0 & (SPIF>>1));
}

uint8_t SPI_ReadByte(uint8_t data)
{
   uint8_t report;
   SPI_PORTX &= ~(1<<SPI_CS);
   SPDR_TX = data;
   while(!(SPSR0 & (SPIF>>1)));
   report = SPDR_RX;
   SPI_PORTX |= (1<<SPI_CS); 
   return report; 
}

void SPI_ReadArray(uint8_t *data, uint16_t length)
{
   SPI_PORTX &= ~(1<<SPI_CS); 
   while(length--){
      SPDR_TX = *data;
      //while(!(SPSR0 & (1<<SPIF)));
	  while(!(SPSR0 & (SPIF>>1)));
      *data++ = SPDR_RX; 
   }
   SPI_PORTX |= (1<<SPI_CS); 
}

void SPI_WriteByte(uint8_t data)
{
   SPI_PORTX &= ~(1<<SPI_CS);
   SPDR_TX = data;
   while(!(SPSR0 & (SPIF>>1)));
   SPI_PORTX |= (1<<SPI_CS);
}

void SPI_WriteArray(uint8_t *data, uint16_t length)
{
   SPI_PORTX &= ~(1<<SPI_CS); 
   while(length--){
      SPDR_TX = *data++;
      while(!(SPSR0 & (SPIF>>1)));
   }
   SPI_PORTX |= (1<<SPI_CS); 
}