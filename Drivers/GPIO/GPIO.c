#include "GPIO.h"

void GPIO_Initialize(GPIO_TypeDef *port, GPIO_Structure *structure)
{
    // every pin should be configured with only four pins
    if(((uint32_t)structure->GPIO_Pin_ & ((uint32_t)0x00FF)) != 0x00)
    {
        // Access Config regiser Low
        uint8_t pins = (uint16_t)structure->GPIO_Pin_;
        // the output mode
        if ((structure->GPIO_Mode_)  == GPIO_Mode_Out_OD_ || (structure->GPIO_Mode_) == GPIO_Mode_Out_PP_)
        {
            // Set the speed first
            for(int i = 0; i < 8; i++)
            {
                if(READ_BIT(pins, i))
                {
                    // Set the speed to the corresponding bit in CFGLR
                    uint8_t startBit = i * 4;
                    if((uint8_t)structure->GPIO_Speed_ == 1)
                    {
                        SET_BIT(port->CFGLR, startBit);
                        CLEAR_BIT(port->CFGLR, startBit + 1);
                    }
                    if ((uint8_t)structure->GPIO_Speed_ == 2)
                    {
                        CLEAR_BIT(port->CFGLR, startBit);
                        SET_BIT(port->CFGLR, startBit + 1);
                    }
                    if ((uint8_t)structure->GPIO_Speed_ == 3)
                    {
                        SET_BIT(port->CFGLR, startBit);
                        SET_BIT(port->CFGLR, startBit + 1);
                    }
                    // open drain output 01
                    if ((uint8_t)(structure->GPIO_Mode_)  == GPIO_Mode_Out_OD_)
                    {
                        SET_BIT(port->CFGLR, startBit + 2);
                        CLEAR_BIT(port->CFGLR, startBit + 3);
                    }
                    // push pull output 00
                    if ((uint8_t)(structure->GPIO_Mode_)  == GPIO_Mode_Out_PP_)
                    {
                        CLEAR_BIT(port->CFGLR, startBit + 2);
                        CLEAR_BIT(port->CFGLR, startBit + 3);
                    }
                }
            }
        }
        if (structure->GPIO_Mode_ == GPIO_Mode_IPD_ || structure->GPIO_Mode_ == GPIO_Mode_IPU_)
        {
            for(int i = 0; i < 8; i++)
            {
                if(READ_BIT(pins, i))
                {
                    uint8_t startBit = i * 4;
                    CLEAR_BIT(port->CFGLR, startBit);
                    CLEAR_BIT(port->CFGLR, startBit + 1);
                    CLEAR_BIT(port->CFGLR, startBit + 2);
                    SET_BIT(port->CFGLR, startBit + 3);

                    // Enable the internal pull up resistor
                    if (structure->GPIO_Mode_ == GPIO_Mode_IPU_)
                    {
                        SET_BIT(port->BSHR, i);
                    }
                    // Enable the internal pull down resistor
                    if (structure->GPIO_Mode_ == GPIO_Mode_IPD_)
                    {
                        SET_BIT(port->BCR, i);
                    }
                }
            }
        }

        if (structure->GPIO_Mode_ == GPIO_Mode_AIN_ || structure->GPIO_Mode_ == GPIO_Mode_IN_FLOATING_)
        {
            for(int i = 0; i < 8; i++)
            {
                if(READ_BIT(pins, i))
                {
                    uint8_t startBit = i * 4;
                    CLEAR_BIT(port->CFGLR, startBit);
                    CLEAR_BIT(port->CFGLR, startBit + 1);
                    if(structure->GPIO_Mode_ == GPIO_Mode_AIN_)
                    {
                        CLEAR_BIT(port->CFGLR, startBit + 2);
                        CLEAR_BIT(port->CFGLR, startBit + 3);
                    }
                    if(structure->GPIO_Mode_ == GPIO_Mode_IN_FLOATING_)
                    {
                        SET_BIT(port->CFGLR, startBit + 2);
                        CLEAR_BIT(port->CFGLR, startBit + 3);
                    }
                }
            }
        }
    }
    if(structure->GPIO_Pin_ > 0x00FF)
    {
        uint8_t pins = ((uint16_t)structure->GPIO_Pin_) >> 8;
        // Access config register High
        if ((structure->GPIO_Mode_)  == GPIO_Mode_Out_OD_ || (structure->GPIO_Mode_) == GPIO_Mode_Out_PP_)
        {
            // Set the speed first
            for(int i = 0; i < 8; i++)
            {
                if(READ_BIT(pins, i))
                {
                    // Set the speed to the corresponding bit in CFGHR
                    uint8_t startBit = i * 4;
                    if((uint8_t)structure->GPIO_Speed_ == 1)
                    {
                        SET_BIT(port->CFGHR, startBit);
                        CLEAR_BIT(port->CFGHR, startBit + 1);
                    }
                    if ((uint8_t)structure->GPIO_Speed_ == 2)
                    {
                        CLEAR_BIT(port->CFGHR, startBit);
                        SET_BIT(port->CFGHR, startBit + 1);
                    }
                    if ((uint8_t)structure->GPIO_Speed_ == 3)
                    {
                        SET_BIT(port->CFGHR, startBit);
                        SET_BIT(port->CFGHR, startBit + 1);
                    }
                    // open drain output 01
                    if ((uint8_t)(structure->GPIO_Mode_)  == GPIO_Mode_Out_OD_)
                    {
                        SET_BIT(port->CFGHR, startBit + 2);
                        CLEAR_BIT(port->CFGHR, startBit + 3);
                    }
                    // push pull output 00
                    if ((uint8_t)(structure->GPIO_Mode_)  == GPIO_Mode_Out_PP_)
                    {
                        CLEAR_BIT(port->CFGHR, startBit + 2);
                        CLEAR_BIT(port->CFGHR, startBit + 3);
                    }
                }
            }
        }
        if (structure->GPIO_Mode_ == GPIO_Mode_IPD_ || structure->GPIO_Mode_ == GPIO_Mode_IPU_)
        {
            for(int i = 0; i < 8; i++)
            {
                if(READ_BIT(pins, i))
                {
                    uint8_t startBit = i * 4;
                    CLEAR_BIT(port->CFGHR, startBit);
                    CLEAR_BIT(port->CFGHR, startBit + 1);
                    CLEAR_BIT(port->CFGHR, startBit + 2);
                    SET_BIT(port->CFGHR, startBit + 3);

                    // Enable the internal pull up resistor
                    if (structure->GPIO_Mode_ == GPIO_Mode_IPU_)
                    {
                        SET_BIT(port->BSHR, i + 8);
                    }
                    // Enable the internal pull down resistor
                    if (structure->GPIO_Mode_ == GPIO_Mode_IPD_)
                    {
                        SET_BIT(port->BCR, i + 8);
                    }
                }
            }
        }

        if (structure->GPIO_Mode_ == GPIO_Mode_AIN_ || structure->GPIO_Mode_ == GPIO_Mode_IN_FLOATING_)
        {
            for(int i = 0; i < 8; i++)
            {
                if(READ_BIT(pins, i))
                {
                    uint8_t startBit = i * 4;
                    CLEAR_BIT(port->CFGHR, startBit);
                    CLEAR_BIT(port->CFGHR, startBit + 1);
                    if(structure->GPIO_Mode_ == GPIO_Mode_AIN_)
                    {
                        CLEAR_BIT(port->CFGHR, startBit + 2);
                        CLEAR_BIT(port->CFGHR, startBit + 3);
                    }
                    if(structure->GPIO_Mode_ == GPIO_Mode_IN_FLOATING_)
                    {
                        SET_BIT(port->CFGHR, startBit + 2);
                        CLEAR_BIT(port->CFGHR, startBit + 3);
                    }
                }
            }
        }
    }
    return;
}

