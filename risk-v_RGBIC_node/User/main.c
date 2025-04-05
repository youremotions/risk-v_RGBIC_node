/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/12/25
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *Multiprocessor communication mode routine:
 *Master:USART1_Tx(PD5)\USART1_Rx(PD6).
 *This routine demonstrates that USART1 receives the data sent by CH341 and inverts
 *it and sends it (baud rate 115200).
 *
 *Hardware connection:PD5 -- Rx
 *                     PD6 -- Tx
 *
 */

#include "debug.h"


/* Global define */


/* Global Variable */
vu8 val;


/* CH1CVR register Definition */
#define TIM1_CH1CVR_ADDRESS    0x40012C34
#define TIM1_CH2CVR_ADDRESS    0x40012C38
#define TIM1_CH3CVR_ADDRESS    0x40012C3C
#define TIM1_CH4CVR_ADDRESS    0x40012C40
#define TIM2_CH1CVR_ADDRESS    0x40000034
#define TIM2_CH2CVR_ADDRESS    0x40000038
#define TIM2_CH3CVR_ADDRESS    0x4000003C
#define TIM2_CH4CVR_ADDRESS    0x40000040

/* Private variables */
#define DUTY_CYCLE_SIZE 3
#define MAX_DUTY 100
#define MIN_DUTY 0
u16 pbuf[DUTY_CYCLE_SIZE] = {10, 50, 80}; // this is the array of duty cycles

/*********************************************************************
 * @fn      TIM1_PWMOut_Init
 *
 * @brief   Initializes TIM1 PWM output.
 *
 * @param   arr - the period value.
 *          psc - the prescaler value.
 *          ccp - the pulse value.
 *
 * @return  none
 */
void TIM1_PWMOut_Init(u16 arr, u16 psc, u16 ccp)
{
    GPIO_InitTypeDef        GPIO_InitStructure = {0};
    TIM_OCInitTypeDef       TIM_OCInitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_TIM1, ENABLE); // original
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_TIM1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // original
    // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure); // original 
    // GPIO_Init(GPIOC, &GPIO_InitStructure);

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ccp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
}

/*********************************************************************
 * @fn      TIM1_Pin_0_PWMOut_Init
 *
 * @brief   Initializes TIM1_CH2 PWM output.
 *
 * @param   arr - the period value.
 *          psc - the prescaler value.
 *          ccp - the pulse value.
 *
 * @return  none
 */
void TIM1_Pin_0_PWMOut_Init(u16 arr, u16 psc, u16 ccp)
{
    GPIO_InitTypeDef        GPIO_InitStructure = {0};
    TIM_OCInitTypeDef       TIM_OCInitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_TIM1, ENABLE); // original

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure); // original 

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ccp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
}

/*********************************************************************
 * @fn      TIM1_PWMOut_Init
 *
 * @brief   Initializes TIM1 PWM output. modified by ty
 *
 * @param   arr - the period value.
 *          psc - the prescaler value.
 *          ccp - the pulse value.
 *          GPIO_Pin_Port_x - GPIO port.
 *          GPIO_Pin_x - GPIO Pin
 *
 * @return  none
 */
void TIM1_PWMOut_Full_Init(u16 arr, u16 psc, u16 ccp, GPIO_TypeDef *GPIO_Pin_Port_x, u16 GPIO_Pin_x, TIM_TypeDef *TIMx)
{
    GPIO_InitTypeDef        GPIO_InitStructure = {0};
    TIM_OCInitTypeDef       TIM_OCInitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_TIM1 , ENABLE); // original
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC | RCC_APB2Periph_TIM1 , ENABLE); // original
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x; // original
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIO_Pin_Port_x, &GPIO_InitStructure); // original 

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ccp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OC1Init(TIMx, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig(TIMx, ENABLE);
}

/*********************************************************************
 * @fn      TIM2_PWMOut_Init
 *
 * @brief   Initializes TIM2 PWM output.
 *
 * @param   arr - the period value.
 *          psc - the prescaler value.
 *          ccp - the pulse value.
 *
 * @return  none
 */
