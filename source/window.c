#include <SBX/window.h>

// Project headers
#include <SBX/strings.h>

// Dependency headers
#include <glfw/glfw3native.h>

// LibC headers
#include <stdlib.h>

SBX_window_report_t SBXWindowCreate(SBX_window_t* window,
                                    SBX_string_t title,
                                    SBX_window_dimensions_t width, 
                                    SBX_window_dimensions_t height)
{
    // Check if required arguments are provided
    if(!(window && title && width && height)) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = 0,
            .errorFlags      = SBX_WINDOW_ERROR_MISSING_ARGUMENT,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_MISSING_ARGUMENT
        };
    }
    // Check if window is already initialized
    if(window->flags & SBX_WINDOW_INIT) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = SBX_WINDOW_INIT,
            .errorFlags      = SBX_WINDOW_ERROR_NOT_DEINIT,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_ALREADY_INIT
        };
    }

    // Remove the window deinit flag (if set)
    window->flags &= ~SBX_WINDOW_DEINIT;

    // Make sure GLFW is initialized
    if(glfwInit() != GLFW_TRUE) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = 0,
            .errorFlags      = SBX_WINDOW_ERROR_GLFW_INIT_FAILED,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_GLFW_INIT_FAILED
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
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = 0,
            .errorFlags      = SBX_WINDOW_ERROR_HANDLE_INIT_FAILED,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_HANDLE_FAILED
        };
    }

    // Set window handle user pointer to the SBXWindow manager object
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
            .errorFlags      = SBX_WINDOW_ERROR_CONTEXT_INIT_FAILED,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_CONTEXT_FAILED
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
    // Check if required arguments are provided
    if(!window) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = 0,
            .errorFlags      = SBX_WINDOW_ERROR_MISSING_ARGUMENT,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_MISSING_ARGUMENT
        };
    }
    // Check if window is not initialized
    if(window->flags & SBX_WINDOW_DEINIT) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = SBX_WINDOW_DEINIT,
            .errorFlags      = SBX_WINDOW_ERROR_NOT_INIT,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_ALREADY_DEINIT
        };
    }

    // Remove the window deinit flag (if set)
    window->flags &= ~SBX_WINDOW_INIT;

    // Check if window handle exists, then destroy window and set handle to NULL
    if(window->windowHandle) {
        glfwDestroyWindow(window->windowHandle);
        window->windowHandle = NULL;
    }

    // Reset window state parameters
    window->title  = "\n";
    window->width  = -1;
    window->height = -1;

    // Set the deinit flag
    window->flags |= SBX_WINDOW_DEINIT;

    return (SBX_window_report_t){
        .problmaticFlags = 0,
        .errorFlags      = 0,
        .reportMessage   = SBX_REPORT_STRING_WINDOW_DEINIT_SUCCESSFUL
    };
}

SBX_window_report_t SBXWindowGetSize(SBX_window_t* window, SBX_window_dimensions_t* width, SBX_window_dimensions_t* height) {
    // Check if required arguments are provided
    if(!window) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = 0,
            .errorFlags      = SBX_WINDOW_ERROR_MISSING_ARGUMENT,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_MISSING_ARGUMENT
        };
    }
    // Check if window is initialized
    if(!(window->flags & SBX_WINDOW_INIT)) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = SBX_WINDOW_DEINIT,
            .errorFlags      = SBX_WINDOW_ERROR_NOT_INIT,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_HANDLE_NOT_INIT
        };
    }

    // Get window size
    glfwGetWindowSize(window->windowHandle, width, height);
    if((width && *width == 0) || (height && *height == 0)) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = 0,
            .errorFlags      = SBX_WINDOW_ERROR_GET_FAILED,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_GET_FAILED
        };
    }

    // Return success
    return (SBX_window_report_t){
        .problmaticFlags = 0,
        .errorFlags      = 0,
        .reportMessage   = SBX_REPORT_STRING_WINDOW_GET_SUCCESSFUL
    };
}

SBX_window_report_t SBXWindowGetTitle(SBX_window_t* window, SBX_string_t* title) {
    // Check if required arguments are provided
    if(!(window && title)) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = 0,
            .errorFlags      = SBX_WINDOW_ERROR_MISSING_ARGUMENT,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_MISSING_ARGUMENT
        };
    }
    // Check if window is initialized
    if(!(window->flags & SBX_WINDOW_INIT)) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = SBX_WINDOW_DEINIT,
            .errorFlags      = SBX_WINDOW_ERROR_NOT_INIT,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_HANDLE_NOT_INIT
        };
    }

    // Get window size
    *title = glfwGetWindowTitle(window->windowHandle);
    if(*title == NULL) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = 0,
            .errorFlags      = SBX_WINDOW_ERROR_GET_FAILED,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_GET_FAILED
        };
    }

    // Return success
    return (SBX_window_report_t){
        .problmaticFlags = 0,
        .errorFlags      = 0,
        .reportMessage   = SBX_REPORT_STRING_WINDOW_GET_SUCCESSFUL
    };
}
