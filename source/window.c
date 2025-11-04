#include <SBX/window.h>

// Project headers
#include <SBX/strings.h>

// Dependency headers
#include <glfw/glfw3native.h>

// LibC headers
#include <stdlib.h>

// Window allocation function
SBX_window_report_t SBXWindowCreate(SBX_window_t** window) {
    // Check if required arguments are provided
    if(!(window && *window)) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = 0,
            .errorFlags      = SBX_WINDOW_ERROR_MISSING_ARGUMENT,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_MISSING_ARGUMENT
        };
    }

    *window = malloc(sizeof(SBX_window_t));
    if(!*window) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = 0,
            .errorFlags      = SBX_WINDOW_ERROR_MEMORY_FAILURE,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_MEMORY_FAILURE
        };
    }
    *window->flags        = SBX_WINDOW_DEINIT;
    *window->windowHandle = NULL;

    return (SBX_window_report_t){
        .problmaticFlags = 0,
        .errorFlags      = 0,
        .reportMessage   = SBX_REPORT_STRING_WINDOW_CREATION_SUCCESSFUL
    };
}

// Window creation function
SBX_window_report_t SBXWindowInit(SBX_window_t* window,
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
    if(!(window->flags & SBX_WINDOW_DEINIT)) {
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

    // Make our window handle the current context
    glfwMakeContextCurrent(window->windowHandle);

    // Attempt to allocate memory for the OpenGL context
    window->openglContext = malloc(sizeof(GladGLContext));
    if(!window->openglContext) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = 0,
            .errorFlags      = SBX_WINDOW_ERROR_MEMORY_FAILURE,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_MEMORY_FAILURE
        };
    }

    // Attempt to initialize context
    if(!gladLoadGLContext(window->openglContext, (GLADloadfunc)glfwGetProcAddress)) {
        // Free the memory used by the GladGLContext struct before exiting
        free(window->openglContext);

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

// Window destruction function
SBX_window_report_t SBXWindowDeinit(SBX_window_t* window) {
    // Check if required arguments are provided
    if(!window) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = 0,
            .errorFlags      = SBX_WINDOW_ERROR_MISSING_ARGUMENT,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_MISSING_ARGUMENT
        };
    }
    // Check if window is not already deinitialized
    if(!(window->flags & SBX_WINDOW_INIT)) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = SBX_WINDOW_DEINIT,
            .errorFlags      = SBX_WINDOW_ERROR_NOT_INIT,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_ALREADY_DEINIT
        };
    }

    // Remove the window init flag
    window->flags &= ~SBX_WINDOW_INIT;

    // Check if window handle exists, then destroy window and set handle to NULL
    if(window->windowHandle) {
        glfwDestroyWindow(window->windowHandle);
        window->windowHandle = NULL;
    }

    // Check if the OpenGL context is allocated/initialized, then free the memory
    if(window->openglContext) {
        free(window->openglContext);
    }

    // Set the deinit flag
    window->flags |= SBX_WINDOW_DEINIT;

    return (SBX_window_report_t){
        .problmaticFlags = 0,
        .errorFlags      = 0,
        .reportMessage   = SBX_REPORT_STRING_WINDOW_DEINIT_SUCCESSFUL
    };
}

// Window get size function
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
            .reportMessage   = SBX_REPORT_STRING_WINDOW_GET_SIZE_FAILED
        };
    }

    // Return success
    return (SBX_window_report_t){
        .problmaticFlags = 0,
        .errorFlags      = 0,
        .reportMessage   = SBX_REPORT_STRING_WINDOW_GET_SIZE_SUCCESSFUL
    };
}

// Window get title function
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
            .reportMessage   = SBX_REPORT_STRING_WINDOW_GET_TITLE_FAILED
        };
    }

    // Return success
    return (SBX_window_report_t){
        .problmaticFlags = 0,
        .errorFlags      = 0,
        .reportMessage   = SBX_REPORT_STRING_WINDOW_GET_TITLE_SUCCESSFUL
    };
}

// Window set size function
SBX_window_report_t SBXWindowSetSize(SBX_window_t* window, SBX_window_dimensions_t width, SBX_window_dimensions_t height) {
    // Check if required arguments are provided
    if(!(window && width && height)) {
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

    // Set window size
    glfwSetWindowSize(window->windowHandle, width, height);
    if(glfwGetError(NULL)) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = SBX_WINDOW_DEINIT,
            .errorFlags      = SBX_WINDOW_ERROR_SET_FAILED,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_SET_SIZE_FAILED
        };
    }

    // Return success
    return (SBX_window_report_t){
        .problmaticFlags = 0,
        .errorFlags      = 0,
        .reportMessage   = SBX_REPORT_STRING_WINDOW_SET_SIZE_SUCCESSFUL
    };
}

// Window get title function
SBX_window_report_t SBXWindowSetTitle(SBX_window_t* window, SBX_string_t title) {
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

    // Set window size
    glfwSetWindowTitle(window->windowHandle, title);
    if(glfwGetError(NULL)) {
        // Return error
        return (SBX_window_report_t){
            .problmaticFlags = SBX_WINDOW_DEINIT,
            .errorFlags      = SBX_WINDOW_ERROR_SET_FAILED,
            .reportMessage   = SBX_REPORT_STRING_WINDOW_SET_TITLE_FAILED
        };
    }

    // Return success
    return (SBX_window_report_t){
        .problmaticFlags = 0,
        .errorFlags      = 0,
        .reportMessage   = SBX_REPORT_STRING_WINDOW_SET_TITLE_SUCCESSFUL
    };
}
