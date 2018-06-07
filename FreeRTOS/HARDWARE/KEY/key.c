#include "key.h"
#include "delay.h"

/************PE3->Key1*************/
/************PE4->Key0*************/

void Key_Init()
{

	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOA,GPIOE时钟
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4; //KEY0 KEY1 KEY2对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP对应引脚PA0
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA0
} 

u8 Key_Scan(u8 model)
{
	static u8 key_up=1;   //松手标志位
	if (model==1)key_up=1;
	if (key_up && (KEY0==0 || KEY1==0 || KEY_UP==1))
	{
		delay_ms(20);
		key_up=0;
		if (KEY0==0)       return KEY0_PRES;
		else if (KEY1==0)  return KEY1_PRES;
		else if (KEY_UP==1)return WKUP_PRES;
	}else if((KEY0==1 && KEY1==1 && KEY_UP==0)) key_up=1;
	return 0;
}

