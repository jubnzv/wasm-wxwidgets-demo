#include <functional>
#include <emscripten.h>
#include <stdio.h>
#include <stdint.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GraphicsEngine.h"

#define GLFW_INCLUDE_ES3

GLFWwindow* window;

std::function<void()> loop;
void main_loop() { loop(); }

int main(void)
{
    if (!glfwInit())
    {
        fprintf(stderr, "Error: GLFW Initialization failed.");
        emscripten_force_exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(1024, 768, "Demo", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Error: GLFW Window Creation Failed");
        glfwTerminate();
        emscripten_force_exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    GraphicsEngine engine;

    loop = [&]
    {
        // Clear the screen
        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        engine.DisplaySample();

        glfwPollEvents();
        glfwSwapBuffers(window);
    };
    emscripten_set_main_loop(main_loop, 0, true);

    return 0;
}
