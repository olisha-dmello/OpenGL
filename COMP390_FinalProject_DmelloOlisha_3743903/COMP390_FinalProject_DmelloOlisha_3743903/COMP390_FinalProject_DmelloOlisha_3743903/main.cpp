/* Athabasca University

   Comp390 - Introduction to Computer Graphics

   Final Project - City Skyscraper Scene

   @author: Olisha Dmello
   @id: 3743903

   Description:
   This program renders a 3D city scene featuring skyscrapers, a textured fireworks/ sky background, colored lights, trees, fog, interaction, and basic animation support.
 
   Option 1 chosen
 
   Note for Instructor:
   - Please change the file paths for the textures according to your path placement.
   - Developed and tested on MacOS using GLUT framework.
*/

#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>

#include "skyscraper.h"
#include "texture.h"
#include "lighting.h"
#include "ground.h"
#include "fountain.h"
#include "tree.h"

GLuint textureID; // global variable storing textureID

// draws the textured background walls (back, left, right) - sky in the "day" and fireworks in the "night"
void drawBackground() {
    glDisable(GL_LIGHTING); // disables the lighting to keep the brightness of the texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor3f(1.0f, 1.0f, 1.0f); // No tint

    float wallBottomY = 0.0f; // base y of the wall
    float wallTopY = 30.0f; // height of the wall

    // Back wall
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(-20.0f, wallBottomY, -25.5f);
        glTexCoord2f(1.0, 0.0); glVertex3f( 20.0f, wallBottomY, -25.5f);
        glTexCoord2f(1.0, 1.0); glVertex3f( 20.0f, wallTopY, -25.5f);
        glTexCoord2f(0.0, 1.0); glVertex3f(-20.0f, wallTopY, -25.5f);
    glEnd();

    // Left side wall
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(-20.0f, wallBottomY, 25.5f);
        glTexCoord2f(1.0, 0.0); glVertex3f(-20.0f, wallBottomY, -25.5f);
        glTexCoord2f(1.0, 1.0); glVertex3f(-20.0f, wallTopY, -25.5f);
        glTexCoord2f(0.0, 1.0); glVertex3f(-20.0f, wallTopY, 25.5f);
    glEnd();

    // Right side wall
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(20.0f, wallBottomY, -25.5f);
        glTexCoord2f(1.0, 0.0); glVertex3f(20.0f, wallBottomY, 25.5f);
        glTexCoord2f(1.0, 1.0); glVertex3f(20.0f, wallTopY, 25.5f);
        glTexCoord2f(0.0, 1.0); glVertex3f(20.0f, wallTopY, -25.5f);
    glEnd();

    glDisable(GL_TEXTURE_2D); // turns off texturing
    glEnable(GL_LIGHTING); // re-enables lighting
}

// updates the windows lighting of the skyscraper
void updateLights(int value) {
    tower.randomizeLights(); // randomizes lit windows
    glutPostRedisplay(); // redraws scene
    glutTimerFunc(1000, updateLights, 0); // updates every second
}

// handles mouse interaction to toggle between "day" effect and "night" effect
// click anywhere on the screen for toggling
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        sunOn = !sunOn;  // toggle sun

        // Reload appropriate texture when sun mode changes
        if (!sunOn) // "night" texture
            textureID = loadBMP("/Users/olishadmello/Desktop/GITHUB/COMP390_FinalProject_DmelloOlisha_3743903/COMP390_FinalProject_DmelloOlisha_3743903/COMP390_FinalProject_DmelloOlisha_3743903/textures/fireworks.bmp"); // please change this according to your path placement
        else // "day" texture
            textureID = loadBMP("/Users/olishadmello/Desktop/GITHUB/COMP390_FinalProject_DmelloOlisha_3743903/COMP390_FinalProject_DmelloOlisha_3743903/COMP390_FinalProject_DmelloOlisha_3743903/textures/sky.bmp"); // please change this according to your path placement

        glutPostRedisplay(); // redraw with the updated texture
    }
}

// renders an atmospheric effect - "day" has fog and "night" has no fog
void setupFog() {
    if (sunOn) {
        glEnable(GL_FOG); // enables fog
        GLfloat fogColor[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // neutral gray
        glFogfv(GL_FOG_COLOR, fogColor); // sets fog color

        glFogi(GL_FOG_MODE, GL_LINEAR);

        // Set fog start and end (for linear)
        glFogf(GL_FOG_START, 15.0f);  // where fog begins
        glFogf(GL_FOG_END, 80.0f);    // where fog fully covers
        glFogf(GL_FOG_DENSITY, 0.005f);
    }
    else {
        glDisable(GL_FOG); // disables fog at "night"
    }
}

// renders the entire city
void drawCity() {
    drawBackground(); // textured background
    // includes atleast 5 different 3D composite objects with two light sources of different lighting colors
    draw_ground_layout();
    draw_fountain_layout();
    draw_trees_layout();
    // includes animations effect
    draw_skyscraper_layout();
    
    // The program has also has interaction and atmospheric attenuation effect
}

// main rendering function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(10.0, 30.0, 40.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // camera view (eye position, look-at target, up-vector)
    setupSunlight(); // main light source (sun or moon)
    setupFog(); // enable or disable fog based on "day" or "night"
    drawCity(); // draws all objects
    drawSun(); // draws sun/moon
    glutSwapBuffers();
}

// window resizing
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w/h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// one-time scene initialization
void initialize() {
    glEnable(GL_DEPTH_TEST);
    GLfloat global_ambient[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    setupSunlight();
    glClearColor(0.6, 0.6, 0.6, 1.0); // grey back drop
}

// program launch
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutCreateWindow("Olisha Dmello - Final Project: City Scene");

    initialize();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    textureID = loadBMP("/Users/olishadmello/Desktop/COMP 390/COMP390_FinalProject_DmelloOlisha_3743903/COMP390_FinalProject_DmelloOlisha_3743903/COMP390_FinalProject_DmelloOlisha_3743903/textures/sky.bmp"); // please change this according to your path placement
    glutMouseFunc(mouse);
    glutTimerFunc(1000, updateLights, 0);
    glutMainLoop();
    return 0;
}
