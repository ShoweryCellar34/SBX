// Project headers
#include <SBX/plock.h>
#include <SBX/errors.h>
#include <SBX/strings.h>

// Plock creation function
SBX_plock_report_t SBXPlockCreate(SBX_plock_t** plock, SBX_color_t color) {
    // Check if required arguments are provided
    if(!plock) {
        // Return error
        return (SBX_plock_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }

    // Allocate memory for the SBXPlock struture
    *plock = malloc(sizeof(SBX_plock_t));

    // Check for a memory allocation error
    if(!*plock) {
        // Return error
        return (SBX_plock_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MEMORY_FAILURE,
            .reportMessage = SBX_REPORT_STRING_COMMON_MEMORY_FAILURE
        };
    }

    // Set SBXPlock members to values provided
    (*plock)->color = color;

    return (SBX_plock_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_CREATION_SUCCESSFUL
    };
}

// Window destruction function
SBX_plock_report_t SBXPlockDestroy(SBX_plock_t* plock) {
    // Check if required arguments are provided
    if(!plock) {
        // Return error
        return (SBX_plock_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }

    free(plock);

    return (SBX_plock_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_DESTRUCTION_SUCCESSFUL
    };
}
