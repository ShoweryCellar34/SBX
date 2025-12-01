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
    // Create the report struct we will use for error checking
    SBX_report_t report = {
        .errorFlags    = 0,
        .reportMessage = NULL
    };

    // Set error callback for GLFW
    glfwSetErrorCallback(errorCallback);

    // Not needed becuase this is done by SBXWindowDeinit, but still good practice if we need to do GLFW stuff before creating the window
    glfwInit();

    // Create the window
    SBX_window_t* window = NULL;
    report = SBXWindowCreate(&window);
    // Check if window was created properly
    if(report.errorFlags) {
        printf("Failed to create window: %s", report.reportMessage);
        glfwTerminate();
        return 1;
    }

    // Initialize window
    report = SBXWindowInit(window, "SBX", 1200, 675);
    // Check if window was initialized properly
    if(report.errorFlags) {
        printf("Failed to initialize window: %s", report.reportMessage);
        SBXWindowDestroy(window);
        glfwTerminate();
        return 1;
    }

    // Create the box
    SBX_box_t* box = NULL;
    report = SBXBoxCreate(&box);
    // Check if box was created properly
    if(report.errorFlags) {
        printf("Failed to create sandbox: %s", report.reportMessage);

        // Deinit window and glfw first, and don't worry about errors as we are already exiting
        report = SBXWindowDeinit(window);
        report = SBXWindowDestroy(window);
        glfwTerminate();

        return 1;
    }

    // Initialize box
    report = SBXBoxInit(box, 5, 5);
    // Check if box was initialized properly
    if(report.errorFlags) {
        printf("Failed to initialize box: %s", report.reportMessage);

        // Destroy box object, and don't worry about errors as we are already exiting
        SBXBoxDestroy(box);

        // Deinit and destroy window and terminate glfw first, and don't worry about errors as we are already exiting
        SBXWindowDeinit(window);
        SBXWindowDestroy(window);
        glfwTerminate();

        return 1;
    }

    for(SBX_plock_id_matrix_dimensions_t y = 0; y < box->plockIDMatrix.height; y++) {
        for(SBX_plock_id_matrix_dimensions_t x = 0; x < box->plockIDMatrix.width; x++) {
            size_t index = y * box->width + x;
            box->plockIDMatrix.plockIDs[index] = y;
            printf("%i ", box->plockIDMatrix.plockIDs[index]);
        }
        printf("\n");
    }
    printf("\n");

    SBXBoxSetSize(box, 8, 10);
    for(SBX_plock_id_matrix_dimensions_t y = 0; y < box->plockIDMatrix.height; y++) {
        for(SBX_plock_id_matrix_dimensions_t x = 0; x < box->plockIDMatrix.width; x++) {
            size_t index = y * box->width + x;
            printf("%i ", box->plockIDMatrix.plockIDs[index]);
        }
        printf("\n");
    }

    // Main application loop
    while(!glfwWindowShouldClose(window->windowHandle)) {
        // Clear the framebuffer
        prFramebufferClearColor(window->openglContext, NULL, 0, (vec4s){1.0f, 0.0f, 0.0f, 1.0f});

        // Swap buffers and check for inputs
        glfwSwapBuffers(window->windowHandle);
        glfwPollEvents();
    }

    // No error check as we are already exiting

    // Deinit and destroy box
    SBXBoxDeinit(box);
    SBXBoxDestroy(box);

    // Deinit and destroy window
    SBXWindowDeinit(window);
    SBXWindowDestroy(window);

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
