/* Athabasca University

   Comp390 - Introduction to Computer Graphics - Final Project

   Fountain Component

   @author: Olisha Dmello

   @id: 3743903

   Description: This file defines the fountain component as a composite 3D object made up of cylinders, disks, torus, and spheres to represent a water fountain with droplets or sprinkle effect.
 
   Note for Instructor: Developed and tested on MacOS using GLUT framework.
*/

#define GL_SILENCE_DEPRECATION

#include "fountain.h"
#include "lighting.h" // required for sunOn

#include <GLUT/glut.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>


void drawFountain(float centerX, float centerZ) {
    GLUquadric* quad = gluNewQuadric(); // creates a quadric object which helps render cylinders/disks
    
    if (!sunOn) glDisable(GL_LIGHTING); // turns off the lighting at "night"
    glPushMatrix(); // save transformation state
        glScalef(2.0f, 2.5f, 2.0f); // scales the whole fountain
    
        // Fountain base - cylinder
        glColor3f(0.71f, 0.65f, 0.26f); // yellow gold
        glPushMatrix();
            glTranslatef(centerX, 0.0f, centerZ); // moves to the position x and z coordinates flexible (but fixed for that one object/component)
            glRotatef(-90.0f, 1, 0, 0); // rotates to align cylinder vertically
            gluCylinder(quad, 2.0f, 2.0f, 1.0f, 32, 1); // draws the cylinder of radius = 2.0 and height = 1.0
        glPopMatrix();

        // Top disk to cap the base
        glColor3f(0.0f, 0.0f, 0.0f); // black
        glPushMatrix();
            glTranslatef(centerX, 1.0f, centerZ); // moves to the position x and z coordinates flexible (but fixed for that one object/component)
            glRotatef(-90.0f, 1, 0, 0); // rotates to align the disk vertically
            gluDisk(quad, 0.0, 2.0, 32, 1); // flat circular top of radius = 2.0
        glPopMatrix();
        
        // Water pool
        glColor3f(0.0f, 0.0f, 1.0f); // blue
        glPushMatrix();
            glTranslatef(centerX, 1.1f, centerZ); // moves to the position x and z coordinates flexible (but fixed for that one object/component)
            glRotatef(-90.0f, 1, 0, 0); // rotates to align the disk vertically
            gluDisk(quad, 0.0, 1.5, 32, 1); // flat circular top of radius = 1.5
        glPopMatrix();

        // Water ring
        glColor3f(0.0f, 0.5f, 1.0f); // light blue
        glPushMatrix();
            glTranslatef(centerX, 1.15f, centerZ); // moves to the position x and z coordinates flexible (but fixed for that one object/component)
            glRotatef(-90.0f, 1, 0, 0); // rotates to align the torus vertically
            glutSolidTorus(0.1, 1.2, 12, 24); // ring of inner radius = 0.1 and outer radius = 1.2
        glPopMatrix();

        // Pipe center
        glColor3f(0.7f, 0.7f, 0.7f); // light grey
        glPushMatrix();
            glTranslatef(centerX, 1.0f, centerZ); // moves to the position x and z coordinates flexible (but fixed for that one object/component)
            glRotatef(-90.0f, 1, 0, 0); // rotates to align the cylinder vertically
            gluCylinder(quad, 0.1f, 0.3f, 2.0f, 12, 3); // draws the (conical-looking) cylinder of one side radius = 0.1 and other side radius = 0.3 and height = 2.0
        glPopMatrix();

        // Top sphere (water top)
        glColor3f(0.0f, 0.7f, 1.0f); // bright blue
        glPushMatrix();
            glTranslatef(centerX, 3.2f, centerZ); // moves to the position x and z coordinates flexible (but fixed for that one object/component)
            glutSolidSphere(0.15f, 12, 12); // draws spherical water ball
        glPopMatrix();

        // Water Droplets
        for (float y = 3.2f; y >= 1.2f; y -= 0.2f) { // multiple height levels (top to bottom)
            float radius = 0.3f + (y - 3.2f); // increasing radius per level (closer to spreadout)
            for (int angle = 0; angle < 360; angle += 25) { // number of droplets
                float rad = angle * 3.14159f / 180.0f;
                float x = centerX + radius * cos(rad);
                float z = centerZ + radius * sin(rad);
                glPushMatrix();
                    glTranslatef(x, y, z); // position of the droplet
                    glutSolidSphere(0.05f, 8, 8); // spherical water droplet
                glPopMatrix();
            }
        }
    glPopMatrix(); // restores transformation
    glEnable(GL_LIGHTING); // re-enable lighting if was off
}

void draw_fountain_layout(){
    drawFountain(0.0f, -5.5f); // fountain on the top-center (back-most)
    drawFountain(0.0f, 5.5f); // fountain on the bottom-center (front-most)
}
