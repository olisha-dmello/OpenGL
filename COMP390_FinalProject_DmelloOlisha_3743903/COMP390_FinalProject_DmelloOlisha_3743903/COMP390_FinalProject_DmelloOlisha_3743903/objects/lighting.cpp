/* Athabasca University

   Comp390 - Introduction to Computer Graphics - Final Project

   Lighting Component

   @author: Olisha Dmello

   @id: 3743903

   Description: This file defines the lighting component for the scene, it includes a sun (global light), lamp post lights (local lights), and a toggle/interaction logic for "day" and "night".
 
   Note for Instructor: Developed and tested on MacOS using GLUT framework.
*/

#define GL_SILENCE_DEPRECATION

#include "lighting.h"

bool sunOn = true; // global variable to help toggle between "day" and "night" lighting modes

// draws a yellow spherical sun
void drawSun() {
    glPushMatrix();
        glTranslatef(1.0f, 20.0f, -10.0f); // place sun high in the sky
        glColor3f(1.0f, 1.0f, 0.0f); // bright yellow
        glutSolidSphere(1.5, 24, 24); // spherical
    glPopMatrix();
}

// sets up directional light (sunlight)
void setupSunlight() {
    if (sunOn) {
        glEnable(GL_LIGHTING); // enables global lighting if "day"
        glEnable(GL_LIGHT0); // enables sun lighting if "day"

        // properties of the sun light
        GLfloat sun_diffuse[]  = { 1.0f, 1.0f, 0.9f, 1.0f }; // soft yellow-white light
        GLfloat sun_ambient[]  = { 0.3f, 0.3f, 0.3f, 1.0f }; // ambient fill light
        GLfloat sun_specular[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // highlights
        GLfloat sun_position[] = { -1.0f, -20.0f, 10.0f, 0.0f }; // directional light
        // applies light properties
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_diffuse);
        glLightfv(GL_LIGHT0, GL_AMBIENT, sun_ambient);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sun_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, sun_position);
    } else {
        glDisable(GL_LIGHT0);  // only disables sunlight, keeps GL_LIGHTING on for lamps
    }

    glEnable(GL_COLOR_MATERIAL); // color tracking
    glShadeModel(GL_SMOOTH); // smooth shading
}

// draws lamp posts and enables per lamp light control
void drawLampPosts(float roadX, float zStart, float zEnd, float spacing) {
    int lightIndex = 2; // GL_LIGHT2 onward; maximum is GL_LIGHT7
    float lampHeight = 3.5f; // height of the lamp post pole

    for (float z = zStart; z <= zEnd && lightIndex <= 7; z += spacing) {
        float lampPositions[2][3] = { // two lamp posts per z position (left and right road)
            { roadX - 2.5f, lampHeight, z },
            { roadX + 3.5f, lampHeight, z }
        };

        for (int i = 0; i < 2 && lightIndex <= 7; ++i, ++lightIndex) {
            float* pos = lampPositions[i];

            // Draws lamp pole (always dark gray)
            glDisable(GL_LIGHTING);
            if (sunOn) glColor3f(0.3f, 0.3f, 0.3f); // darker during the "day"
            else glColor3f(0.5f, 0.5f, 0.5f); // lighter at "night"
            glPushMatrix();
                glTranslatef(pos[0], lampHeight / 2.0f, pos[2]);
                glPushMatrix();
                    glScalef(0.1f, lampHeight, 0.1f); // thin long cube
                    glutSolidCube(1.0);
                glPopMatrix();
            glPopMatrix();
            glEnable(GL_LIGHTING);

            // Draw bulb and apply light if night
            glPushMatrix();
            glTranslatef(pos[0], lampHeight, pos[2]); // bulb's position

            if (!sunOn) {
                // Enable OpenGL light at bulb position
                glEnable(GL_LIGHT0 + lightIndex);

                // soft yellow white glowing bulb
                GLfloat diffuse[]  = { 1.0f, 1.0f, 0.6f, 1.0f };
                GLfloat ambient[]  = { 0.2f, 0.2f, 0.1f, 1.0f };
                GLfloat position[] = { pos[0], lampHeight, pos[2], 1.0f }; // point light

                glLightfv(GL_LIGHT0 + lightIndex, GL_DIFFUSE, diffuse);
                glLightfv(GL_LIGHT0 + lightIndex, GL_AMBIENT, ambient);
                glLightfv(GL_LIGHT0 + lightIndex, GL_POSITION, position);
                glLightf(GL_LIGHT0 + lightIndex, GL_CONSTANT_ATTENUATION, 1.0f);
                glLightf(GL_LIGHT0 + lightIndex, GL_LINEAR_ATTENUATION, 0.05f);
                glLightf(GL_LIGHT0 + lightIndex, GL_QUADRATIC_ATTENUATION, 0.01f);

                // Make sphere emissive
                GLfloat emission[] = { 1.0f, 1.0f, 0.4f, 1.0f };
                glMaterialfv(GL_FRONT, GL_EMISSION, emission);
                glColor3f(1.0f, 1.0f, 0.4f);
            } else {
                glDisable(GL_LIGHT0 + lightIndex);
                GLfloat noEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
                glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
                glColor3f(0.3f, 0.3f, 0.3f);
            }

            glutSolidSphere(0.25, 12, 12); // bulb is a sphere
            glPopMatrix();

            // resets emission to avoid affecting the rest of the scene
            GLfloat resetEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
            glMaterialfv(GL_FRONT, GL_EMISSION, resetEmission);
        }
    }
}

