#ifndef SBX_ERRORS_H
#define SBX_ERROR_H

// Common error type flags
enum SBXCommonErrorFlags {
    SBX_COMMON_ERROR_MISSING_ARGUMENT    = 1 << 0,
    SBX_COMMON_ERROR_MEMORY_FAILURE      = 1 << 1
};

// SBXWindowReport error type flags
enum SBXWindowErrorFlags {
    SBX_WINDOW_ERROR_NOT_INIT            = 1 << 0,
    SBX_WINDOW_ERROR_NOT_DEINIT          = 1 << 1,
    SBX_WINDOW_ERROR_ALREADY_INIT        = 1 << 2,
    SBX_WINDOW_ERROR_ALREADY_DEINIT      = 1 << 4,
    SBX_WINDOW_ERROR_GLFW_INIT_FAILED    = 1 << 5,
    SBX_WINDOW_ERROR_HANDLE_INIT_FAILED  = 1 << 6,
    SBX_WINDOW_ERROR_CONTEXT_INIT_FAILED = 1 << 7,
    SBX_WINDOW_ERROR_GET_SIZE_FAILED     = 1 << 8,
    SBX_WINDOW_ERROR_SET_SIZE_FAILED     = 1 << 9,
    SBX_WINDOW_ERROR_GET_TITLE_FAILED    = 1 << 10,
    SBX_WINDOW_ERROR_SET_TITLE_FAILED    = 1 << 11
};

// SBXBoxReport error type flags
enum SBXBoxErrorFlags {
    SBX_BOX_ERROR_MISSING_ARGUMENT = 1 << 0,
    SBX_BOX_                       = 1 << 1,
    SBX_BOX_ERROR_GET_FAILED       = 1 << 2,
    SBX_BOX_ERROR_SET_FAILED       = 1 << 3
};

// SBXPlockReport error type flags
enum SBXPlockErrorFlags {
    SBX_PLOCK_ERROR_MISSING_ARGUMENT = 1 << 0,
    SBX_PLOCK_                       = 1 << 1,
    SBX_PLOCK_ERROR_GET_FAILED       = 1 << 2,
    SBX_PLOCK_ERROR_SET_FAILED       = 1 << 3
};

#endif // SBX_ERROR_H
