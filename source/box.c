// Project headers
#include <SBX/box.h>
#include <SBX/strings.h>

// Box creation function
SBX_report_t SBXBoxCreate(SBX_box_t** box) {
    // Check if required arguments are provided
    if(!box) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }

    // Allocate memory for the SBXBox struture
    *box = malloc(sizeof(SBX_box_t));

    // Check for a memory allocation error
    if(!*box) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MEMORY_FAILURE,
            .reportMessage = SBX_REPORT_STRING_COMMON_MEMORY_FAILURE
        };
    }

    // Set SBXBox members to values provided
    (*box)->initialized = false;
    (*box)->plocks      = SBX_POINTER_UNSET;
    (*box)->title       = SBX_POINTER_UNSET;
    (*box)->width       = SBX_DIMENSION_UNSET;
    (*box)->height      = SBX_DIMENSION_UNSET;

    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_CREATION_SUCCESSFUL
    };
}

// Window destruction function
SBX_report_t SBXBoxDestroy(SBX_box_t* box) {
    // Check if required arguments are provided
    if(!box) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }
    // Check for box not already initialized
    if(box->initialized) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_BOX_ERROR_NOT_DEINIT,
            .reportMessage = SBX_REPORT_STRING_BOX_NOT_DEINIT
        };
    }

    free(box);

    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_DESTRUCTION_SUCCESSFUL
    };
}
