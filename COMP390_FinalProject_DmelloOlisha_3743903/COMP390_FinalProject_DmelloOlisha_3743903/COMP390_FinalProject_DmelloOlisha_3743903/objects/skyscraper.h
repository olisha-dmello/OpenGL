/* Athabasca University
   Comp390 - Introduction to Computer Graphics - Final Project
 
   Skyscraper Header File
 
   @author: Olisha Dmello
   @id: 3743903
   Description: This file defines the skyscraper component (skyscraper.cpp)
*/

#ifndef SKYSCRAPER_H
#define SKYSCRAPER_H
#define MAX_ROWS 8
#define MAX_COL 3

class Skyscraper {
private:
    bool litWindows[MAX_ROWS][MAX_COL];
    void drawBase(float w, float h, float d, float r, float g, float b);
    void drawWindows(int row, int col);
public:
    Skyscraper();
    void randomizeLights();
    void draw(float r, float g, float b);
};

extern Skyscraper tower;
void draw_skyscraper_layout();

#endif
