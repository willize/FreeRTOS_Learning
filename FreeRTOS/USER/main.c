#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
/************************************************
 ALIENTEK Ì½Ë÷ÕßSTM32F407¿ª·¢°å FreeRTOSÊµÑé2-1
 FreeRTOSÒÆÖ²ÊµÑé-¿âº¯Êý°æ±¾
 ¼¼ÊõÖ§³Ö£ºwww.openedv.com
 ÌÔ±¦µêÆÌ£ºhttp://eboard.taobao.com 
 ¹Ø×¢Î¢ÐÅ¹«ÖÚÆ½Ì¨Î¢ÐÅºÅ£º"ÕýµãÔ­×Ó"£¬Ãâ·Ñ»ñÈ¡STM32×ÊÁÏ¡£
 ¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾  
 ×÷Õß£ºÕýµãÔ­×Ó @ALIENTEK
************************************************/

#define START_TASK_STACK  120
#define START_TASK_PRIO   1
void start_task(void* pvParameters);
TaskHandle_t StartTask_Handle;


#define TASK1_LED_STACK  120
#define TASK1_LED_PRIO   2
void task1_LED(void* pvParameters);
TaskHandle_t Task1LED_Handle;	

#define TASK2_LED_STACK  120
#define TASK2_LED_PRIO   3
TaskHandle_t Task2LED_Handle;	
void task2_LED(void* pvParameters);

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//ÉèÖÃÏµÍ³ÖÐ¶ÏÓÅÏÈ¼¶·Ö×é4
	delay_init(168);		//³õÊ¼»¯ÑÓÊ±º¯Êý
	uart_init(115200);     	//³õÊ¼»¯´®¿Ú
	LED_Init();		        //³õÊ¼»¯LED¶Ë¿Ú
	xTaskCreate(	(TaskFunction_t ) start_task,
								(char *					) "start_task",
								(uint16_t				) START_TASK_STACK,
								(void *					) NULL,
								(UBaseType_t		) START_TASK_PRIO,
								(TaskHandle_t*	) &StartTask_Handle ) ;
														
        
    vTaskStartScheduler();          //¿ªÆôÈÎÎñµ÷¶È
}
 
void start_task(void * pvParameters)//¿ªÊ¼ÈÎÎñ¡
{
		xTaskCreate((TaskFunction_t ) task1_LED,
								(char *					) "task1_LED",
								(uint16_t				) TASK1_LED_STACK ,
								(void *					) NULL,
								(UBaseType_t		) TASK1_LED_PRIO,
								(TaskHandle_t*	) &Task1LED_Handle ) ;
								
		xTaskCreate((TaskFunction_t ) task2_LED,
								(char *					) "task2_LED",
								(uint16_t				) TASK2_LED_STACK ,
								(void *					) NULL,
								(UBaseType_t		) TASK2_LED_PRIO,
								(TaskHandle_t*	) &Task2LED_Handle ) ;
		vTaskDelete(NULL);//Startask_Handle
}

void task1_LED(void* pvParameters)
{
	u8 task1_num=0;
	while(1)
	{
		task1_num++;
		//printf("task1_num:%d\r\n",task1_num);
		if(task1_num==5)
		{
			vTaskDelete(Task2LED_Handle);
			printf("Del_Task2!!\r\n");
		}
		LED0=0;
		vTaskDelay(200);
		LED0=1;
		vTaskDelay(800);
		printf("task1_num:%d\r\n",task1_num);
		
	}
}


void task2_LED(void* pvParameters)
{
	u8 task2_num=0;
	while(1)
	{
		task2_num++;
		
		LED1=0;
		vTaskDelay(500);
		LED1=1;
		vTaskDelay(500);
		printf("task2_num:%d\r\n",task2_num);
	}
}


