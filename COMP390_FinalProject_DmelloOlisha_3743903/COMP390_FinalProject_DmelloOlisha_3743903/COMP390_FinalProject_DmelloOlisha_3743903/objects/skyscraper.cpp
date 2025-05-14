/* Athabasca University

   Comp390 - Introduction to Computer Graphics - Final Project

   Skyscraper Component

   @author: Olisha Dmello

   @id: 3743903

   Description: This module defines a 3D skyscraper object for the city scene. The skyscraper is a composite object composed of a base structure, floors, and windows. The windows illuminate randomized lights.

   Note for Instructor:
   - Developed and tested on MacOS using GLUT framework.
*/

#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>
#include "skyscraper.h"
#include "lighting.h"
#include <cstdlib> // for rand()

Skyscraper tower;

Skyscraper::Skyscraper() {
    randomizeLights(); // initializes random window lights
}

// randomly turns on/off the windows lights
void Skyscraper::randomizeLights() {
    for (int r = 0; r < MAX_ROWS; ++r) {
        for (int c = 0; c < MAX_COL; ++c) {
            litWindows[r][c] = rand() % 2; // 0 or 1 randomly (lit and unlit)
        }
    }
}

// draws the body of the skyscraper (cube) and colors it
void Skyscraper::drawBase(float w, float h, float d, float r, float g, float b) {
    glColor3f(r, g, b); // light gray
    glPushMatrix();
        glScalef(w, h, d); // scales the skyscraper's dimensions (width, height, depth)
        glutSolidCube(1.0); // cube shaped base of the skyscraper
    glPopMatrix();
}

// draws the grid of windows on the front and back and sides of the skyscraper
// spacingX and spacingY - horizontal and vertical spacing between the windows
void Skyscraper::drawWindows(int row, int col) {
    glColor3f(0.8f, 0.9f, 1.0f); // light blue
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glDisable(GL_LIGHTING);
    
    // spacing and alignment
    float spacingX = 0.6f;  // horizontal spacing of the windows
    float spacingY = 7.0f / (row + 1);  // vertical spacing of the windows based on height
    float startingX = -0.6f;  // left margin
    float startingY = -7.0f / 2 + spacingY + 0.2f;

    // postion of the windows grid
    float frontZ = 1.05f; // front grid
    float backZ = -1.05f; // back grid
    float rightX = 1.05f; // right grid
    float leftX = -1.05f; // left grid
    
    for (int r = 0; r < row; ++r) { // loop for the number of rows
        for (int c = 0; c < col; ++c) { // loop for the number of columns
            glColor3f(
                litWindows[r][c] ? 1.0f : 0.2f,  // Red: full or dim
                litWindows[r][c] ? 1.0f : 0.2f,  // Green: full or dim
                litWindows[r][c] ? 0.6f : 0.2f   // Blue: warm glow or dim
            );
            float offsetX = startingX + c * spacingX;
            float offsetY = startingY + r * spacingY;
            // front grid of windows
            glPushMatrix();
                glTranslatef(offsetX, offsetY, frontZ);
                glScalef(0.25f, 0.25f, 0.02f);
                glutSolidCube(1.0);
            glPopMatrix();
            // back grid of windows
            glPushMatrix();
                glTranslatef(offsetX, offsetY, backZ);
                glScalef(0.25f, 0.25f, 0.02f);
                glutSolidCube(1.0);
            glPopMatrix();
            // right side grid of windows
            glPushMatrix();
                glTranslatef(rightX, offsetY, offsetX); // axis swapped for the side
                glRotatef(90, 0, 1, 0); // rotate to face right
                glScalef(0.25f, 0.25f, 0.02f);
                glutSolidCube(1.0);
            glPopMatrix();
            // left side grid of windows
            glPushMatrix();
                glTranslatef(leftX, offsetY, offsetX); // axis swapped for the side
                glRotatef(90, 0, 1, 0); // rotate to face left
                glScalef(0.25f, 0.25f, 0.02f);
                glutSolidCube(1.0);
            glPopMatrix();
        }
    }
    glEnable(GL_LIGHTING); // re-enable lighting for the scene
}

