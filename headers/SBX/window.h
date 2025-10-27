#ifndef SBX_WINDOW_H
#define SBX_WINDOW_H

// Project headers
#include <SBX/types.h>

// Dependency headers
#include <glad/gl.h>
#include <GLFW/glfw3.h>

enum SBXWindowFlags {
    SBX_WINDOW_INIT   = 1 << 0,
    SBX_WINDOW_DEINIT = 1 << 1
};

enum SBXWindowErrorFlags {
    SBX_WINDOW_ERROR_BAD_FLAGS          = 1 << 0,
    SBX_WINDOW_ERROR_GLFW_INIT_ERROR    = 1 << 1,
    SBX_WINDOW_ERROR_HANDLE_INIT_ERROR  = 1 << 2,
    SBX_WINDOW_ERROR_CONTEXT_INIT_ERROR = 1 << 3
};

struct SBXWindowReport {
    // Flags
    SBX_bit_flags_t    problmaticFlags; // SBXWindowFlags
    SBX_bit_flags_t    errorFlags;      // SBXWindowErrorFlags

    // Error string
    SBX_const_string_t reportMessage;
};

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

// Window creation and destruction functions
SBX_window_report_t SBXWindowCreate(SBX_window_t* window,
                                   SBX_const_string_t title,
                                   SBX_window_dimensions_t width,
                                   SBX_window_dimensions_t height);

SBX_window_report_t SBXWindowDestroy(SBX_window_t* window);

#endif // SBX_WIDNOW_H
