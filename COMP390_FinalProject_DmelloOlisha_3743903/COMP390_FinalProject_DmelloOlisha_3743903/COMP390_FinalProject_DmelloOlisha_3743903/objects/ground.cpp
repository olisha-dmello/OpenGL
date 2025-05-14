/* Athabasca University

   Comp390 - Introduction to Computer Graphics - Final Project

   Ground Component

   @author: Olisha Dmello

   @id: 3743903

   Description: This file defines the ground component as a composite 3D object made up of a base (ground plane), two roads with sidewalks and lane dividers, and zebra crossings.
 
   Note for Instructor: Developed and tested on MacOS using GLUT framework.
*/

#define GL_SILENCE_DEPRECATION

#include "ground.h"
#include "lighting.h" // required for sunOn

#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>

// draws a flat base for the city
void drawGround() {
    if (!sunOn) glDisable(GL_LIGHTING); // turns off lighting at "night" for a full black ground

    glColor3f(0.2f, 0.2f, 0.2f); // dark grey color
    if (!sunOn) glColor3f(0.05f, 0.05f, 0.05f); // dark/black at "night"

    // draws a ground base plane
    glBegin(GL_QUADS);
        glVertex3f(-20.0f, 0.0f, -25.5f);
        glVertex3f( 20.0f, 0.0f, -25.5f);
        glVertex3f( 20.0f, 0.0f,  25.5f);
        glVertex3f(-20.0f, 0.0f,  25.5f);
    glEnd();

    if (!sunOn) glEnable(GL_LIGHTING); // restores lighting after
}

// draws a road with sidewalks and lane dividers with respect to the x position
void drawRoad(float roadX) {
    if (!sunOn) glDisable(GL_LIGHTING); // no lighting at "night"
    glColor3f(sunOn ? 0.4f : 0.05f, sunOn ? 0.4f : 0.05f, sunOn ? 0.4f : 0.05f); // darker road at "night" and lighter road in the "day"

    // Main road
    glBegin(GL_QUADS);
        glVertex3f(roadX - 2.0f, 0.02f, -25.5f);
        glVertex3f(roadX + 2.0f, 0.02f, -25.5f);
        glVertex3f(roadX + 2.0f, 0.02f,  25.5f);
        glVertex3f(roadX - 2.0f, 0.02f,  25.5f);
    glEnd();

    // Sidewalk color - if "day" then light grey, else if it's "night" then medium/darker grey
    if (sunOn) glColor3f(0.7f, 0.7f, 0.7f);
    else glColor3f(0.3f, 0.3f, 0.3f);

    // Sidewalks
    glBegin(GL_QUADS);
        // left sidewalk
        glVertex3f(roadX - 4.0f, 0.03f, -25.5f);
        glVertex3f(roadX - 2.0f, 0.03f, -25.5f);
        glVertex3f(roadX - 2.0f, 0.03f,  25.5f);
        glVertex3f(roadX - 4.0f, 0.03f,  25.5f);
        // right sidewalk
        glVertex3f(roadX + 2.0f, 0.03f, -25.5f);
        glVertex3f(roadX + 4.0f, 0.03f, -25.5f);
        glVertex3f(roadX + 4.0f, 0.03f,  25.5f);
        glVertex3f(roadX + 2.0f, 0.03f,  25.5f);
    glEnd();

    // Lane Divider
    glColor3f(1.0f, 1.0f, 0.0f); // bright yellow
    for (float z = -24.5f; z <= 24.5f; z += 3.0f) { // draws the lane dividers until reached the desired z
        glBegin(GL_QUADS);
            glVertex3f(roadX - 0.1f, 0.04f, z);
            glVertex3f(roadX + 0.1f, 0.04f, z);
            glVertex3f(roadX + 0.1f, 0.04f, z + 1.0f);
            glVertex3f(roadX - 0.1f, 0.04f, z + 1.0f);
        glEnd();
    }
    if (!sunOn) glEnable(GL_LIGHTING); // re-enable lighting

}

// draws a pedestrian crossing
void drawZebraCrossing(float zPos, float centerX) {
    float stripeWidth = 1.0f; // width of the stripe
    float stripeLength = 4.0f; // length of the stripe
    float gap = 1.0f; // space between each stripe
    int stripeCount = 8; // number of stripes
    
    if (!sunOn) glEnable(GL_LIGHTING); // turns on lighting at "night"

    for (int i = 0; i < stripeCount; ++i) {
        float x = centerX - stripeLength/2 + i * (stripeWidth + gap); // the x value for the position of the stripe to be placed

        if (!sunOn) glDisable(GL_LIGHTING); // turns off lighting if needed
        glColor3f(sunOn ? 1.0f : 0.9f, sunOn ? 1.0f : 0.9f, sunOn ? 1.0f : 0.9f); // dimmer white at "night"

        // draws the stripe (rectangle/quad)
        glBegin(GL_QUADS);
            glVertex3f(x, 0.035f, zPos - stripeLength / 2);
            glVertex3f(x + stripeWidth, 0.035f, zPos - stripeLength / 2);
            glVertex3f(x + stripeWidth, 0.035f, zPos + stripeLength / 2);
            glVertex3f(x, 0.035f, zPos + stripeLength / 2);
        glEnd();
    }

    glEnable(GL_LIGHTING); // turns on the lighting
}

// blueprint/layout of the ground - setup
void draw_ground_layout(){
    drawGround(); // base of the city
    drawZebraCrossing(-22.0f, -5.5f); // zebra crossing - top
    drawZebraCrossing(0.0f, -5.5f); // zebra crossing - middle
    drawZebraCrossing(22.0f, -5.5f); // zebra crossing - bottom
    // Left road with lamp posts
    glPushMatrix();
        glTranslatef(-17.0f, 0.0f, 0.0f); // left most
        drawRoad(5.5f); // draws the road with sidewalks and lane dividers
        drawLampPosts(5.0f, -24.0f, 24.0f, 22.0f); // lamp posts along the road
    glPopMatrix();
    // Right road with lamp posts
    glPushMatrix();
        glTranslatef(17.0f, 0.0f, 0.0f); // right most
        drawRoad(-5.5f); // draws the road with sidewalks and lane dividers
        drawLampPosts(-6.0f, -24.0f, 24.0f, 22.0f); // lamp posts along the road
    glPopMatrix();

    
}
