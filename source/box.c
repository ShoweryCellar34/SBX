// Project headers
#include <SBX/box.h>
#include <SBX/strings.h>

// LibC headers
#include <stdlib.h>
#include <string.h>

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
    (*box)->width       = SBX_DIMENSION_UNSET;
    (*box)->height      = SBX_DIMENSION_UNSET;
    (*box)->plocks      = SBX_POINTER_UNSET;

    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_CREATION_SUCCESSFUL
    };
}

// Box destruction function
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

SBX_report_t SBXBoxInit(SBX_box_t* box,
                        SBX_box_dimensions_t width,
                        SBX_box_dimensions_t height)
{
    // Check if required arguments are provided
    if(!(box && width && height)) {
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

    // Set box parameters
    box->width  = width;
    box->height = height;

    // Create an array of plock ids to store all plocks
    box->plocks = malloc(box->width * box->height * sizeof(SBX_plock_id_t));

    // Check if plock id array creation failed
    if(!box->plocks) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MEMORY_FAILURE,
            .reportMessage = SBX_REPORT_STRING_COMMON_MEMORY_FAILURE
        };
    }

    // Set init state to init
    box->initialized = true;

    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_BOX_INIT_SUCCESSFUL
    };
}

SBX_report_t SBXBoxDeinit(SBX_box_t* box) {
    // Check if required arguments are provided
    if(!box) {
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

    // Check if plocks id array exists, then destroy it and set pointer to NULL
    if(box->plocks) {
        free(box->plocks);
        box->plocks = NULL;
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
    if(!box) {
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
    *width  = box->width;
    *height = box->height;

    // Return success
    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_BOX_GET_SIZE_SUCCESSFUL
    };
}

SBX_report_t SBXBoxSetSize(SBX_box_t* box, SBX_box_dimensions_t width, SBX_box_dimensions_t height) {
    // Check if required arguments are provided
    if(!(box && width && height)) {
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

    // Allocate temp memory for new box
    SBX_plock_id_t* temp = malloc(width * height * sizeof(SBX_plock_id_t));
    if(!temp) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MEMORY_FAILURE,
            .reportMessage = SBX_REPORT_STRING_COMMON_MEMORY_FAILURE
        };
    }

    // FIX THIS, THERE ARE SO MANY ISSUES

    // Copy rows into new buffer
    for(SBX_box_dimensions_t i = 0; i < height; i++) {
        memcpy(&temp[i * width], &box->plocks[i * box->width], width * sizeof(SBX_plock_id_t));
    }

    // Free the old buffer and set the pointer to the new buffer
    free(box->plocks);
    box->plocks = temp;

    // Set box parameters
    box->width  = width;
    box->height = height;

    // Return success
    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_BOX_SET_SIZE_SUCCESSFUL
    };
}