// draws the skyscraper object - base and windows (the full building)
void Skyscraper::draw(float r, float g, float b) {
    GL_SMOOTH; // smooth shading
    glPushMatrix();
        glTranslatef(0.0f, 4.0f, 0.0f);
        drawBase(2.0f, 7.0f, 2.0f, r, g, b); // Tall building base
        drawWindows(8, 3); // Grid of windows on front and back and side faces
    glPopMatrix();
}

void draw_skyscraper_layout(){
    // Place towers (front most to back most) - left most
    // three sized skyskyscraper (size 1: small, size 2: midsize, size 3: tall)
    // colored handpicked
    glPushMatrix();
        glTranslatef(-17.0f, 0.0f, 0.0f);
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 24.0f); tower.draw(0.4f, 0.8f, 0.5f); glPopMatrix(); // size 1 aquamarine
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 21.0f); glScalef(1.0f, 1.5f, 1.0f); tower.draw(0.6f, 0.3f, 0.6f); glPopMatrix(); // size 2 brown
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 18.0f); glScalef(1.0f, 2.0f, 1.0f); tower.draw(1.0f, 0.5f, 0.4f); glPopMatrix(); // size 3 coral
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 15.0f); tower.draw(0.18f, 0.3f, 0.18f); glPopMatrix(); // size 1 dark green
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 12.0f); glScalef(1.0f, 1.5f, 1.0f); tower.draw(0.18f, 0.3f, 0.3f); glPopMatrix(); // size 2 dark grey
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 18.0f); glScalef(1.0f, 2.0f, 1.0f); tower.draw(0.55f, 0.13f, 0.13f); glPopMatrix(); // size 3 firebrick
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 15.0f); tower.draw(0.8f, 0.5f, 0.2f); glPopMatrix(); // size 1 gold
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 12.0f); glScalef(1.0f, 1.5f, 1.0f); tower.draw(1.0f, 0.5f, 0.0f); glPopMatrix(); // size 2 orange
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 9.0f); glScalef(1.0f, 2.0f, 1.0f); tower.draw(0.73f, 0.56f, 0.56f); glPopMatrix(); // size 3 pink
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 6.0f); tower.draw(0.3f, 0.2f, 0.3f); glPopMatrix(); // size 1 violet
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 3.0f); glScalef(1.0f, 1.5f, 1.0f); tower.draw(0.13f, 0.37f, 0.31f); glPopMatrix(); // size 2 hunters green
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 0.0f); tower.draw(0.55f, 0.09f, 0.09f); glPopMatrix(); // size 1 red
        glPushMatrix(); glTranslatef(0.0f, 0.0f, -3.0f); glScalef(1.0f, 1.5f, 1.0f); tower.draw(0.87f, 0.58f, 0.98f); glPopMatrix(); // size 2 light purple
        glPushMatrix(); glTranslatef(0.0f, 0.0f, -6.0f); tower.draw(0.6f, 0.3f, 0.6f); glPopMatrix(); // size 1 brown
        glPushMatrix(); glTranslatef(0.0f, 0.0f, -9.0f); glScalef(1.0f, 2.0f, 1.0f); tower.draw(1.0f, 0.5f, 0.0f); glPopMatrix(); // size 3 coral
        glPushMatrix(); glTranslatef(0.0f, 0.0f, -12.0f); glScalef(1.0f, 1.5f, 1.0f); tower.draw(1.0f, 0.5f, 0.0f); glPopMatrix(); // size 2 orange
        glPushMatrix(); glTranslatef(0.0f, 0.0f, -15.0f); tower.draw(0.8f, 0.5f, 0.2f); glPopMatrix(); // size 1 gold
        glPushMatrix(); glTranslatef(0.0f, 0.0f, -18.0f); glScalef(1.0f, 2.0f, 1.0f); tower.draw(0.3f, 0.2f, 0.3f); glPopMatrix(); // size 3 violet
        glPushMatrix(); glTranslatef(0.0f, 0.0f, -21.0f); glScalef(1.0f, 2.0f, 1.0f); tower.draw(0.8f, 0.8f, 0.8f); glPopMatrix(); // size 3 grey
    glPopMatrix();
    
    // Place 2nd row of towers (front most to back most) - right most
    // three sized skyskyscraper (size 1: small, size 2: midsize, size 3: tall)
    // colored handpicked
    glPushMatrix();
        glTranslatef(17.0f, 0.0f, 0.0f);
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 24.0f); tower.draw(0.4f, 0.8f, 0.5f); glPopMatrix(); // size 1 aquamarine
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 21.0f); glScalef(1.0f, 1.5f, 1.0f); tower.draw(0.6f, 0.3f, 0.6f); glPopMatrix(); // size 2 brown
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 18.0f); glScalef(1.0f, 2.0f, 1.0f); tower.draw(1.0f, 0.5f, 0.4f); glPopMatrix(); // size 3 coral
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 15.0f); tower.draw(0.18f, 0.3f, 0.18f); glPopMatrix(); // size 1 dark green
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 12.0f); glScalef(1.0f, 1.5f, 1.0f); tower.draw(0.18f, 0.3f, 0.3f); glPopMatrix(); // size 2 dark grey
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 18.0f); glScalef(1.0f, 2.0f, 1.0f); tower.draw(0.55f, 0.13f, 0.13f); glPopMatrix(); // size 3 firebrick
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 15.0f); tower.draw(0.8f, 0.5f, 0.2f); glPopMatrix(); // size 1 gold
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 12.0f); glScalef(1.0f, 1.5f, 1.0f); tower.draw(1.0f, 0.5f, 0.0f); glPopMatrix(); // size 2 orange
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 9.0f); glScalef(1.0f, 2.0f, 1.0f); tower.draw(0.73f, 0.56f, 0.56f); glPopMatrix(); // size 3 pink
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 6.0f); tower.draw(0.3f, 0.2f, 0.3f); glPopMatrix(); // size 1 violet
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 3.0f); glScalef(1.0f, 1.5f, 1.0f); tower.draw(0.13f, 0.37f, 0.31f); glPopMatrix(); // size 2 hunters green
        glPushMatrix(); glTranslatef(0.0f, 0.0f, 0.0f); tower.draw(0.55f, 0.09f, 0.09f); glPopMatrix(); // size 1 red
        glPushMatrix(); glTranslatef(0.0f, 0.0f, -3.0f); glScalef(1.0f, 1.5f, 1.0f); tower.draw(0.87f, 0.58f, 0.98f); glPopMatrix(); // size 2 light purple
        glPushMatrix(); glTranslatef(0.0f, 0.0f, -6.0f); tower.draw(0.6f, 0.3f, 0.6f); glPopMatrix(); // size 1 brown
        glPushMatrix(); glTranslatef(0.0f, 0.0f, -9.0f); glScalef(1.0f, 2.0f, 1.0f); tower.draw(1.0f, 0.5f, 0.0f); glPopMatrix(); // size 3 coral
        glPushMatrix(); glTranslatef(0.0f, 0.0f, -12.0f); glScalef(1.0f, 1.5f, 1.0f); tower.draw(1.0f, 0.5f, 0.0f); glPopMatrix(); // size 2 orange
        glPushMatrix(); glTranslatef(0.0f, 0.0f, -15.0f); tower.draw(0.8f, 0.5f, 0.2f); glPopMatrix(); // size 1 gold
        glPushMatrix(); glTranslatef(0.0f, 0.0f, -18.0f); glScalef(1.0f, 2.0f, 1.0f); tower.draw(0.3f, 0.2f, 0.3f); glPopMatrix(); // size 3 violet
        glPushMatrix(); glTranslatef(0.0f, 0.0f, -21.0f); glScalef(1.0f, 2.0f, 1.0f); tower.draw(0.8f, 0.8f, 0.8f); glPopMatrix(); // size 3 grey
    glPopMatrix();
}
