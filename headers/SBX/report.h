#ifndef SBX_REPORT_H
#define SBX_REPORT_H

// Project headers
#include <SBX/types.h>

/// @brief Structure used by SBXWindow functions to report exit state for operation
struct SBXReport {
    /// @brief This variable contains the bit flag for the error that was raised
    SBX_bit_flags_t errorFlags; // A variable to store different values from SBXErrorFlags

    /// @brief This variable contains an error message to go with the error
    SBX_string_t    reportMessage;
};

// Error type flags
enum SBXErrorFlags {
    // Common error flags

    /// @brief This error is generated when one or more required arguments are set to NULL, 0, or another state that represents an unset value
    SBX_COMMON_ERROR_MISSING_ARGUMENT    = 1 << 0,
    /// @brief This error is generated when a memory operation fails (malloc, realloc, free, etc.)
    SBX_COMMON_ERROR_MEMORY_FAILURE      = 1 << 1,

    // Window error flags

    /// @brief This error is generated when the window is not initialized when an operation needs it to be
    SBX_WINDOW_ERROR_NOT_INIT            = 1 << 2,
    /// @brief This error is generated when the window is not deinitialized when an operation needs it to be
    SBX_WINDOW_ERROR_NOT_DEINIT          = 1 << 3,
    /// @brief This error is generated when the window is already initialized when an operation tries to initialize it
    SBX_WINDOW_ERROR_ALREADY_INIT        = 1 << 4,
    /// @brief This error is generated when the window is already deinitialized when an operation tries to deinitialize it
    SBX_WINDOW_ERROR_ALREADY_DEINIT      = 1 << 5,
    /// @brief This error is generated when initializing GLFW fails
    SBX_WINDOW_ERROR_GLFW_INIT_FAILED    = 1 << 6,
    /// @brief This error is generated when creating the GLFW window handle fails
    SBX_WINDOW_ERROR_HANDLE_INIT_FAILED  = 1 << 7,
    /// @brief This error is generated when creating the glad OpenGL context fails
    SBX_WINDOW_ERROR_CONTEXT_INIT_FAILED = 1 << 8,
    /// @brief This error is generated when the getting the window size fails
    SBX_WINDOW_ERROR_GET_SIZE_FAILED     = 1 << 9,
    /// @brief This error is generated when the setting the window size fails
    SBX_WINDOW_ERROR_SET_SIZE_FAILED     = 1 << 10,
    /// @brief This error is generated when the getting the window title fails
    SBX_WINDOW_ERROR_GET_TITLE_FAILED    = 1 << 11,
    /// @brief This error is generated when the setting the window title fails
    SBX_WINDOW_ERROR_SET_TITLE_FAILED    = 1 << 12,

    // Box error flags

    /// @brief This error is generated when the box is not initialized when an operation needs it to be
    SBX_BOX_ERROR_NOT_INIT               = 1 << 13,
    /// @brief This error is generated when the box is not deinitialized when an operation needs it to be
    SBX_BOX_ERROR_NOT_DEINIT             = 1 << 14,
    /// @brief This error is generated when the box is already initialized when an operation tries to initialize it
    SBX_BOX_ERROR_ALREADY_INIT           = 1 << 15,
    /// @brief This error is generated when the box is already deinitialized when an operation tries to deinitialize it
    SBX_BOX_ERROR_ALREADY_DEINIT         = 1 << 16,
    /// @brief This error is generated when creating the plock array fails
    SBX_BOX_ERROR_PLOCKS_INIT_FAILED     = 1 << 17,
    /// @brief This error is generated when creating the plock ID matrix fails
    SBX_BOX_ERROR_PLOCK_IDS_INIT_FAILED  = 1 << 18,

    // Plock Array error flags

    /// @brief This error is generated when the setting window size fails
    SBX_PLOCK_ERROR_SET_SIZE_FAILED      = 1 << 19

    // Plock error flags
};

#endif // SBX_REPORT_H
