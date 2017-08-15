/*
 * animations.h
 *
 *  Created on: Jan 30, 2015
 *      Author: Stcupp
 */

#ifndef ANIMATIONS_H_
#define ANIMATIONS_H_



void Light_LED(uint8_t red, uint8_t green, uint8_t blue, uint8_t x, uint8_t y, uint8_t z);
void Light_Column(uint8_t red, uint8_t green, uint8_t blue, uint8_t cx, uint8_t cy);
void Light_Layer(uint8_t red, uint8_t green, uint8_t blue, uint8_t Layer);
void Light_RowX(uint8_t red, uint8_t green, uint8_t blue, uint8_t rx, uint8_t rz);
void Light_RowY(uint8_t red, uint8_t green, uint8_t blue, uint8_t ry, uint8_t rz);
void Fill_Cube(uint8_t FPS, uint8_t DIR, uint8_t Clear);
void Clear_Cube();
void Cube_Test();
void Lines(uint8_t FPS, uint8_t Runtime, uint8_t DIR, uint8_t Color);
void Lines2(uint8_t FPS, uint8_t Runtime, uint8_t DIR, uint8_t Color);
void Random(uint8_t FPS, uint8_t Runtime);
void Test(uint8_t FPS, uint8_t Runtime);
void Fly(uint8_t FPS, uint8_t Runtime, uint8_t Color);
void Fill_Cube_A(uint8_t FPS, uint8_t Runtime);
void Rain(uint8_t FPS, uint8_t Runtime);
void Cube(uint8_t FPS, uint8_t Runtime);
void Spin(uint8_t FPS, uint8_t Runtime, uint8_t DIR);
void Zoom(uint8_t FPS, uint8_t Runtime, uint8_t Clear, uint8_t Dir);
void Zoom2(uint8_t FPS, uint8_t Runtime, uint8_t Clear, uint8_t Dir);
#endif /* ANIMATIONS_H_ */
