// Project headers
#include <SBX/window.h>

// Dependency headers
#include <cglm/struct.h>

// LibC headers
#include <stdio.h>

void errorCallback(int errorCode, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", errorCode, description);
}

int main(int argc, char* argv[]) {
    glfwSetErrorCallback(errorCallback);
    glfwInit();

    SBX_window_t window;
    SBXWindowCreate(&window, "SBX", 800, 450);

    while(!glfwWindowShouldClose(window.windowHandle)) {
        window.openglContext.Enable(GL_DEPTH_TEST);
        prFramebufferClearColor(&window.openglContext, NULL, 0, (vec4s){1.0f, 0.0f, 0.0f, 1.0f});

        glfwSwapBuffers(window.windowHandle);
        glfwPollEvents();
    }

    return 0;
}
