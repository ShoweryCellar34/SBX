#ifndef SBX_BOX_H
#define SBX_BOX_H

// Project headers
#include <SBX/types.h>
#include <SBX/report.h>

/// @brief Structure used by SBXBox fuctions to store pixels, states, and more data to represent a sandbox environment
struct SBXBox {
    // State keeping
    SBX_bool_t           initialized;

    // Sandbox parameters
    SBX_box_dimensions_t width,
                         height;

    // Plocks
    SBX_plock_id_t*      plocks;
};

/// @brief Allocates memory for a SBXBox object and then sets values according to the provided settings, on error the address pointed to by the SBX_box_t** will be set to NULL
/// @param box A pointer to a SBX_box_t pointer to set to the allocated SBXBox objects memory, cannot be SBX_POINTER_UNSET
/// @return A SBXReport struct that reports the return state of the creation function, this can be an error, or a success.
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT, SBX_COMMON_ERROR_MEMORY_FAILURE
SBX_report_t SBXBoxCreate(SBX_box_t** box);

/// @brief Deallocates a SBXBox objects memory
/// @param box    A SBX_box_t pointer to the desired SBXBox to be destroyed, cannot be SBX_POINTER_UNSET
/// @param width  The desired width for the box, cannot be SBX_DIMENSION_UNSET
/// @param height The desired height for the box, cannot be SBX_DIMENSION_UNSET
/// @return A SBXReport struct that reports the return state of the destruction function, this can be an error, or a success.
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT
SBX_report_t SBXBoxDestroy(SBX_box_t* box);

SBX_report_t SBXBoxInit(SBX_box_t* box,
                        SBX_box_dimensions_t width,
                        SBX_box_dimensions_t height);

SBX_report_t SBXBoxDeinit(SBX_box_t* box);

SBX_report_t SBXBoxGetSize(SBX_box_t* box, SBX_box_dimensions_t* width, SBX_box_dimensions_t* height);

SBX_report_t SBXBoxSetSize(SBX_box_t* box, SBX_box_dimensions_t width, SBX_box_dimensions_t height);

#endif // SBX_BOX_H
