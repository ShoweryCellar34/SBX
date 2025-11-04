#ifndef SBX_STRINGS_H
#define SBX_STRINGS_H

// SBXwindow error strings
#define SBX_REPORT_STRING_WINDOW_MISSING_ARGUMENT     "One or more required arguments set to NULL"
#define SBX_REPORT_STRING_WINDOW_MEMORY_FAILURE       "Error executing a memory operation (allocation, reallocation, and deallocation)"

#define SBX_REPORT_STRING_WINDOW_ALREADY_INIT         "Window and/or OpenGL context already initialized"
#define SBX_REPORT_STRING_WINDOW_ALREADY_DEINIT       "Window and/or OpenGL context not initialized"

#define SBX_REPORT_STRING_WINDOW_GLFW_INIT_FAILED     "GLFW failed to initialize"
#define SBX_REPORT_STRING_WINDOW_HANDLE_FAILED        "Failed to create window handle"
#define SBX_REPORT_STRING_WINDOW_HANDLE_NOT_INIT      "Window handle not initialized"
#define SBX_REPORT_STRING_WINDOW_CONTEXT_FAILED       "Failed to initialize OpenGL context"

#define SBX_REPORT_STRING_WINDOW_GET_SIZE_FAILED      "Getting window size failed"
#define SBX_REPORT_STRING_WINDOW_GET_TITLE_FAILED     "Getting window title failed"
#define SBX_REPORT_STRING_WINDOW_SET_SIZE_FAILED      "Setting window size failed"
#define SBX_REPORT_STRING_WINDOW_SET_TITLE_FAILED     "Setting window title failed"

// SBXWindow success strings
#define SBX_REPORT_STRING_WINDOW_CREATION_SUCCESSFUL  "Successfuly created/allocated window object"
#define SBX_REPORT_STRING_WINDOW_INIT_SUCCESSFUL      "Successfuly initialized window"
#define SBX_REPORT_STRING_WINDOW_DEINIT_SUCCESSFUL    "Successfuly deinitialized window"
#define SBX_REPORT_STRING_WINDOW_GET_SIZE_SUCCESSFUL  "Successfuly got window size"
#define SBX_REPORT_STRING_WINDOW_GET_TITLE_SUCCESSFUL "Successfuly got window title"
#define SBX_REPORT_STRING_WINDOW_SET_SIZE_SUCCESSFUL  "Successfuly set window size"
#define SBX_REPORT_STRING_WINDOW_SET_TITLE_SUCCESSFUL "Successfuly set window title"

#endif // SBX_STRINGS_H
