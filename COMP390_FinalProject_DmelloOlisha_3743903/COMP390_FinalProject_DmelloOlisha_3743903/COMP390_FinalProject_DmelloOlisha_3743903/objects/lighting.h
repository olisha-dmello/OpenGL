/* Athabasca University
   Comp390 - Introduction to Computer Graphics - Final Project
 
   Lighting Header File
 
   @author: Olisha Dmello
   @id: 3743903
   Description: This file defines the lighting component (lighting.cpp)
*/

#ifndef LIGHTING_H
#define LIGHTING_H

#include <GLUT/glut.h>

extern bool sunOn;

void drawSun();
void setupSunlight();
void drawLampPosts(float roadX, float zStart, float zEnd, float spacing);

#endif
