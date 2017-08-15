/*
 * animations.c
 *
 *  Created on: Jan 30, 2015
 *      Author: Stcupp
 */
#include "LPC13Uxx.h"
#include <stdlib.h>
#include "driver.h"
#include "RIT.h"

extern void Delay(uint32_t delay);
extern volatile uint32_t msTicks;
uint32_t Animation_Runtime;



void Light_LED(uint8_t red, uint8_t green, uint8_t blue, uint8_t x, uint8_t y, uint8_t z)
{

	Cube_Array[x][y][z][0] = red;
	Cube_Array[x][y][z][1] = green;
	Cube_Array[x][y][z][2] = blue;

}
void Light_Column(uint8_t red, uint8_t green, uint8_t blue, uint8_t cx, uint8_t cy)
{
	uint8_t z;
	for(z=0; z<CUBE_Z; z++)
	{
		Light_LED(red, green, blue, cx, cy, z);
	}
}
void Light_Layer(uint8_t red, uint8_t green, uint8_t blue, uint8_t Layer)
{
	uint8_t x, y;
	for(x=0; x<CUBE_X; x++)
	{
	    for(y=0; y<CUBE_Y; y++)
	    {
	    	Light_LED(red, green, blue, x, y, Layer);
	    }
	}
}
void Light_RowX(uint8_t red, uint8_t green, uint8_t blue, uint8_t rx, uint8_t rz)
{
	uint8_t  y, z;
	for(y=0; y<CUBE_Y; y++)
	{
		if(rz == 4)
		{
			for(z=0; z<CUBE_Z; z++)
			{
				Light_LED(red, green, blue, rx, y, z);
			}
		}else{
			Light_LED(red, green, blue, rx, y, rz);
		}
	}
}
void Light_RowY(uint8_t red, uint8_t green, uint8_t blue, uint8_t ry, uint8_t rz)
{
	uint8_t x, z;
	for(x=0; x<CUBE_X; x++)
	{
		if(rz == 4)
		{
			for(z=0; z<CUBE_Z; z++)
			{
				Light_LED(red, green, blue, x, ry, z);
			}
		}else{
			Light_LED(red, green, blue, x, ry, rz);
		}
	}
}
void Fill_Cube(uint8_t FPS, uint8_t DIR, uint8_t Clear)
{
	srand(msTicks);
	int8_t x, y, z;
	uint8_t c1, c2, c3, start;
	uint16_t c;
	start = rand()%2;

	if(start){
		for(x=CUBE_X - 1; x>-1; x--)
		{
			for(y=CUBE_Y - 1; y>-1; y--)
			{
				for(z=CUBE_Z - 1; z>-1; z--)
				{
					if(Clear){
						c1 = 0;
						c2 = 0;
						c3 = 0;
					}else{
						c = rand()%COLOUR_WHEEL_LENGTH;
						c1 = Color_Array[c][0];
						c2 = Color_Array[c][1];
						c3 = Color_Array[c][2];
					}
					if(DIR == 0){
						Light_LED(c1, c2, c3, x, y, z);
					}
					if(DIR == 1){
						Light_LED(c1, c2, c3, x, z, y);
					}
					if(DIR == 2){
						Light_LED(c1, c2, c3, z, y, x);
					}
					if(DIR == 3){
						Light_LED(c1, c2, c3, z, x, y);
					}
					if(DIR == 4){
						Light_LED(c1, c2, c3, y, x, z);
					}
					if(DIR == 5){
						Light_LED(c1, c2, c3, y, z, x);
					}
					Delay((1000/FPS));
				}
			}
		}
	}else{
		for(x=0; x<CUBE_X; x++)
		{
			for(y=0; y<CUBE_Y; y++)
			{
				for(z=0; z<CUBE_Z; z++)
				{
					if(Clear){
						c1 = 0;
						c2 = 0;
						c3 = 0;
					}else{
						c = rand()%COLOUR_WHEEL_LENGTH;
						c1 = Color_Array[c][0];
						c2 = Color_Array[c][1];
						c3 = Color_Array[c][2];
					}
					if(DIR == 0){
					Light_LED(c1, c2, c3, x, y, z);
					}
					if(DIR == 1){
						Light_LED(c1, c2, c3, x, z, y);
					}
					if(DIR == 2){
						Light_LED(c1, c2, c3, z, y, x);
					}
					if(DIR == 3){
						Light_LED(c1, c2, c3, z, x, y);
					}
					if(DIR == 4){
						Light_LED(c1, c2, c3, y, x, z);
					}
					if(DIR == 5){
						Light_LED(c1, c2, c3, y, z, x);
					}
					Delay((1000/FPS));
				}
			}
		}
	}
}
void Clear_Cube()
{
	uint8_t x, y, z;
	for(x=0; x<CUBE_X; x++)
	{
	    for(y=0; y<CUBE_Y; y++)
	    {
	    	for(z=0; z<CUBE_Z; z++)
	    	{
	    		Light_LED(0, 0, 0, x, y, z);

	    	}
	    }
	}
}
void Cube_Test()
{
	uint8_t x, y, z;
	uint16_t i;
	for(i=0; i<COLOUR_WHEEL_LENGTH; i++)
	{
		for(x=0; x<CUBE_X; x++)
		{
			for(y=0; y<CUBE_Y; y++)
			{
				for(z=0; z<CUBE_Z; z++)
				{

					Light_LED(Color_Array[i][0], Color_Array[i][1], Color_Array[i][2], x, y, z);

				}
			}
		}
		Delay(100);
	}
}

