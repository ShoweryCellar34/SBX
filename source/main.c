// Project headers
#include <SBX/window.h>
#include <SBX/box.h>
#include <SBX/plock.h>
#include <SBX/types.h>

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
    SBX_window_t* window = NULL;
    SBX_window_report_t windowReport = SBXWindowCreate(&window);
    // Check if window was created properly
    if(windowReport.errorFlags) {
        printf("Failed to create window: %s", windowReport.reportMessage);
        glfwTerminate();
        return 1;
    }

    // Initialize window
    windowReport = SBXWindowInit(window, "SBX", 1200, 675);
    // Check if window was initialized properly
    if(windowReport.errorFlags) {
        printf("Failed to initialize window: %s", windowReport.reportMessage);
        glfwTerminate();
        return 1;
    }

    // Main application loop
    while(!glfwWindowShouldClose(window->windowHandle)) {
        // Clear the framebuffer
        prFramebufferClearColor(window->openglContext, NULL, 0, (vec4s){1.0f, 0.0f, 0.0f, 1.0f});

        // Swap buffers and check for inputs
        glfwSwapBuffers(window->windowHandle);
        glfwPollEvents();
    }

    // Deinit window
    windowReport = SBXWindowDeinit(window);
    // Check if window was deinitialized properly
    if(windowReport.errorFlags) {
        printf("Failed to deinitialize window: %s", windowReport.reportMessage);
        glfwTerminate();
        return 1;
    }

    // Destroy window
    windowReport = SBXWindowDestroy(window);
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
