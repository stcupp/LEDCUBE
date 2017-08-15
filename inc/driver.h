/*
 * driver.h
 *
 *  Created on: Jan 16, 2015
 *      Author: Stcupp
 */



#define RED_PORT		1	//p1.20
#define BLUE_PORT		1	//p1.19
#define GREEN_PORT		1	//p1.25
#define LE_PORT			1	//p1.26
#define CLK_PORT		1	//p1.27
#define OE_PORT			1	//p1.16
#define M4G_PORT		0	//p0.11
#define M3G_PORT		0	//p0.12
#define M2G_PORT		0	//p0.13
#define M1G_PORT		0	//p0.14

#define RED_PIN			20	//p1.20
#define BLUE_PIN		19	//p1.19
#define GREEN_PIN		25	//p1.25
#define LE_PIN			26	//p1.26
#define CLK_PIN			27	//p1.27
#define OE_PIN			16	//p1.16
#define M4G_PIN			11	//p0.11
#define M3G_PIN			12	//p0.12
#define M2G_PIN			13	//p0.13
#define M1G_PIN			14	//p0.14


#define REFRESH_RATE 	100 //Hz
#define CUBE_X			4
#define CUBE_Y			4
#define CUBE_Z			4
#define COLOUR_WHEEL_LENGTH 512
#define BAM_RESOLUTION 8
#define INT7 			(int)((SystemCoreClock/(REFRESH_RATE*CUBE_Z))/2)
#define INT6			(int)INT7/2
#define INT5			(int)INT6/2
#define INT4			(int)INT5/2
#define INT3			(int)INT4/2
#define INT2			(int)INT3/2
#define INT1			(int)INT2/2
#define INT0			(int)INT1/2

extern uint8_t Cube_Array[CUBE_X][CUBE_Y][CUBE_Z][3];
extern uint8_t Color_Array[COLOUR_WHEEL_LENGTH][3];
void Disable_Layer();
void Enable_Layer(uint8_t Layer);
void Setup_GPIO(void);
void Setup_RIT(void);
void OSTIMER_IRQHandler(void);
void fill_colour_wheel(void);
uint16_t Get_Color(uint8_t INC);


