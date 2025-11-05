#include <SBX/window.h>

// Project headers
#include <SBX/errors.h>
#include <SBX/strings.h>

// Dependency headers
#include <glfw/glfw3native.h>

// LibC headers
#include <stdlib.h>
#include <stdbool.h>

// Window creation function
SBX_window_report_t SBXWindowCreate(SBX_window_t** window) {
    // Check if required arguments are provided
    if(!window) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }

    // Allocate memory for the SBXWindow struture
    *window = malloc(sizeof(SBX_window_t));

    // Check for a memory allocation error
    if(!*window) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MEMORY_FAILURE,
            .reportMessage = SBX_REPORT_STRING_COMMON_MEMORY_FAILURE
        };
    }

    // Set SBXWindow members to a deinitialized state
    (*window)->initialized   = false;
    (*window)->windowHandle  = NULL;
    (*window)->openglContext = NULL;

    return (SBX_window_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_CREATION_SUCCESSFUL
    };
}

// Window destruction function
SBX_window_report_t SBXWindowDestroy(SBX_window_t* window) {
    // Check if required arguments are provided
    if(!window) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }
    // Check for window not already initialized
    if(window->initialized) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_WINDOW_ERROR_NOT_DEINIT,
            .reportMessage = SBX_REPORT_STRING_WINDOW_NOT_DEINIT
        };
    }

    free(window);

    return (SBX_window_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_DESTRUCTION_SUCCESSFUL
    };
}

// Window initialization function
SBX_window_report_t SBXWindowInit(SBX_window_t* window,
                                  SBX_string_t title,
                                  SBX_window_dimensions_t width, 
                                  SBX_window_dimensions_t height)
{
    // Check if required arguments are provided
    if(!(window && title && width && height)) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }
    // Check for window not already initialized
    if(window->initialized) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_WINDOW_ERROR_ALREADY_INIT,
            .reportMessage = SBX_REPORT_STRING_WINDOW_ALREADY_INIT
        };
    }

    // Make sure GLFW is initialized
    if(glfwInit() != GLFW_TRUE) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_WINDOW_ERROR_GLFW_INIT_FAILED,
            .reportMessage = SBX_REPORT_STRING_WINDOW_GLFW_INIT_FAILED
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
            .errorFlags    = SBX_WINDOW_ERROR_HANDLE_INIT_FAILED,
            .reportMessage = SBX_REPORT_STRING_WINDOW_HANDLE_FAILED
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
            .errorFlags    = SBX_COMMON_ERROR_MEMORY_FAILURE,
            .reportMessage = SBX_REPORT_STRING_COMMON_MEMORY_FAILURE
        };
    }

    // Attempt to initialize context
    if(!gladLoadGLContext(window->openglContext, (GLADloadfunc)glfwGetProcAddress)) {
        // Free the memory used by the GladGLContext struct before exiting
        free(window->openglContext);

        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_WINDOW_ERROR_CONTEXT_INIT_FAILED,
            .reportMessage = SBX_REPORT_STRING_WINDOW_CONTEXT_FAILED
        };
    }

    // Set init state to init
    window->initialized = true;

    return (SBX_window_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_WINDOW_INIT_SUCCESSFUL
    };
}


// Window deinitialization function
SBX_window_report_t SBXWindowDeinit(SBX_window_t* window) {
    // Check if required arguments are provided
    if(!window) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }
    // Check for window not already deinitialized
    if(!window->initialized) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_WINDOW_ERROR_ALREADY_DEINIT,
            .reportMessage = SBX_REPORT_STRING_WINDOW_ALREADY_DEINIT
        };
    }

    // Check if window handle exists, then destroy window and set handle to NULL
    if(window->windowHandle) {
        glfwDestroyWindow(window->windowHandle);
        window->windowHandle = NULL;
    }

    // Check if the OpenGL context is allocated/initialized, then free the memory
    if(window->openglContext) {
        free(window->openglContext);
    }

    // Set the init state to deinit
    window->initialized = false;

    return (SBX_window_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_WINDOW_DEINIT_SUCCESSFUL
    };
}

// Window get size function
SBX_window_report_t SBXWindowGetSize(SBX_window_t* window, SBX_window_dimensions_t* width, SBX_window_dimensions_t* height) {
    // Check if required arguments are provided
    if(!window) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }
    // Check for window initialized
    if(!window->initialized) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_WINDOW_ERROR_NOT_INIT,
            .reportMessage = SBX_REPORT_STRING_WINDOW_NOT_INIT
        };
    }

    // Get window size
    glfwGetWindowSize(window->windowHandle, width, height);
    if((width && *width == 0) || (height && *height == 0)) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_WINDOW_ERROR_GET_SIZE_FAILED,
            .reportMessage = SBX_REPORT_STRING_WINDOW_GET_SIZE_FAILED
        };
    }

    // Return success
    return (SBX_window_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_WINDOW_GET_SIZE_SUCCESSFUL
    };
}

// Window set size function
SBX_window_report_t SBXWindowSetSize(SBX_window_t* window, SBX_window_dimensions_t width, SBX_window_dimensions_t height) {
    // Check if required arguments are provided
    if(!(window && width && height)) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }
    // Check for window initialized
    if(!window->initialized) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_WINDOW_ERROR_NOT_INIT,
            .reportMessage = SBX_REPORT_STRING_WINDOW_NOT_INIT
        };
    }

    // Set window size
    glfwSetWindowSize(window->windowHandle, width, height);
    if(glfwGetError(NULL)) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_WINDOW_ERROR_SET_SIZE_FAILED,
            .reportMessage = SBX_REPORT_STRING_WINDOW_SET_SIZE_FAILED
        };
    }

    // Return success
    return (SBX_window_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_WINDOW_SET_SIZE_SUCCESSFUL
    };
}

// Window get title function
SBX_window_report_t SBXWindowGetTitle(SBX_window_t* window, SBX_string_t* title) {
    // Check if required arguments are provided
    if(!(window && title)) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }
    // Check for window initialized
    if(!window->initialized) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_WINDOW_ERROR_NOT_INIT,
            .reportMessage = SBX_REPORT_STRING_WINDOW_NOT_INIT
        };
    }

    // Get window size
    *title = glfwGetWindowTitle(window->windowHandle);
    if(*title == NULL) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_WINDOW_ERROR_GET_SIZE_FAILED,
            .reportMessage = SBX_REPORT_STRING_WINDOW_GET_TITLE_FAILED
        };
    }

    // Return success
    return (SBX_window_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_WINDOW_GET_TITLE_SUCCESSFUL
    };
}

// Window get title function
SBX_window_report_t SBXWindowSetTitle(SBX_window_t* window, SBX_string_t title) {
    // Check if required arguments are provided
    if(!(window && title)) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }
    // Check for window initialized
    if(!window->initialized) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_WINDOW_ERROR_NOT_INIT,
            .reportMessage = SBX_REPORT_STRING_WINDOW_NOT_INIT
        };
    }

    // Set window size
    glfwSetWindowTitle(window->windowHandle, title);
    if(glfwGetError(NULL)) {
        // Return error
        return (SBX_window_report_t){
            .errorFlags    = SBX_WINDOW_ERROR_SET_SIZE_FAILED,
            .reportMessage = SBX_REPORT_STRING_WINDOW_SET_TITLE_FAILED
        };
    }

    // Return success
    return (SBX_window_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_WINDOW_SET_TITLE_SUCCESSFUL
    };
}
