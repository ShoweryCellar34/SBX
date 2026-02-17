#ifndef SBX_BOX_H
#define SBX_BOX_H

// Project headers
#include <SBX/plock.h>
#include <SBX/types.h>
#include <SBX/report.h>

/// @brief Structure used by SBXBox* functions to store dimension and plock data required to represent a box
struct SBXBox {
    /// @brief SBX_bool_t object used to keep initialization state
    SBX_bool_t            initialized;

    /// @brief SBX_box_dimensions_t object used to keep box width
    SBX_box_dimensions_t  width;
    /// @brief SBX_box_dimensions_t object used to keep box height
    SBX_box_dimensions_t  height;

    /// @brief SBX_plock_array_t object used to store all the plocks associated with 
    SBX_plock_array_t     plockArray;
    SBX_plock_id_matrix_t plockIDMatrix;
};


/// @brief Allocates memory for a SBXBox object and then sets values to a deinitialized state.
/// @param box A pointer to a SBX_box_t pointer that will be set to the new object, cannot be SBX_POINTER_UNSET
/// @return A SBXReport struct that reports the return state of the creation function, this can be an error, or a success.
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT, SBX_COMMON_ERROR_MEMORY_FAILURE
SBX_report_t SBXBoxCreate(SBX_box_t** box);

/// @brief Deallocates a SBXBox objects memory after check for deinitialization
/// @param box A SBX_box_t pointer to the desired SBXBox to be destroyed, cannot be SBX_POINTER_UNSET
/// @return A SBXReport struct that reports the return state of the destruction function, this can be an error, or a success.
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT, SBX_BOX_ERROR_NOT_DEINIT
SBX_report_t SBXBoxDestroy(SBX_box_t* box);

/// @brief Creates the plocks, sets initialization state, width, and height parameters.
/// @param box SBXBox struct used to retrieve, store, and check initialization related box data, cannot be SBX_POINTER_UNSET
/// @param width  The desired width for the box, cannot be SBX_DIMENSION_UNSET
/// @param height The desired height for the box, cannot be SBX_DIMENSION_UNSET
/// @return A SBXReport struct that reports the return state of the initialization function, this can be an error, or a success.
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT, SBX_BOX_ERROR_ALREADY_INIT,
///                                  SBX_BOX_ERROR_HANDLE_INIT_FAILED, SBX_COMMON_ERROR_MEMORY_FAILURE
SBX_report_t SBXBoxInit(SBX_box_t* box,
                        SBX_box_dimensions_t width,
                        SBX_box_dimensions_t height);


/// @brief Destroys the plocks, sets initialization state, width, and height parameters to unset values.
/// @param box SBXBox struct used to retrieve, store, and check deinitialization related box data, cannot be SBX_POINTER_UNSET
/// @return A SBXReport struct that reports the return state of the deinitialization function, this can be an error, or a success
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT, SBX_BOX_ERROR_NOT_INIT
SBX_report_t SBXBoxDeinit(SBX_box_t* box);

/// @brief Gets the width and height of the supplied box and stores them in the supplied pointers, width and/or height can be SBX_POINTER_UNSET.
/// @param box SBXBox struct used to retrieve, store, and check size query related box data, cannot be SBX_POINTER_UNSET
/// @param width  A pointer to a SBX_box_dimensions_t variable to store box width in, can be SBX_POINTER_UNSET
/// @param height A pointer to a SBX_box_dimensions_t variable to store box height in, can be SBX_POINTER_UNSET
/// @return A SBXReport struct that reports the return state of the size query function, this can be an error, or a success
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT, SBX_BOX_ERROR_NOT_INIT,
///                                  SBX_BOX_ERROR_GET_SIZE_FAILED
SBX_report_t SBXBoxGetSize(SBX_box_t* box, SBX_box_dimensions_t* width, SBX_box_dimensions_t* height);

/// @brief Sets the width and height of the supplied box, width or height cannot be SBX_DIMENSION_UNSET
/// @param box SBXBox struct used to retrieve, store, and check size setting related box data, cannot be SBX_POINTER_UNSET
/// @param width  The desired width for the box, cannot be SBX_DIMENSION_UNSET
/// @param height The desired height for the box, cannot be SBX_DIMENSION_UNSET
/// @return A SBXReport struct that reports the return state of the size setting function, this can be an error, or a success
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT, SBX_BOX_ERROR_NOT_INIT,
///                                  SBX_BOX_ERROR_PLOCKS_INIT_FAILED, SBX_BOX_ERROR_PLOCK_IDS_INIT_FAILED
SBX_report_t SBXBoxSetSize(SBX_box_t* box, SBX_box_dimensions_t width, SBX_box_dimensions_t height);

#endif // SBX_BOX_H
