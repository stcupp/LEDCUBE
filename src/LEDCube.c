/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC13Uxx.h"
#endif
#include <stdlib.h>
#include <cr_section_macros.h>
#include "gpio.h"
#include "RIT.h"
#include "driver.h"
#include "animations.h"

// TODO: insert other include files here

// TODO: insert other definitions and declarations here
volatile uint32_t msTicks = 0; // counter for 1ms SysTicks

void Delay(uint32_t delay)
{
	uint32_t timer_mark;
	timer_mark = msTicks; // Take timer snapshot
	while(msTicks < (timer_mark + delay));
}
void SysTick_Handler(void)
{
msTicks++;

}


int main(void) {


    // Enter an infinite loop, just incrementing a counter
    SysTick_Config(SystemCoreClock / 1000);

    Clear_Cube();

    Setup_GPIO();
    Setup_RIT();
    Enable_Layer(0);
    srand(msTicks);
    fill_colour_wheel();
    while(1) {
    	Test(6,15);
    	Test(12,15);
    	Zoom(8, 15, 0, 0);
    	Zoom(8, 15, 0, 1);
    	Zoom(8, 15, 1, 0);
    	Zoom(8, 15, 1, 1);
    	Random(4, 15);
    	Zoom2(8, 15, 0, 0);
    	Zoom2(8, 15, 0, 1);
    	Zoom2(8, 15, 1, 0);
    	Zoom2(8, 15, 1, 1);
    	Rain(6, 15);
    	Lines(6, 15, 0, 1);
    	Lines(6, 15, 1, 1);
    	Lines(6, 15, 2, 1);
    	Cube(6, 15);
    	Lines2(12, 15, 0, 1);
    	Lines2(12, 15, 1, 1);
    	Lines2(12, 15, 2, 1);
    	Fill_Cube_A(16, 30);
    	Spin(12, 15, 0);
    	Spin(12, 15, 1);
    	Spin(12, 15, 2);




    }
    return 0 ;
}
