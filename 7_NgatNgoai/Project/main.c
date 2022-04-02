#include "stm32f10x.h"

static void GPIOLed_Config(void);
static void GPIONutNhan_Config(void);
static void EXTI0_Config(void);

void Delay_ms(uint32_t u32Delay);

int main(void)
{
	GPIOLed_Config();
	GPIONutNhan_Config();
	EXTI0_Config();
	while(1)
	{
		
	}
}

static void GPIOLed_Config(void)
{
	GPIO_InitTypeDef GPIO_LED;
	GPIO_LED.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_LED.GPIO_Pin = GPIO_Pin_13;
	GPIO_LED.GPIO_Speed = GPIO_Speed_50MHz;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_Init(GPIOC, &GPIO_LED);
}

static void GPIONutNhan_Config(void)
{
	GPIO_InitTypeDef GPIO_NutNhan;
	GPIO_NutNhan.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_NutNhan.GPIO_Pin = GPIO_Pin_0;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_Init(GPIOA, &GPIO_NutNhan);
}

static void EXTI0_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI->PR |= (1 << 0); //clear it
	RCC->APB2ENR |= (1 << 0); //Anabling Preiph AFIO */
	AFIO->EXTICR[0] &= ~(0xF << 0); //EXTI0 PAx
	EXTI->RTSR &= ~(1 << 0); //falling trigger
	EXTI->FTSR |= (1 << 0); //falling trigger
	EXTI->SWIER &= ~(1 << 0);
	EXTI->EMR &= ~(1 << 0);
	EXTI->IMR |= (1 << 0); //mask on line 0
	NVIC->IP[0] = 0;
	NVIC->ISER[0] |= (1 << 6); //enable it
}

void Delay_ms(uint32_t u32Delay)
{
	while(u32Delay)
		{
			SysTick->LOAD = 72U * 1000U - 1U;
			SysTick->VAL = 0U;
			SysTick->CTRL = 5U;
			while(!(SysTick->CTRL & (1U << 16U)));
			--u32Delay;
		}
}