uint8_t GPIO_Read_Pin(GPIO_TypeDef *GPIOx, uint16_t pinNumber)
{
    return READ_BIT(GPIOx->INDR, pinNumber); // Read the state of the specified pin
}

uint16_t GPIO_Read_Port(GPIO_TypeDef *GPIOx)
{
    uint16_t port = (uint16_t)GPIOx->INDR; // Read the state of the entire port
    return port;
}

void GPIO_Write_Pins(GPIO_TypeDef *GPIOx, uint16_t pins_numbers, GPIO_Bit_Value bitValue)
{
    if (bitValue == ONE)
    {
        GPIOx->BSHR = pins_numbers; // Set the specified pins
    }
    else
    {
        GPIOx->BCR = pins_numbers; // Clear the specified pins
    }
}

void GPIO_Toggle_Pin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
    TOGGLE_BIT(GPIOx->OUTDR, PinNumber); // Toggle the state of the specified pin
}

void GPIO_Write_Port(GPIO_TypeDef *GPIOx, uint16_t portValue)
{
    GPIOx->OUTDR = portValue; // Write a value to the entire port
}

uint16_t GPIO_Read_Data_Register(GPIO_TypeDef *GPIOx)
{
    uint16_t port = (uint16_t)GPIOx->OUTDR; // Read the output data register
    return port;
}

uint8_t GPIO_Read_Bit_In_Data_Register(GPIO_TypeDef *GPIOx, uint16_t bitNumber)
{
    uint8_t bit = READ_BIT(GPIOx->OUTDR, bitNumber); // Read a specific bit in the output data register
    return bit;
}