void TIM2_PWMOut_Init(u16 arr, u16 psc, u16 ccp)
{ //look at page 66 for dma information
    GPIO_InitTypeDef        GPIO_InitStructure = {0};
    TIM_OCInitTypeDef       TIM_OCInitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_TIM1, ENABLE); // original
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB1Periph_TIM2, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ccp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
}



/*********************************************************************
 * @fn      TIM1_DMA_Init
 *
 * @brief   Initializes the TIM DMAy Channelx configuration.
 *
 * @param   DMA_CHx -
 *            x can be 1 to 7.
 *          ppadr - Peripheral base address.
 *          memadr - Memory base address.
 *          bufsize - DMA channel buffer size.
 *
 * @return  none
 */
void TIM1_DMA_Init(DMA_Channel_TypeDef *DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA_CHx);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
    DMA_InitStructure.DMA_MemoryBaseAddr = memadr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = bufsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA_CHx, &DMA_InitStructure);

    DMA_Cmd(DMA_CHx, ENABLE);
}

/*********************************************************************
 * @fn      TIM2_DMA_Init
 *
 * @brief   Initializes the TIM DMAy Channelx configuration.
 *
 * @param   DMA_CHx -
 *            x can be 1 to 7.
 *          ppadr - Peripheral base address.
 *          memadr - Memory base address.
 *          bufsize - DMA channel buffer size.
 *
 * @return  none
 */
void TIM2_DMA_Init(DMA_Channel_TypeDef *DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA_CHx);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
    DMA_InitStructure.DMA_MemoryBaseAddr = memadr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = bufsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA_CHx, &DMA_InitStructure);

    DMA_Cmd(DMA_CHx, ENABLE);
}

/*********************************************************************
 * @fn      USARTx_CFG
 *
 * @brief   Initializes the USART2 & USART3 peripheral.
 *
 * @return  none
 */
