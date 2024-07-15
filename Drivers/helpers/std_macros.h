#ifndef STD_MACROS_H_
#define STD_MACROS_H_

#define REGISTER_SIZE	16
#define SET_BIT(reg,d) reg |=(1<<d)
#define CLEAR_BIT(reg,d) reg &=(~(1<<d))
#define TOGGLE_BIT(reg,d) reg ^= (1<<d)
#define ROR(reg,d) (reg>>d)|(reg<<(REGISTER_SIZE-d))
#define ROL(reg,d) (reg<<d)|(reg>>(REGISTER_SIZE-d))
#define READ_BIT(reg,d) ((reg & (1<<d))>>d)
#define IS_BIT_CLEAR(reg,d) ~((reg & (1<<d))>>d)
#define IS_BIT_SET(reg,d) (reg & (1<<d))>>d

#endif /* STD_MACROS_H_ */
