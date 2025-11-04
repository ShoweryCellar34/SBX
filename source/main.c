// Project headers
#include <SBX/window.h>

// Dependency headers
#include <PR/PR.h>
#include <cglm/struct.h>

// LibC headers
#include <stdio.h>

// Basic GLFW error callback
void errorCallback(int errorCode, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", errorCode, description);
}

int main(int argc, char* argv[]) {
    // Set error callback for GLFW
    glfwSetErrorCallback(errorCallback);

    // Not needed becuase this is done by SBXWindowDeinit, but still good practice if we need to do GLFW stuff before creating the window
    glfwInit();

    // Create the window
    SBX_window_t window;
    SBX_window_report_t windowReport = SBXWindowInit(&window, "SBX", 1200, 675);

    // Check if window was create properly
    if(windowReport.errorFlags) {
        printf("Failed to create window: %s", windowReport.reportMessage);
        glfwTerminate();
        return 1;
    }

    // Main application loop
    while(!glfwWindowShouldClose(window.windowHandle)) {
        // Clear the framebuffer
        prFramebufferClearColor(window.openglContext, NULL, 0, (vec4s){1.0f, 0.0f, 0.0f, 1.0f});

        // Swap buffers and check for inputs
        glfwSwapBuffers(window.windowHandle);
        glfwPollEvents();
    }

    // Destroy window
    windowReport = SBXWindowDeinit(&window);

    // Check if window was destroyed properly
    if(windowReport.errorFlags) {
        printf("Failed to destroy window: %s", windowReport.reportMessage);
        glfwTerminate();
        return 1;
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
