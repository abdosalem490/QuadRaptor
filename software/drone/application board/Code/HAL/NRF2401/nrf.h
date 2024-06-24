/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   header file for NRF2401                                                                                     |
 * |    @file           :   nrf_config.h                                                                                                |
 * |    @author         :   Ahmed Fawzy                                                                                                 |
 * |    @origin_date    :   18/06/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this header file contains some interface function to be used with NRF2401                                   |
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    MIT License                                                                                                                     |
 * |                                                                                                                                    |
 * |    Copyright (c) - 2024 - Abdelrahman Mohamed Salem - All Rights Reserved                                                          |
 * |                                                                                                                                    |
 * |    Permission is hereby granted, free of charge, to any person obtaining a copy                                                    |
 * |    of this software and associated documentation files (the "Software"), to deal                                                   |
 * |    in the Software without restriction, including without limitation the rights                                                    |
 * |    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                                                       |
 * |    copies of the Software, and to permit persons to whom the Software is                                                           |
 * |    furnished to do so, subject to the following conditions:                                                                        |
 * |                                                                                                                                    |
 * |    The above copyright notice and this permission notice shall be included in all                                                  |
 * |    copies or substantial portions of the Software.                                                                                 |
 * |                                                                                                                                    |
 * |    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                                                      |
 * |    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                                                        |
 * |    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                                                     |
 * |    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                                                          |
 * |    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                                                   |
 * |    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                                                   |
 * |    SOFTWARE.                                                                                                                       |
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @history_change_list                                                                                                            |
 * |    ====================                                                                                                            |
 * |    Date            Version         Author                          Description                                                     |
 * |    18/06/2023      1.0.0           Ahmed Fawzy                     Interface Created.                                              |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */


#ifndef USER_NRF_H_
#define USER_NRF_H_

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reaosn: contains standard integer definitions
 */
#include "stdint.h"

/******************************************************************************
 * Preprocessor Constants
 *******************************************************************************/

/******************************************************************************
 * Configuration Constants
 *******************************************************************************/

/******************************************************************************
 * Macros
 *******************************************************************************/

/******************************************************************************
 * Typedefs
 *******************************************************************************/

/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/


/**
 *  \b function                                 :       None
 *  \b Description                              :       Gets the status of the NRF module.
 *  @param  void [IN]                           :       None
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       The status byte.
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
uint8_t get_status();

/**
 *  \b function                                 :       None
 *  \b Description                              :       Sends a command to the NRF module.
 *  @param  command [IN]                        :       The command byte to send.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       The status byte returned by the NRF module.
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
uint8_t NRF_send_command(uint8_t command);


/**
 *  \b function                                 :       None
 *  \b Description                              :       Writes a value to an NRF register.
 *  @param  reg [IN]                            :       The register to write to.
 *  @param  value [IN]                          :       The value to write.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       The status byte returned by the NRF module.
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
uint8_t NRF_write_register(uint8_t reg, uint8_t value);

/**
 *  \b function                                 :       None
 *  \b Description                              :       Writes a buffer to an NRF register.
 *  @param  reg [IN]                            :       The register to write to.
 *  @param  buf [IN]                            :       The buffer containing the data to write.
 *  @param  len [IN]                            :       The length of the buffer.
 *  @param  arg_u32TaskPriority [IN]            :       None
 *  @param  arg_pTaskHandle [OUT]               :       None
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void NRF_write_data_register(uint8_t reg, const uint8_t *buf, uint8_t len);

/**
 *  \b function                                 :       None
 *  \b Description                              :       Reads a value from an NRF register.
 *  @param  reg [IN]                            :       The register to read from.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       The value read from the register.
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
uint8_t NRF_read_register(uint8_t reg);

/**
 *  \b function                                 :       None
 *  \b Description                              :       Writes data to the NRF module.
 *  @param  buf [IN]                            :       The buffer containing the data to write.
 *  @param  data_len [IN]                       :       The length of the data.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       True if the write was successful, false otherwise.
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void NRF_write(const void* buf, uint8_t data_len);

/**
 *  \b function                                 :       None
 *  \b Description                              :       Initializes the NRF module.
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None
 *  @param  arg_u16TaskStackDepth [IN]          :       None
 *  @param  arg_u32TaskPriority [IN]            :       None
 *  @param  arg_pTaskHandle [OUT]               :       None
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void NRF_init();

/**
 *  \b function                                 :       None
 *  \b Description                              :       Starts listening for incoming data.
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None
 *  @param  arg_u16TaskStackDepth [IN]          :       None
 *  @param  arg_u32TaskPriority [IN]            :       None
 *  @param  arg_pTaskHandle [OUT]               :       None
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void NRF_start_listening();

/**
 *  \b function                                 :       None
 *  \b Description                              :       Stops listening for incoming data.
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None
 *  @param  arg_u16TaskStackDepth [IN]          :       None
 *  @param  arg_u32TaskPriority [IN]            :       None
 *  @param  arg_pTaskHandle [OUT]               :       None
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void NRF_stop_listening();

/**
 *  \b function                                 :       None
 *  \b Description                              :       Reads data from an NRF register into a buffer.
 *  @param  reg [IN]                            :       The register to read from.
 *  @param  buf [IN]                            :       The buffer to store the data.
 *  @param  len [IN]                            :       The length of the buffer.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       The status byte returned by the NRF module.
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
uint8_t NRF_read_data_register(uint8_t reg, uint8_t *buf, uint8_t len);


/**
 *  \b function                                 :       None
 *  \b Description                              :       Opens a writing pipe with a specific address.
 *  @param  address [IN]                        :       The address of the writing pipe.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void NRF_openWritingPipe(const uint8_t *address);

/**
 *  \b function                                 :       None
 *  \b Description                              :       Opens a reading pipe with a specific address.
 *  @param  child [IN]                          :       The child pipe number.
 *  @param  address [IN]                        :       The address of the reading pipe.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void NRF_openReadingPipe(uint8_t child, const uint8_t *address);

/**
 *  \b function                                 :       None
 *  \b Description                              :       Reads payload data from the NRF module.
 *  @param  buf [IN]                            :       The buffer to store the data.
 *  @param  len [IN]                            :       The length of the buffer.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       The status byte returned by the NRF module.
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
uint8_t NRF_read_payload(void *buf, uint8_t len);

/**
 *  \b function                                 :       None
 *  \b Description                              :       Reads data from the NRF module into a buffer.
 *  @param  buf [IN]                            :       The buffer to store the data.
 *  @param  len [IN]                            :       The length of the buffer.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void NRF_read(void *buf, uint8_t len);

/**
 *  \b function                                 :       None
 *  \b Description                              :       Checks if data is available in the NRF module.
 *  @param  void [IN]                           :       None.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       True if data is available, false otherwise.
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
uint8_t NRF_data_available();

#endif /* USER_NRF_H_ */