void Lines(uint8_t FPS, uint8_t Runtime, uint8_t DIR, uint8_t Color)
{
	Animation_Runtime = msTicks + (Runtime * 1000);
	srand(msTicks);
	uint16_t c1, c2, c3, c4;
	if(Color)
	{
		c1 = rand()%COLOUR_WHEEL_LENGTH;
		c2 = rand()%COLOUR_WHEEL_LENGTH;
		c3 = rand()%COLOUR_WHEEL_LENGTH;
		c4 = rand()%COLOUR_WHEEL_LENGTH;
	}else{
		c1 = Get_Color(1);
		c2 = Get_Color(1);
		c3 = Get_Color(1);
		c4 = Get_Color(1);
	}
	Clear_Cube();
	while(msTicks<Animation_Runtime)
	{
		if(DIR == 0){
			Light_RowX(Color_Array[c1][0], Color_Array[c1][1], Color_Array[c1][2], 0, 4);
			Light_RowX(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], 1, 4);
			Light_RowX(Color_Array[c3][0], Color_Array[c3][1], Color_Array[c3][2], 2, 4);
			Light_RowX(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], 3, 4);
		}
		if(DIR == 1){
			Light_RowY(Color_Array[c1][0], Color_Array[c1][1], Color_Array[c1][2], 0, 4);
			Light_RowY(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], 1, 4);
			Light_RowY(Color_Array[c3][0], Color_Array[c3][1], Color_Array[c3][2], 2, 4);
			Light_RowY(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], 3, 4);
		}
		if(DIR == 2){
			Light_Layer(Color_Array[c1][0], Color_Array[c1][1], Color_Array[c1][2], 0);
			Light_Layer(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], 1);
			Light_Layer(Color_Array[c3][0], Color_Array[c3][1], Color_Array[c3][2], 2);
			Light_Layer(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], 3);
		}
		c4 = c3;
		c3 = c2;
		c2 = c1;
		if(Color)
		{
			c1 = rand()%COLOUR_WHEEL_LENGTH;
		}else{
			c1 = Get_Color(1);
		}
		Delay((1000/FPS));

	}

}
void Lines2(uint8_t FPS, uint8_t Runtime, uint8_t DIR, uint8_t Color)
{
	Animation_Runtime = msTicks + (Runtime * 1000);
	srand(msTicks);
	uint16_t c1, c2, c3, c4, c5, c6, c7;
	if(Color)
	{
		c1 = rand()%COLOUR_WHEEL_LENGTH;
		c2 = rand()%COLOUR_WHEEL_LENGTH;
		c3 = rand()%COLOUR_WHEEL_LENGTH;
		c4 = rand()%COLOUR_WHEEL_LENGTH;
		c5 = rand()%COLOUR_WHEEL_LENGTH;
		c6 = rand()%COLOUR_WHEEL_LENGTH;
		c7 = rand()%COLOUR_WHEEL_LENGTH;
	}else{
		c1 = Get_Color(1);
		c2 = Get_Color(1);
		c3 = Get_Color(1);
		c4 = Get_Color(1);
		c5 = Get_Color(1);
		c6 = Get_Color(1);
		c7 = Get_Color(1);
	}
	Clear_Cube();
	while(msTicks<Animation_Runtime)
	{
		if(DIR == 0){
			Light_RowX(Color_Array[c1][0], Color_Array[c1][1], Color_Array[c1][2], 0, 0);

			Light_RowX(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], 0, 1);
			Light_RowX(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], 1, 0);

			Light_RowX(Color_Array[c3][0], Color_Array[c3][1], Color_Array[c3][2], 2, 0);
			Light_RowX(Color_Array[c3][0], Color_Array[c3][1], Color_Array[c3][2], 1, 1);
			Light_RowX(Color_Array[c3][0], Color_Array[c3][1], Color_Array[c3][2], 0, 2);

			Light_RowX(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], 0, 3);
			Light_RowX(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], 1, 2);
			Light_RowX(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], 2, 1);
			Light_RowX(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], 3, 0);

			Light_RowX(Color_Array[c5][0], Color_Array[c5][1], Color_Array[c5][2], 1, 3);
			Light_RowX(Color_Array[c5][0], Color_Array[c5][1], Color_Array[c5][2], 2, 2);
			Light_RowX(Color_Array[c5][0], Color_Array[c5][1], Color_Array[c5][2], 3, 1);

			Light_RowX(Color_Array[c6][0], Color_Array[c6][1], Color_Array[c6][2], 2, 3);
			Light_RowX(Color_Array[c6][0], Color_Array[c6][1], Color_Array[c6][2], 3, 2);

			Light_RowX(Color_Array[c7][0], Color_Array[c7][1], Color_Array[c7][2], 3, 3);
		}
		if(DIR == 1){
			Light_RowY(Color_Array[c1][0], Color_Array[c1][1], Color_Array[c1][2], 0, 0);

			Light_RowY(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], 0, 1);
			Light_RowY(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], 1, 0);

			Light_RowY(Color_Array[c3][0], Color_Array[c3][1], Color_Array[c3][2], 2, 0);
			Light_RowY(Color_Array[c3][0], Color_Array[c3][1], Color_Array[c3][2], 1, 1);
			Light_RowY(Color_Array[c3][0], Color_Array[c3][1], Color_Array[c3][2], 0, 2);

			Light_RowY(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], 0, 3);
			Light_RowY(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], 1, 2);
			Light_RowY(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], 2, 1);
			Light_RowY(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], 3, 0);

			Light_RowY(Color_Array[c5][0], Color_Array[c5][1], Color_Array[c5][2], 1, 3);
			Light_RowY(Color_Array[c5][0], Color_Array[c5][1], Color_Array[c5][2], 2, 2);
			Light_RowY(Color_Array[c5][0], Color_Array[c5][1], Color_Array[c5][2], 3, 1);

			Light_RowY(Color_Array[c6][0], Color_Array[c6][1], Color_Array[c6][2], 2, 3);
			Light_RowY(Color_Array[c6][0], Color_Array[c6][1], Color_Array[c6][2], 3, 2);

			Light_RowY(Color_Array[c7][0], Color_Array[c7][1], Color_Array[c7][2], 3, 3);
		}
		if(DIR == 2){
			Light_Column(Color_Array[c1][0], Color_Array[c1][1], Color_Array[c1][2], 0, 0);

			Light_Column(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], 0, 1);
			Light_Column(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], 1, 0);

			Light_Column(Color_Array[c3][0], Color_Array[c3][1], Color_Array[c3][2], 2, 0);
			Light_Column(Color_Array[c3][0], Color_Array[c3][1], Color_Array[c3][2], 1, 1);
			Light_Column(Color_Array[c3][0], Color_Array[c3][1], Color_Array[c3][2], 0, 2);

			Light_Column(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], 0, 3);
			Light_Column(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], 1, 2);
			Light_Column(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], 2, 1);
			Light_Column(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], 3, 0);

			Light_Column(Color_Array[c5][0], Color_Array[c5][1], Color_Array[c5][2], 1, 3);
			Light_Column(Color_Array[c5][0], Color_Array[c5][1], Color_Array[c5][2], 2, 2);
			Light_Column(Color_Array[c5][0], Color_Array[c5][1], Color_Array[c5][2], 3, 1);

			Light_Column(Color_Array[c6][0], Color_Array[c6][1], Color_Array[c6][2], 2, 3);
			Light_Column(Color_Array[c6][0], Color_Array[c6][1], Color_Array[c6][2], 3, 2);

			Light_Column(Color_Array[c7][0], Color_Array[c7][1], Color_Array[c7][2], 3, 3);
		}
		c7 = c6;
		c6 = c5;
		c5 = c4;
		c4 = c3;
		c3 = c2;
		c2 = c1;
		if(Color)
		{
			c1 = rand()%COLOUR_WHEEL_LENGTH;
		}else{
			c1 = Get_Color(1);
		}
		Delay((1000/FPS));

	}

}
void Random(uint8_t FPS, uint8_t Runtime)
{
	Animation_Runtime = msTicks + (Runtime * 1000);
	srand(msTicks);
	uint8_t x, y, z, i;
	uint16_t c;

	while(msTicks<Animation_Runtime)
	{
		Clear_Cube();
		for(x=0; x<CUBE_X; x++)
		{
			for(y=0; y<CUBE_Y; y++)
			{
				for(z=0; z<CUBE_Z; z++)
				{
					i = rand()%2;
					if(i){
						c = rand()%COLOUR_WHEEL_LENGTH;
						Light_LED(Color_Array[c][0], Color_Array[c][1], Color_Array[c][2], x, y, z);
					}
				}
			}
		}
		Delay((1000/FPS));
	}

}
void Test(uint8_t FPS, uint8_t Runtime)
{
	Animation_Runtime = msTicks + (Runtime * 1000);
	srand(msTicks);
	uint8_t c1[16][3], c2[16][3], c3[16][3], c4[16][3];
	uint8_t x = 0, y = 0, i = 0, s, t = 1;
	uint16_t c;
	for(s=0; s<16; s++)
	{
		c1[s][0] = 0;
		c1[s][1] = 0;
		c1[s][2] = 0;

		c2[s][0] = 0;
		c2[s][1] = 0;
		c2[s][2] = 0;

		c3[s][0] = 0;
		c3[s][1] = 0;
		c3[s][2] = 0;

		c4[s][0] = 0;
		c4[s][1] = 0;
		c4[s][2] = 0;
	}
	while(msTicks<Animation_Runtime)
	{
		Clear_Cube();
		for(s=0; s<16; s++)
		{
			if(i == 2){
				i = 0;
			}
			if (t == 1){
				c4[s][0] = c3[s][0];
				c4[s][1] = c3[s][1];
				c4[s][2] = c3[s][2];

				c3[s][0] = c2[s][0];
				c3[s][1] = c2[s][1];
				c3[s][2] = c2[s][2];

				c2[s][0] = c1[s][0];
				c2[s][1] = c1[s][1];
				c2[s][2] = c1[s][2];

				if(i == 1){
					c = rand()%COLOUR_WHEEL_LENGTH;
					c1[s][0] = Color_Array[c][0];
					c1[s][1] = Color_Array[c][1];
					c1[s][2] = Color_Array[c][2];
				}else{
					c1[s][0] = 0;
					c1[s][1] = 0;
					c1[s][2] = 0;
				}

			}
			if(t == 2){
				c1[s][0] = c2[s][0];
				c1[s][1] = c2[s][1];
				c1[s][2] = c2[s][2];

				c2[s][0] = c3[s][0];
				c2[s][1] = c3[s][1];
				c2[s][2] = c3[s][2];

				c3[s][0] = c4[s][0];
				c3[s][1] = c4[s][1];
				c3[s][2] = c4[s][2];

				if(i == 1){
					c = rand()%COLOUR_WHEEL_LENGTH;
					c4[s][0] = Color_Array[c][0];
					c4[s][1] = Color_Array[c][1];
					c4[s][2] = Color_Array[c][2];
				}else{
					c4[s][0] = 0;
					c4[s][1] = 0;
					c4[s][2] = 0;
				}
				t = 0;
			}
			t++;
			i++;






			Light_LED(c1[s][0], c1[s][1], c1[s][2], x, y, 3);
			Light_LED(c2[s][0], c2[s][1], c2[s][2], x, y, 2);
			Light_LED(c3[s][0], c3[s][1], c3[s][2], x, y, 1);
			Light_LED(c4[s][0], c4[s][1], c4[s][2], x, y, 0);
			y++;
			if(y == 4){
				y = 0;
				if(i == 2){
					i = 0;
				}
				i++;
				x++;
			}
			if(x == 4){
				if(i == 2){
					i = 0;
				}
				i++;

				x = 0;
				y = 0;
			}
		}
		Delay((1000/FPS));
	}

}
void Fly(uint8_t FPS, uint8_t Runtime, uint8_t Color)
{
	Animation_Runtime = msTicks + (Runtime * 1000);
	srand(msTicks);
	uint8_t x = 0, y = 0, z = 0, i;
	uint16_t c;

	while(msTicks<Animation_Runtime)
	{
		Clear_Cube();
		if(x < 3)
		{
			i = rand()%2;
			if(i)
			{
				x++;
			}
		}else if(x > 0)
		{
			i = rand()%2;
			if(i)
			{
				x--;
			}
		}
		if(y < 3)
		{
			i = rand()%2;
			if(i)
			{
				y++;
			}
		}else if(y > 0)
		{
			i = rand()%2;
			if(i)
			{
				y--;
			}
		}
		if(z < 3)
		{
			i = rand()%2;
			if(i)
			{
				z++;
			}
		}else if(z > 0)
		{
			i = rand()%2;
			if(i)
			{
				x--;
			}
		}
		if(Color){
			c = rand()%COLOUR_WHEEL_LENGTH;
		}else{
			c = Get_Color(1);
		}
		Light_LED(Color_Array[c][0], Color_Array[c][1], Color_Array[c][2], x, y, z);
		Delay((1000/FPS));
	}

}
void Fill_Cube_A(uint8_t FPS, uint8_t Runtime)
{
	Animation_Runtime = msTicks + (Runtime * 1000);
	srand(msTicks);
	uint8_t i;

	while(msTicks<Animation_Runtime)
	{
		i = rand()%6;
		Clear_Cube();
		Fill_Cube(FPS, i, 0);
		i = rand()%6;
		Fill_Cube(FPS, i, 1);

	}

}
void Rain(uint8_t FPS, uint8_t Runtime)
{
	Animation_Runtime = msTicks + (Runtime * 1000);
	srand(msTicks);
	uint8_t c1[16][3], c2[16][3], c3[16][3], c4[16][3];
	uint8_t x = 0, y = 0, i, s;
	uint16_t c;
	for(s=0; s<16; s++)
	{
		c1[s][0] = 0;
		c1[s][1] = 0;
		c1[s][2] = 0;

		c2[s][0] = 0;
		c2[s][1] = 0;
		c2[s][2] = 0;

		c3[s][0] = 0;
		c3[s][1] = 0;
		c3[s][2] = 0;

		c4[s][0] = 0;
		c4[s][1] = 0;
		c4[s][2] = 0;
	}
	while(msTicks<Animation_Runtime)
	{
		Clear_Cube();
		for(s=0; s<16; s++)
		{
			c4[s][0] = c3[s][0];
			c4[s][1] = c3[s][1];
			c4[s][2] = c3[s][2];

			c3[s][0] = c2[s][0];
			c3[s][1] = c2[s][1];
			c3[s][2] = c2[s][2];

			c2[s][0] = c1[s][0];
			c2[s][1] = c1[s][1];
			c2[s][2] = c1[s][2];

			c1[s][0] = 0;
			c1[s][1] = 0;
			c1[s][2] = 0;



			i = rand()%4;

			if(i == 1){
				c = rand()%COLOUR_WHEEL_LENGTH;
				c1[s][0] = Color_Array[c][0];
				c1[s][1] = Color_Array[c][1];
				c1[s][2] = Color_Array[c][2];
			}
			Light_LED(c1[s][0], c1[s][1], c1[s][2], x, y, 3);
			Light_LED(c2[s][0], c2[s][1], c2[s][2], x, y, 2);
			Light_LED(c3[s][0], c3[s][1], c3[s][2], x, y, 1);
			Light_LED(c4[s][0], c4[s][1], c4[s][2], x, y, 0);
			y++;
			if(y == 4){
				y = 0;
				x++;
			}
			if(x == 4){
				x = 0;
				y = 0;
			}
		}
		Delay((1000/FPS));
	}

}
void Cube(uint8_t FPS, uint8_t Runtime)
{
	Animation_Runtime = msTicks + (Runtime * 1000);
	srand(msTicks);
	uint8_t x, y, z, i=0;
	uint16_t c1, c2;
	c1 = rand()%COLOUR_WHEEL_LENGTH;
	c2 = rand()%COLOUR_WHEEL_LENGTH;
	while(msTicks<Animation_Runtime)
	{

		for(x=0; x<CUBE_X; x++)
		{
			for(y=0; y<CUBE_Y; y++)
			{
				for(z=0; z<CUBE_Z; z++)
				{
					if(i == 0 ){
						if((x == 1 || x == 2) && (y == 1 || y == 2) && (z == 1 || z == 2)){
							Light_LED(Color_Array[c1][0], Color_Array[c1][1], Color_Array[c1][2], x, y, z);
						}
					}
					if(i == 1){
						if(!(x == 1 || x == 2) && !(y == 1 || y == 2) && !(z == 1 || z == 2)){
							Light_LED(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], x, y, z);
						}
					}
					if(i == 2){
						if(!((x == 1 || x == 2) && (y == 1 || y == 2) && (z == 1 || z == 2))){
							Light_LED(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], x, y, z);
						}
					}


				}
			}
		}

		i++;
		if(i == 4){
			Clear_Cube();
			i = 0;
			c1 = rand()%COLOUR_WHEEL_LENGTH;
			c2 = rand()%COLOUR_WHEEL_LENGTH;
		}
		Delay((1000/FPS));
	}

}
void Spin(uint8_t FPS, uint8_t Runtime, uint8_t DIR)
{
	Animation_Runtime = msTicks + (Runtime * 1000);
	srand(msTicks);
	uint8_t i = 0, r1, r2, r3, r4, y1 = 0, y2 = 1, y3 = 2, y4 = 3;
	uint16_t c1, c2, c3, c4;
	c1 = rand()%COLOUR_WHEEL_LENGTH;
	c2 = rand()%COLOUR_WHEEL_LENGTH;
	c3 = rand()%COLOUR_WHEEL_LENGTH;
	c4 = rand()%COLOUR_WHEEL_LENGTH;
	while(msTicks<Animation_Runtime)
	{
		if(i == 0 || i == 9){
			r1 = 0;
			r2 = 1;
			r3 = 2;
			r4 = 3;
		}
		if(i == 1 || i == 8){
			r1 = 1;
			r2 = 1;
			r3 = 2;
			r4 = 2;
		}
		if(i == 2 || i == 7){
			r1 = 2;
			r2 = 2;
			r3 = 1;
			r4 = 1;
		}
		if(i == 3){
			r1 = 3;
			r2 = 2;
			r3 = 1;
			r4 = 0;
		}
		if(i == 4 || i == 11){
			y1 = 1;
			y2 = 1;
			y3 = 2;
			y4 = 2;
		}
		if(i == 5 || i == 10){
			y1 = 2;
			y2 = 2;
			y3 = 1;
			y4 = 1;
		}
		if(i == 6){
			y1 = 3;
			y2 = 2;
			y3 = 1;
			y4 = 0;
		}

		if(i == 12){
			y1 = 0;
			y2 = 1;
			y3 = 2;
			y4 = 3;
		}
		Clear_Cube();
		if(DIR == 0){
			Light_RowY(Color_Array[c1][0], Color_Array[c1][1], Color_Array[c1][2], y1, r1);
			Light_RowY(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], y2, r2);
			Light_RowY(Color_Array[c3][0], Color_Array[c3][1], Color_Array[c3][2], y3, r3);
			Light_RowY(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], y4, r4);
		}
		if(DIR == 1){
			Light_RowX(Color_Array[c1][0], Color_Array[c1][1], Color_Array[c1][2], y1, r1);
			Light_RowX(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], y2, r2);
			Light_RowX(Color_Array[c3][0], Color_Array[c3][1], Color_Array[c3][2], y3, r3);
			Light_RowX(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], y4, r4);
		}
		if(DIR == 2){
			Light_Column(Color_Array[c1][0], Color_Array[c1][1], Color_Array[c1][2], y1, r1);
			Light_Column(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], y2, r2);
			Light_Column(Color_Array[c3][0], Color_Array[c3][1], Color_Array[c3][2], y3, r3);
			Light_Column(Color_Array[c4][0], Color_Array[c4][1], Color_Array[c4][2], y4, r4);
		}
		i++;
		if(i == 13){
			i = 0;
			c1 = rand()%COLOUR_WHEEL_LENGTH;
			c2 = rand()%COLOUR_WHEEL_LENGTH;
			c3 = rand()%COLOUR_WHEEL_LENGTH;
			c4 = rand()%COLOUR_WHEEL_LENGTH;
		}
		Delay((1000/FPS));

	}

}

