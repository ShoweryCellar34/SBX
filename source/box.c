// Project headers
#include <SBX/box.h>
#include <SBX/strings.h>
#include <SBX/plock.h>

// LibC headers
#include <stdlib.h>
#include <string.h>

// Box creation function
SBX_report_t SBXBoxCreate(SBX_box_t** box) {
    // Check if required arguments are provided
    if(box == SBX_POINTER_UNSET) {
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

    // Set SBXBox members to values a deinitialized state
    (*box)->initialized   = false;
    (*box)->width         = SBX_DIMENSION_UNSET;
    (*box)->height        = SBX_DIMENSION_UNSET;
    (*box)->plockArray    = (SBX_plock_array_t){.plocks = NULL, .count = 0};
    (*box)->plockIDMatrix = (SBX_plock_id_matrix_t){.plockIDs = NULL, .width = SBX_DIMENSION_UNSET, .height = SBX_DIMENSION_UNSET};

    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_COMMON_CREATION_SUCCESSFUL
    };
}

// Box destruction function
SBX_report_t SBXBoxDestroy(SBX_box_t* box) {
    // Check if required arguments are provided
    if(box == SBX_POINTER_UNSET) {
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
        .reportMessage = SBX_REPORT_STRING_COMMON_DESTRUCTION_SUCCESSFUL
    };
}

SBX_report_t SBXBoxInit(SBX_box_t* box,
                        SBX_box_dimensions_t width,
                        SBX_box_dimensions_t height)
{
    // Check if required arguments are provided
    if((box == SBX_POINTER_UNSET) || (width == SBX_DIMENSION_UNSET) || (height == SBX_DIMENSION_UNSET)) {
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
            .errorFlags    = SBX_BOX_ERROR_ALREADY_INIT,
            .reportMessage = SBX_REPORT_STRING_BOX_ALREADY_INIT
        };
    }

    // Create plock array
    SBX_report_t report = SBXPlockArraySetSize(&box->plockArray, width * height);

    // Check if plock array creation failed
    if(report.errorFlags) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_BOX_ERROR_PLOCKS_INIT_FAILED,
            .reportMessage = SBX_REPORT_STRING_BOX_PLOCKS_FAILED
        };
    }

    // Create plock array
    report = SBXPlockIDMatrixSetSize(&box->plockIDMatrix, width, height);

    // Check if plock ID matrix creation failed
    if(report.errorFlags) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_BOX_ERROR_PLOCK_IDS_INIT_FAILED,
            .reportMessage = SBX_REPORT_STRING_BOX_PLOCK_IDS_FAILED
        };
    }

    // Set box parameters
    box->width  = width;
    box->height = height;

    // Set init state to init
    box->initialized = true;

    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_BOX_INIT_SUCCESSFUL
    };
}

SBX_report_t SBXBoxDeinit(SBX_box_t* box) {
    // Check if required arguments are provided
    if(box == SBX_POINTER_UNSET) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }
    // Check for box not already deinitialized
    if(!box->initialized) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_BOX_ERROR_ALREADY_DEINIT,
            .reportMessage = SBX_REPORT_STRING_BOX_ALREADY_DEINIT
        };
    }

    // Check if plock array exists, then destroy it
    if(box->plockArray.plocks) {
        SBXPlockArraySetSize(&box->plockArray, 0);
    }

    // Check if plock ID matrix exists, then destroy it
    if(box->plockIDMatrix.plockIDs) {
        SBXPlockIDMatrixSetSize(&box->plockIDMatrix, 0, 0);
    }

    // Set the init state to deinit
    box->initialized = false;

    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_BOX_DEINIT_SUCCESSFUL
    };
}

SBX_report_t SBXBoxGetSize(SBX_box_t* box, SBX_box_dimensions_t* width, SBX_box_dimensions_t* height) {
    // Check if required arguments are provided
    if(box == SBX_POINTER_UNSET) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }
    // Check for box initialized
    if(!box->initialized) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_BOX_ERROR_NOT_INIT,
            .reportMessage = SBX_REPORT_STRING_BOX_NOT_INIT
        };
    }

    // Get box size
    if(width != SBX_POINTER_UNSET) {
        *width  = box->width;
    }
    if(height != SBX_POINTER_UNSET) {
        *height = box->height;
    }

    // Return success
    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_BOX_GET_SIZE_SUCCESSFUL
    };
}

SBX_report_t SBXBoxSetSize(SBX_box_t* box, SBX_box_dimensions_t width, SBX_box_dimensions_t height) {
    // Check if required arguments are provided
    if((box == SBX_POINTER_UNSET) || (width == SBX_DIMENSION_UNSET) || (height == SBX_DIMENSION_UNSET)) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }
    // Check for box initialized
    if(!box->initialized) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_BOX_ERROR_NOT_INIT,
            .reportMessage = SBX_REPORT_STRING_BOX_NOT_INIT
        };
    }

    // Resize plock array
    SBX_report_t report = SBXPlockArraySetSize(&box->plockArray, width * height);

    // Check if plock array recreation failed
    if(report.errorFlags) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_BOX_ERROR_PLOCKS_INIT_FAILED,
            .reportMessage = SBX_REPORT_STRING_BOX_PLOCKS_FAILED
        };
    }

    // Create/Resize plock array
    report = SBXPlockIDMatrixSetSize(&box->plockIDMatrix, width, height);

    // Check if plock ID matrix creation failed
    if(report.errorFlags) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_BOX_ERROR_PLOCK_IDS_INIT_FAILED,
            .reportMessage = SBX_REPORT_STRING_BOX_PLOCK_IDS_FAILED
        };
    }

    // Set box parameters
    box->width  = width;
    box->height = height;

    // Return success
    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_BOX_SET_SIZE_SUCCESSFUL
    };
}
