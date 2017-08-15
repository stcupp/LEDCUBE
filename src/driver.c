/*
 * driver.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: Stcupp
 */
#include "LPC13Uxx.h"
#include "gpio.h"
#include "RIT.h"
#include "driver.h"
#include "math.h"
uint8_t Layer_Count = 0;
uint8_t INT_Count = 0;
uint16_t Color_Count = 0;
uint8_t Cube_Array[CUBE_X][CUBE_Y][CUBE_Z][3];
uint8_t Color_Array[COLOUR_WHEEL_LENGTH][3];
void Disable_Layer() {
	GPIO_SetMaskValue(0, 0x7800);//Everything HIGH
}
void Enable_Layer(uint8_t Layer) {
	uint32_t Layer_Buff = 0;
	switch (Layer) {
		case 0:
			Layer_Buff = 0x3800;
			break;
		case 1:
			Layer_Buff = 0x5800;
			break;
		case 2:
			Layer_Buff = 0x6800;
			break;
		case 3:
			Layer_Buff = 0x7000;
			break;
		default:
			break;
		}
	GPIO_SetMaskValue(0, Layer_Buff);
}
void Setup_GPIO(void) {
	LPC_IOCON->PIO1_20 = 0x90;
	LPC_IOCON->PIO1_19 = 0x90;
	LPC_IOCON->PIO1_25 = 0x90;
	LPC_IOCON->PIO1_26 = 0x90;
	LPC_IOCON->PIO1_27 = 0x90;
	LPC_IOCON->PIO1_16 = 0x90;
	LPC_IOCON->TDI_PIO0_11 = 0x91;
	LPC_IOCON->TMS_PIO0_12 = 0x91;
	LPC_IOCON->TDO_PIO0_13 = 0x91;
	LPC_IOCON->TRST_PIO0_14 = 0x91;
	GPIOInit();
	GPIO_SetDir(1, 20, 1);
	GPIO_SetDir(1, 19, 1);
	GPIO_SetDir(1, 25, 1);
	GPIO_SetDir(1, 26, 1);
	GPIO_SetDir(1, 27, 1);
	GPIO_SetDir(1, 16, 1);
	GPIO_SetDir(0, 11, 1);
	GPIO_SetDir(0, 12, 1);
	GPIO_SetDir(0, 13, 1);
	GPIO_SetDir(0, 14, 1);
	GPIO_SetMask(1, 0xF1E6FFFF);//Set Port 1 Mask
	GPIO_SetMask(0, 0xFFFF87FF);//Set Port 0 Mask
	GPIO_SetMaskValue(1, 0x10000);//Everything LOW except OE
	GPIO_SetMaskValue(0, 0x7800);//Everything HIGH


}

void Setup_RIT(void) {
	RIT_SetCNTRL(1,1,1,0);//Turn OFF the RIT
	RIT_SetCount(0);//Set the count to 0
	RIT_SetMask(0);//Set the RIT Mask
	RIT_SetComp(INT0);//Set the RIT compare register
	RIT_SetCNTRL(1,1,1,1);//Turn ON the RIT
	NVIC_EnableIRQ(RIT_IRQn);//Enable IRQ for RIT

}

void OSTIMER_IRQHandler(void)
{
	uint8_t x = 0, y = 0, i = 0, c = 15;
	uint32_t RED_Buff = 0, GREEN_Buff = 0, BLUE_Buff = 0;
	if(INT_Count == 8)
	{
		INT_Count = 0;
		Disable_Layer();
		Layer_Count++;
		if(Layer_Count == 4)
		{
			Layer_Count = 0;
		}
		GPIO_SetMaskValue(1, 0x10000);//Everything LOW except OE
		Enable_Layer(Layer_Count);

	}
	switch (INT_Count) {
	case 0:
		RIT_SetComp(INT1);
		break;
	case 1:
		RIT_SetComp(INT2);
		break;
	case 2:
		RIT_SetComp(INT3);
		break;
	case 3:
		RIT_SetComp(INT4);
		break;
	case 4:
		RIT_SetComp(INT5);
		break;
	case 5:
		RIT_SetComp(INT6);
		break;
	case 6:
		RIT_SetComp(INT7);
		break;
	case 7:
		RIT_SetComp(INT0);
		break;
	default:
		break;
	}
	for(x=0; x<CUBE_X; x++)
	{
		for(y=0; y<CUBE_Y; y++)
			{

			RED_Buff |= ((Cube_Array[x][y][Layer_Count][0] & (1<<INT_Count))>>INT_Count)<<c;
			GREEN_Buff |= ((Cube_Array[x][y][Layer_Count][1] & (1<<INT_Count))>>INT_Count)<<c;
			BLUE_Buff |= ((Cube_Array[x][y][Layer_Count][2] & (1<<INT_Count))>>INT_Count)<<c;
			c--;
			}
	}

	GPIO_SetMaskValue(1, 0x10000);//Everything LOW except OE

	for(i=0; i<16; i++)
	{
		uint32_t GPIO_Buff = 0;
		GPIO_Buff |= ((RED_Buff & (1<<i))>>i)<<RED_PIN;
		GPIO_Buff |= ((GREEN_Buff & (1<<i))>>i)<<GREEN_PIN;
		GPIO_Buff |= ((BLUE_Buff & (1<<i))>>i)<<BLUE_PIN;
		GPIO_Buff |= 0x10000;// Set OE HIGH
		GPIO_SetMaskValue(1, GPIO_Buff);// shift everything but LE & CLK into gpio register
		GPIO_Buff |= 0x8000000;// Set CLK HIGH
		GPIO_SetMaskValue(1, GPIO_Buff);// shift everything but LE

	}
	GPIO_SetMaskValue(1, 0x4010000);//Everything LOW except OE & LE
	GPIO_SetMaskValue(1, 0);//Everything LOW
	INT_Count++;
	RIT_SetCNTRL(1,1,1,1);
	NVIC_ClearPendingIRQ(RIT_IRQn);
}

void fill_colour_wheel(void){
	float red, green, blue;
	float c, s;
	int32_t phase = 0;
	int16_t I = 0;

	while(phase < COLOUR_WHEEL_LENGTH){
		s = (1<<BAM_RESOLUTION)*sin(M_PI*(3*phase-I*COLOUR_WHEEL_LENGTH)/(2*COLOUR_WHEEL_LENGTH));
		c = (1<<BAM_RESOLUTION)*cos(M_PI*(3*phase-I*COLOUR_WHEEL_LENGTH)/(2*COLOUR_WHEEL_LENGTH));

		red = (I==0?1:0)*s + (I==1?1:0)*c;
		green = (I==1?1:0)*s + (I==2?1:0)*c;
		blue = (I==2?1:0)*s + (I==0?1:0)*c;

		Color_Array[phase][0] = red;
		Color_Array[phase][1] = green;
		Color_Array[phase][2] = blue;
		if(++phase >= (1+I)*COLOUR_WHEEL_LENGTH/3){
			I++;
		}
	}
}

uint16_t Get_Color(uint8_t INC){
	Color_Count = Color_Count + INC;
	if(Color_Count >= COLOUR_WHEEL_LENGTH)
	{
		Color_Count = 0;
	}
	return Color_Count;
}
