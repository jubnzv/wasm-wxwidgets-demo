#pragma once

#include <stdint.h>
#include <GL/glew.h>


class GraphicsEngine
{
  private:

    // Screen dimensions
    GLint width;
    GLint height;

    GLuint vertexbuffer;
    GLuint vertexArrayId;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    GLuint screenSize;

    // Initialize shader objects
    void initShaders(void);

    // Initialize buffer for sample data
    void initBuffer(void);

  public:
    void DisplaySample(void);
    GraphicsEngine(void);
};
