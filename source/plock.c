// Project headers
#include <SBX/plock.h>
#include <SBX/strings.h>

// Plock type creation function
SBX_report_t SBXPlockTypeCreate(SBX_plock_type_t** plockType, SBX_color_t color) {
    // Check if required arguments are provided
    if(!plockType) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }

    // Allocate memory for the SBXPlock struture
    *plockType = malloc(sizeof(SBX_plock_type_t));

    // Check for a memory allocation error
    if(!*plockType) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MEMORY_FAILURE,
            .reportMessage = SBX_REPORT_STRING_COMMON_MEMORY_FAILURE
        };
    }

    // Set SBXPlockType members to values provided
    (*plockType)->color = color;

    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_COMMON_CREATION_SUCCESSFUL
    };
}

// Plock type destruction function
SBX_report_t SBXPlockTypeDestroy(SBX_plock_type_t* plockType) {
    // Check if required arguments are provided
    if(!plockType) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }

    free(plockType);

    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_COMMON_DESTRUCTION_SUCCESSFUL
    };
}

// Plock creation function
SBX_report_t SBXPlocksCreate(SBX_plock_t*** plocks, SBX_plock_count_t count) {
    // Check if required arguments are provided
    if(!plocks) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }

    // Allocate memory for the SBXPlock struture
    *plocks = malloc(sizeof(SBX_plock_t) * count);

    // Check for a memory allocation error
    if(!*plocks) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MEMORY_FAILURE,
            .reportMessage = SBX_REPORT_STRING_COMMON_MEMORY_FAILURE
        };
    }

    // Set SBXPlockType members to values provided
    for(int)

    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_COMMON_CREATION_SUCCESSFUL
    };
}
