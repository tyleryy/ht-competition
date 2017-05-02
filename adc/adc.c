#include "adc.h"
#include "math.h"

#define    macADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    macADC_CLK                       RCC_APB2Periph_ADC1

#define    macADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    macADC_GPIO_CLK                  RCC_APB2Periph_GPIOC
#define    macADC_PORT                      GPIOC

#define    macADC_PIN                       GPIO_Pin_1
#define    macADC_CHANNEL                   ADC_Channel_11

#define    macADCx                          ADC1
#define    macADC_DMA_CHANNEL               DMA1_Channel1

u16 adc_converted_value;

static void adc_gpio_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	macADC_GPIO_APBxClock_FUN(macADC_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = macADC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;

	GPIO_Init(macADC_PORT, &GPIO_InitStructure);
}

static void adc_mode_config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	macADC_APBxClock_FUN(macADC_CLK, ENABLE);

	DMA_DeInit(macADC_DMA_CHANNEL);

	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32) (&(macADCx->DR));

	DMA_InitStructure.DMA_MemoryBaseAddr = (u32) &adc_converted_value;

	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;

	DMA_InitStructure.DMA_BufferSize = 1;

	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;

	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;

	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;

	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;

	DMA_InitStructure.DMA_Priority = DMA_Priority_High;

	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

	DMA_Init(macADC_DMA_CHANNEL, &DMA_InitStructure);

	DMA_Cmd(macADC_DMA_CHANNEL, ENABLE);

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;

	ADC_InitStructure.ADC_ScanConvMode = DISABLE;

	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;

	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;

	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;

	ADC_InitStructure.ADC_NbrOfChannel = 1;

	ADC_Init(macADCx, &ADC_InitStructure);

	RCC_ADCCLKConfig(RCC_PCLK2_Div8);

	ADC_RegularChannelConfig(macADCx, macADC_CHANNEL, 1,
			ADC_SampleTime_55Cycles5);

	ADC_DMACmd(macADCx, ENABLE);

	ADC_Cmd(macADCx, ENABLE);

	ADC_ResetCalibration(macADCx);

	while (ADC_GetResetCalibrationStatus(macADCx))
		;

	ADC_StartCalibration(macADCx);

	while (ADC_GetCalibrationStatus(macADCx))
		;

	ADC_SoftwareStartConvCmd(macADCx, ENABLE);
}

void initialise_adc(void)
{
	adc_gpio_config();
	adc_mode_config();
}
float get_distance(void)
{
	return ((-1.51 * pow(10, -8)) * pow(adc_converted_value, 3)
			+ (8.821 * pow(10, -5)) * pow(adc_converted_value, 2)
			- 0.1816 * adc_converted_value + 166.9);

}
u16 get_adc_raw_data(void)
{
	return adc_converted_value;
}
