

#ifndef GPIO_GPIO_CONFIG_H_
#define GPIO_GPIO_CONFIG_H_


#include "ch32v20x.h"

typedef enum
{
	ZERO ,
	ONE

}GPIO_Bit_Value;

// Pin Toggling frequency
typedef enum
{

    GPIO_Speed_10MHz_ = 1 ,
	GPIO_Speed_2MHz_ ,
    GPIO_Speed_50MHz_
} GPIO_Pin_Speed;

// pin mode
/********************************
 * input can be:
 *              1- floating (without pull up or pull down connection)
 *              2- analog
 *              2- pull up
 *              3- pull down
 * output can be:
 *              1- output open drain
 *              2- output push pull
 */
typedef enum
{
    GPIO_Mode_AIN_  ,
    GPIO_Mode_IN_FLOATING_  ,
    GPIO_Mode_IPD_ ,
    GPIO_Mode_IPU_ ,
    GPIO_Mode_Out_OD_ ,
    GPIO_Mode_Out_PP_
} GPIO_Pin_Mode;

// Define a structure of GPIO pin that contain the pin number, speed and mode
typedef struct
{
    uint16_t GPIO_Pin_;

    GPIO_Pin_Speed GPIO_Speed_;

    GPIO_Pin_Mode GPIO_Mode_;

} GPIO_Structure;




#endif /* GPIO_GPIO_CONFIG_H_ */
