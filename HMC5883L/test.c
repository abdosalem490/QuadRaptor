/*
 * main.c
 *
 *  Created on: Jun 11, 2024
 *      Author: mohab
 */

#include "debug.h"
#include "math.h"
#include "hmc5883l.h"

/* Just a character buffer to print the angle rates */
char x_buffer[10], y_buffer[10], z_buffer[10];

int main(void)
{
    hmc5883l_packet obj;
    USART_Printf_Init(57600);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();

    hmc5883l_init();
    Delay_Ms(70);

    while(1){
      hmc5883l_read(&obj);


      gcvt(obj.magnetometer_raw[X_AXIS], 6, x_buffer);
      gcvt(obj.magnetometer_raw[Y_AXIS], 6, y_buffer);
      gcvt(obj.magnetometer_raw[Z_AXIS], 6, z_buffer);
      printf("%s, %s, %s\r\n", x_buffer, y_buffer, z_buffer);

      Delay_Ms(50);
    }

}