void Zoom(uint8_t FPS, uint8_t Runtime, uint8_t Clear, uint8_t Dir)
{
	Animation_Runtime = msTicks + (Runtime * 1000);
	srand(msTicks);
	uint8_t x, y, z, i = 4;
	uint16_t c1, c2;
	while(msTicks<Animation_Runtime)
	{
		Clear_Cube();
		i = 4;
		c1 = rand()%COLOUR_WHEEL_LENGTH;
		c2 = rand()%COLOUR_WHEEL_LENGTH;
		for(z=0; z<CUBE_Z; z++)
		{
			Delay((1000/FPS));
			if(Clear)
			{
				Clear_Cube();
			}
			i--;
			for(x=0; x<CUBE_X; x++)
			{
				for(y=0; y<CUBE_Y; y++)
				{

					if(!((x == 1 || x == 2) && (y == 1 || y == 2)))
					{
						if(Dir)
						{
							Light_LED(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], x, y, i);
						}else{
							Light_LED(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], x, y, z);
						}
					}
					if(!(x == 0 || x == 3) && !(y == 0 || y == 3))
					{
						if(Dir)
						{
							Light_LED(Color_Array[c1][0], Color_Array[c1][1], Color_Array[c1][2], x, y, z);
						}else{
							Light_LED(Color_Array[c1][0], Color_Array[c1][1], Color_Array[c1][2], x, y, i);
						}
					}

				}
			}
		}
		Delay((1000/FPS));
	}
}

