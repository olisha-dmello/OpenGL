/* Athabasca University

   Comp390 - Introduction to Computer Graphics - Final Project

   Texture Component

   @author: Olisha Dmello

   @id: 3743903

   Description: This module helps to load a BMP image and converts it into an OpenGL texture.

   Note for Instructor:
   - Developed and tested on MacOS using GLUT framework.
*/

#define GL_SILENCE_DEPRECATION

#include "texture.h"
#include <stdio.h>
#include <stdlib.h>

// Load BMP file and returns the OpenGL TextureID
GLuint loadBMP(const char* filename) {
    FILE* file = fopen(filename, "rb");
    
    // checks if file opened successfully
    if (!file) {
        printf("Failed to open BMP file: %s\n", filename);
        return 0;
    }

    unsigned char header[54];
    fread(header, 1, 54, file);

    unsigned int dataPos   = *(int*)&(header[0x0A]);
    unsigned int imageSize = *(int*)&(header[0x22]);
    unsigned int width     = *(int*)&(header[0x12]);
    unsigned int height    = *(int*)&(header[0x16]);

    if (imageSize == 0) imageSize = width * height * 3;
    if (dataPos == 0) dataPos = 54;

    unsigned char* data = new unsigned char[imageSize];
    fread(data, 1, imageSize, file);
    fclose(file);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    delete[] data;
    return texture;
}
