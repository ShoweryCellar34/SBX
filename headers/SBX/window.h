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
    SBX_WINDOW_ERROR_MISSING_ARGUMENT    = 1 << 0,
    SBX_WINDOW_ERROR_NOT_INIT            = 1 << 1,
    SBX_WINDOW_ERROR_NOT_DEINIT          = 1 << 2,
    SBX_WINDOW_ERROR_GLFW_INIT_FAILED    = 1 << 3,
    SBX_WINDOW_ERROR_HANDLE_INIT_FAILED  = 1 << 4,
    SBX_WINDOW_ERROR_CONTEXT_INIT_FAILED = 1 << 5,
    SBX_WINDOW_ERROR_GET_FAILED          = 1 << 6,
    SBX_WINDOW_ERROR_SET_FAILED          = 1 << 7
};

/// @brief Structure used by SBXWindow management functions to report exit state for operation
struct SBXWindowReport {
    // Flags
    SBX_bit_flags_t    problmaticFlags; // SBXWindowFlags
    SBX_bit_flags_t    errorFlags;      // SBXWindowErrorFlags

    // Error string
    SBX_string_t reportMessage;
};

/// @brief Structure used by SBXWindow fuctions to store window handle, OpenGl context, and more data to repesent a window
struct SBXWindow {
    // State flags (DO NOT EDIT)
    SBX_bit_flags_t         flags; // SBXWindowFlags

    // Handles
    GLFWwindow*             windowHandle;
    GladGLContext           openglContext;
};


/// @brief Creates the window handle, initializes the OpenGl context, sets window init state flag, and other state settings such as title, width, height, etc.
/// @param window SBXWindow struct used to retrive, store, and check initialization related window data, cannot be NULL
/// @param title  The desired title for the window, cannot be NULL
/// @param width  The desired width for the window, cannot be 0
/// @param height The desired height for the window, cannot be 0
/// @return A SBXWindowReport struct that reports the return state of the creation function, this can be an error, or a success.
///         Possible errors include: SBX_WINDOW_ERROR_MISSING_ARGUMENT, SBX_WINDOW_ERROR_NOT_DEINIT,
///                                  SBX_WINDOW_ERROR_GLFW_INIT_FAILED, SBX_WINDOW_ERROR_HANDLE_INIT_FAILED,
///                                  SBX_WINDOW_ERROR_CONTEXT_INIT_FAILED
SBX_window_report_t SBXWindowCreate(SBX_window_t* window,
                                   SBX_string_t title,
                                   SBX_window_dimensions_t width,
                                   SBX_window_dimensions_t height);

/// @brief Destroys the window handle, deinitializes the OpenGl context, sets window deinit state flag, and unsets other state settings such as title, width, height, etc.
/// @param window SBXWindow struct used to retrive, store, and check deinitialization related window data, cannot be NULL
/// @return A SBXWindowReport struct that reports the return state of the destruction function, this can be an error, or a success
///         Possible errors include: SBX_WINDOW_ERROR_MISSING_ARGUMENT, SBX_WINDOW_ERROR_NOT_INIT
SBX_window_report_t SBXWindowDestroy(SBX_window_t* window);

/// @note This function does not cache values
/// @brief Gets the width and height of the supplied window and stores them in the supplied pointers, width and/or height can be NULL, on error width and height (if not NULL) will be set to 0
/// @param window SBXWindow struct used to retrive, store, and check size query related window data, cannot be NULL
/// @param width  A pointer to a SBX_window_dimensions_t variable to store window width in, can be NULL
/// @param height A pointer to a SBX_window_dimensions_t variable to store window height in, can be NULL
/// @return A SBXWindowReport struct that reports the return state of the size query function, this can be an error, or a success
///         Possible errors include: SBX_WINDOW_ERROR_MISSING_ARGUMENT, SBX_WINDOW_ERROR_NOT_INIT,
///                                  SBX_WINDOW_ERROR_GET_FAILED
SBX_window_report_t SBXWindowGetSize(SBX_window_t* window, SBX_window_dimensions_t* width, SBX_window_dimensions_t* height);

/// @note This function does not cache values
/// @brief Gets the title of the supplied window and stores it in the supplied pointer, on error title will be set to NULL
/// @param window SBXWindow struct used to retrive, store, and check title query related window data, cannot be NULL
/// @param title  A pointer to a SBX_string_t variable to store window title in, cannot be NULL
/// @return A SBXWindowReport struct that reports the return state of the title query function, this can be an error, or a success
///         Possible errors include: SBX_WINDOW_ERROR_MISSING_ARGUMENT, SBX_WINDOW_ERROR_NOT_INIT,
///                                  SBX_WINDOW_ERROR_GET_FAILED
SBX_window_report_t SBXWindowGetTitle(SBX_window_t* window, SBX_string_t* title);

/// @brief Sets the width and height of the supplied window, width or height cannot be 0
/// @param window SBXWindow struct used to retrive, store, and check size setting related window data, cannot be NULL
/// @param width  The desired width for the window, cannot be 0
/// @param height The desired height for the window, cannot be 0
/// @return A SBXWindowReport struct that reports the return state of the size setting function, this can be an error, or a success
///         Possible errors include: SBX_WINDOW_ERROR_MISSING_ARGUMENT, SBX_WINDOW_ERROR_NOT_INIT,
///                                  SBX_WINDOW_ERROR_SET_FAILED
SBX_window_report_t SBXWindowSetSize(SBX_window_t* window, SBX_window_dimensions_t width, SBX_window_dimensions_t height);

/// @brief Sets the title of the supplied window, title cannot be NULL
/// @param window SBXWindow struct used to retrive, store, and check title setting related window data, cannot be NULL
/// @param title  The desired title for the window, cannot be NULL
/// @return A SBXWindowReport struct that reports the return state of the title setting function, this can be an error, or a success
///         Possible errors include: SBX_WINDOW_ERROR_MISSING_ARGUMENT, SBX_WINDOW_ERROR_NOT_INIT,
///                                  SBX_WINDOW_ERROR_SET_FAILED
SBX_window_report_t SBXWindowSetTitle(SBX_window_t* window, SBX_string_t title);

#endif // SBX_WIDNOW_H
