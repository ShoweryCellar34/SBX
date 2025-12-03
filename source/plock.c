// Project headers
#include <SBX/plock.h>
#include <SBX/strings.h>

// LibC headers
#include <string.h>

SBX_report_t SBXPlockArrayGetSize(SBX_plock_array_t* plockArray, SBX_plock_count_t* count) {
    // Check if required arguments are provided
    if(!plockArray) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }

    if(count) {
        *count = plockArray->count;
    }

    // Return success
    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_PLOCK_ARRAY_GET_SIZE_SUCCESSFUL
    };
}

SBX_report_t SBXPlockArraySetSize(SBX_plock_array_t* plockArray, SBX_plock_count_t count) {
    // Check if required arguments are provided
    if(!(plockArray)) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }

    // If count is 0 destroy the array
    if(!count && plockArray->plocks) {
        free(plockArray->plocks);
        plockArray->count = 0;

        return (SBX_report_t){
            .errorFlags    = 0,
            .reportMessage = SBX_REPORT_STRING_PLOCK_ARRAY_SET_SIZE_SUCCESSFUL
        };
    }

    // Allocate memory for the internal array in the SBXPlockArray structure, realloc will malloc if the plocks pointer is NULL
    plockArray->plocks = realloc(plockArray->plocks, sizeof(SBX_plock_t) * count);

    // Check for a memory allocation error
    if(!plockArray->plocks) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MEMORY_FAILURE,
            .reportMessage = SBX_REPORT_STRING_COMMON_MEMORY_FAILURE
        };
    }

    // Set SBXPlockArray new internal array members to values unset
    for(SBX_plock_count_t i = plockArray->count; i < count; i++) {
        plockArray->plocks[i].temperature = SBX_TEMPERATURE_UNSET;
        plockArray->plocks[i].type        = SBX_PLOCK_TYPE_ID_UNSET;
    }

    // Update the count variable in the SBXPlockArray
    plockArray->count = count;

    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_PLOCK_ARRAY_SET_SIZE_SUCCESSFUL
    };
}

SBX_report_t SBXPlockIDMatrixGetSize(SBX_plock_id_matrix_t* plockIDMatrix,
                                     SBX_plock_id_matrix_dimensions_t* width, SBX_plock_id_matrix_dimensions_t* height)
{
    // Check if required arguments are provided
    if(!plockIDMatrix) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }

    if(width) {
        *width = plockIDMatrix->width;
    }
    if(height) {
        *height = plockIDMatrix->height;
    }

    // Return success
    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_PLOCK_ID_MATRIX_GET_SIZE_SUCCESSFUL
    };
}

SBX_report_t SBXPlockIDMatrixSetSize(SBX_plock_id_matrix_t* plockIDMatrix,
                                     SBX_plock_id_matrix_dimensions_t width, SBX_plock_id_matrix_dimensions_t height)
{
    // Check if required arguments are provided
    if(!(plockIDMatrix)) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MISSING_ARGUMENT,
            .reportMessage = SBX_REPORT_STRING_COMMON_MISSING_ARGUMENT
        };
    }

    // If width or height is 0 destroy the matrix
    if(!(width || height) && plockIDMatrix->plockIDs) {
        free(plockIDMatrix->plockIDs);
        plockIDMatrix->width  = 0;
        plockIDMatrix->height = 0;

        return (SBX_report_t){
            .errorFlags    = 0,
            .reportMessage = SBX_REPORT_STRING_PLOCK_ID_MATRIX_SET_SIZE_SUCCESSFUL
        };
    }

    // Allocate memory for the internal array in the SBXPlockArray structure, realloc will malloc if the plock ID matrix pointer is NULL
    plockIDMatrix->plockIDs = realloc(plockIDMatrix->plockIDs, sizeof(SBX_plock_t) * width * height);

    // Check for a memory allocation error
    if(!plockIDMatrix->plockIDs) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MEMORY_FAILURE,
            .reportMessage = SBX_REPORT_STRING_COMMON_MEMORY_FAILURE
        };
    }

    // Set SBXPlockIDMatrix new internal array members to values unset
    for(SBX_plock_id_count_t i = plockIDMatrix->width * plockIDMatrix->height; i < (size_t)(width * height); i++) {
        plockIDMatrix->plockIDs[i] = SBX_PLOCK_ID_UNSET;
    }

    for(SBX_plock_id_matrix_dimensions_t y = plockIDMatrix->height - 1; y > 0; y--) {
        void* dest = &plockIDMatrix->plockIDs[y * width];
        void* src  = &plockIDMatrix->plockIDs[y * plockIDMatrix->width];
        memcpy(dest, src, plockIDMatrix->width * sizeof(SBX_plock_id_t));

        if(width > plockIDMatrix->width) {
            memset(&plockIDMatrix->plockIDs[y * plockIDMatrix->width], SBX_PLOCK_ID_UNSET, (width - plockIDMatrix->width) * sizeof(SBX_plock_id_t));
        }
    }

    // Update the width and height variables in the SBXPlockIDMatrix
    plockIDMatrix->width  = width;
    plockIDMatrix->height = height;

    return (SBX_report_t){
        .errorFlags    = 0,
        .reportMessage = SBX_REPORT_STRING_PLOCK_ID_MATRIX_SET_SIZE_SUCCESSFUL
    };
}
