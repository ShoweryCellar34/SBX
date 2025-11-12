#ifndef SBX_STRINGS_H
#define SBX_STRINGS_H

// Common error strings
#define SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT       "One or more required arguments set to an invalid value (NULL or 0)"
#define SBX_REPORT_STRING_COMMON_MEMORY_FAILURE         "Error executing a memory operation (allocation, reallocation, and deallocation)"

// Common success string
#define SBX_REPORT_STRING_COMMON_CREATION_SUCCESSFUL    "Successfuly created/allocated object"
#define SBX_REPORT_STRING_COMMON_DESTRUCTION_SUCCESSFUL "Successfuly destroyed/freed object"

// SBXwindow error strings
#define SBX_REPORT_STRING_WINDOW_ALREADY_INIT           "Window already initialized"
#define SBX_REPORT_STRING_WINDOW_ALREADY_DEINIT         "Window already deinitialized"
#define SBX_REPORT_STRING_WINDOW_NOT_INIT               "Window not initialized"
#define SBX_REPORT_STRING_WINDOW_NOT_DEINIT             "Window not deinitialized"

#define SBX_REPORT_STRING_WINDOW_GLFW_INIT_FAILED       "GLFW failed to initialize"
#define SBX_REPORT_STRING_WINDOW_HANDLE_FAILED          "Failed to create window handle"
#define SBX_REPORT_STRING_WINDOW_CONTEXT_FAILED         "Failed to initialize OpenGL context"

#define SBX_REPORT_STRING_WINDOW_GET_SIZE_FAILED        "Getting window size failed"
#define SBX_REPORT_STRING_WINDOW_SET_SIZE_FAILED        "Setting window size failed"
#define SBX_REPORT_STRING_WINDOW_GET_TITLE_FAILED       "Getting window title failed"
#define SBX_REPORT_STRING_WINDOW_SET_TITLE_FAILED       "Setting window title failed"

// SBXWindow success strings
#define SBX_REPORT_STRING_WINDOW_INIT_SUCCESSFUL        "Successfuly initialized window"
#define SBX_REPORT_STRING_WINDOW_DEINIT_SUCCESSFUL      "Successfuly deinitialized window"
#define SBX_REPORT_STRING_WINDOW_GET_SIZE_SUCCESSFUL    "Successfuly got window size"
#define SBX_REPORT_STRING_WINDOW_SET_SIZE_SUCCESSFUL    "Successfuly set window size"
#define SBX_REPORT_STRING_WINDOW_GET_TITLE_SUCCESSFUL   "Successfuly got window title"
#define SBX_REPORT_STRING_WINDOW_SET_TITLE_SUCCESSFUL   "Successfuly set window title"

// SBXBox error strings
#define SBX_REPORT_STRING_BOX_ALREADY_INIT              "Box already initialized"
#define SBX_REPORT_STRING_BOX_ALREADY_DEINIT            "Box already deinitialized"
#define SBX_REPORT_STRING_BOX_NOT_INIT                  "Box not initialized"
#define SBX_REPORT_STRING_BOX_NOT_DEINIT                "Box not deinitialized"

// SBXBox success strings
#define SBX_REPORT_STRING_BOX_INIT_SUCCESSFUL           "Successfuly initialized box"
#define SBX_REPORT_STRING_BOX_DEINIT_SUCCESSFUL         "Successfuly deinitialized box"
#define SBX_REPORT_STRING_BOX_GET_SIZE_SUCCESSFUL       "Successfuly got box size"
#define SBX_REPORT_STRING_BOX_SET_SIZE_SUCCESSFUL       "Successfuly set box size"

#endif // SBX_STRINGS_H
