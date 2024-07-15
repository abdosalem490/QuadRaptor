
#ifndef SPI_SPI_H_
#define SPI_SPI_H_


#include "ch32v20x.h"
#include "std_macros.h"

#define SPI_Master  1
#define SPI_Slave   0

#define SPI_Data_Size_8_bits 0
#define SPI_Data_Size_16_bits 1


/* SPI_BaudRate_Prescaler */
#define SPI_Prescaler_2            ((uint16_t)0x0000)
#define SPI_Prescaler_4            ((uint16_t)0x0008)
#define SPI_Prescaler_8            ((uint16_t)0x0010)
#define SPI_Prescaler_16           ((uint16_t)0x0018)
#define SPI_Prescaler_32           ((uint16_t)0x0020)
#define SPI_Prescaler_64           ((uint16_t)0x0028)
#define SPI_Prescaler_128          ((uint16_t)0x0030)
#define SPI_Prescaler_256          ((uint16_t)0x0038)


typedef enum
{

   OFF,
   ON

} Status;


/* SPI structure definition */
typedef struct
{

    uint8_t SPI_Mode_Selection;

    uint8_t SPI_Data_Size;

    uint16_t SPI_Data_Rate;


} SPI_Structure;

void SPI_Initialize(SPI_TypeDef *SPIx, SPI_Structure *structure);
void SPI_Turn_On_Off(SPI_TypeDef *SPIx, Status status );
void SPI_Send_Data(SPI_TypeDef *SPIx, uint16_t data);
uint16_t SPI_Receive_Data(SPI_TypeDef *SPIx);
Status SPI_IS_Transmit_Buffer_Empty(SPI_TypeDef *SPIx);
Status SPI_IS_Receive_Buffer_Not_Empty(SPI_TypeDef *SPIx);


#endif /* SPI_SPI_H_ */
