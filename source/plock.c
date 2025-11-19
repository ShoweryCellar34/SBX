// Project headers
#include <SBX/plock.h>
#include <SBX/strings.h>

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

    // Allocate memory for the internal array in the SBXPlockArray structure
    if(plockArray->plocks) {
        plockArray->plocks = realloc(plockArray->plocks, sizeof(SBX_plock_t) * count);
    } else {
        plockArray->plocks = malloc(sizeof(SBX_plock_t) * count);
    }

    // Check for a memory allocation error
    if(!plockArray->plocks) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MEMORY_FAILURE,
            .reportMessage = SBX_REPORT_STRING_COMMON_MEMORY_FAILURE
        };
    }

    // Set SBXPlockArray unset internal array members to values unset
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
        plockIDMatrix->height = 0;

        return (SBX_report_t){
            .errorFlags    = 0,
            .reportMessage = SBX_REPORT_STRING_PLOCK_ID_MATRIX_SET_SIZE_SUCCESSFUL
        };
    }

    // Allocate memory for the internal array in the SBXPlockArray structure
    if(plockIDMatrix->plockIDs) {
        plockIDMatrix = realloc(plockIDMatrix->plockIDs, sizeof(SBX_plock_t) * width * height);
    } else {
        plockIDMatrix = malloc(sizeof(SBX_plock_t) * width * height);
    }

    // Check for a memory allocation error
    if(!plockIDMatrix->plockIDs) {
        // Return error
        return (SBX_report_t){
            .errorFlags    = SBX_COMMON_ERROR_MEMORY_FAILURE,
            .reportMessage = SBX_REPORT_STRING_COMMON_MEMORY_FAILURE
        };
    }

    // Set SBXPlockArray unset internal array members to values unset
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
