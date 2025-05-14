/* Athabasca University

   Comp390 - Introduction to Computer Graphics - Final Project

   Tree Component

   @author: Olisha Dmello

   @id: 3743903

   Description: This file defines the tree component as a composite 3D object made up of cylinders and cones to represent a pine tree.

   Note for Instructor:
   - Developed and tested on MacOS using GLUT framework.
*/

#define GL_SILENCE_DEPRECATION

#include "tree.h"
#include "lighting.h"

#include <GLUT/glut.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

// draws a tree at position x and z
void drawTree(float x, float z) {
    GLUquadric* quad = gluNewQuadric(); // creates a quadric object which helps render cylinders

    if (!sunOn) glEnable(GL_LIGHTING);  // ensure lighting is on for trees at night
    glPushMatrix();
        glScalef(4.0f, 4.5f, 4.0f);
        // Tree trunk
        glColor3f(0.55f, 0.27f, 0.07f);  // brown
        glPushMatrix();
            glTranslatef(x, 0.0f, z); // moves to the position x and z coordinates flexible (but fixed for that one object/component)
            glRotatef(-90.0f, 1, 0, 0); // rotates to align cylinder vertically
            gluCylinder(quad, 0.1f, 0.1f, 0.6f, 12, 3); // draws the cylinder of radius = 0.1 and height = 0.6
        glPopMatrix();

        // Tree foliage (cone)
        glColor3f(0.0f, 0.5f, 0.0f);  // green
        glPushMatrix();
            glTranslatef(x, 0.6f, z); // moves to the position x and z coordinates flexible (but fixed for that one object/component)
            glRotatef(-90.0f, 1, 0, 0); // rotates to align cylinder vertically
            glutSolidCone(0.4f, 1.0f, 12, 4); // draws the cone of radius = 0.4 and height = 1.0
        glPopMatrix();
    glPopMatrix();
}

// placement of the trees along the ground
void draw_trees_layout(){
    // mirrored left and right side on the path (back to front)
    drawTree(1.5f, -4.0f);
    drawTree(-1.5f, -4.0f);
    drawTree(1.5f, -2.5f);
    drawTree(-1.5f, -2.5f);
    drawTree(1.5f, -1.0f);
    drawTree(-1.5f, -1.0f);
    drawTree(1.5f, 1.5f);
    drawTree(-1.5f, 1.5f);
    drawTree(1.5f, 3.0f);
    drawTree(-1.5f, 3.0f);
    drawTree(1.5f, 4.5f);
    drawTree(-1.5f, 4.5f);
}
