#ifndef SBX_PLOCK_H
#define SBX_PLOCK_H

// Project headers
#include <SBX/types.h>
#include <SBX/report.h>

/// @brief Structure used by SBXPlock functions to store pixel settings, types, and more to represent a pixel type
struct SBXPlock {
    /// @brief The color of the plock
    SBX_color_t color;

    /// @brief The secondary color for the plock, if set when the plock is queried for color it will provide a random color in the range of color and color2
    SBX_color_t color2;
};

/// @brief Allocates memory for a SBXPlock object and then sets values according to the provided settings, on error the address pointed to by the SBX_plock_t** will be set to NULL
/// @param plock  A pointer to a SBX_plock_t pointer to set to the allocated SBXPlock objects memory, cannot be SBX_POINTER_UNSET
/// @param color  The desired color for the plock, cannot be SBX_COLOR_UNSET
/// @param color2 The desired secondary color for the plock, if set when the plock is queried for color it will provide a random color in the range of color and color2, can be SBX_COLOR_UNSET
/// @return A SBXReport struct that reports the return state of the creation function, this can be an error, or a success.
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT, SBX_COMMON_ERROR_MEMORY_FAILURE
SBX_report_t SBXPlockCreate(SBX_plock_t** plock, SBX_color_t color, SBX_color_t color2);

/// @brief Deallocates a SBXPlock objects memory
/// @param plock A SBX_plock_t pointer to the desired SBXPlock to be destroyed, cannot be SBX_POINTER_UNSET
/// @return A SBXReport struct that reports the return state of the destruction function, this can be an error, or a success.
///         Possible errors include: SBX_COMMON_ERROR_MISSING_ARGUMENT
SBX_report_t SBXPlockDestroy(SBX_plock_t* plock);

#endif // SBX_PLOCK_H