void USARTx_CFG(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    /* USART1 TX-->D.5   RX-->D.6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

/*********************************************************************
 * @fn      initGpioCustom
 *
 * @brief   Initializes GPIO custom.
 *
 * @return  none
 */
void initGpioCustom(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC, ENABLE);

    //Port D
    //Inputs
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    //Outputs
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // | GPIO_Pin_2 this is the RGBIC pin
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    //Port C
    //Inputs
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // Outputs
    // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // | GPIO_Pin_4 this is the test pin
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    // GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      flashLed
 *
 * @brief   Flash and led on a port.
 *
 * @return  none
 */
void flashLed()
{
    // GPIO_WriteBit(GPIOD, GPIO_Pin_0, Bit_SET);
    GPIO_WriteBit(GPIOD, GPIO_Pin_0, (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0) == Bit_SET) ? Bit_RESET : Bit_SET);
    GPIO_WriteBit(GPIOC, GPIO_Pin_0, (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == Bit_SET) ? Bit_RESET : Bit_SET);
    // GPIO_WriteBit(GPIOD, GPIO_Pin_2, Bit_SET); // this is the RGBIC pin
    // GPIO_WriteBit(GPIOC, GPIO_Pin_4, Bit_SET); // this is the test pin
    Delay_Ms(1); 
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemInit(); // setting up at the moment
    SystemCoreClockUpdate();
    RCC_HSEConfig(RCC_HSE_ON);
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    Delay_Init();
    USART_Printf_Init(115200);
//     printf("SystemClk:%d\r\n",SystemCoreClock);
//     printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
    USARTx_CFG();
    // initGpioCustom();

    //timer DMA

    //TIM1
    // TIM1_PWMOut_Init(100-1, 2-1, pbuf[0]); // oringinal
    // TIM1_PWMOut_Full_Init(100-1, 2-1, pbuf[0], GPIOD, GPIO_Pin_2, TIM1);// this works it is pulsing the original pin that the that this fuction came with
    
    //TIM1 pin PD0 fade led, Works
    TIM1_PWMOut_Full_Init(100-1, 2-1, pbuf[0], GPIOD, GPIO_Pin_0, TIM1); //this works
    TIM1_DMA_Init(DMA1_Channel5, (u32)TIM1_CH1CVR_ADDRESS, (u32)pbuf, DUTY_CYCLE_SIZE); // original  // page 66 for dma mapping
    TIM_DMACmd(TIM1, TIM_DMA_Update, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    //TIM1 pin PC4 fade led, Does not work
    // TIM1_PWMOut_Full_Init(100-1, 2-1, pbuf[0], GPIOC, GPIO_Pin_4, TIM1); //this works
    // TIM1_DMA_Init(DMA1_Channel5, (u32)TIM1_CH4CVR_ADDRESS, (u32)pbuf, DUTY_CYCLE_SIZE); // original  // page 66 for dma mapping
    // TIM_DMACmd(TIM1, TIM_DMA_Update, ENABLE);
    // TIM_Cmd(TIM1, ENABLE);
    // TIM_CtrlPWMOutputs(TIM1, ENABLE);

    //TIM2 pin PC0 fade led, Does not work, I'm trying to get it to work
    // TIM1_PWMOut_Full_Init(100-1, 2-1, pbuf[0], GPIOC, GPIO_Pin_0, TIM2);
    // TIM1_DMA_Init(DMA1_Channel2, (u32)TIM2_CH3CVR_ADDRESS, (u32)pbuf, DUTY_CYCLE_SIZE);
    // TIM_DMACmd(TIM2, TIM_DMA_Update, ENABLE);
    // TIM_Cmd(TIM2, ENABLE);
    // TIM_CtrlPWMOutputs(TIM2, ENABLE);

    //TIM2 pin PD7 fade led, Does not work
    // TIM1_PWMOut_Full_Init(100-1, 2-1, pbuf[0], GPIOD, GPIO_Pin_7, TIM2);
    // TIM1_DMA_Init(DMA1_Channel2, (u32)TIM2_CH4CVR_ADDRESS, (u32)pbuf, DUTY_CYCLE_SIZE);
    // TIM_DMACmd(TIM2, TIM_DMA_Update, ENABLE);
    // TIM_Cmd(TIM2, ENABLE);
    // TIM_CtrlPWMOutputs(TIM2, ENABLE);

    //testing not working
    // TIM2_PWMOut_Init(100-1, 48000-1, pbuf[0]);
    // TIM2_DMA_Init(DMA1_Channel2, (u32)TIM2_CH3CVR_ADDRESS, (u32)pbuf, DUTY_CYCLE_SIZE); // original
    // TIM_DMACmd(TIM2, TIM_DMA_Update, ENABLE);
    // TIM_Cmd(TIM2, ENABLE);
    // TIM_CtrlPWMOutputs(TIM2, ENABLE);

    while(1)
    {
        static int8_t direction = 1;
        static int8_t duty = 0;
        static int8_t resolution = 1; // lower is higher resolution
        static u8 speed = 10; // lower is faster

        while(1)
        {
            duty = duty + resolution*direction;

            if(duty >=100)
            {
                duty = 100;
                direction = -1;
            }
            if(duty <0)
            {
                duty = 0;
                direction = 1;
            }

            pbuf[0] = pbuf[1] = pbuf[2] = (u8)duty;
            Delay_Ms(speed);
        }

        // for(u8 i = 0; i < 100; i++) // this is 
        // {
        //     for(u8 j = 0; j < DUTY_CYCLE_SIZE; j++)
        //     {
        //         pbuf[j] = i;
        //         Delay_Ms(10);
        //     }
        // }
        // flashLed();

        // while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        // {
        //     /* waiting for receiving finish */
        // }
        // val = (USART_ReceiveData(USART1));
        // USART_SendData(USART1, 10);
        // printf("hello");
        // while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        // {
        //     /* waiting for sending finish */
        // }
    }
}
