#include "GraphicsEngine.h"
#include <stdio.h>

// Vertex data for demo project
static const GLfloat vertexBufferData[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
};

GraphicsEngine::GraphicsEngine(void)
{
    width = 640;
    height = 480;

    // Initialize Vertex Array Object
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    initShaders();
    initBuffer();
}

void GraphicsEngine::initShaders(void) {
    // Shader sources
    const GLchar* vertexSource =
        "attribute vec4 position;                     \n"
        "void main()                                  \n"
        "{                                            \n"
        "  gl_Position = vec4(position.xyz, 1.0);     \n"
        "}                                            \n";
    const GLchar* fragmentSource =
        "precision mediump float;\n"
        "void main()                                  \n"
        "{                                            \n"
        "  gl_FragColor[0] = gl_FragCoord.x/640.0;    \n"
        "  gl_FragColor[1] = gl_FragCoord.y/480.0;    \n"
        "  gl_FragColor[2] = 0.5;                     \n"
        "}                                            \n";

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, 0);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, 0);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
}

void GraphicsEngine::initBuffer(void) {
    glGenBuffers(1, &vertexbuffer);

    // Make it current
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData,
                 GL_STATIC_DRAW);
}

void GraphicsEngine::DisplaySample(void)
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Use our shader
    // glUseProgram(shaderProgram);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0 );

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}
