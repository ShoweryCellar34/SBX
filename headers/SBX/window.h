#ifndef SBX_WINDOW_H
#define SBX_WINDOW_H

// Project headers
#include <SBX/types.h>

// Dependency headers
#include <glad/gl.h>
#include <GLFW/glfw3.h>

// SBXWindow state keeping flags
enum SBXWindowFlags {
    SBX_WINDOW_INIT   = 1 << 0,
    SBX_WINDOW_DEINIT = 1 << 1
};

// SBXWindowReport error type flags
enum SBXWindowErrorFlags {
    SBX_WINDOW_ERROR_BAD_FLAGS          = 1 << 0,
    SBX_WINDOW_ERROR_GLFW_INIT_ERROR    = 1 << 1,
    SBX_WINDOW_ERROR_HANDLE_INIT_ERROR  = 1 << 2,
    SBX_WINDOW_ERROR_CONTEXT_INIT_ERROR = 1 << 3
};

/// @brief Structure used by SBXWindow management functions to report exit state for operation
struct SBXWindowReport {
    // Flags
    SBX_bit_flags_t    problmaticFlags; // SBXWindowFlags
    SBX_bit_flags_t    errorFlags;      // SBXWindowErrorFlags

    // Error string
    SBX_const_string_t reportMessage;
};

/// @brief Structure used by SBXWindow fuctions to store window handle, OpenGl context, and more data to repesent a window
struct SBXWindow {
    // State flags (DO NOT EDIT)
    SBX_bit_flags_t         flags; // SBXWindowFlags

    // Handles
    GLFWwindow*             windowHandle;
    GladGLContext           openglContext;

    // Parameters
    SBX_const_string_t      title;
    SBX_window_dimensions_t width,
                            height;
};


/// @brief Creates the window handle, initializes the OpenGl context, sets window init state flag, and other state settings such as title, width, height, etc.
/// @param window SBXWindow struct used to retrive, store, and check initialization related window data
/// @param title  The desired title for the window
/// @param width  The desired width for the window
/// @param height The desired height for the window
/// @return A SBXWindowReport struct that reports the return state of the creation function, this can be an error, or a success
SBX_window_report_t SBXWindowCreate(SBX_window_t* window,
                                   SBX_const_string_t title,
                                   SBX_window_dimensions_t width,
                                   SBX_window_dimensions_t height);

/// @brief Destroys the window handle, deinitializes the OpenGl context, sets window deinit state flag, and unsets other state settings such as title, width, height, etc.
/// @param window SBXWindow struct used to retrive, store, and check deinitialization related window data
/// @return A SBXWindowReport struct that reports the return state of the destruction function, this can be an error, or a success
SBX_window_report_t SBXWindowDestroy(SBX_window_t* window);

#endif // SBX_WIDNOW_H