void Zoom2(uint8_t FPS, uint8_t Runtime, uint8_t Clear, uint8_t Dir)
{
	Animation_Runtime = msTicks + (Runtime * 1000);
	srand(msTicks);
	uint8_t x, y, z, i, s;
	uint16_t c1, c2;
	while(msTicks<Animation_Runtime)
	{
		Clear_Cube();
		i = 4;
		c1 = rand()%COLOUR_WHEEL_LENGTH;
		c2 = rand()%COLOUR_WHEEL_LENGTH;
		for(s=0; s<2; s++)
		{
			i = 4;
			for(z=0; z<CUBE_Z; z++)
			{
				Delay((1000/FPS));
				if(Clear)
				{
					Clear_Cube();
				}
				i--;

				for(x=0; x<CUBE_X; x++)
				{
					for(y=0; y<CUBE_Y; y++)
					{

						if(s == 0)
						{
							if(!((x == 1 || x == 2) && (y == 1 || y == 2)))
							{
								if(Dir)
								{
									Light_LED(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], x, y, z);
								}else{
									Light_LED(Color_Array[c2][0], Color_Array[c2][1], Color_Array[c2][2], x, y, i);
								}
							}
						}
						if(s == 1)
						{
							if(!(x == 0 || x == 3) && !(y == 0 || y == 3))
							{
								if(Dir)
								{
									Light_LED(Color_Array[c1][0], Color_Array[c1][1], Color_Array[c1][2], x, y, i);
								}else{
									Light_LED(Color_Array[c1][0], Color_Array[c1][1], Color_Array[c1][2], x, y, z);
								}
							}
						}
					}
				}
			}
		}
		Delay((1000/FPS));
	}
}
