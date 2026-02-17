#ifndef SBX_WINDOW_H
#define SBX_WINDOW_H

// Project headers
#include <SBX/types.h>
#include <SBX/report.h>

// Dependency headers
#include <glad/gl.h>
#include <GLFW/glfw3.h>

/// @brief Structure used by SBXWindow* functions to store window and OpenGl context handles required to represent a window
struct SBXWindow {
    /// @brief SBX_bool_t object used to keep initialization state
    SBX_bool_t initialized;

    /// @brief GLFWwindow* object that points to the internal window handle
    GLFWwindow*     windowHandle;
    /// @brief GladGLContext* object that points to the internal OpenGL context handle
    GladGLContext*  openglContext;
};

/// @brief Allocates memory for a SBXWindow object and then sets values to a deinitialized state.
/// @param window A pointer to a SBX_window_t pointer that will be set to the new object, cannot be SBX_POINTER_UNSET
/// @return A SBXReport struct that reports the return state of the creation function, this can be an error, or a success.
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT, SBX_COMMON_ERROR_MEMORY_FAILURE
SBX_report_t SBXWindowCreate(SBX_window_t** window);

/// @brief Deallocates a SBXWindow objects memory after check for deinitialization
/// @param window A SBX_window_t pointer to the desired SBXWindow to be destroyed, cannot be SBX_POINTER_UNSET
/// @return A SBXReport struct that reports the return state of the destruction function, this can be an error, or a success.
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT, SBX_WINDOW_ERROR_NOT_DEINIT
SBX_report_t SBXWindowDestroy(SBX_window_t* window);

/// @brief Creates the window and OpenGl context handles, sets initialization state, and title, width, and height parameters.
/// @param window SBXWindow struct used to retrieve, store, and check initialization related window data, cannot be SBX_POINTER_UNSET
/// @param title  The desired title for the window, cannot be SBX_POINTER_UNSET
/// @param width  The desired width for the window, cannot be SBX_DIMENSION_UNSET
/// @param height The desired height for the window, cannot be SBX_DIMENSION_UNSET
/// @return A SBXReport struct that reports the return state of the initialization function, this can be an error, or a success.
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT, SBX_WINDOW_ERROR_ALREADY_INIT,
///                                  SBX_WINDOW_ERROR_GLFW_INIT_FAILED, SBX_WINDOW_ERROR_HANDLE_INIT_FAILED,
///                                  SBX_COMMON_ERROR_MEMORY_FAILURE
SBX_report_t SBXWindowInit(SBX_window_t* window,
                                  SBX_string_t title,
                                  SBX_window_dimensions_t width,
                                  SBX_window_dimensions_t height);

/// @brief Destroys the window and OpenGl context handles, sets initialization state, title, width, and height parameters to unset values.
/// @param window SBXWindow struct used to retrieve, store, and check deinitialization related window data, cannot be SBX_POINTER_UNSET
/// @return A SBXReport struct that reports the return state of the deinitialization function, this can be an error, or a success
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT, SBX_WINDOW_ERROR_NOT_INIT
SBX_report_t SBXWindowDeinit(SBX_window_t* window);

/// @brief Gets the width and height of the supplied window and stores them in the supplied pointers, width and/or height can be SBX_POINTER_UNSET, on error width and height (if not SBX_POINTER_UNSET) will be set to SBX_DIMENSION_UNSET
/// @param window SBXWindow struct used to retrieve, store, and check size query related window data, cannot be SBX_POINTER_UNSET
/// @param width  A pointer to a SBX_window_dimensions_t variable to store window width in, can be SBX_POINTER_UNSET
/// @param height A pointer to a SBX_window_dimensions_t variable to store window height in, can be SBX_POINTER_UNSET
/// @return A SBXReport struct that reports the return state of the size query function, this can be an error, or a success
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT, SBX_WINDOW_ERROR_NOT_INIT,
///                                  SBX_WINDOW_ERROR_GET_SIZE_FAILED
SBX_report_t SBXWindowGetSize(SBX_window_t* window, SBX_window_dimensions_t* width, SBX_window_dimensions_t* height);

/// @brief Sets the width and height of the supplied window, width or height cannot be SBX_DIMENSION_UNSET
/// @param window SBXWindow struct used to retrieve, store, and check size setting related window data, cannot be SBX_POINTER_UNSET
/// @param width  The desired width for the window, cannot be SBX_DIMENSION_UNSET
/// @param height The desired height for the window, cannot be SBX_DIMENSION_UNSET
/// @return A SBXReport struct that reports the return state of the size setting function, this can be an error, or a success
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT, SBX_WINDOW_ERROR_NOT_INIT,
///                                  SBX_WINDOW_ERROR_SET_SIZE_FAILED
SBX_report_t SBXWindowSetSize(SBX_window_t* window, SBX_window_dimensions_t width, SBX_window_dimensions_t height);

/// @brief Gets the title of the supplied window and stores it in the supplied pointer, on error title will be set to NULL
/// @param window SBXWindow struct used to retrieve, store, and check title query related window data, cannot be SBX_POINTER_UNSET
/// @param title  A pointer to a SBX_string_t variable to store window title in, cannot be SBX_POINTER_UNSET
/// @return A SBXReport struct that reports the return state of the title query function, this can be an error, or a success
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT, SBX_WINDOW_ERROR_NOT_INIT,
///                                  SBX_WINDOW_ERROR_GET_TITLE_FAILED
SBX_report_t SBXWindowGetTitle(SBX_window_t* window, SBX_string_t* title);

/// @brief Sets the title of the supplied window, title cannot be SBX_POINTER_UNSET
/// @param window SBXWindow struct used to retrieve, store, and check title setting related window data, cannot be SBX_POINTER_UNSET
/// @param title  The desired title for the window, cannot be SBX_POINTER_UNSET
/// @return A SBXReport struct that reports the return state of the title setting function, this can be an error, or a success
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT, SBX_WINDOW_ERROR_NOT_INIT,
///                                  SBX_WINDOW_ERROR_SET_TITLE_FAILED
SBX_report_t SBXWindowSetTitle(SBX_window_t* window, SBX_string_t title);

#endif // SBX_WIDNOW_H
