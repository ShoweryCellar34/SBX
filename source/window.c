#include <SBX/window.h>

// Project headers
#include <SBX/strings.h>

// Dependency headers
#include <glfw/glfw3native.h>

// LibC headers
#include <stdlib.h>

SBX_window_report_t SBXWindowCreate(SBX_window_t* window,
                                    SBX_const_string_t title,
                                    SBX_window_dimensions_t width, 
                                    SBX_window_dimensions_t height)
{
    // Check if window and/or context is already initialized
    if(window->flags & SBX_WINDOW_INIT) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = SBX_WINDOW_INIT,
            .errorFlags      = SBX_WINDOW_ERROR_BAD_FLAGS,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_INIT_BAD_FLAGS
        };
    }

    // Make sure GLFW is initialized
    if(glfwInit() != GLFW_TRUE) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = 0,
            .errorFlags      = SBX_WINDOW_ERROR_GLFW_INIT_ERROR,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_INIT_GLFW_INIT_FAILED
        };
    }

    // Set window creation hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    window->windowHandle = glfwCreateWindow(width, height, title, NULL, NULL);

    // Reset window hints
    glfwDefaultWindowHints();

    // Check if window creation failed
    if(!window->windowHandle) {
        // Define errors as flags
        SBX_bit_flags_t errorFlags = SBX_WINDOW_ERROR_HANDLE_INIT_ERROR;

        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = 0,
            .errorFlags      = errorFlags,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_INIT_WINDOW_FAILED
        };
    }

    // Set window user pointer to the SBXWindow manager object
    glfwSetWindowUserPointer(window->windowHandle, window);

    // Get current window parameters
    glfwGetWindowSize(window->windowHandle, &window->width, &window->height);
    window->title = glfwGetWindowTitle(window->windowHandle);

    // Make our window handle the current context
    glfwMakeContextCurrent(window->windowHandle);
    // Attempt to initialize context
    if(!gladLoadGLContext(&window->openglContext, (GLADloadfunc)glfwGetProcAddress)) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = 0,
            .errorFlags      = SBX_WINDOW_ERROR_CONTEXT_INIT_ERROR,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_INIT_CONTEXT_FAILED
        };
    }

    window->flags |= SBX_WINDOW_INIT;

    return (SBX_window_report_t){
        .problmaticFlags = 0,
        .errorFlags      = 0,
        .reportMessage   = SBX_REPORT_STRING_WINDOW_INIT_SUCCESSFUL
    };
}

SBX_window_report_t SBXWindowDestroy(SBX_window_t* window) {
    // Check if window and/or context is initialized
    if(window->flags & SBX_WINDOW_DEINIT) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = SBX_WINDOW_DEINIT,
            .errorFlags      = SBX_WINDOW_ERROR_BAD_FLAGS,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_DEINIT_BAD_FLAGS
        };
    }

    // Check if window handle exists, then destroy window and set handle to NULL
    if(window->windowHandle) {
        glfwDestroyWindow(window->windowHandle);
        window->windowHandle = NULL;
    }

    return (SBX_window_report_t){
        .problmaticFlags = 0,
        .errorFlags      = 0,
        .reportMessage   = SBX_REPORT_STRING_WINDOW_DEINIT_SUCCESSFUL
    };
}
