#include "sys.h"

//下面的方式是通过直接操作HAL库函数方式读取IO
#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define KEY1 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)	//PE3 
#define KEY_UP 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	//PA0

#define KEY0_PRES 	1
#define KEY1_PRES		2
#define WKUP_PRES   3


void Key_Init(void);
u8 Key_Scan(u8 model);
